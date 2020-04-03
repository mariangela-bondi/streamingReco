#!/bin/python

import fnmatch
import os
import SCons
import glob
import platform
import sys




################
# File handling
################s

def getSubdirs(abs_path_dir) :  
    lst = [ name for name in os.listdir(abs_path_dir) if os.path.isdir(os.path.join(abs_path_dir, name)) and name[0] != '.' ]
    lst.sort()
    return lst

def recursiveDirs(root) :
    """Return a list of all subdirectories of root, top down,
       including root, but without .svn and .<arch> directories"""
    return filter( (lambda a : (a.rfind( ".svn")==-1) and \
                               (a.rfind( ".Linux")==-1) and \
                               (a.rfind( ".SunOS")==-1) and \
                               (a.rfind( ".Darwin")==-1) and \
                               (a.rfind( ".vxworks")==-1)),  [ a[0] for a in os.walk(root)]  )



def unique(list) :
    """Remove duplicates from list"""
    return dict.fromkeys(list).keys()



def scanFiles(dir, accept=["*.cpp"], reject=[]) :
    """Return a list of selected files from a directory & its subdirectories"""
    sources = []
    paths = recursiveDirs(dir)
    for path in paths :
        for pattern in accept :
            sources+=glob.glob(path+"/"+pattern)
    for pattern in reject :
        sources = filter( (lambda a : a.rfind(pattern)==-1 ),  sources )
    return unique(sources)


def subdirsContaining(root, patterns):
    """Return a list of subdirectories containing files of the given pattern"""
    dirs = unique(map(os.path.dirname, scanFiles(root, patterns)))
    dirs.sort()
    return dirs
    
class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    RED = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


def AddROOTdict(env,reldir,absdir):
    rootsys = os.getenv('ROOTSYS')
    rootclingpath = "%s/bin/rootcling" % (rootsys)
    if ("RECO_HOME" not in os.environ):
        print bcolors.RED+" RECO_HOME env. var is not defined!! Can't work with ROOT dictionaries "+bcolors.ENDC
        print bcolors.RED+" PLEASE DEFINE IT! "+bcolors.ENDC
        return -1
    dictdir = os.getenv('RECO_HOME')+"/lib"

    if env['SHOWBUILD']==0:
        rootclingactionNoLinkDef = SCons.Script.Action("%s -f $TARGET -c -p -I%s $SOURCE ; mv `echo $TARGET | awk '{print substr($0,0,length($0)-3) \"_rdict.pcm\"}'` %s" % (rootclingpath," -I".join(env['CPPPATH']),dictdir), 'ROOTCLING  [$SOURCE]')
        rootclingactionLinkDef = SCons.Script.Action("%s -f $TARGET -c -p -I%s $SOURCES ; mv `echo $TARGET | awk '{print substr($0,0,length($0)-3) \"_rdict.pcm\"}'` %s" % (rootclingpath," -I".join(env['CPPPATH']),dictdir), 'ROOTCLING  [$SOURCES]')
    else:     	
        rootclingactionNoLinkDef = SCons.Script.Action("%s -f $TARGET -c -p -I%s $SOURCE ; mv `echo $TARGET | awk '{print substr($0,0,length($0)-3) \"_rdict.pcm\"}'` %s" % (rootclingpath," -I".join(env['CPPPATH']),dictdir))
        rootclingactionLinkDef = SCons.Script.Action("%s -f $TARGET -c -p -I%s $SOURCES ; mv `echo $TARGET | awk '{print substr($0,0,length($0)-3) \"_rdict.pcm\"}'` %s" % (rootclingpath," -I".join(env['CPPPATH']),dictdir))
    
    if os.path.exists(rootclingpath) :
       # bldNoLinkDef = SCons.Script.Builder(action = rootclingactionNoLinkDef)
        bldNoLinkDef = SCons.Script.Builder(action = rootclingactionNoLinkDef, suffix='_Dict.cc', src_suffix='.h')
        bldLinkDef = SCons.Script.Builder(action = rootclingactionLinkDef)
    else:
        print 'Rootcling does not exists. Unable to create ROOT dictionaries if any encountered.'
        return 
  


    env.Append(BUILDERS = {'ROOTDictNoLinkDef' : bldNoLinkDef})
    env.Append(BUILDERS = {'ROOTDictLinkDef' : bldLinkDef})

	# Generate ROOT dictionary file targets for each header
	# containing "ClassDef"
	#
	# n.b. It seems if scons is run when the build directory doesn't exist,
	# then the cwd is set to the source directory. Otherwise, it is the
	# build directory. Since the headers will only exist in the source
	# directory, we must temporarily cd into that to look for headers that
	# we wish to generate dictionaries for. (This took a long time to figure
	# out!)
    curpath = os.getcwd()
    srcpath = absdir
    if(int(env['SHOWBUILD'])>=1):
		print "---- Scanning for headers to generate ROOT dictionaries in: %s" % (srcpath)	
    os.chdir(srcpath)
	
		 
    retVal="";
    for f in glob.glob('*.[h|hh|hpp]'):
        if 'ClassDef' in open(f).read():  
            filename, file_extension = os.path.splitext(f)          
            if(int(env['SHOWBUILD'])>=1):
                print "  -----> ROOT dictionary for %s" % f
            if os.path.isfile(filename+"_LinkDef.h"):     
                retVal=env.ROOTDictLinkDef(reldir+"/"+filename+"_Dict.cc",[reldir+"/"+f,reldir+"/"+filename+"_LinkDef.h"])
                if(int(env['SHOWBUILD'])>=1):
                    print "  -----> Using "+filename+"_LinkDef.h for dictionary"
            else:
                retVal=0
                if(int(env['SHOWBUILD'])>=1):
                    print "  -----> No LinkDef provided, will proceed without it"
                retVal=env.ROOTDictNoLinkDef(reldir+"/"+filename+"_Dict.cc",[reldir+"/"+f])
    os.chdir(curpath)            
    
def check_if_dir_exist(system) :
    OSENV = os.environ
    SYSTEM = OSENV[system]
    if os.path.exists(SYSTEM) == False :
        print "  !! Error: " , SYSTEM , " does not exist. Maybe ", system, " is not installed?"
        sys.exit(1)
       
    

    
    
def loadoptions(env) :
    # EHsc and MD only for win32 envs
    if  env['PLATFORM'] == 'win32':
        env.Append(CXXFLAGS='-MD')     # for multithread, dynamic link. Causes compiler to place msvcrt in object file
        env.Append(CXXFLAGS='-EHsc')     
        env.Append(ENV = {'PATH': os.environ['PATH']})
        env.Append(ENV = {'INCLUDE': os.environ['INCLUDE']})
        env.AppendUnique(LIBPATH = [os.environ['MSLIBS']])
        env.AppendUnique(LIBPATH = [os.environ['SDKLIBS']])

    if env['PLATFORM'] == 'posix':
        env.Append(ENV = {'PATH': os.environ['PATH']})
        env.Append(CXXFLAGS = '-fexceptions')
        env.Append(CXXFLAGS = '-fstack-protector')
        env.Append(CXXFLAGS = '-Wall')
        env.Append(LIBS = 'dl')
        if env['LIBRARY'] == 'shared':
            env.Append(CPPFLAGS = ' -fPIC')
    
    
    if env['PLATFORM'] == 'darwin':
        env.Append(CXXFLAGS = '-fexceptions')
        env.Append(CXXFLAGS = '-fstack-protector')
        env.Append(CXXFLAGS = '-Wall')
        env.Append(CCFLAGS  = '-Wno-unused-private-field')

            
    if env['SHOWBUILD'] != "1":
        env['PRINT_CMD_LINE_FUNC'] = print_cmd_line
        env['CXXCOM']   = "${TEMPFILE('%s')}" % env['CXXCOM'] 
    
    if env['SHOWENV'] == "1":
        print "  "
        print "Compiler: ", env['CC']
        print "Linker: ",   env.subst('$LINK')
        print "Platform: ", env['PLATFORM']
        print "  "
    
    if env['OPT'] == "1":
        if env['PLATFORM'] == 'posix':
            env.Append(CXXFLAGS = '-O2')
            print "Compiling with -O2 optimization."
        if env['PLATFORM'] == 'darwin':
            env.Append(CXXFLAGS = '-O2')
            print "Compiling with -O2 optimization."
        if env['PLATFORM'] == 'win32':
            env.Append(CXXFLAGS = '/O2 /Gs')
            print "Compiling with /O2 /Gs optimization."
    
#    if env['XERCES3'] == "1":
#        OSENV  = os.environ
#        XERCESCROOT = OSENV['XERCESCROOT']
#        env.Append(CXXFLAGS='-DHAVE_XERCES=1 -DXERCES3=1 -I' + XERCESCROOT + '/include')
#

    if env['DEBUG'] == "1":
        if env['PLATFORM'] == 'posix':
            env.Append(CXXFLAGS = '-g')
            print "Compiling with -g debug."
        if env['PLATFORM'] == 'darwin':
            env.Append(CXXFLAGS = '-g')
            print "Compiling with -g debug."
        if env['PLATFORM'] == 'win32':
            env.Append(CXXFLAGS = '/DEBUG')    
            print "Compiling with -/DEBUG debug."
    
    if env['ARCHI'] == 'x86':
        env.Append(CXXFLAGS  = '-m32 ')
        env.Append(CPPFLAGS  = '-m32 ')
        env.Append(LINKFLAGS = '-m32 ')
        

    if env['PROFILE'] == "1":
        if env['PLATFORM'] == 'posix':
            env.Append(CXXFLAGS = '-pg')
            env.Append(LINKFLAGS = '-pg')
            print "Compiling with -pg profiling."
    

    # using c++11 starting from ceInstall 1.4 version
    env.Append(CXXFLAGS = ' -std=c++14 ')


def cmloptions(opts) :
    opts.Add('ARCHI',     'Set to x86 to force 32 bit environment', 0)
    opts.Add('SHOWENV',   'Set to 1 to show environment used', 0)
    opts.Add('SHOWBUILD', 'Set to 1 to show build commands executed', 0)
    opts.Add('OPT',       'Set to 1 to optimize code', 0)
    opts.Add('DEBUG',     'Set to 1 to compile in debug mode', 0)
    opts.Add('PROFILE',   'Set to 1 to compile in profiling mode', 0)
    opts.Add('CUDA_EMU',  'Set to 1 to compile in video-card emulation mode', 0)
    opts.Add('XERCES3',   'Set to 1 to compile with option -DXERCES3=1', 0)
    opts.Add('LIBRARY',   'Set at run time to compile shared or static library', 0)
        
    
    
    
    
    
    
##################################
# ROOTSPY Macro build function
##################################
def RootSpyMacroCodeGen(target, source, env):
    # Used by AddROOTSpyMacros below. See comments there for details
    t = '%s' % target[0]
    s = '%s' % source[0]

    base = os.path.basename(s[:-2])
    class_name = '%s_rootspy_class' % base
    fin  = open(s)
    fout = open(t, 'w')

    fout.write('#include <dlfcn.h>\n')
    fout.write('#include <iostream>\n')
    fout.write('#include <string>\n')
    fout.write('using namespace std;\n')
    fout.write('static string macro_data=""\n')
    for line in fin:
        line = line.replace('"', '\\\"')
        fout.write('"%s\\n"\n' % line[:-1])
    fout.write(';\n')
    fout.write('class %s{\n' % class_name)
    fout.write('   public:\n')
    fout.write('   typedef void rmfcn(string, string, string);\n')
    fout.write('   %s(){\n' % class_name)
    fout.write('      rmfcn* fcn = (rmfcn*)dlsym(RTLD_DEFAULT, "REGISTER_ROOTSPY_MACRO");\n')
    fout.write('      if(fcn) (*fcn)("%s","/", macro_data);\n' % base)
    fout.write('   }\n')
    fout.write('};\n')
    fout.write('static %s tmp;' % class_name)

    fin.close()
    fout.close()

##################################
# ROOTSPY Macros
##################################
def AddROOTSpyMacros(env,reldir,absdir):
    #
    # This is used to generate a C++ file for each ROOT macro file
    # where the complete macro file is embedded as a string. A small
    # piece of code is also inserted that allows the string to be
    # automatically registered with the RootSpy system, if present.
    # (Basically, if the rootspy plugin is attached.) ROOT macros
    # are identified by a file ending with a ".C" suffix. The macro
    # name will be the basename of the file.
    #

    # Create Builder that can convert .C file into _rootspy_macro.cc file
    if env['SHOWBUILD']==0:
        rootmacroaction = SCons.Script.Action(RootSpyMacroCodeGen, 'ROOTSPY    [$SOURCE]')
    else:
        rootmacroaction = SCons.Script.Action(RootSpyMacroCodeGen)
    bld = SCons.Script.Builder(action = rootmacroaction, suffix='_rootspy_macro.cc', src_suffix='.C')
    env.Append(BUILDERS = {'ROOTSpyMacro' : bld})

    # Find all macro files and schedule them to be converted using the above builder
    curpath = os.getcwd()
    srcpath = absdir
    if(int(env['SHOWBUILD'])>=1):
        print "---- Looking for ROOT macro files (*.C) in: %s" % srcpath
    os.chdir(srcpath)
    for f in glob.glob('*.C'):
        env.AppendUnique(ALL_SOURCES = env.ROOTSpyMacro(reldir+"/"+f))
        if(int(env['SHOWBUILD'])>=1) : print "       ROOTSpy Macro for %s" % f

    os.chdir(curpath)

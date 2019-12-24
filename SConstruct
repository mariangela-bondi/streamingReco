from utils import *
#from init_env import init_environment
import platform
import SCons
import os
from SCons.Environment import *
from SCons.Variables import *
from SCons.Script import *


mc_enable = ARGUMENTS.get('MC',0)
if int(mc_enable):
    print "MC support is enabled - not supported for now"
    exit
#    env = init_environment("qt5 root geant4 clhep evio xercesc ccdb mlibrary clas12")
#   env.AppendUnique(CPPDEFINES='MC_SUPPORT_ENABLE')
else:
    print bcolors.WARNING," no MC support",bcolors.ENDC
    #Need a manual setting
    opts = Variables()
    cmloptions(opts)
    env = Environment(tools=['default'], options = opts, ENV = os.environ)
#    from loadccdb import loadccdb
#    loadccdb(env)
#    from loadclhep import loadclhep
#    loadclhep(env)
  
if os.environ.get('JANA_HOME') is not None:
    env['JANA_HOME'] = os.environ.get('JANA_HOME')
    env.Append(CPPPATH=["$JANA_HOME/src/lib"])
else:
    print("ERROR, JANA_HOME NOT DEFINED")
    exit
 
if os.environ.get('BOOSTROOT') is not None:
    env['BOOSTROOT'] = os.environ.get('BOOSTROOT')
    env.Append(CPPPATH=["$BOOSTROOT/include"])
else:
    print("ERROR, BOOSTROOT NOT DEFINED")
    exit    

debug = ARGUMENTS.get('debug', 0)
if int(debug):
   print "DEBUG IS ON"
   env.Append(CCFLAGS = '-g')

#A.C. probably do this better
if (platform.system()=="Darwin"):
	print "We are on MAC"
	env.AppendUnique(LINKFLAGS='-flat_namespace')
	env.AppendUnique(SHLINKFLAGS=['-undefined', 'suppress'])
 
env.Append(CPPPATH=Dir('#/src/libraries').srcnode().abspath)
env.Append(CPPPATH=Dir('#/src/plugins').srcnode().abspath)
env.Append(CPPPATH=Dir('#/.').srcnode().abspath)
env.Append(LIBPATH = ['#/lib'])

env.Replace(RPATH=Dir('#/lib').srcnode().abspath)

#This drove me crazy! jlab_software jana was including this, and we need it for sophisticated rootspy features..
env.Append(LINKFLAGS = '-rdynamic')

Export('env debug mc_enable')


lib=SConscript('src/libraries/SConstruct')
#progs=SConscript('src/programs/SConstruct')
#plugins=SConscript('src/plugins/SConstruct')
#users=SConscript('src/users/SConstruct')











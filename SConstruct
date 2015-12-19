import os
if ARGUMENTS.get('debug', 0):
    cppflags = ['-g', '-Wall']
    variant = 'Debug'
else:
    cppflags = ['-O2']
    variant = 'Release'
cppflags += ['-fPIC','-std=c++1y']

baseEnv = Environment(LIBPATH=[],
                      CPPFLAGS = cppflags)

# Clone Qt environment
qtEnv = baseEnv.Clone()
qtdir = os.environ.get('QTDIR','/usr')
qtEnv['ENV']['PKG_CONFIG_PATH'] = os.path.join(qtdir, 'lib/pkgconfig')
qtEnv.Append(CPPFLAGS=['-fPIC'],
             QT5DIR = qtdir)
qtEnv.Tool('qt5')
Export('baseEnv qtEnv')

SConscript('TreeVisibility/SConscript')



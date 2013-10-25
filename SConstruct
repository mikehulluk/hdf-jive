


env = Environment(
    CPPFLAGS = "-Wall -Werror -O3 -std=c++0x ",
    LIBS = ['hdf5', 'hdf5_hl']   
    )
env.Append(CPPPATH = ['include/'])


hdflib = env.SharedLibrary('lib/libhdfjive.so', ['src/hdfjive.cpp', 'src/hdfjive-neuro.cpp'] )

env.Program('test/test_hdfjive-neuro.x', ['test/test_hdfjive-neuro.cpp', hdflib])

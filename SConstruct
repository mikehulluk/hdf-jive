


env = Environment(
    CPPFLAGS = "-Wall -Werror -O3 -std=c++0x ",    
    )
env.Append(CPPPATH = ['include/'])


env.SharedLibrary('lib/libhdfjive.so', ['src/hdfjive.cpp', 'src/hdfjive-neuro.cpp'] )


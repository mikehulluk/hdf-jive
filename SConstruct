


env = Environment(
    CPPFLAGS = "-Wall -Werror -O3 -std=c++0x -g -Wfatal-errors",
    LIBS = ['hdf5', 'hdf5_hl']   
    )
env.Append(CPPPATH = ['include/'])



# Build the library
hdflib = env.SharedLibrary('lib/libhdfjive.so', ['src/hdfjive.cpp', 'src/hdfjive-neuro.cpp', 'src/hdfjive-events.cpp'] )



# Test libraries
test_neuron_x = env.Program('test/test_hdfjive-neuro.x', ['test/test_hdfjive-neuro.cpp', hdflib])


# Run the test program
output_files = ["MyResults1.hdf", "MyResults2.hdf", "MyResults3.hdf"]
env.Command(output_files, test_neuron_x, './%s'%str(test_neuron_x[0])  )




# vim: set ft=python:

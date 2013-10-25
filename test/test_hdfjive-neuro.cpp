
#include "hdfjive-neuro.h"

#include <boost/assign/list_of.hpp>
#include <vector>
#include <list>
#include <array>
using std::list;
using std::vector;
using std::array;
using boost::assign::list_of;


void test_pointers()
{
    double time_data[] = { 2.4, 5.6, 9.6, 14.3};
    float voltage_data[] = { 4.2, 6.3, 6.7, 13.4};
    int int_data[] = { 4,3,5,6 };
    
    SimulationResultsPtr output = SimulationResultsFile("MyResults1.hdf").Simulation("Sim1");
    SharedTimeBufferPtr times = output->write_shared_time_buffer(4, time_data);

    // Store some traces:
    for(int i=0;i<100;i++)
    {
        output->write_trace("population-dINs-RHS", i, "V", times, voltage_data);
        output->write_trace("population-dINs-RHS", i, "int_data", times, int_data);
    }
}


void test_std()
{
    vector<double> time_data = list_of<double>(2.4)(5.6)(9.6)(14.3);
    list<float>  voltage_data = list_of<float>(4.2)(6.3)(6.7)(13.4);
    vector<int>  int_data = list_of<int>(4)(3)(5)(6);
    
    SimulationResultsPtr output = SimulationResultsFile("MyResults2.hdf").Simulation("Sim1");
    SharedTimeBufferPtr times = output->write_shared_time_buffer(time_data.begin(), time_data.end());

    // Store some traces:
    for(int i=0;i<100;i++)
    {
        output->write_trace("population-dINs-RHS", i, "V", times, voltage_data.begin(), voltage_data.end());
        output->write_trace("population-dINs-RHS", i, "int_data", times, int_data.begin(), int_data.end());
    }
}





int main(int argc, char* argv[])
{
    test_pointers();
    test_std();
}

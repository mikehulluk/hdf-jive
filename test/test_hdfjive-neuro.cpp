
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


void test_stl()
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







/**
template<typename EVENTTYPE>
class EventBuffer
{
    EventBuffer();
    list<EVENTTYPE> _events;
    
public:
    void add_event(const EVENTTYPE&);

};

template<typename DATATYPE, int NPARAMS>
class EventType
{
    size_t event_index;
    DATATYPE time;
    std::array<DATATYPE, NPARAMS> parameters;

public:

    // Constructor
    EventType(size_t event_index, DATATYPE time);
    EventType(size_t event_index, DATATYPE time, DATATYPE* pParams);
    EventType(size_t event_index, DATATYPE time, DATATYPE p0);
    EventType(size_t event_index, DATATYPE time, DATATYPE p0, DATATYPE p1);
    EventType(size_t event_index, DATATYPE time, DATATYPE p0, DATATYPE p1, DATATYPE p2);
    EventType(size_t event_index, DATATYPE time, DATATYPE p0, DATATYPE p1, DATATYPE p2, DATATYPE p3);
};
**/





void test_events()
{
    typedef EventType<float, 0> MyEventType0;
    typedef EventType<double,1> MyEventType1;
    typedef EventType<float, 2> MyEventType2;

    vector<MyEventType0> evts_0_vec;
    list<MyEventType0> evts_0_list;
    //buffer<MyEventType0> evts_0_buff;


    // Create some events (0-param):
    MyEventType0 evt0_a(-1, 0.2);
    MyEventType0 evt0_b(-1, 0.3);
    MyEventType0 evt0_c(-1, 0.7);

    // Create some events (1-param):
    MyEventType1 evt1_a(-1, 0.2, 45);
    MyEventType1 evt1_b(-1, 0.3, 46);
    MyEventType1 evt1_c(-1, 0.7, 47);

    // Create some events (2-param):
    MyEventType2 evt2_a(-1, 0.2, 45, 56);
    MyEventType2 evt2_b(-1, 0.3, 46, 23);
    MyEventType2 evt2_c(-1, 0.7, 47, 90);


    // Save the events:
    evts_0_vec.push_back(evt0_a); evts_0_vec.push_back(evt0_b); evts_0_vec.push_back(evt0_c);
    evts_0_list.push_back(evt0_a); evts_0_list.push_back(evt0_b); evts_0_list.push_back(evt0_c);
    

    
    SimulationResultsPtr output = SimulationResultsFile("MyResults2.hdf").Simulation("Sim1");

    
    output->write_outputeventsNEW("population-dINs-RHS", 0, "evts_0_vec", evts_0_vec.begin(), evts_0_vec.end() );
    output->write_outputeventsNEW("population-dINs-RHS", 0, "evts_0_list", evts_0_list.begin(), evts_0_list.end() );




//    void write_outputeventsNEW( const std::string& populationname, int index, const std::string& record_name, const EventBuffer<EVENTTYPE>& , const TagList& tags );
}





int main(int argc, char* argv[])
{
    test_pointers();
    test_stl();
    test_events();
    
}

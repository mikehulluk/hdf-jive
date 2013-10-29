
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







// There are different ways for storing and writing events:

// Method: 1 - Passing array pointers to the times (no parameters):
void test_output_events_1()
{
    // i. by pointers:
    int pTimes0[] =  {2, 4, 6, 8, 10};
    long pTimes1[] =  {3, 4, 5, 6, 7};
    float pTimes2[] =  {2.3, 6.9, 4.7, 9.7, 34.5};
    double pTimes3[] =  {2.3, 6.9, 4.7, 9.7, 34.5};

    // ii. by stl containers:
    vector<int>  pTimes0STL(pTimes0, pTimes0+5);
    list<long>   pTimes1STL(pTimes1, pTimes1+5);
    vector<float>pTimes2STL(pTimes2, pTimes2+5);
    list<double> pTimes3STL(pTimes3, pTimes3+5);

    SimulationResultsPtr output = SimulationResultsFile("MyResults3.hdf").Simulation("Sim1");

    output->write_outputevents_onlytimes("population-dINs-RHS", 0, "out_evts_0_vec", 5, pTimes0 );
    output->write_outputevents_onlytimes("population-dINs-RHS", 0, "out_evts_1_ptr", 5, pTimes1 );
    output->write_outputevents_onlytimes("population-dINs-RHS", 0, "out_evts_2_ptr", 5, pTimes2 );
    output->write_outputevents_onlytimes("population-dINs-RHS", 0, "out_evts_3_ptr", 5, pTimes3 );

    output->write_outputevents_onlytimes("population-dINs-RHS", 0, "out_evts_0_stl", pTimes0STL.begin(), pTimes0STL.end() );
    output->write_outputevents_onlytimes("population-dINs-RHS", 0, "out_evts_1_stl", pTimes1STL.begin(), pTimes1STL.end() );
    output->write_outputevents_onlytimes("population-dINs-RHS", 0, "out_evts_2_stl", pTimes2STL.begin(), pTimes2STL.end() );
    output->write_outputevents_onlytimes("population-dINs-RHS", 0, "out_evts_3_stl", pTimes3STL.begin(), pTimes3STL.end() );
}



// Method: 2 - Creating 'Event' objects:
void test_output_events_2()
{
    typedef EventType<float, 0> MyEventType0;
    typedef EventType<double,1> MyEventType1;
    typedef EventType<float, 2> MyEventType2;

    vector<MyEventType0> evts_0_vec;
    list<MyEventType0> evts_0_list;
    vector<MyEventType1> evts_1_vec;
    list<MyEventType1> evts_1_list;
    vector<MyEventType2> evts_2_vec;
    list<MyEventType2> evts_2_list;

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


    // Save the events
    evts_0_vec.push_back(evt0_a); evts_0_vec.push_back(evt0_b); evts_0_vec.push_back(evt0_c);
    evts_0_list.push_back(evt0_a); evts_0_list.push_back(evt0_b); evts_0_list.push_back(evt0_c);
    evts_1_vec.push_back(evt1_a); evts_1_vec.push_back(evt1_b); evts_1_vec.push_back(evt1_c);
    evts_1_list.push_back(evt1_a); evts_1_list.push_back(evt1_b); evts_1_list.push_back(evt1_c);
    evts_2_vec.push_back(evt2_a); evts_2_vec.push_back(evt2_b); evts_2_vec.push_back(evt2_c);
    evts_2_list.push_back(evt2_a); evts_2_list.push_back(evt2_b); evts_2_list.push_back(evt2_c);


    SimulationResultsPtr output = SimulationResultsFile("MyResults4.hdf").Simulation("Sim1");

    output->write_outputevents_byobjects("population-dINs-RHS", 0, "evts_0_vec", evts_0_vec.begin(), evts_0_vec.end() );
    output->write_outputevents_byobjects("population-dINs-RHS", 0, "evts_0_list", evts_0_list.begin(), evts_0_list.end() );
    output->write_outputevents_byobjects("population-dINs-RHS", 0, "evts_1_vec", evts_1_vec.begin(), evts_1_vec.end() );
    output->write_outputevents_byobjects("population-dINs-RHS", 0, "evts_1_list", evts_1_list.begin(), evts_1_list.end() );
    output->write_outputevents_byobjects("population-dINs-RHS", 0, "evts_2_vec", evts_2_vec.begin(), evts_2_vec.end() );
    output->write_outputevents_byobjects("population-dINs-RHS", 0, "evts_2_list", evts_2_list.begin(), evts_2_list.end() );
}

// Method: 3 - Passing pointers to arrays of data (TODO)
void test_output_events_3()
{
}







void test_input_events_1()
{
    // i. by pointers:
    int pTimes0[] =  {2, 4, 6, 8, 10};
    long pTimes1[] =  {3, 4, 5, 6, 7};
    float pTimes2[] =  {2.3, 6.9, 4.7, 9.7, 34.5};
    double pTimes3[] =  {2.3, 6.9, 4.7, 9.7, 34.5};

    // ii. by stl containers:
    vector<int>   pTimes0STL(pTimes0, pTimes0+5);
    list<long>    pTimes1STL(pTimes1, pTimes1+5);
    vector<float> pTimes2STL(pTimes2, pTimes2+5);
    list<double>  pTimes3STL(pTimes3, pTimes3+5);

    SimulationResultsPtr output = SimulationResultsFile("MyResults5.hdf").Simulation("Sim1");

    output->write_inputevents_onlytimes("population-dINs-RHS", 0, "in_evts_0_vec", 5, pTimes0 );
    output->write_inputevents_onlytimes("population-dINs-RHS", 0, "in_evts_1_ptr", 5, pTimes1 );
    output->write_inputevents_onlytimes("population-dINs-RHS", 0, "in_evts_2_ptr", 5, pTimes2 );
    output->write_inputevents_onlytimes("population-dINs-RHS", 0, "in_evts_3_ptr", 5, pTimes3 );

    output->write_inputevents_onlytimes("population-dINs-RHS", 0, "in_evts_0_stl", pTimes0STL.begin(), pTimes0STL.end() );
    output->write_inputevents_onlytimes("population-dINs-RHS", 0, "in_evts_1_stl", pTimes1STL.begin(), pTimes1STL.end() );
    output->write_inputevents_onlytimes("population-dINs-RHS", 0, "in_evts_2_stl", pTimes2STL.begin(), pTimes2STL.end() );
    output->write_inputevents_onlytimes("population-dINs-RHS", 0, "in_evts_3_stl", pTimes3STL.begin(), pTimes3STL.end() );
}

void test_input_events_2()
{
    // B. With parameters, storing events as objects:
    //template<typename FwdIt>
    //void write_inputeventsNEW2(const std::string& populationname, int index, const std::string& record_name, FwdIt it, FwdIt end, const TagList& tags=TagList() );
}

void test_input_events_3()
{
    /* Create some output-events: */
    // ==============================
    typedef EventType<float, 0> MyEventType0;
    typedef EventType<double,1> MyEventType1;
    typedef EventType<float, 2> MyEventType2;

    vector<MyEventType0> evts_0_vec;
    list<MyEventType0> evts_0_list;
    vector<MyEventType1> evts_1_vec;
    list<MyEventType1> evts_1_list;
    vector<MyEventType2> evts_2_vec;
    list<MyEventType2> evts_2_list;

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


    // Save the events
    evts_0_vec.push_back(evt0_a); evts_0_vec.push_back(evt0_b); evts_0_vec.push_back(evt0_c);
    evts_0_list.push_back(evt0_a); evts_0_list.push_back(evt0_b); evts_0_list.push_back(evt0_c);
    evts_1_vec.push_back(evt1_a); evts_1_vec.push_back(evt1_b); evts_1_vec.push_back(evt1_c);
    evts_1_list.push_back(evt1_a); evts_1_list.push_back(evt1_b); evts_1_list.push_back(evt1_c);
    evts_2_vec.push_back(evt2_a); evts_2_vec.push_back(evt2_b); evts_2_vec.push_back(evt2_c);
    evts_2_list.push_back(evt2_a); evts_2_list.push_back(evt2_b); evts_2_list.push_back(evt2_c);


    SimulationResultsPtr output = SimulationResultsFile("MyResults6.hdf").Simulation("Sim1");

    output->write_outputevents_byobjects("population-dINs-RHS", 0, "out_evts_0_vec", evts_0_vec.begin(), evts_0_vec.end() );
    output->write_outputevents_byobjects("population-dINs-RHS", 0, "out_evts_0_list", evts_0_list.begin(), evts_0_list.end() );
    output->write_outputevents_byobjects("population-dINs-RHS", 0, "out_evts_1_vec", evts_1_vec.begin(), evts_1_vec.end() );
    output->write_outputevents_byobjects("population-dINs-RHS", 0, "out_evts_1_list", evts_1_list.begin(), evts_1_list.end() );
    output->write_outputevents_byobjects("population-dINs-RHS", 0, "out_evts_2_vec", evts_2_vec.begin(), evts_2_vec.end() );
    output->write_outputevents_byobjects("population-dINs-RHS", 0, "out_evts_2_list", evts_2_list.begin(), evts_2_list.end() );




    // Save the events:
    typedef InputEventType<MyEventType0> InEventFloat0;
    typedef InputEventType<MyEventType2> InEventFloat2;
    vector<InEventFloat0> in_evts_float0_vec;
    vector<InEventFloat2> in_evts_float2_vec;

    // Input events (0-param):
    in_evts_float0_vec.push_back(InEventFloat0(SrcEventReference(0,0,0,0), MyEventType0(0, 1.0)));
    in_evts_float0_vec.push_back(InEventFloat0(SrcEventReference(0,0,0,1), MyEventType0(1, 3.0)));
    in_evts_float0_vec.push_back(InEventFloat0(SrcEventReference(0,0,0,2), MyEventType0(2, 8.0)));

    // Input events (2-param):
    in_evts_float2_vec.push_back(InEventFloat2(SrcEventReference(1,0,0,0), MyEventType2(0, 1.0, 2.3, 5.6 ) )  );
    in_evts_float2_vec.push_back(InEventFloat2(SrcEventReference(1,0,0,1), MyEventType2(1, 3.0, 4.3, 5.6 ) )  );
    in_evts_float2_vec.push_back(InEventFloat2(SrcEventReference(1,0,0,2), MyEventType2(2, 8.0, 7.3, 6.6 ) )  );

    output->write_inputevents_byobjects("population-dINs-RHS", 0, "in_evts_0_list", in_evts_float0_vec.begin(), in_evts_float0_vec.end() );
    output->write_inputevents_byobjects("population-dINs-RHS", 0, "in_evts_2_list", in_evts_float2_vec.begin(), in_evts_float2_vec.end() );


}








struct MyEvent
{
    float time;
    float param1;
    float param2;
};




struct MyEventExtractor 
{
    typedef MyEvent EVENTTYPE;
    typedef double DTYPE;
    static const int NPARAMS = 2;

    static float get_time(const EVENTTYPE& o) { return o.time; }
    static float get_parameter_value(const EVENTTYPE& o, int i) { switch(i){ case 0: return o.param1; case 1: return o.param2; default: assert(0); } }
    static string get_parameter_name( int i) { switch(i){ case 0: return "param1"; case 1: return "asd";    default: assert(0); } }
};





template<typename ExtractorType>
void myfunction(const typename ExtractorType::EVENTTYPE& evt)
{
    for(int i=0;i<ExtractorType::NPARAMS;i++)
    {
        cout << "\n" << ExtractorType::get_parameter_name(i) <<  " " << ExtractorType::get_parameter_value(evt, i);
     }
}





void test_input_events_4()
{

    MyEvent o;
    myfunction<MyEventExtractor>(o);


    vector<MyEvent> evts;
    evts.push_back(o);

    SimulationResultsPtr output = SimulationResultsFile("MyResults6.hdf").Simulation("Sim1");
    output->write_outputevents_byobjects_extractor<MyEventExtractor>( ",,",0,"ll", evts.begin(), evts.end() ); 



}





int main(int argc, char* argv[])
{
    test_pointers();
    test_stl();

    test_output_events_1();
    test_output_events_2();
    test_output_events_3();

    test_input_events_1();
    test_input_events_2();
    test_input_events_3();



    test_input_events_4();
}


#include "hdfjive-neuro.h"

#include <boost/assign/list_of.hpp>
#include <vector>
using boost::assign::list_of;

#include "boost/tuple/tuple.hpp"





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
    std::vector<double> time_data = list_of<double>(2.4)(5.6)(9.6)(14.3);
    std::list<float>  voltage_data = list_of<float>(4.2)(6.3)(6.7)(13.4);
    std::vector<int>  int_data = list_of<int>(4)(3)(5)(6);

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
    std::vector<int>  pTimes0STL(pTimes0, pTimes0+5);
    std::list<long>   pTimes1STL(pTimes1, pTimes1+5);
    std::vector<float>pTimes2STL(pTimes2, pTimes2+5);
    std::list<double> pTimes3STL(pTimes3, pTimes3+5);

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



struct MyEventType0
{
    float time;
    MyEventType0(float time) : time(time) {}
};

struct MyEventType1
{
    int TIME;
    int P0;
    MyEventType1(int TIME, int P0): TIME(TIME), P0(P0) {}
};

struct MyEventType2
{
    double my_time;
    double P0;
    double P1;

    MyEventType2( double my_time, double P0, double P1 )
        :  my_time(my_time),  P0(P0),  P1(P1)
    {}
};

struct MyEventExtractor0
{
    typedef MyEventType0 EVENTTYPE;
    typedef double DTYPE;
    static const int NPARAMS = 0;
    static float get_time(const EVENTTYPE& o) { return o.time; }
    static float get_parameter_value(const EVENTTYPE& o, int i) {  assert(0);  }
    static std::string get_parameter_name( int i) { assert(0); }
};


struct MyEventExtractor1
{
    typedef MyEventType1 EVENTTYPE;
    typedef double DTYPE;
    static const int NPARAMS = 1;
    static float get_time(const EVENTTYPE& o) { return o.TIME; }
    static float get_parameter_value(const EVENTTYPE& o, int i) { switch(i){ case 0: return o.P0;  default: assert(0); } }
    static std::string get_parameter_name( int i) { switch(i){ case 0: return "P0";   default: assert(0); } }
};



struct MyEventExtractor2
{
    typedef MyEventType2 EVENTTYPE;
    typedef double DTYPE;
    static const int NPARAMS = 2;
    static float get_time(const EVENTTYPE& o) { return o.my_time; }
    static float get_parameter_value(const EVENTTYPE& o, int i) { switch(i){ case 0: return o.P0; case 1: return o.P1; default: assert(0); } }
    static std::string get_parameter_name( int i) { switch(i){ case 0: return "P0"; case 1: return "P1";    default: assert(0); } }
};


// Method: 2 - Creating 'Event' objects:
void test_output_events_2()
{

    std::vector<MyEventType0> evts_0_vec;
    std::list<MyEventType0> evts_0_list;
    std::vector<MyEventType1> evts_1_vec;
    std::list<MyEventType1> evts_1_list;
    std::vector<MyEventType2> evts_2_vec;
    std::list<MyEventType2> evts_2_list;

    // Create some events (0-param):
    MyEventType0 evt0_a(0.2f);
    MyEventType0 evt0_b(0.3f);
    MyEventType0 evt0_c(0.7f);

    // Create some events (1-param):
    MyEventType1 evt1_a(2, 45);
    MyEventType1 evt1_b(3, 46);
    MyEventType1 evt1_c(7, 47);

    // Create some events (2-param):
    MyEventType2 evt2_a(0.2, 45., 56.);
    MyEventType2 evt2_b(0.3, 46., 23.);
    MyEventType2 evt2_c(0.7, 47., 90.);


    // Save the events
    evts_0_vec.push_back(evt0_a); evts_0_vec.push_back(evt0_b); evts_0_vec.push_back(evt0_c);
    evts_0_list.push_back(evt0_a); evts_0_list.push_back(evt0_b); evts_0_list.push_back(evt0_c);
    evts_1_vec.push_back(evt1_a); evts_1_vec.push_back(evt1_b); evts_1_vec.push_back(evt1_c);
    evts_1_list.push_back(evt1_a); evts_1_list.push_back(evt1_b); evts_1_list.push_back(evt1_c);
    evts_2_vec.push_back(evt2_a); evts_2_vec.push_back(evt2_b); evts_2_vec.push_back(evt2_c);
    evts_2_list.push_back(evt2_a); evts_2_list.push_back(evt2_b); evts_2_list.push_back(evt2_c);


    SimulationResultsPtr output = SimulationResultsFile("MyResults4.hdf").Simulation("Sim1");

    output->write_outputevents_byobjects_extractor<MyEventExtractor0>("population-dINs-RHS", 0, "evts_0_vec", evts_0_vec.begin(), evts_0_vec.end() );
    output->write_outputevents_byobjects_extractor<MyEventExtractor0>("population-dINs-RHS", 0, "evts_0_list", evts_0_list.begin(), evts_0_list.end() );
    output->write_outputevents_byobjects_extractor<MyEventExtractor1>("population-dINs-RHS", 0, "evts_1_vec", evts_1_vec.begin(), evts_1_vec.end() );
    output->write_outputevents_byobjects_extractor<MyEventExtractor1>("population-dINs-RHS", 0, "evts_1_list", evts_1_list.begin(), evts_1_list.end() );
    output->write_outputevents_byobjects_extractor<MyEventExtractor2>("population-dINs-RHS", 0, "evts_2_vec", evts_2_vec.begin(), evts_2_vec.end() );
    output->write_outputevents_byobjects_extractor<MyEventExtractor2>("population-dINs-RHS", 0, "evts_2_list", evts_2_list.begin(), evts_2_list.end() );
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
    std::vector<int>   pTimes0STL(pTimes0, pTimes0+5);
    std::list<long>    pTimes1STL(pTimes1, pTimes1+5);
    std::vector<float> pTimes2STL(pTimes2, pTimes2+5);
    std::list<double>  pTimes3STL(pTimes3, pTimes3+5);

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




struct MyInputEventType0
{
    float time;

    size_t src_population_index;
    size_t src_neuron_index;
    size_t src_evtport_index;
    size_t src_event_index;

    MyInputEventType0(size_t src_population_index, size_t src_neuron_index, size_t src_evtport_index, size_t src_event_index, float time)
    : time(time), src_population_index(src_population_index),  src_neuron_index(src_neuron_index),  src_evtport_index(src_evtport_index),  src_event_index(src_event_index)
    {}
};


struct MyInputEventType2
{
    double my_time;
    double P0;
    double P1;

    size_t src_population_index;
    size_t src_neuron_index;
    size_t src_evtport_index;
    size_t src_event_index;

    MyInputEventType2(size_t src_population_index, size_t src_neuron_index, size_t src_evtport_index, size_t src_event_index, double my_time, double P0, double P1 )
        :  my_time(my_time),  P0(P0),  P1(P1) , src_population_index(src_population_index),  src_neuron_index(src_neuron_index),  src_evtport_index(src_evtport_index),  src_event_index(src_event_index)

    {}
};

struct MyInputEventExtractor0
{
    typedef MyInputEventType0 EVENTTYPE;
    typedef double DTYPE;
    static const int NPARAMS = 0;
    static DTYPE get_time(const EVENTTYPE& o) { return o.time; }
    static DTYPE get_parameter_value(const EVENTTYPE& o, int i) {  assert(0);  }
    static std::string get_parameter_name( int i) { assert(0); }

    static const size_t NSRCINDICES = 4;
    static DTYPE get_srcindex_value(const EVENTTYPE& o, size_t i)
    {
        switch(i){
            case 0: return o.src_population_index;
            case 1: return o.src_neuron_index;
            case 2: return o.src_evtport_index;
            case 3: return o.src_event_index;
            default: assert(0);
        }
    }
    static std::string get_index_name( size_t i)
    {
        switch(i){
            case 0: return "PopIndex";
            case 1: return "NrnIndex";
            case 2: return "EvtPortIndex";
            case 3: return "EvtIndex";
            default: assert(0);
        }
    }

};





struct MyInputEventExtractor2
{
    typedef MyInputEventType2 EVENTTYPE;
    typedef double DTYPE;
    static const int NPARAMS = 2;
    static DTYPE get_time(const EVENTTYPE& o) { return o.my_time; }
    static DTYPE get_parameter_value(const EVENTTYPE& o, int i) { switch(i){ case 0: return o.P0; case 1: return o.P1; default: assert(0); } }
    static std::string get_parameter_name( int i) { switch(i){ case 0: return "P0"; case 1: return "P1";    default: assert(0); } }


    static const size_t NSRCINDICES = 4;
    static DTYPE get_srcindex_value(const EVENTTYPE& o, size_t i)
    {
        switch(i){
            case 0: return o.src_population_index;
            case 1: return o.src_neuron_index;
            case 2: return o.src_evtport_index;
            case 3: return o.src_event_index;
            default: assert(0);
        }
    }
    static std::string get_index_name(size_t i)
    {
        switch(i){
            case 0: return "PopIndex";
            case 1: return "NrnIndex";
            case 2: return "EvtPortIndex";
            case 3: return "EvtIndex";
            default: assert(0);
        }
    }



};














void test_input_events_3()
{
    /* Create some output-events: */
    // ==============================
    //
    std::vector<MyEventType0> evts_0_vec;
    std::list<MyEventType0> evts_0_list;
    std::vector<MyEventType1> evts_1_vec;
    std::list<MyEventType1> evts_1_list;
    std::vector<MyEventType2> evts_2_vec;
    std::list<MyEventType2> evts_2_list;

    // Create some events (0-param):
    MyEventType0 evt0_a(0.2f);
    MyEventType0 evt0_b(0.3f);
    MyEventType0 evt0_c(0.7f);

    // Create some events (1-param):
    MyEventType1 evt1_a(2, 45);
    MyEventType1 evt1_b(3, 46);
    MyEventType1 evt1_c(7, 47);

    // Create some events (2-param):
    MyEventType2 evt2_a(0.2, 45., 56.);
    MyEventType2 evt2_b(0.3, 46., 23.);
    MyEventType2 evt2_c(0.7, 47., 90.);


    // Save the events
    evts_0_vec.push_back(evt0_a); evts_0_vec.push_back(evt0_b); evts_0_vec.push_back(evt0_c);
    evts_0_list.push_back(evt0_a); evts_0_list.push_back(evt0_b); evts_0_list.push_back(evt0_c);
    evts_1_vec.push_back(evt1_a); evts_1_vec.push_back(evt1_b); evts_1_vec.push_back(evt1_c);
    evts_1_list.push_back(evt1_a); evts_1_list.push_back(evt1_b); evts_1_list.push_back(evt1_c);
    evts_2_vec.push_back(evt2_a); evts_2_vec.push_back(evt2_b); evts_2_vec.push_back(evt2_c);
    evts_2_list.push_back(evt2_a); evts_2_list.push_back(evt2_b); evts_2_list.push_back(evt2_c);


    SimulationResultsPtr output = SimulationResultsFile("MyResults6.hdf").Simulation("Sim1");

    output->write_outputevents_byobjects_extractor<MyEventExtractor0>("population-dINs-RHS", 0, "evts_0_vec", evts_0_vec.begin(), evts_0_vec.end() );
    output->write_outputevents_byobjects_extractor<MyEventExtractor0>("population-dINs-RHS", 0, "evts_0_list", evts_0_list.begin(), evts_0_list.end() );
    output->write_outputevents_byobjects_extractor<MyEventExtractor1>("population-dINs-RHS", 0, "evts_1_vec", evts_1_vec.begin(), evts_1_vec.end() );
    output->write_outputevents_byobjects_extractor<MyEventExtractor1>("population-dINs-RHS", 0, "evts_1_list", evts_1_list.begin(), evts_1_list.end() );
    output->write_outputevents_byobjects_extractor<MyEventExtractor2>("population-dINs-RHS", 0, "evts_2_vec", evts_2_vec.begin(), evts_2_vec.end() );
    output->write_outputevents_byobjects_extractor<MyEventExtractor2>("population-dINs-RHS", 0, "evts_2_list", evts_2_list.begin(), evts_2_list.end() );




    // Save the events:
    std::vector<MyInputEventType0> in_evts_float0_vec;
    std::vector<MyInputEventType2> in_evts_float2_vec;

    // Input events (0-param):
    in_evts_float0_vec.push_back(MyInputEventType0(0,0,0,0, 0));
    in_evts_float0_vec.push_back(MyInputEventType0(0,0,0,1, 1));
    in_evts_float0_vec.push_back(MyInputEventType0(0,0,0,2, 2));

    // Input events (2-param):
    in_evts_float2_vec.push_back(MyInputEventType2(1,0,0,0, 0, 1.0, 2.3 ) );
    in_evts_float2_vec.push_back(MyInputEventType2(1,0,0,1, 1, 3.0, 4.3 ) );
    in_evts_float2_vec.push_back(MyInputEventType2(1,0,0,2, 2, 8.0, 7.3 ) );

    output->write_inputevents_byobjects_extractor<MyInputEventExtractor0>("population-dINs-RHS", 0, "in_evts_0_list", in_evts_float0_vec.begin(), in_evts_float0_vec.end() );
    output->write_inputevents_byobjects_extractor<MyInputEventExtractor2>("population-dINs-RHS", 0, "in_evts_2_list", in_evts_float2_vec.begin(), in_evts_float2_vec.end() );

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
}

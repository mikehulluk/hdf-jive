

#include "hdfjive-events.h"
#include <assert.h>


template<typename DATATYPE, int NPARAMS>
EventType<DATATYPE,NPARAMS>::EventType(size_t event_index, DATATYPE time)
    : event_index(event_index), time(time)
{
    assert(NPARAMS==0);
}

template<typename DATATYPE, int NPARAMS>
EventType<DATATYPE,NPARAMS>::EventType(size_t event_index, DATATYPE time, DATATYPE p0)
    : event_index(event_index), time(time)
{
    assert(NPARAMS==1);
    parameters[0] = p0;
}

template<typename DATATYPE, int NPARAMS>
EventType<DATATYPE,NPARAMS>::EventType(size_t event_index, DATATYPE time, DATATYPE p0, DATATYPE p1)
    : event_index(event_index), time(time)
{
    assert(NPARAMS==2);
    parameters[0] = p0;  parameters[1] = p1; 
}

template<typename DATATYPE, int NPARAMS>
EventType<DATATYPE,NPARAMS>::EventType(size_t event_index, DATATYPE time, DATATYPE p0, DATATYPE p1, DATATYPE p2)
    : event_index(event_index), time(time)
{
    assert(NPARAMS==3);
    parameters[0] = p0;  parameters[1] = p1; parameters[2] = p2; 
}

template<typename DATATYPE, int NPARAMS>
EventType<DATATYPE,NPARAMS>::EventType(size_t event_index, DATATYPE time, DATATYPE p0, DATATYPE p1, DATATYPE p2, DATATYPE p3)
    : event_index(event_index), time(time)
{
    assert(NPARAMS==4);
    parameters[0] = p0;  parameters[1] = p1; parameters[2] = p2; parameters[3] = p3;
}




SrcEventReference::SrcEventReference(size_t src_population_index, size_t src_neuron_index, size_t src_event_index)
: src_population_index(src_population_index), src_neuron_index(src_neuron_index), src_event_index(src_event_index)
{

}



template<typename EVENTTYPE_>
InputEventType<EVENTTYPE_>::InputEventType(const SrcEventReference& src, const EVENTTYPE& evt_details)
    : evt_src(evt_src), evt_details(evt_details)
{


}






// Instantiation:
template EventType<int,0>::EventType(size_t, int);
template EventType<int,1>::EventType(size_t, int, int);
template EventType<int,2>::EventType(size_t, int, int, int);
template EventType<int,3>::EventType(size_t, int, int, int, int);
template EventType<int,4>::EventType(size_t, int, int, int, int, int);

template EventType<long,0>::EventType(size_t, long);
template EventType<long,1>::EventType(size_t, long, long);
template EventType<long,2>::EventType(size_t, long, long, long);
template EventType<long,3>::EventType(size_t, long, long, long, long);
template EventType<long,4>::EventType(size_t, long, long, long, long, long);

template EventType<float,0>::EventType(size_t, float);
template EventType<float,1>::EventType(size_t, float, float);
template EventType<float,2>::EventType(size_t, float, float, float);
template EventType<float,3>::EventType(size_t, float, float, float, float);
template EventType<float,4>::EventType(size_t, float, float, float, float, float);

template EventType<double,0>::EventType(size_t, double);
template EventType<double,1>::EventType(size_t, double, double);
template EventType<double,2>::EventType(size_t, double, double, double);
template EventType<double,3>::EventType(size_t, double, double, double, double);
template EventType<double,4>::EventType(size_t, double, double, double, double, double);


template InputEventType< EventType<int,0> >::InputEventType(const SrcEventReference&, const EventType<int,0>& );
template InputEventType< EventType<int,1> >::InputEventType(const SrcEventReference&, const EventType<int,1>& );
template InputEventType< EventType<int,2> >::InputEventType(const SrcEventReference&, const EventType<int,2>& );
template InputEventType< EventType<int,3> >::InputEventType(const SrcEventReference&, const EventType<int,3>& );
template InputEventType< EventType<int,4> >::InputEventType(const SrcEventReference&, const EventType<int,4>& );

template InputEventType< EventType<long,0> >::InputEventType(const SrcEventReference&, const EventType<long,0>& );
template InputEventType< EventType<long,1> >::InputEventType(const SrcEventReference&, const EventType<long,1>& );
template InputEventType< EventType<long,2> >::InputEventType(const SrcEventReference&, const EventType<long,2>& );
template InputEventType< EventType<long,3> >::InputEventType(const SrcEventReference&, const EventType<long,3>& );
template InputEventType< EventType<long,4> >::InputEventType(const SrcEventReference&, const EventType<long,4>& );

template InputEventType< EventType<float,0> >::InputEventType(const SrcEventReference&, const EventType<float,0>& );
template InputEventType< EventType<float,1> >::InputEventType(const SrcEventReference&, const EventType<float,1>& );
template InputEventType< EventType<float,2> >::InputEventType(const SrcEventReference&, const EventType<float,2>& );
template InputEventType< EventType<float,3> >::InputEventType(const SrcEventReference&, const EventType<float,3>& );
template InputEventType< EventType<float,4> >::InputEventType(const SrcEventReference&, const EventType<float,4>& );

template InputEventType< EventType<double,0> >::InputEventType(const SrcEventReference&, const EventType<double,0>& );
template InputEventType< EventType<double,1> >::InputEventType(const SrcEventReference&, const EventType<double,1>& );
template InputEventType< EventType<double,2> >::InputEventType(const SrcEventReference&, const EventType<double,2>& );
template InputEventType< EventType<double,3> >::InputEventType(const SrcEventReference&, const EventType<double,3>& );
template InputEventType< EventType<double,4> >::InputEventType(const SrcEventReference&, const EventType<double,4>& );





#include "hdfjive-events.h"
#include <assert.h>


/*
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
*/

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





#ifndef __HDFJIVE_EVENTS_GUARD_H__
#define __HDFJIVE_EVENTS_GUARD_H__



#include <string>
#include <vector>
#include <array>
#include <map>
using namespace std;



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



#endif

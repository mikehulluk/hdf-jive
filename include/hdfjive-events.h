


#ifndef __HDFJIVE_EVENTS_GUARD_H__
#define __HDFJIVE_EVENTS_GUARD_H__



#include <string>
#include <vector>
#include <array>
#include <map>
using namespace std;



template<typename DATATYPE_, int NPARAMS_>
class EventType
{
public:
    typedef DATATYPE_ DATATYPE;
    const static int NPARAMS = NPARAMS_;

private:
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




struct SrcEventReference
{
    size_t src_population_index;
    size_t src_neuron_index;
    size_t src_event_index;

public:

    SrcEventReference(size_t src_population_index, size_t src_neuron_index, size_t src_event_index);
};





template<typename EVENTTYPE_>
class InputEventType
{
    typedef EVENTTYPE_ EVENTTYPE;
    SrcEventReference evt_src;
    EVENTTYPE evt_details;

public:
    InputEventType(const SrcEventReference& src, const EVENTTYPE& evt_details);


};




#endif

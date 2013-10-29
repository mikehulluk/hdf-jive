

// Explicitly instantiate the various templated functions:
#include <vector>
using std::vector;


typedef vector<int> VecInt;
typedef vector<long> VecLong;
typedef vector<float> VecFloat;
typedef vector<double> VecDouble;

typedef list<int> ListInt;
typedef list<long> ListLong;
typedef list<float> ListFloat;
typedef list<double> ListDouble;


template SharedTimeBufferPtr SimulationResults::write_shared_time_buffer<int>(size_t, int*);
template SharedTimeBufferPtr SimulationResults::write_shared_time_buffer<long>(size_t, long*);
template SharedTimeBufferPtr SimulationResults::write_shared_time_buffer<float>(size_t, float*);
template SharedTimeBufferPtr SimulationResults::write_shared_time_buffer<double>(size_t, double*);

template SharedTimeBufferPtr SimulationResults::write_shared_time_buffer<int>(size_t, int);
template SharedTimeBufferPtr SimulationResults::write_shared_time_buffer<long>(size_t, long);
template SharedTimeBufferPtr SimulationResults::write_shared_time_buffer<float>(size_t, float);
template SharedTimeBufferPtr SimulationResults::write_shared_time_buffer<double>(size_t, double);

template SharedTimeBufferPtr SimulationResults::write_shared_time_buffer<VecInt::iterator> (VecInt::iterator, VecInt::iterator);
template SharedTimeBufferPtr SimulationResults::write_shared_time_buffer<VecLong::iterator> (VecLong::iterator, VecLong::iterator);
template SharedTimeBufferPtr SimulationResults::write_shared_time_buffer<VecFloat::iterator> (VecFloat::iterator, VecFloat::iterator);
template SharedTimeBufferPtr SimulationResults::write_shared_time_buffer<VecDouble::iterator> (VecDouble::iterator, VecDouble::iterator);
template SharedTimeBufferPtr SimulationResults::write_shared_time_buffer<ListInt::iterator> (ListInt::iterator, ListInt::iterator);
template SharedTimeBufferPtr SimulationResults::write_shared_time_buffer<ListLong::iterator> (ListLong::iterator, ListLong::iterator);
template SharedTimeBufferPtr SimulationResults::write_shared_time_buffer<ListFloat::iterator> (ListFloat::iterator, ListFloat::iterator);
template SharedTimeBufferPtr SimulationResults::write_shared_time_buffer<ListDouble::iterator> (ListDouble::iterator, ListDouble::iterator);



template void SimulationResults::write_trace<int>( const std::string& populationname, int index, const std::string& record_name, SharedTimeBufferPtr times, int* pData, const TagList& tags);
template void SimulationResults::write_trace<long>( const std::string& populationname, int index, const std::string& record_name, SharedTimeBufferPtr times, long* pData, const TagList& tags);
template void SimulationResults::write_trace<float>( const std::string& populationname, int index, const std::string& record_name, SharedTimeBufferPtr times, float* pData, const TagList& tags);
template void SimulationResults::write_trace<double>( const std::string& populationname, int index, const std::string& record_name, SharedTimeBufferPtr times, double* pData, const TagList& tags);

template void SimulationResults::write_trace<VecInt::iterator > (const std::string& populationname, int index, const std::string& record_name, SharedTimeBufferPtr times, VecInt::iterator it, VecInt::iterator end, const TagList&);
template void SimulationResults::write_trace<VecLong::iterator> (const std::string& populationname, int index, const std::string& record_name, SharedTimeBufferPtr times, VecLong::iterator it, VecLong::iterator end, const TagList&);
template void SimulationResults::write_trace<VecFloat::iterator > (const std::string& populationname, int index, const std::string& record_name, SharedTimeBufferPtr times, VecFloat::iterator it, VecFloat::iterator end, const TagList&);
template void SimulationResults::write_trace<VecDouble::iterator > (const std::string& populationname, int index, const std::string& record_name, SharedTimeBufferPtr times, VecDouble::iterator it, VecDouble::iterator end, const TagList&);
template void SimulationResults::write_trace<ListInt::iterator> (const std::string& populationname, int index, const std::string& record_name, SharedTimeBufferPtr times, ListInt::iterator it, ListInt::iterator end, const TagList&);
template void SimulationResults::write_trace<ListLong::iterator> (const std::string& populationname, int index, const std::string& record_name, SharedTimeBufferPtr times, ListLong::iterator it, ListLong::iterator end, const TagList&);
template void SimulationResults::write_trace<ListFloat::iterator> (const std::string& populationname, int index, const std::string& record_name, SharedTimeBufferPtr times, ListFloat::iterator it, ListFloat::iterator end, const TagList&);
template void SimulationResults::write_trace<ListDouble::iterator> (const std::string& populationname, int index, const std::string& record_name, SharedTimeBufferPtr times, ListDouble::iterator it, ListDouble::iterator end, const TagList&);






//#include "hdfjive-events.h"
/*
typedef EventType<int, 0> EventInt0;
typedef EventType<int, 1> EventInt1;
typedef EventType<int, 2> EventInt2;
typedef EventType<int, 3> EventInt3;
typedef EventType<int, 4> EventInt4;

typedef EventType<long, 0> EventLong0;
typedef EventType<long, 1> EventLong1;
typedef EventType<long, 2> EventLong2;
typedef EventType<long, 3> EventLong3;
typedef EventType<long, 4> EventLong4;


typedef EventType<float, 0> EventFloat0;
typedef EventType<float, 1> EventFloat1;
typedef EventType<float, 2> EventFloat2;
typedef EventType<float, 3> EventFloat3;
typedef EventType<float, 4> EventFloat4;

typedef EventType<double, 0> EventDouble0;
typedef EventType<double, 1> EventDouble1;
typedef EventType<double, 2> EventDouble2;
typedef EventType<double, 3> EventDouble3;
typedef EventType<double, 4> EventDouble4;

typedef vector<EventInt0> VecEventInt0;
typedef vector<EventInt1> VecEventInt1;
typedef vector<EventInt2> VecEventInt2;
typedef vector<EventInt3> VecEventInt3;
typedef vector<EventInt4> VecEventInt4;

typedef vector<EventLong0> VecEventLong0;
typedef vector<EventLong1> VecEventLong1;
typedef vector<EventLong2> VecEventLong2;
typedef vector<EventLong3> VecEventLong3;
typedef vector<EventLong4> VecEventLong4;

typedef vector<EventFloat0> VecEventFloat0;
typedef vector<EventFloat1> VecEventFloat1;
typedef vector<EventFloat2> VecEventFloat2;
typedef vector<EventFloat3> VecEventFloat3;
typedef vector<EventFloat4> VecEventFloat4;

typedef vector<EventDouble0> VecEventDouble0;
typedef vector<EventDouble1> VecEventDouble1;
typedef vector<EventDouble2> VecEventDouble2;
typedef vector<EventDouble3> VecEventDouble3;
typedef vector<EventDouble4> VecEventDouble4;

typedef list<EventInt0> ListEventInt0;
typedef list<EventInt1> ListEventInt1;
typedef list<EventInt2> ListEventInt2;
typedef list<EventInt3> ListEventInt3;
typedef list<EventInt4> ListEventInt4;

typedef list<EventLong0> ListEventLong0;
typedef list<EventLong1> ListEventLong1;
typedef list<EventLong2> ListEventLong2;
typedef list<EventLong3> ListEventLong3;
typedef list<EventLong4> ListEventLong4;

typedef list<EventFloat0> ListEventFloat0;
typedef list<EventFloat1> ListEventFloat1;
typedef list<EventFloat2> ListEventFloat2;
typedef list<EventFloat3> ListEventFloat3;
typedef list<EventFloat4> ListEventFloat4;

typedef list<EventDouble0> ListEventDouble0;
typedef list<EventDouble1> ListEventDouble1;
typedef list<EventDouble2> ListEventDouble2;
typedef list<EventDouble3> ListEventDouble3;
typedef list<EventDouble4> ListEventDouble4;
*/

template void SimulationResults::write_outputevents_onlytimes<int>( const std::string& populationname, int index, const std::string& record_name,    size_t, int*, const TagList& );
template void SimulationResults::write_outputevents_onlytimes<long>( const std::string& populationname, int index, const std::string& record_name,    size_t, long*, const TagList& );
template void SimulationResults::write_outputevents_onlytimes<float>( const std::string& populationname, int index, const std::string& record_name,    size_t, float*, const TagList& );
template void SimulationResults::write_outputevents_onlytimes<double>( const std::string& populationname, int index, const std::string& record_name,    size_t, double*, const TagList& );

template void SimulationResults::write_outputevents_onlytimes<VecInt::iterator>( const std::string& populationname, int index, const std::string& record_name,    VecInt::iterator it, VecInt::iterator end, const TagList& );
template void SimulationResults::write_outputevents_onlytimes<VecLong::iterator>( const std::string& populationname, int index, const std::string& record_name,   VecLong::iterator it, VecLong::iterator end, const TagList& );
template void SimulationResults::write_outputevents_onlytimes<VecFloat::iterator>( const std::string& populationname, int index, const std::string& record_name,  VecFloat::iterator it, VecFloat::iterator end, const TagList& );
template void SimulationResults::write_outputevents_onlytimes<VecDouble::iterator>( const std::string& populationname, int index, const std::string& record_name, VecDouble::iterator it, VecDouble::iterator end, const TagList& );

template void SimulationResults::write_outputevents_onlytimes<ListInt::iterator>( const std::string& populationname, int index, const std::string& record_name,    ListInt::iterator it,     ListInt::iterator end, const TagList& );
template void SimulationResults::write_outputevents_onlytimes<ListLong::iterator>( const std::string& populationname, int index, const std::string& record_name,   ListLong::iterator it,   ListLong::iterator end, const TagList& );
template void SimulationResults::write_outputevents_onlytimes<ListFloat::iterator>( const std::string& populationname, int index, const std::string& record_name,  ListFloat::iterator it,  ListFloat::iterator end, const TagList& );
template void SimulationResults::write_outputevents_onlytimes<ListDouble::iterator>( const std::string& populationname, int index, const std::string& record_name, ListDouble::iterator it, ListDouble::iterator end, const TagList& );













//typedef InputEventType<EventInt0> InEventInt0;
//typedef InputEventType<EventInt1> InEventInt1;
//typedef InputEventType<EventInt2> InEventInt2;
//typedef InputEventType<EventInt3> InEventInt3;
//typedef InputEventType<EventInt4> InEventInt4;
//
//typedef InputEventType<EventLong0> InEventLong0;
//typedef InputEventType<EventLong1> InEventLong1;
//typedef InputEventType<EventLong2> InEventLong2;
//typedef InputEventType<EventLong3> InEventLong3;
//typedef InputEventType<EventLong4> InEventLong4;
//
//typedef InputEventType<EventFloat0> InEventFloat0;
//typedef InputEventType<EventFloat1> InEventFloat1;
//typedef InputEventType<EventFloat2> InEventFloat2;
//typedef InputEventType<EventFloat3> InEventFloat3;
//typedef InputEventType<EventFloat4> InEventFloat4;
//
//typedef InputEventType<EventDouble0> InEventDouble0;
//typedef InputEventType<EventDouble1> InEventDouble1;
//typedef InputEventType<EventDouble2> InEventDouble2;
//typedef InputEventType<EventDouble3> InEventDouble3;
//typedef InputEventType<EventDouble4> InEventDouble4;
//
//typedef vector<InEventInt0> VecInEventInt0;
//typedef vector<InEventInt1> VecInEventInt1;
//typedef vector<InEventInt2> VecInEventInt2;
//typedef vector<InEventInt3> VecInEventInt3;
//typedef vector<InEventInt4> VecInEventInt4;
//
//typedef vector<InEventLong0> VecInEventLong0;
//typedef vector<InEventLong1> VecInEventLong1;
//typedef vector<InEventLong2> VecInEventLong2;
//typedef vector<InEventLong3> VecInEventLong3;
//typedef vector<InEventLong4> VecInEventLong4;
//
//typedef vector<InEventFloat0> VecInEventFloat0;
//typedef vector<InEventFloat1> VecInEventFloat1;
//typedef vector<InEventFloat2> VecInEventFloat2;
//typedef vector<InEventFloat3> VecInEventFloat3;
//typedef vector<InEventFloat4> VecInEventFloat4;
//
//typedef vector<InEventDouble0> VecInEventDouble0;
//typedef vector<InEventDouble1> VecInEventDouble1;
//typedef vector<InEventDouble2> VecInEventDouble2;
//typedef vector<InEventDouble3> VecInEventDouble3;
//typedef vector<InEventDouble4> VecInEventDouble4;
//
//typedef list<InEventInt0> ListInEventInt0;
//typedef list<InEventInt1> ListInEventInt1;
//typedef list<InEventInt2> ListInEventInt2;
//typedef list<InEventInt3> ListInEventInt3;
//typedef list<InEventInt4> ListInEventInt4;
//
//typedef list<InEventLong0> ListInEventLong0;
//typedef list<InEventLong1> ListInEventLong1;
//typedef list<InEventLong2> ListInEventLong2;
//typedef list<InEventLong3> ListInEventLong3;
//typedef list<InEventLong4> ListInEventLong4;
//
//typedef list<InEventFloat0> ListInEventFloat0;
//typedef list<InEventFloat1> ListInEventFloat1;
//typedef list<InEventFloat2> ListInEventFloat2;
//typedef list<InEventFloat3> ListInEventFloat3;
//typedef list<InEventFloat4> ListInEventFloat4;
//
//typedef list<InEventDouble0> ListInEventDouble0;
//typedef list<InEventDouble1> ListInEventDouble1;
//typedef list<InEventDouble2> ListInEventDouble2;
//typedef list<InEventDouble3> ListInEventDouble3;
//typedef list<InEventDouble4> ListInEventDouble4;

template void SimulationResults::write_inputevents_onlytimes<int>( const std::string& populationname, int index, const std::string& record_name,    size_t, int*, const TagList& );
template void SimulationResults::write_inputevents_onlytimes<long>( const std::string& populationname, int index, const std::string& record_name,    size_t, long*, const TagList& );
template void SimulationResults::write_inputevents_onlytimes<float>( const std::string& populationname, int index, const std::string& record_name,    size_t, float*, const TagList& );
template void SimulationResults::write_inputevents_onlytimes<double>( const std::string& populationname, int index, const std::string& record_name,    size_t, double*, const TagList& );

template void SimulationResults::write_inputevents_onlytimes<VecInt::iterator>( const std::string& populationname, int index, const std::string& record_name,    VecInt::iterator it, VecInt::iterator end, const TagList& );
template void SimulationResults::write_inputevents_onlytimes<VecLong::iterator>( const std::string& populationname, int index, const std::string& record_name,   VecLong::iterator it, VecLong::iterator end, const TagList& );
template void SimulationResults::write_inputevents_onlytimes<VecFloat::iterator>( const std::string& populationname, int index, const std::string& record_name,  VecFloat::iterator it, VecFloat::iterator end, const TagList& );
template void SimulationResults::write_inputevents_onlytimes<VecDouble::iterator>( const std::string& populationname, int index, const std::string& record_name, VecDouble::iterator it, VecDouble::iterator end, const TagList& );

template void SimulationResults::write_inputevents_onlytimes<ListInt::iterator>( const std::string& populationname, int index, const std::string& record_name,    ListInt::iterator it,     ListInt::iterator end, const TagList& );
template void SimulationResults::write_inputevents_onlytimes<ListLong::iterator>( const std::string& populationname, int index, const std::string& record_name,   ListLong::iterator it,   ListLong::iterator end, const TagList& );
template void SimulationResults::write_inputevents_onlytimes<ListFloat::iterator>( const std::string& populationname, int index, const std::string& record_name,  ListFloat::iterator it,  ListFloat::iterator end, const TagList& );
template void SimulationResults::write_inputevents_onlytimes<ListDouble::iterator>( const std::string& populationname, int index, const std::string& record_name, ListDouble::iterator it, ListDouble::iterator end, const TagList& );







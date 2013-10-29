

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






#include "hdfjive-events.h"

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





template void SimulationResults::write_outputevents_byobjects<VecEventInt0::iterator>( const std::string& , int , const std::string&, VecEventInt0::iterator, VecEventInt0::iterator, const TagList&);
template void SimulationResults::write_outputevents_byobjects<VecEventInt1::iterator>( const std::string& , int , const std::string&, VecEventInt1::iterator, VecEventInt1::iterator, const TagList&);
template void SimulationResults::write_outputevents_byobjects<VecEventInt2::iterator>( const std::string& , int , const std::string&, VecEventInt2::iterator, VecEventInt2::iterator, const TagList&);
template void SimulationResults::write_outputevents_byobjects<VecEventInt3::iterator>( const std::string& , int , const std::string&, VecEventInt3::iterator, VecEventInt3::iterator, const TagList&);
template void SimulationResults::write_outputevents_byobjects<VecEventInt4::iterator>( const std::string& , int , const std::string&, VecEventInt4::iterator, VecEventInt4::iterator, const TagList&);

template void SimulationResults::write_outputevents_byobjects<VecEventLong0::iterator>( const std::string& , int , const std::string& , VecEventLong0::iterator , VecEventLong0::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<VecEventLong1::iterator>( const std::string& , int , const std::string& , VecEventLong1::iterator , VecEventLong1::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<VecEventLong2::iterator>( const std::string& , int , const std::string& , VecEventLong2::iterator , VecEventLong2::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<VecEventLong3::iterator>( const std::string& , int , const std::string& , VecEventLong3::iterator , VecEventLong3::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<VecEventLong4::iterator>( const std::string& , int , const std::string& , VecEventLong4::iterator , VecEventLong4::iterator , const TagList& );

template void SimulationResults::write_outputevents_byobjects<VecEventFloat0::iterator>( const std::string& , int , const std::string& , VecEventFloat0::iterator , VecEventFloat0::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<VecEventFloat1::iterator>( const std::string& , int , const std::string& , VecEventFloat1::iterator , VecEventFloat1::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<VecEventFloat2::iterator>( const std::string& , int , const std::string& , VecEventFloat2::iterator , VecEventFloat2::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<VecEventFloat3::iterator>( const std::string& , int , const std::string& , VecEventFloat3::iterator , VecEventFloat3::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<VecEventFloat4::iterator>( const std::string& , int , const std::string& , VecEventFloat4::iterator , VecEventFloat4::iterator , const TagList& );

template void SimulationResults::write_outputevents_byobjects<VecEventDouble0::iterator>( const std::string& , int , const std::string& , VecEventDouble0::iterator , VecEventDouble0::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<VecEventDouble1::iterator>( const std::string& , int , const std::string& , VecEventDouble1::iterator , VecEventDouble1::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<VecEventDouble2::iterator>( const std::string& , int , const std::string& , VecEventDouble2::iterator , VecEventDouble2::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<VecEventDouble3::iterator>( const std::string& , int , const std::string& , VecEventDouble3::iterator , VecEventDouble3::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<VecEventDouble4::iterator>( const std::string& , int , const std::string& , VecEventDouble4::iterator , VecEventDouble4::iterator , const TagList& );


template void SimulationResults::write_outputevents_byobjects<ListEventInt0::iterator>( const std::string& , int , const std::string& , ListEventInt0::iterator , ListEventInt0::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<ListEventInt1::iterator>( const std::string& , int , const std::string& , ListEventInt1::iterator , ListEventInt1::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<ListEventInt2::iterator>( const std::string& , int , const std::string& , ListEventInt2::iterator , ListEventInt2::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<ListEventInt3::iterator>( const std::string& , int , const std::string& , ListEventInt3::iterator , ListEventInt3::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<ListEventInt4::iterator>( const std::string& , int , const std::string& , ListEventInt4::iterator , ListEventInt4::iterator , const TagList& );

template void SimulationResults::write_outputevents_byobjects<ListEventLong0::iterator>( const std::string& , int , const std::string& , ListEventLong0::iterator , ListEventLong0::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<ListEventLong1::iterator>( const std::string& , int , const std::string& , ListEventLong1::iterator , ListEventLong1::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<ListEventLong2::iterator>( const std::string& , int , const std::string& , ListEventLong2::iterator , ListEventLong2::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<ListEventLong3::iterator>( const std::string& , int , const std::string& , ListEventLong3::iterator , ListEventLong3::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<ListEventLong4::iterator>( const std::string& , int , const std::string& , ListEventLong4::iterator , ListEventLong4::iterator , const TagList& );

template void SimulationResults::write_outputevents_byobjects<ListEventFloat0::iterator>( const std::string& , int , const std::string& , ListEventFloat0::iterator , ListEventFloat0::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<ListEventFloat1::iterator>( const std::string& , int , const std::string& , ListEventFloat1::iterator , ListEventFloat1::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<ListEventFloat2::iterator>( const std::string& , int , const std::string& , ListEventFloat2::iterator , ListEventFloat2::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<ListEventFloat3::iterator>( const std::string& , int , const std::string& , ListEventFloat3::iterator , ListEventFloat3::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<ListEventFloat4::iterator>( const std::string& , int , const std::string& , ListEventFloat4::iterator , ListEventFloat4::iterator , const TagList& );

template void SimulationResults::write_outputevents_byobjects<ListEventDouble0::iterator>( const std::string& , int , const std::string& , ListEventDouble0::iterator , ListEventDouble0::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<ListEventDouble1::iterator>( const std::string& , int , const std::string& , ListEventDouble1::iterator , ListEventDouble1::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<ListEventDouble2::iterator>( const std::string& , int , const std::string& , ListEventDouble2::iterator , ListEventDouble2::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<ListEventDouble3::iterator>( const std::string& , int , const std::string& , ListEventDouble3::iterator , ListEventDouble3::iterator , const TagList& );
template void SimulationResults::write_outputevents_byobjects<ListEventDouble4::iterator>( const std::string& , int , const std::string& , ListEventDouble4::iterator , ListEventDouble4::iterator , const TagList& );











typedef InputEventType<EventInt0> InEventInt0;
typedef InputEventType<EventInt1> InEventInt1;
typedef InputEventType<EventInt2> InEventInt2;
typedef InputEventType<EventInt3> InEventInt3;
typedef InputEventType<EventInt4> InEventInt4;

typedef InputEventType<EventLong0> InEventLong0;
typedef InputEventType<EventLong1> InEventLong1;
typedef InputEventType<EventLong2> InEventLong2;
typedef InputEventType<EventLong3> InEventLong3;
typedef InputEventType<EventLong4> InEventLong4;

typedef InputEventType<EventFloat0> InEventFloat0;
typedef InputEventType<EventFloat1> InEventFloat1;
typedef InputEventType<EventFloat2> InEventFloat2;
typedef InputEventType<EventFloat3> InEventFloat3;
typedef InputEventType<EventFloat4> InEventFloat4;

typedef InputEventType<EventDouble0> InEventDouble0;
typedef InputEventType<EventDouble1> InEventDouble1;
typedef InputEventType<EventDouble2> InEventDouble2;
typedef InputEventType<EventDouble3> InEventDouble3;
typedef InputEventType<EventDouble4> InEventDouble4;

typedef vector<InEventInt0> VecInEventInt0;
typedef vector<InEventInt1> VecInEventInt1;
typedef vector<InEventInt2> VecInEventInt2;
typedef vector<InEventInt3> VecInEventInt3;
typedef vector<InEventInt4> VecInEventInt4;

typedef vector<InEventLong0> VecInEventLong0;
typedef vector<InEventLong1> VecInEventLong1;
typedef vector<InEventLong2> VecInEventLong2;
typedef vector<InEventLong3> VecInEventLong3;
typedef vector<InEventLong4> VecInEventLong4;

typedef vector<InEventFloat0> VecInEventFloat0;
typedef vector<InEventFloat1> VecInEventFloat1;
typedef vector<InEventFloat2> VecInEventFloat2;
typedef vector<InEventFloat3> VecInEventFloat3;
typedef vector<InEventFloat4> VecInEventFloat4;

typedef vector<InEventDouble0> VecInEventDouble0;
typedef vector<InEventDouble1> VecInEventDouble1;
typedef vector<InEventDouble2> VecInEventDouble2;
typedef vector<InEventDouble3> VecInEventDouble3;
typedef vector<InEventDouble4> VecInEventDouble4;

typedef list<InEventInt0> ListInEventInt0;
typedef list<InEventInt1> ListInEventInt1;
typedef list<InEventInt2> ListInEventInt2;
typedef list<InEventInt3> ListInEventInt3;
typedef list<InEventInt4> ListInEventInt4;

typedef list<InEventLong0> ListInEventLong0;
typedef list<InEventLong1> ListInEventLong1;
typedef list<InEventLong2> ListInEventLong2;
typedef list<InEventLong3> ListInEventLong3;
typedef list<InEventLong4> ListInEventLong4;

typedef list<InEventFloat0> ListInEventFloat0;
typedef list<InEventFloat1> ListInEventFloat1;
typedef list<InEventFloat2> ListInEventFloat2;
typedef list<InEventFloat3> ListInEventFloat3;
typedef list<InEventFloat4> ListInEventFloat4;

typedef list<InEventDouble0> ListInEventDouble0;
typedef list<InEventDouble1> ListInEventDouble1;
typedef list<InEventDouble2> ListInEventDouble2;
typedef list<InEventDouble3> ListInEventDouble3;
typedef list<InEventDouble4> ListInEventDouble4;

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



template void SimulationResults::write_inputevents_byobjects<VecInEventInt0::iterator>( const std::string& , int , const std::string&, VecInEventInt0::iterator, VecInEventInt0::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<VecInEventInt1::iterator>( const std::string& , int , const std::string&, VecInEventInt1::iterator, VecInEventInt1::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<VecInEventInt2::iterator>( const std::string& , int , const std::string&, VecInEventInt2::iterator, VecInEventInt2::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<VecInEventInt3::iterator>( const std::string& , int , const std::string&, VecInEventInt3::iterator, VecInEventInt3::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<VecInEventInt4::iterator>( const std::string& , int , const std::string&, VecInEventInt4::iterator, VecInEventInt4::iterator, const TagList&);

template void SimulationResults::write_inputevents_byobjects<VecInEventLong0::iterator>( const std::string& , int , const std::string&, VecInEventLong0::iterator, VecInEventLong0::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<VecInEventLong1::iterator>( const std::string& , int , const std::string&, VecInEventLong1::iterator, VecInEventLong1::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<VecInEventLong2::iterator>( const std::string& , int , const std::string&, VecInEventLong2::iterator, VecInEventLong2::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<VecInEventLong3::iterator>( const std::string& , int , const std::string&, VecInEventLong3::iterator, VecInEventLong3::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<VecInEventLong4::iterator>( const std::string& , int , const std::string&, VecInEventLong4::iterator, VecInEventLong4::iterator, const TagList&);

template void SimulationResults::write_inputevents_byobjects<VecInEventFloat0::iterator>( const std::string& , int , const std::string&, VecInEventFloat0::iterator, VecInEventFloat0::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<VecInEventFloat1::iterator>( const std::string& , int , const std::string&, VecInEventFloat1::iterator, VecInEventFloat1::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<VecInEventFloat2::iterator>( const std::string& , int , const std::string&, VecInEventFloat2::iterator, VecInEventFloat2::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<VecInEventFloat3::iterator>( const std::string& , int , const std::string&, VecInEventFloat3::iterator, VecInEventFloat3::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<VecInEventFloat4::iterator>( const std::string& , int , const std::string&, VecInEventFloat4::iterator, VecInEventFloat4::iterator, const TagList&);

template void SimulationResults::write_inputevents_byobjects<VecInEventDouble0::iterator>( const std::string& , int , const std::string&, VecInEventDouble0::iterator, VecInEventDouble0::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<VecInEventDouble1::iterator>( const std::string& , int , const std::string&, VecInEventDouble1::iterator, VecInEventDouble1::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<VecInEventDouble2::iterator>( const std::string& , int , const std::string&, VecInEventDouble2::iterator, VecInEventDouble2::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<VecInEventDouble3::iterator>( const std::string& , int , const std::string&, VecInEventDouble3::iterator, VecInEventDouble3::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<VecInEventDouble4::iterator>( const std::string& , int , const std::string&, VecInEventDouble4::iterator, VecInEventDouble4::iterator, const TagList&);


template void SimulationResults::write_inputevents_byobjects<ListInEventInt0::iterator>( const std::string& , int , const std::string&, ListInEventInt0::iterator, ListInEventInt0::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<ListInEventInt1::iterator>( const std::string& , int , const std::string&, ListInEventInt1::iterator, ListInEventInt1::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<ListInEventInt2::iterator>( const std::string& , int , const std::string&, ListInEventInt2::iterator, ListInEventInt2::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<ListInEventInt3::iterator>( const std::string& , int , const std::string&, ListInEventInt3::iterator, ListInEventInt3::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<ListInEventInt4::iterator>( const std::string& , int , const std::string&, ListInEventInt4::iterator, ListInEventInt4::iterator, const TagList&);

template void SimulationResults::write_inputevents_byobjects<ListInEventLong0::iterator>( const std::string& , int , const std::string&, ListInEventLong0::iterator, ListInEventLong0::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<ListInEventLong1::iterator>( const std::string& , int , const std::string&, ListInEventLong1::iterator, ListInEventLong1::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<ListInEventLong2::iterator>( const std::string& , int , const std::string&, ListInEventLong2::iterator, ListInEventLong2::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<ListInEventLong3::iterator>( const std::string& , int , const std::string&, ListInEventLong3::iterator, ListInEventLong3::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<ListInEventLong4::iterator>( const std::string& , int , const std::string&, ListInEventLong4::iterator, ListInEventLong4::iterator, const TagList&);

template void SimulationResults::write_inputevents_byobjects<ListInEventFloat0::iterator>( const std::string& , int , const std::string&, ListInEventFloat0::iterator, ListInEventFloat0::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<ListInEventFloat1::iterator>( const std::string& , int , const std::string&, ListInEventFloat1::iterator, ListInEventFloat1::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<ListInEventFloat2::iterator>( const std::string& , int , const std::string&, ListInEventFloat2::iterator, ListInEventFloat2::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<ListInEventFloat3::iterator>( const std::string& , int , const std::string&, ListInEventFloat3::iterator, ListInEventFloat3::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<ListInEventFloat4::iterator>( const std::string& , int , const std::string&, ListInEventFloat4::iterator, ListInEventFloat4::iterator, const TagList&);

template void SimulationResults::write_inputevents_byobjects<ListInEventDouble0::iterator>( const std::string& , int , const std::string&, ListInEventDouble0::iterator, ListInEventDouble0::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<ListInEventDouble1::iterator>( const std::string& , int , const std::string&, ListInEventDouble1::iterator, ListInEventDouble1::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<ListInEventDouble2::iterator>( const std::string& , int , const std::string&, ListInEventDouble2::iterator, ListInEventDouble2::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<ListInEventDouble3::iterator>( const std::string& , int , const std::string&, ListInEventDouble3::iterator, ListInEventDouble3::iterator, const TagList&);
template void SimulationResults::write_inputevents_byobjects<ListInEventDouble4::iterator>( const std::string& , int , const std::string&, ListInEventDouble4::iterator, ListInEventDouble4::iterator, const TagList&);







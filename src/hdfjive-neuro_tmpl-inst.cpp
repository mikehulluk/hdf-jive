

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







 // Simple, a pointer to an array of spike-times:
//template void SimulationResults::write_outputeventsNEW<typename TIMEDATATYPE>( const std::string&, int index, const std::string& record_name, size_t n_events, TIMEDATATYPE*, const TagList& tags);


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


template void SimulationResults::write_outputeventsNEW<VecEventInt0::iterator>( const std::string& , int , const std::string& , VecEventInt0::iterator , VecEventInt0::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<VecEventInt1::iterator>( const std::string& , int , const std::string& , VecEventInt1::iterator , VecEventInt1::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<VecEventInt2::iterator>( const std::string& , int , const std::string& , VecEventInt2::iterator , VecEventInt2::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<VecEventInt3::iterator>( const std::string& , int , const std::string& , VecEventInt3::iterator , VecEventInt3::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<VecEventInt4::iterator>( const std::string& , int , const std::string& , VecEventInt4::iterator , VecEventInt4::iterator , const TagList& );

template void SimulationResults::write_outputeventsNEW<VecEventLong0::iterator>( const std::string& , int , const std::string& , VecEventLong0::iterator , VecEventLong0::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<VecEventLong1::iterator>( const std::string& , int , const std::string& , VecEventLong1::iterator , VecEventLong1::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<VecEventLong2::iterator>( const std::string& , int , const std::string& , VecEventLong2::iterator , VecEventLong2::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<VecEventLong3::iterator>( const std::string& , int , const std::string& , VecEventLong3::iterator , VecEventLong3::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<VecEventLong4::iterator>( const std::string& , int , const std::string& , VecEventLong4::iterator , VecEventLong4::iterator , const TagList& );

template void SimulationResults::write_outputeventsNEW<VecEventFloat0::iterator>( const std::string& , int , const std::string& , VecEventFloat0::iterator , VecEventFloat0::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<VecEventFloat1::iterator>( const std::string& , int , const std::string& , VecEventFloat1::iterator , VecEventFloat1::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<VecEventFloat2::iterator>( const std::string& , int , const std::string& , VecEventFloat2::iterator , VecEventFloat2::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<VecEventFloat3::iterator>( const std::string& , int , const std::string& , VecEventFloat3::iterator , VecEventFloat3::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<VecEventFloat4::iterator>( const std::string& , int , const std::string& , VecEventFloat4::iterator , VecEventFloat4::iterator , const TagList& );

template void SimulationResults::write_outputeventsNEW<VecEventDouble0::iterator>( const std::string& , int , const std::string& , VecEventDouble0::iterator , VecEventDouble0::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<VecEventDouble1::iterator>( const std::string& , int , const std::string& , VecEventDouble1::iterator , VecEventDouble1::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<VecEventDouble2::iterator>( const std::string& , int , const std::string& , VecEventDouble2::iterator , VecEventDouble2::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<VecEventDouble3::iterator>( const std::string& , int , const std::string& , VecEventDouble3::iterator , VecEventDouble3::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<VecEventDouble4::iterator>( const std::string& , int , const std::string& , VecEventDouble4::iterator , VecEventDouble4::iterator , const TagList& );


template void SimulationResults::write_outputeventsNEW<ListEventInt0::iterator>( const std::string& , int , const std::string& , ListEventInt0::iterator , ListEventInt0::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<ListEventInt1::iterator>( const std::string& , int , const std::string& , ListEventInt1::iterator , ListEventInt1::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<ListEventInt2::iterator>( const std::string& , int , const std::string& , ListEventInt2::iterator , ListEventInt2::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<ListEventInt3::iterator>( const std::string& , int , const std::string& , ListEventInt3::iterator , ListEventInt3::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<ListEventInt4::iterator>( const std::string& , int , const std::string& , ListEventInt4::iterator , ListEventInt4::iterator , const TagList& );

template void SimulationResults::write_outputeventsNEW<ListEventLong0::iterator>( const std::string& , int , const std::string& , ListEventLong0::iterator , ListEventLong0::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<ListEventLong1::iterator>( const std::string& , int , const std::string& , ListEventLong1::iterator , ListEventLong1::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<ListEventLong2::iterator>( const std::string& , int , const std::string& , ListEventLong2::iterator , ListEventLong2::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<ListEventLong3::iterator>( const std::string& , int , const std::string& , ListEventLong3::iterator , ListEventLong3::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<ListEventLong4::iterator>( const std::string& , int , const std::string& , ListEventLong4::iterator , ListEventLong4::iterator , const TagList& );

template void SimulationResults::write_outputeventsNEW<ListEventFloat0::iterator>( const std::string& , int , const std::string& , ListEventFloat0::iterator , ListEventFloat0::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<ListEventFloat1::iterator>( const std::string& , int , const std::string& , ListEventFloat1::iterator , ListEventFloat1::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<ListEventFloat2::iterator>( const std::string& , int , const std::string& , ListEventFloat2::iterator , ListEventFloat2::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<ListEventFloat3::iterator>( const std::string& , int , const std::string& , ListEventFloat3::iterator , ListEventFloat3::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<ListEventFloat4::iterator>( const std::string& , int , const std::string& , ListEventFloat4::iterator , ListEventFloat4::iterator , const TagList& );

template void SimulationResults::write_outputeventsNEW<ListEventDouble0::iterator>( const std::string& , int , const std::string& , ListEventDouble0::iterator , ListEventDouble0::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<ListEventDouble1::iterator>( const std::string& , int , const std::string& , ListEventDouble1::iterator , ListEventDouble1::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<ListEventDouble2::iterator>( const std::string& , int , const std::string& , ListEventDouble2::iterator , ListEventDouble2::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<ListEventDouble3::iterator>( const std::string& , int , const std::string& , ListEventDouble3::iterator , ListEventDouble3::iterator , const TagList& );
template void SimulationResults::write_outputeventsNEW<ListEventDouble4::iterator>( const std::string& , int , const std::string& , ListEventDouble4::iterator , ListEventDouble4::iterator , const TagList& );











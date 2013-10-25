

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

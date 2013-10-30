

#ifndef __HDFJIVE_BUFFERS_GUARD_H__
#define __HDFJIVE_BUFFERS_GUARD_H__


/*
template<typename T>
class DataBuffer1D
{
public:
    vector<T> _data;

    inline T* get_data_pointer() {  return &(this->_data[0]); }
    inline const T* get_data_pointer() const {  return &(this->_data[0]); }
    inline size_t size() const { return this->_data.size(); }

    inline void push(const T& o){ _data.push_back(o); }

    DataBuffer1D( ) {}

    // Initialise from pointers:
    DataBuffer1D( const T* data, size_t size) : _data(data, data+size)  {}
    DataBuffer1D( const std::vector<T>& data) : _data(data)  {}
    
    template<int N>
    static DataBuffer1D<T> from_array( std::array<T,N> data){ return DataBuffer1D(&data[0], N); }


};



// Types of buffers:
typedef DataBuffer1D<float> FloatBuffer1D;
typedef DataBuffer1D<int> IntBuffer1D;

// Synaptic sugar:2
typedef FloatBuffer1D FB;
typedef IntBuffer1D IB;
*/



#endif

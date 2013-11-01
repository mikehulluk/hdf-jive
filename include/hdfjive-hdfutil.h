
#ifndef __HDFJIVE_UTIL_GUARD_H__
#define __HDFJIVE_UTIL_GUARD_H__

#include <hdf5.h>
#include <hdf5_hl.h>

#include <string>



// Utility class for converting between <int,float> to <H5T_NATIVE_INT, H5T_NATIVE_FLOAT>
template<typename T>
struct CPPTypeToHDFType
{ };
template<> struct CPPTypeToHDFType<int> { static hid_t get_hdf_type() { return H5T_NATIVE_INT; }  };
template<> struct CPPTypeToHDFType<long> { static hid_t get_hdf_type() { return H5T_NATIVE_LONG; }  };
template<> struct CPPTypeToHDFType<float> { static hid_t get_hdf_type() { return H5T_NATIVE_FLOAT; }  };
template<> struct CPPTypeToHDFType<double> { static hid_t get_hdf_type() { return H5T_NATIVE_DOUBLE; }  };
template<> struct CPPTypeToHDFType<unsigned long> { static hid_t get_hdf_type() { return H5T_NATIVE_ULONG; }  };




namespace hdfjive
{
namespace util    
{

    void add_attribute(hid_t dataset_id, const std::string& name, const std::string& value);

    void add_attribute(hid_t dataset_id, const std::string& name, int value);
    void add_attribute(hid_t dataset_id, const std::string& name, long value);
    void add_attribute(hid_t dataset_id, const std::string& name, float value);
    void add_attribute(hid_t dataset_id, const std::string& name, double value);
    void add_attribute(hid_t dataset_id, const std::string& name, size_t value);
    
   
}

}
#endif

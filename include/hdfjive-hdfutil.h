
#ifndef __HDFJIVE_UTIL_GUARD_H__
#define __HDFJIVE_UTIL_GUARD_H__

#include <hdf5.h>
#include <hdf5_hl.h>

#include <string>


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

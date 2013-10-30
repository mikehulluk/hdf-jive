
#include <hdf5.h>
#include <hdf5_hl.h>

#include <string>
#include <iostream>

using namespace std;

#include <hdfjive-hdfutil.h>



void hdfjive::util::add_attribute(hid_t dataset_id, const std::string& name, const std::string& value)
{
        H5LTset_attribute_string(dataset_id, ".",  name.c_str(),value.c_str() );
}


void hdfjive::util::add_attribute(hid_t dataset_id, const std::string& name, int value)
{
    H5LTset_attribute_int(dataset_id, ".",  name.c_str(), &value, 1 );
}


void hdfjive::util::add_attribute(hid_t dataset_id, const std::string& name, long value)
{
    H5LTset_attribute_long(dataset_id, ".",  name.c_str(), &value, 1 );
}

void hdfjive::util::add_attribute(hid_t dataset_id, const std::string& name, float value)
{
    H5LTset_attribute_float(dataset_id, ".",  name.c_str(), &value, 1 );
}


void hdfjive::util::add_attribute(hid_t dataset_id, const std::string& name, double value)
{
    H5LTset_attribute_double(dataset_id, ".",  name.c_str(), &value, 1 );
}

void hdfjive::util::add_attribute(hid_t dataset_id, const std::string& name, size_t value)
{
    H5LTset_attribute_ulong(dataset_id, ".",  name.c_str(), &value, 1 );
}


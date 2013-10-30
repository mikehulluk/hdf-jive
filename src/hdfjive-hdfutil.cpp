
#include <hdf5.h>
#include <hdf5_hl.h>

#include <string>
#include <iostream>

using namespace std;

#include <hdfjive-hdfutil.h>

 void hdfjive::util::add_attribute(hid_t dataset_id, const std::string& name, const std::string& value_in, bool allow_override)
    {
        if( H5Aexists_by_name(dataset_id, ".", name.c_str(), H5P_DEFAULT ) )
        {
            cout << "Attribute Exists - deleting" << "\n";
            H5Adelete_by_name(dataset_id, ".", name.c_str(), H5P_DEFAULT );
        }

        
        std::string value = value_in;
        if( value.size() == 0)
        {
            value = " ";
        }
        
        hid_t datatype_id = H5Tcopy (H5T_C_S1);
        H5Tset_size (datatype_id, value.size());
        hid_t space=H5Screate(H5S_SCALAR);
        hid_t attr_id = H5Acreate2(dataset_id, name.c_str(), datatype_id, space, H5P_DEFAULT, H5P_DEFAULT);

        H5Awrite(attr_id, datatype_id,  value.c_str());
        

        // Close up:
        H5Aclose(attr_id);
        H5Sclose(space);
    }
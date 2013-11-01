


#include "hdfjive.h"
#include "hdfjive-datasets.h"


HDF5DataSet2DStd::HDF5DataSet2DStd( const string& name, HDF5GroupPtrWeak pParent, const HDF5DataSet2DStdSettings& settings)
    :length(0), name(name), pParent(pParent), settings(settings)
{
    hsize_t data_dims[2] = {0, settings.size};
    hsize_t data_max_dims[2] = {H5S_UNLIMITED, settings.size} ;
    dataspace_id = H5Screate_simple(2, data_dims, data_max_dims);

    // Setup properties:
    hid_t prop = H5Pcreate(H5P_DATASET_CREATE);

    // -- chunking:
    hsize_t chunk_dims[2] = {50, settings.size};
    //hsize_t chunk_dims[2] = {21, settings.size};
    H5Pset_chunk (prop, 2, chunk_dims);
    
    // -- compression:
    H5Pset_deflate( prop, 6);

    dataset_id = H5Dcreate2 (pParent.lock()->group_id, name.c_str(), settings.type, dataspace_id, H5P_DEFAULT, prop, H5P_DEFAULT);
    H5Pclose (prop);
}




HDF5DataSet2DStd::~HDF5DataSet2DStd()
{
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);
}

std::string HDF5DataSet2DStd::get_fullname() const
{
    return pParent.lock()->get_fullname() + "/" + name;
}



size_t HDF5DataSet2DStd::get_length() const
{
    return length;
}

























HDF5DataSet1DStd::HDF5DataSet1DStd( const string& name, HDF5GroupPtrWeak pParent, const HDF5DataSet1DStdSettings& settings)
    : length(0), name(name), pParent(pParent), settings(settings)
{
    hsize_t data_dims[1] = {0};
    hsize_t data_max_dims[1] = {H5S_UNLIMITED} ;
    dataspace_id = H5Screate_simple(1, data_dims, data_max_dims);

    // Dataset properties:
    hid_t prop = H5Pcreate(H5P_DATASET_CREATE);
    
    // -- chunking:
    hsize_t chunk_dims[1] = {50};
    //hsize_t chunk_dims[1] = {21}; 
    H5Pset_chunk (prop, 1, chunk_dims);

    // -- compression:
    H5Pset_deflate( prop, 6); 

    dataset_id = H5Dcreate2 (pParent.lock()->group_id, name.c_str(), settings.type, dataspace_id, H5P_DEFAULT, prop, H5P_DEFAULT);
    H5Pclose (prop);
}




HDF5DataSet1DStd::~HDF5DataSet1DStd()
{
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);
}

std::string HDF5DataSet1DStd::get_fullname() const
{
    return pParent.lock()->get_fullname() + "/" + name;
}





size_t HDF5DataSet1DStd::get_length() const
{
    return length;
}



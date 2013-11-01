
#ifndef __HDFJIVE_DATASET_GUARD_H__
#define __HDFJIVE_DATASET_GUARD_H__










class HDF5DataSet1DStdSettings
{
public:

    const hid_t type; // H5T_NATIVE_CHAR, H5T_NATIVE_SHORT, H5T_NATIVE_INT, H5T_NATIVE_LONG, H5T_NATIVE_FLOAT
    HDF5DataSet1DStdSettings(hid_t type)
        : type(type) {}
};


class HDF5DataSet2DStdSettings
{
public:
    const size_t size;
    const hid_t type; // H5T_NATIVE_CHAR, H5T_NATIVE_SHORT, H5T_NATIVE_INT, H5T_NATIVE_LONG, H5T_NATIVE_FLOAT
    HDF5DataSet2DStdSettings(hid_t type, size_t size)
        : size(size), type(type) {}
};




















class HDF5DataSetAbstr
{
    hid_t dataset_id;
    hid_t dataspace_id;

}







class HDF5DataSet1DStd : public  boost::enable_shared_from_this<HDF5DataSet1DStd>
{
    hid_t dataset_id;
    hid_t dataspace_id;
    size_t length;

public:
    const string name;
    HDF5GroupPtrWeak pParent;
    HDF5DataSet1DStdSettings settings;

    HDF5DataSet1DStd( const string& name, HDF5GroupPtrWeak pParent, const HDF5DataSet1DStdSettings& settings);
    ~HDF5DataSet1DStd();


    template<typename T>
    inline
    void append(T dataelement)
    {
        hid_t hdf5type = CPPTypeToHDFType<T>::get_hdf_type();
        assert(settings.type==hdf5type);

        // How big is the array:?
        hsize_t dims[1], max_dims[1];
        hid_t dataspace = H5Dget_space(dataset_id);
        H5Sget_simple_extent_dims(dataspace, dims, max_dims);
        H5Sclose(dataspace);

        hsize_t curr_size = dims[0];
        assert( curr_size == this->length() );

        // Extend the table:
        hsize_t new_data_dims[1] = {curr_size+1};
        H5Dextend (dataset_id, new_data_dims);

        // And copy:
        hid_t filespace = H5Dget_space(dataset_id);
        hsize_t offset[1] = {curr_size};
        hsize_t count[1] = {1};
        H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offset, NULL, count, NULL);
        hsize_t dim1[1] = {1};
        hid_t memspace = H5Screate_simple(1, dim1, NULL);
        H5Dwrite (dataset_id, hdf5type, memspace, filespace, H5P_DEFAULT, &dataelement);

        // Clean up the handles:
        H5Sclose(memspace);
        H5Sclose(filespace);

        this->length = new_data_dims[0];

    }


    template<typename T>
    inline
    void set_data(size_t N, const T* pData)
    {
        // Is the datatype consistent?
        hid_t hdf5type = CPPTypeToHDFType<T>::get_hdf_type();
        assert(settings.type==hdf5type);

        // Extend the table:
        hsize_t new_data_dims[1] = {N};
        H5Dextend (dataset_id, new_data_dims);

        // And copy:
        hid_t filespace = H5Dget_space(dataset_id);
        hsize_t offset[1] = {0};
        hsize_t count[1] = {N};
        H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offset, NULL, count, NULL);
        hsize_t dim1[1] = {N};
        hid_t memspace = H5Screate_simple(1, dim1, NULL);
        H5Dwrite (dataset_id, hdf5type, memspace, filespace, H5P_DEFAULT, pData);

        // Clean up the handles:
        H5Sclose(memspace);
        H5Sclose(filespace);

        // Store the length:
        length = N;

    }

    std::string get_fullname() const;
    size_t get_length() const;

    void set_scaling_factor(double scaling_factor)
    {
        hdfjive::util::add_attribute(dataset_id,  "hdfjive:scaling", scaling_factor);
    }
};




class HDF5DataSet2DStd : public  boost::enable_shared_from_this<HDF5DataSet2DStd>
{
    hid_t dataset_id;
    hid_t dataspace_id;
    size_t length;

public:
    const string name;
    HDF5GroupPtrWeak pParent;
    HDF5DataSet2DStdSettings settings;

    HDF5DataSet2DStd( const string& name, HDF5GroupPtrWeak pParent, const HDF5DataSet2DStdSettings& settings);
    ~HDF5DataSet2DStd();

    // For the different datatypes:
    // The pointer should point to a block of memory  of length settings.size

    template<typename T>
    inline
    void append_buffer( const T* pData )
    {
        hid_t hdf5type = CPPTypeToHDFType<T>::get_hdf_type();
        assert(settings.type==hdf5type);

        // How big is the array:?
        hsize_t dims[2], max_dims[2];
        hid_t dataspace = H5Dget_space(dataset_id);
        H5Sget_simple_extent_dims(dataspace, dims, max_dims);
        H5Sclose(dataspace);

        assert(dims[1] == settings.size);

        hsize_t curr_size = dims[0];
        assert( curr_size == this->length() );

        // Extend the table:
        hsize_t new_data_dims[2] = {curr_size+1, dims[1] };
        H5Dextend (dataset_id, new_data_dims);

        // And copy:
        hid_t filespace = H5Dget_space(dataset_id);
        hsize_t offset[2] = {curr_size, 0};
        hsize_t count[2] = {1, dims[1]};
        H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offset, NULL, count, NULL);
        hsize_t dim1[2] = {1,dims[1]};
        hid_t memspace = H5Screate_simple(2, dim1, NULL);
        H5Dwrite (dataset_id, hdf5type, memspace, filespace, H5P_DEFAULT, pData);

        H5Sclose(memspace);
        H5Sclose(filespace);


        // Save the new length:
        this->length = new_data_dims[0];
    }



    template<typename T>
    inline
    void set_data(size_t M, size_t N, const T* pData)
    {
        hid_t hdf5type = CPPTypeToHDFType<T>::get_hdf_type();
        assert(settings.type==hdf5type);
        assert(N==settings.size);

        // Extend the table:
        hsize_t new_data_dims[2] = {M,N};
        H5Dextend (dataset_id, new_data_dims);
        // And copy:
        hid_t filespace = H5Dget_space(dataset_id);
        hsize_t offset[2] = {0, 0};
        hsize_t count[2] = {M, N};
        H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offset, NULL, count, NULL);
        hsize_t dim1[2] = {M,N};
        hid_t memspace = H5Screate_simple(2, dim1, NULL);
        H5Dwrite (dataset_id, hdf5type, memspace, filespace, H5P_DEFAULT, pData);

        H5Sclose(memspace);
        H5Sclose(filespace);


        this->length = M;
    }




    std::string get_fullname() const;
    size_t get_length() const;


   void set_scaling_factor(double scaling_factor)
    {
        hdfjive::util::add_attribute(dataset_id,  "hdfjive:scaling", scaling_factor);
    }
};







#endif

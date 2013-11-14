
#ifndef __HDFJIVE_DATASET_GUARD_H__
#define __HDFJIVE_DATASET_GUARD_H__



//Standard libraries:

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include "boost/optional/optional.hpp" 
#include <boost/enable_shared_from_this.hpp>



// Forward declare classes:
class HDF5DataSet1DStdSettings;
class HDF5DataSet2DStdSettings;
class HDF5DataSet1DStd;
class HDF5DataSet2DStd;

typedef boost::shared_ptr<HDF5DataSet2DStd> HDF5DataSet2DStdPtr;
typedef boost::shared_ptr<HDF5DataSet1DStd> HDF5DataSet1DStdPtr;




// HDFjive includes:
#include "hdfjive-hdfutil.h"
#include "hdfjive-core.h"





template<typename T>
struct HDF5DataSetStdSettingsAbstr
{
    const hid_t type; // H5T_NATIVE_CHAR, H5T_NATIVE_SHORT, H5T_NATIVE_INT, H5T_NATIVE_LONG, H5T_NATIVE_FLOAT

    size_t chunksize;
    boost::optional<int> compression_level;
    
    HDF5DataSetStdSettingsAbstr(hid_t type)
    :   type(type),
        chunksize(50)
    {}


    // Allow chainable method calls:
    T& set_compression_level(int compression_level) { this->compression_level = compression_level; return *this; }
    T& set_chunksize(size_t chunksize) { this->chunksize = chunksize; return *this; }
};


class HDF5DataSet1DStdSettings : public  HDF5DataSetStdSettingsAbstr<HDF5DataSet1DStdSettings>
{
public:
    HDF5DataSet1DStdSettings(hid_t type)
        : HDF5DataSetStdSettingsAbstr(type) {}
};


class HDF5DataSet2DStdSettings : public HDF5DataSetStdSettingsAbstr<HDF5DataSet2DStdSettings>
{
public:
    const size_t size;
    HDF5DataSet2DStdSettings(hid_t type, size_t size)
        : HDF5DataSetStdSettingsAbstr(type), size(size) {}
};




















struct HDF5DataSetAbstr
{

    boost::optional<hid_t> dataspace_id;
    boost::optional<hid_t> dataset_id;
    
    const std::string name;
    HDF5GroupPtrWeak pParent;

    HDF5DataSetAbstr( const std::string& name, HDF5GroupPtrWeak pParent );
    ~HDF5DataSetAbstr();

    std::string get_fullname() const;
    void set_scaling_factor(double scaling_factor);


    void _set_length(size_t);
    size_t get_length() const;

private:
    size_t _length;
};







class HDF5DataSet1DStd : public  boost::enable_shared_from_this<HDF5DataSet1DStd>, public HDF5DataSetAbstr
{

public:
    
    
    HDF5DataSet1DStdSettings settings;

    HDF5DataSet1DStd( const std::string& name, HDF5GroupPtrWeak pParent, const HDF5DataSet1DStdSettings& settings);
    //~HDF5DataSet1DStd();

    
    template<typename T>
    inline
    void append(T dataelement)
    {
        hid_t hdf5type = hdfjive::util::CPPTypeToHDFType<T>::get_hdf_type();
        assert(settings.type==hdf5type);

        // How big is the array:?
        hsize_t dims[1], max_dims[1];
        hid_t dataspace = H5Dget_space(*dataset_id);
        H5Sget_simple_extent_dims(dataspace, dims, max_dims);
        H5Sclose(dataspace);

        hsize_t curr_size = dims[0];
        assert( curr_size == this->get_length() );

        // Extend the table:
        hsize_t new_data_dims[1] = {curr_size+1};
        H5Dextend (*dataset_id, new_data_dims);

        // And copy:
        hid_t filespace = H5Dget_space(*dataset_id);
        hsize_t offset[1] = {curr_size};
        hsize_t count[1] = {1};
        H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offset, NULL, count, NULL);
        hsize_t dim1[1] = {1};
        hid_t memspace = H5Screate_simple(1, dim1, NULL);
        H5Dwrite (dataset_id, hdf5type, memspace, filespace, H5P_DEFAULT, &dataelement);

        // Clean up the handles:
        H5Sclose(memspace);
        H5Sclose(filespace);

        //this->length = new_data_dims[0];
        this->_set_length(new_data_dims[0]);

        // Flush the caches:
        H5Fflush( *dataset_id, H5F_SCOPE_GLOBAL);
    }


    template<typename T>
    inline
    void set_data(size_t N, const T* pData)
    {
        // Is the datatype consistent?
        hid_t hdf5type = hdfjive::util::CPPTypeToHDFType<T>::get_hdf_type();
        assert(settings.type==hdf5type);

        // Extend the table:
        hsize_t new_data_dims[1] = {N};
        H5Dextend (*dataset_id, new_data_dims);

        // And copy:
        hid_t filespace = H5Dget_space(*dataset_id);
        hsize_t offset[1] = {0};
        hsize_t count[1] = {N};
        H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offset, NULL, count, NULL);
        hsize_t dim1[1] = {N};
        hid_t memspace = H5Screate_simple(1, dim1, NULL);
        H5Dwrite (*dataset_id, hdf5type, memspace, filespace, H5P_DEFAULT, pData);

        // Clean up the handles:
        H5Sclose(memspace);
        H5Sclose(filespace);

        // Store the length:
        this->_set_length(N);

        // Flush the caches:
        H5Fflush( *dataset_id, H5F_SCOPE_GLOBAL);
    }

};




class HDF5DataSet2DStd : public  boost::enable_shared_from_this<HDF5DataSet2DStd>, public HDF5DataSetAbstr
{

public:
    
    HDF5DataSet2DStdSettings settings;

    HDF5DataSet2DStd( const std::string& name, HDF5GroupPtrWeak pParent, const HDF5DataSet2DStdSettings& settings);
    //~HDF5DataSet2DStd();

    // For the different datatypes:
    // The pointer should point to a block of memory  of length settings.size

    template<typename T>
    inline
    void append_buffer( const T* pData )
    {
        hid_t hdf5type = hdfjive::util::CPPTypeToHDFType<T>::get_hdf_type();
        assert(settings.type==hdf5type);

        // How big is the array:?
        hsize_t dims[2], max_dims[2];
        hid_t dataspace = H5Dget_space(*dataset_id);
        H5Sget_simple_extent_dims(dataspace, dims, max_dims);
        H5Sclose(dataspace);

        assert(dims[1] == settings.size);

        hsize_t curr_size = dims[0];
        assert( curr_size == this->get_length() );

        // Extend the table:
        hsize_t new_data_dims[2] = {curr_size+1, dims[1] };
        H5Dextend (*dataset_id, new_data_dims);

        // And copy:
        hid_t filespace = H5Dget_space(*dataset_id);
        hsize_t offset[2] = {curr_size, 0};
        hsize_t count[2] = {1, dims[1]};
        H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offset, NULL, count, NULL);
        hsize_t dim1[2] = {1,dims[1]};
        hid_t memspace = H5Screate_simple(2, dim1, NULL);
        H5Dwrite (dataset_id, hdf5type, memspace, filespace, H5P_DEFAULT, pData);

        H5Sclose(memspace);
        H5Sclose(filespace);

        // Save the new length:
        this->_set_length(new_data_dims[0]);

        // Flush the caches:
        H5Fflush( *dataset_id, H5F_SCOPE_GLOBAL);
    }



    template<typename T>
    inline
    void set_data(size_t M, size_t N, const T* pData)
    {
        hid_t hdf5type = hdfjive::util::CPPTypeToHDFType<T>::get_hdf_type();
        assert(settings.type==hdf5type);
        assert(N==settings.size);

        // Extend the table:
        hsize_t new_data_dims[2] = {M,N};
        H5Dextend (*dataset_id, new_data_dims);
        // And copy:
        hid_t filespace = H5Dget_space(*dataset_id);
        hsize_t offset[2] = {0, 0};
        hsize_t count[2] = {M, N};
        H5Sselect_hyperslab(filespace, H5S_SELECT_SET, offset, NULL, count, NULL);
        hsize_t dim1[2] = {M,N};
        hid_t memspace = H5Screate_simple(2, dim1, NULL);
        H5Dwrite (*dataset_id, hdf5type, memspace, filespace, H5P_DEFAULT, pData);

        H5Sclose(memspace);
        H5Sclose(filespace);
        
        //this->length = M;
        this->_set_length(M);

        // Flush the caches:
        H5Fflush( *dataset_id, H5F_SCOPE_GLOBAL);
    }

};







#endif

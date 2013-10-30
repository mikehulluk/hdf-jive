

#ifndef __HDFJIVE_GUARD_H__
#define __HDFJIVE_GUARD_H__

#include "hdf5.h"
#include <hdf5_hl.h>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <boost/enable_shared_from_this.hpp>
using namespace std;



// Signal Errors:
herr_t my_hdf5_error_handler (hid_t estack_id, void *unused);





#include "hdfjive-buffers.h"



// Forward declarations:
class HDF5Group;
class HDF5File;
class HDF5DataSet1DStd;
class HDF5DataSet2DStd;


typedef boost::shared_ptr<HDF5File> HDF5FilePtr;
typedef boost::weak_ptr<HDF5File> HDF5FilePtrWeak;
typedef boost::shared_ptr<HDF5Group> HDF5GroupPtr;
typedef boost::weak_ptr<HDF5Group> HDF5GroupPtrWeak;

typedef boost::shared_ptr<HDF5DataSet2DStd> HDF5DataSet2DStdPtr;
typedef boost::shared_ptr<HDF5DataSet1DStd> HDF5DataSet1DStdPtr;








// Utility class for converting between <int,float> to <H5T_NATIVE_INT, H5T_NATIVE_FLOAT>=
template<typename T>
struct CPPTypeToHDFType
{ };
template<> struct CPPTypeToHDFType<int> { static hid_t get_hdf_type() { return H5T_NATIVE_INT; }  };
template<> struct CPPTypeToHDFType<long> { static hid_t get_hdf_type() { return H5T_NATIVE_LONG; }  };
template<> struct CPPTypeToHDFType<float> { static hid_t get_hdf_type() { return H5T_NATIVE_FLOAT; }  };
template<> struct CPPTypeToHDFType<double> { static hid_t get_hdf_type() { return H5T_NATIVE_DOUBLE; }  };
//template<> struct CPPTypeToHDFType<long unsigned int> { static hid_t get_hdf_type() { return H5T_NATIVE_ULONG; }  };















template<typename T>
size_t _append_to_array_2D(hid_t datatype, const T* pData, size_t n, hid_t dataset_id)
{
 
    // How big is the array:?
    hsize_t dims[2], max_dims[2];
    hid_t dataspace = H5Dget_space(dataset_id);
    H5Sget_simple_extent_dims(dataspace, dims, max_dims);
    H5Sclose(dataspace);

    assert(dims[1] == n);

    hsize_t curr_size = dims[0];

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
    H5Dwrite (dataset_id, datatype, memspace, filespace, H5P_DEFAULT, pData);

    H5Sclose(memspace);
    H5Sclose(filespace);

    // Return the new size:
    return new_data_dims[0];

}





template<typename T>
size_t _write_to_array_2D(hid_t datatype, const T* pData, size_t M, size_t N, hid_t dataset_id)
{
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
    H5Dwrite (dataset_id, datatype, memspace, filespace, H5P_DEFAULT, pData);

    H5Sclose(memspace);
    H5Sclose(filespace);
    return M;
}



















class HDF5DataSet2DStdSettings
{
public:
    const size_t size;
    const hid_t type; // H5T_NATIVE_CHAR, H5T_NATIVE_SHORT, H5T_NATIVE_INT, H5T_NATIVE_LONG, H5T_NATIVE_FLOAT
    HDF5DataSet2DStdSettings(hid_t type, size_t size)
        : size(size), type(type) {}
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
    /*
    void append_buffer( const float* pData );
    void append_buffer( const double* pData );
    void append_buffer( const int* pData );
    void append_buffer( const long* pData );
    */





    inline
    void append_buffer( const float* pData )
    {
        assert(settings.type==H5T_NATIVE_FLOAT);
        length = _append_to_array_2D<float>(H5T_NATIVE_FLOAT, pData, settings.size, dataset_id);
    }

    inline
    void append_buffer( const double* pData )
    {
        assert(settings.type==H5T_NATIVE_DOUBLE);
        length = _append_to_array_2D<double>(H5T_NATIVE_DOUBLE, pData, settings.size, dataset_id);
    }

    inline
    void append_buffer( const int* pData )
    {
        assert(settings.type==H5T_NATIVE_INT);
        length = _append_to_array_2D<int>(H5T_NATIVE_INT, pData, settings.size, dataset_id);
    }

    inline
    void append_buffer( const long* pData )
    {
        assert(settings.type==H5T_NATIVE_FLOAT);
        length = _append_to_array_2D<long>(H5T_NATIVE_LONG, pData, settings.size, dataset_id);
    }













    // Convience methods:
    // ///////////////////////////
    template<typename TYPE>
    inline void append_buffer( DataBuffer1D<TYPE> fb )
    {
        assert(fb.size() == this->settings.size);
        this->append_buffer(fb.get_data_pointer() );
    }

    // Single values:
    template<typename TYPE>
    inline void append_single( TYPE value)
    {
        assert(settings.size==1);
        append_buffer(&value);
    }

    //void set_data(size_t m, size_t n, const double* pData);
    //void set_data(size_t m, size_t n, const float* pData);
    //void set_data(size_t m, size_t n, const int* pData);
    //void set_data(size_t m, size_t n, const long* pData);




    inline
    void set_data(size_t m, size_t n, const float* pData)
    {
        assert(settings.type==H5T_NATIVE_FLOAT);
        assert(n==settings.size);
        length = _write_to_array_2D<float>(H5T_NATIVE_FLOAT, pData, m, n, dataset_id);
    }

    inline
    void set_data(size_t m, size_t n, const double* pData)
    {
        assert(settings.type==H5T_NATIVE_DOUBLE);
        assert(n==settings.size);
        length = _write_to_array_2D<double>(H5T_NATIVE_DOUBLE, pData, m, n, dataset_id);
    }

    inline
    void set_data(size_t m, size_t n, const int* pData)
    {
        assert(settings.type==H5T_NATIVE_INT);
        assert(n==settings.size);
        length = _write_to_array_2D<int>(H5T_NATIVE_INT, pData, m, n, dataset_id);
    }

    inline
    void set_data(size_t m, size_t n, const long* pData)
    {
        assert(settings.type==H5T_NATIVE_LONG);
        assert(n==settings.size);
        length = _write_to_array_2D<long>(H5T_NATIVE_LONG, pData, m, n, dataset_id);
    }









    


    std::string get_fullname() const;

    size_t get_length() const;
};























class HDF5DataSet1DStdSettings
{
public:

    const hid_t type; // H5T_NATIVE_CHAR, H5T_NATIVE_SHORT, H5T_NATIVE_INT, H5T_NATIVE_LONG, H5T_NATIVE_FLOAT
    HDF5DataSet1DStdSettings(hid_t type)
        : type(type) {}
};








template<typename T>
size_t _append_to_array_1D(hid_t datatype, T data, hid_t dataset_id)
{
    // How big is the array:?
    hsize_t dims[1], max_dims[1];
    hid_t dataspace = H5Dget_space(dataset_id);
    H5Sget_simple_extent_dims(dataspace, dims, max_dims);
    H5Sclose(dataspace);

    hsize_t curr_size = dims[0];

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
    H5Dwrite (dataset_id, datatype, memspace, filespace, H5P_DEFAULT, &data);

    H5Sclose(memspace);
    H5Sclose(filespace);

    return new_data_dims[0];
}







template<typename T>
size_t _write_to_array_1D(hid_t datatype, const T* pData, size_t N, hid_t dataset_id)
{
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
    H5Dwrite (dataset_id, datatype, memspace, filespace, H5P_DEFAULT, pData);

    H5Sclose(memspace);
    H5Sclose(filespace);

    return N;
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
        length = _append_to_array_1D<T>(hdf5type, dataelement, dataset_id);
    }


    template<typename T>
    inline
    void set_data(size_t n, const T* pData)
    {
        hid_t hdf5type = CPPTypeToHDFType<T>::get_hdf_type();
        assert(settings.type==hdf5type);
        length = _write_to_array_1D<T>(hdf5type, pData, n, dataset_id);
    }

    /*
    inline
    void set_data(size_t n, const float* pData)
    {
        assert(settings.type==H5T_NATIVE_FLOAT);
        length = _write_to_array_1D<float>(H5T_NATIVE_FLOAT, pData, n, dataset_id);
    }

    inline
    void set_data(size_t n, const double* pData)
    {
        assert(settings.type==H5T_NATIVE_DOUBLE);
        length = _write_to_array_1D<double>(H5T_NATIVE_DOUBLE, pData, n, dataset_id);
    }

    inline
    void set_data(size_t n, const int* pData)
    {
         assert(settings.type==H5T_NATIVE_INT);
        length = _write_to_array_1D<int>(H5T_NATIVE_INT, pData, n, dataset_id);
    }

    inline
    void set_data(size_t n, const long* pData)
    {
        assert(settings.type==H5T_NATIVE_LONG);
        length = _write_to_array_1D<long>(H5T_NATIVE_LONG, pData, n, dataset_id);
    }
    */




    template<typename T>
    void set_data( const DataBuffer1D<T>& buff)
    {
        set_data(buff.size(), buff.get_data_pointer() );
    }

    std::string get_fullname() const;
    size_t get_length() const;
};




class HDF5Group : public boost::enable_shared_from_this<HDF5Group>
{

public:
    const string location;
    hid_t group_id;

    HDF5FilePtrWeak fileptr;
    HDF5GroupPtrWeak pParent;

    bool is_root() const;


public:
    HDF5Group(const string& location,  HDF5FilePtrWeak fileptr,  HDF5GroupPtrWeak parentptr);
    ~HDF5Group();

    typedef map<const string, HDF5GroupPtr> GroupPtrMap;
    GroupPtrMap groups;


    inline HDF5GroupPtr get_group(const string& location) { return get_subgroup(location); }

    // Subgroups:
    HDF5GroupPtr get_subgroup(const string& location);
    HDF5GroupPtr get_subgrouplocal(const string& location);

    // Datasets:
    typedef map<const string, HDF5DataSet1DStdPtr> Dataset1DPtrMap;
    typedef map<const string, HDF5DataSet2DStdPtr> Dataset2DPtrMap;
    Dataset1DPtrMap datasets_1d;
    Dataset2DPtrMap datasets_2d;

    HDF5DataSet1DStdPtr create_empty_dataset1D(const string& name, const HDF5DataSet1DStdSettings& settings);
    HDF5DataSet2DStdPtr create_empty_dataset2D(const string& name, const HDF5DataSet2DStdSettings& settings);



    HDF5DataSet1DStdPtr create_dataset1D(const string& name, const FloatBuffer1D& data);
    HDF5DataSet1DStdPtr create_dataset1D(const string& name, const IntBuffer1D& data);




    HDF5DataSet1DStdPtr get_dataset1D(const string& name);
    HDF5DataSet2DStdPtr get_dataset2D(const string& name);

    // Links:
    void create_softlink(const  HDF5DataSet1DStdPtr& target, const std::string& name);
    void create_softlink(const  HDF5DataSet2DStdPtr& target, const std::string& name);

    std::string get_fullname() const;
    void add_attribute(const string& name, const string& value);


    size_t get_length() const;
};






class HDF5File : public boost::enable_shared_from_this<HDF5File>
{
    HDF5GroupPtr root_group;
public:
    const string filename;
    hid_t file_id;

public:
    HDF5File(const string& filename);
    ~HDF5File();
    void init();


    HDF5GroupPtr get_group(const string& location);
    HDF5DataSet1DStdPtr get_dataset1D(const string& location);
    HDF5DataSet2DStdPtr get_dataset2D(const string& location);
};






class HDFManager
{
    public:
        static HDFManager& getInstance()
        {
            static HDFManager instance;
            return instance;
        }

    private:
        HDFManager(HDFManager const&);     // Don't Implement.
        void operator=(HDFManager const&); // Don't implement


        HDFManager()
        {
            H5Eset_auto2(H5E_DEFAULT, my_hdf5_error_handler, NULL);
        }
        ~HDFManager()
        {
            //cout << "\n~HDFManager:";
        }


    private:

    typedef map<const string, HDF5FilePtr> FilePtrMap;
    FilePtrMap files;


    // Operations:
    public:
    HDF5FilePtr get_file(const string& filename)
    {
        // Create the new file object, if it doesn't exist:
        if( files.find(filename) == files.end() )
        {
            // Create the new file object:
            files[filename] = HDF5FilePtr( new HDF5File(filename) );
        }
        return files[filename];
    }

};




#endif

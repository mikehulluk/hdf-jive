

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












class HDF5DataSet2DStdSettings
{
public:
    const size_t size;
    const hid_t type; // H5T_NATIVE_CHAR, H5T_NATIVE_SHORT, H5T_NATIVE_INT, H5T_NATIVE_LONG, H5T_NATIVE_FLOAT
    HDF5DataSet2DStdSettings(size_t size, hid_t type)
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
    void append_buffer( const float* pData );
    void append_buffer( const double* pData );
    void append_buffer( const int* pData );
    void append_buffer( const long* pData );

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

    void set_data(size_t m, size_t n, const double* pData);
    void set_data(size_t m, size_t n, const float* pData);
    void set_data(size_t m, size_t n, const int* pData);
    void set_data(size_t m, size_t n, const long* pData);
    

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

  
    // Single values:
    void append(int value);
    void append(long value);
    void append(float value);
    void append(double value);
    

    void set_data(size_t n, const double* pData);
    void set_data(size_t n, const float* pData);
    void set_data(size_t n, const int* pData);
    void set_data(size_t n, const long* pData);

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
            cout << "\n~HDFManager:";
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



#ifndef __HDFJIVE_CORE_GUARD_H__
#define __HDFJIVE_CORE_GUARD_H__



// Standard libraries:
// =====================
#include <map>
#include <string>



// Forward declarations:
// =====================
class HDF5Group;
class HDF5File;
class HDFManager;
class HDF5DataSet1DStd;
class HDF5DataSet2DStd;

typedef boost::shared_ptr<HDF5File> HDF5FilePtr;
typedef boost::weak_ptr<HDF5File> HDF5FilePtrWeak;
typedef boost::shared_ptr<HDF5Group> HDF5GroupPtr;
typedef boost::weak_ptr<HDF5Group> HDF5GroupPtrWeak;

herr_t my_hdf5_error_handler (hid_t estack_id, void *unused);  // (Signal Errors:)




#include "hdfjive-datasets.h"






class HDF5Group : public boost::enable_shared_from_this<HDF5Group>
{

public:
    const std::string location;
    hid_t group_id;

    HDF5FilePtrWeak fileptr;
    HDF5GroupPtrWeak pParent;

    bool is_root() const;


public:
    HDF5Group(const std::string& location,  HDF5FilePtrWeak fileptr,  HDF5GroupPtrWeak parentptr);
    ~HDF5Group();

    typedef std::map<const std::string, HDF5GroupPtr> GroupPtrMap;
    GroupPtrMap groups;


    inline HDF5GroupPtr get_group(const std::string& location) { return get_subgroup(location); }

    // Subgroups:
    HDF5GroupPtr get_subgroup(const std::string& location);
    HDF5GroupPtr get_subgrouplocal(const std::string& location);

    // Datasets:
    typedef std::map<const std::string, HDF5DataSet1DStdPtr> Dataset1DPtrMap;
    typedef std::map<const std::string, HDF5DataSet2DStdPtr> Dataset2DPtrMap;
    Dataset1DPtrMap datasets_1d;
    Dataset2DPtrMap datasets_2d;

    HDF5DataSet1DStdPtr create_empty_dataset1D(const std::string& name, const HDF5DataSet1DStdSettings& settings);
    HDF5DataSet2DStdPtr create_empty_dataset2D(const std::string& name, const HDF5DataSet2DStdSettings& settings);

    HDF5DataSet1DStdPtr get_dataset1D(const std::string& name);
    HDF5DataSet2DStdPtr get_dataset2D(const std::string& name);

    // Links:
    void create_softlink(const  HDF5DataSet1DStdPtr& target, const std::string& name);
    void create_softlink(const  HDF5DataSet2DStdPtr& target, const std::string& name);

    std::string get_fullname() const;
    void add_attribute(const std::string& name, const std::string& value);

};






class HDF5File : public boost::enable_shared_from_this<HDF5File>
{
    HDF5GroupPtr root_group;
public:
    const std::string filename;
    hid_t file_id;

public:
    HDF5File(const std::string& filename);
    ~HDF5File();
    void init();


    HDF5GroupPtr get_group(const std::string& location);
    HDF5DataSet1DStdPtr get_dataset1D(const std::string& location);
    HDF5DataSet2DStdPtr get_dataset2D(const std::string& location);
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
        }


    private:

    typedef std::map<const std::string, HDF5FilePtr> FilePtrMap;
    FilePtrMap files;


    // Operations:
    public:
    HDF5FilePtr get_file(const std::string& filename)
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


#include "hdfjive.h"
#include "hdfjive-hdfutil.h"




class _HDF5Location
{
    string location;
    bool _is_absolute;
    public:
        _HDF5Location(const string& location_in)
        {
            string location = location_in;

            if( location[0] == '/')
            {
                location = location.substr(1, location.size() );
                _is_absolute = true;
            }
            else
            {
                _is_absolute = false;
            }


            if( location[location.size()-1] == '/') 
                location = location.substr(0, location.size()-1);

            this->location = location;
        }

        bool is_local() const
        {
            size_t sep_loc = location.find('/');
            return (sep_loc == string::npos);
        }

        bool is_absolute() const
        {
            return _is_absolute;
        }

        string get_local_path() const
        {
            size_t sep_loc = location.find('/');
            return location.substr(0,sep_loc);
        }

        string get_child_path() const
        {
            assert( !is_local() );
            size_t sep_loc = location.find('/');
            return location.substr(sep_loc+1, location.size());
        }
};









void HDF5Group::add_attribute(const string& name, const string& value_in)
{
    return hdfjive::util::add_attribute(group_id, name, value_in);
}


std::string HDF5Group::get_fullname() const
{
    if(is_root())
    {
        return "/";
    }
    else
    {
        return pParent.lock()->get_fullname() + "/" + location;
    }
}



HDF5Group::HDF5Group(const string& location, HDF5FilePtrWeak fileptr,  HDF5GroupPtrWeak parentptr)
    :location(location), fileptr(fileptr), pParent(parentptr)
{

    if( is_root() )
    {
        // Pass
    }
    else
    {
        HDF5GroupPtr parent = parentptr.lock();
        if(parent->is_root() )
        {
            group_id = H5Gcreate2(fileptr.lock()->file_id, location.c_str(), H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        }
        else
        {
            group_id = H5Gcreate2(parent->group_id, location.c_str(), H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
        }
    }

}

HDF5Group::~HDF5Group()
{
    datasets_2d.clear();
    groups.clear();

    if(!is_root())
    {
        H5Gclose(group_id);
    }


}




HDF5GroupPtr HDF5Group::get_subgroup(const string& location_in)
{
    _HDF5Location loc(location_in);

    // Sanity checks:
    if( loc.is_absolute() ) assert(this->is_root() );

    if(loc.is_local())
    {
        return this->get_subgrouplocal(loc.get_local_path());
    }
    else
    {
        return this->get_subgrouplocal(loc.get_local_path())->get_subgroup(loc.get_child_path());
    }

}



HDF5GroupPtr HDF5Group::get_subgrouplocal(const string& location)
{
    assert( location.find("/") == string::npos );

    // Group does not exist:
    if( groups.find(location) == groups.end() )
    {
        fileptr.lock();
        groups[location] = HDF5GroupPtr( new HDF5Group(location, fileptr,  HDF5GroupPtrWeak(shared_from_this()) ) );
    }

    return groups[location];
}



bool HDF5Group::is_root() const
{
    return this->location == "/";
}







HDF5DataSet2DStdPtr HDF5Group::create_empty_dataset2D(const string& name, const HDF5DataSet2DStdSettings& settings)
{
    assert( datasets_2d.find(name) == datasets_2d.end() );
    datasets_2d[name] = HDF5DataSet2DStdPtr( new HDF5DataSet2DStd(name, HDF5GroupPtrWeak(shared_from_this()), settings ) );
    return datasets_2d[name];
}


HDF5DataSet1DStdPtr HDF5Group::create_empty_dataset1D(const string& name, const HDF5DataSet1DStdSettings& settings)
{
    assert( datasets_1d.find(name) == datasets_1d.end() );
    datasets_1d[name] = HDF5DataSet1DStdPtr( new HDF5DataSet1DStd(name, HDF5GroupPtrWeak(shared_from_this()), settings ) );
    return datasets_1d[name];
}



HDF5DataSet2DStdPtr HDF5Group::get_dataset2D(const string& name)
{
    _HDF5Location loc(name);
    // Sanity checks:
    if( loc.is_absolute() ) assert(this->is_root() );

    if(loc.is_local())
    {
        assert( datasets_2d.find(loc.get_local_path()) != datasets_2d.end() );
        return datasets_2d[loc.get_local_path()];
    }
    else
    {
        return this->get_subgrouplocal(loc.get_local_path())->get_dataset2D(loc.get_child_path());
    }
}


HDF5DataSet1DStdPtr HDF5Group::get_dataset1D(const string& name)
{
    _HDF5Location loc(name);
    // Sanity checks:
    if( loc.is_absolute() ) assert(this->is_root() );

    if(loc.is_local())
    {
        assert( datasets_1d.find(loc.get_local_path()) != datasets_1d.end() );
        return datasets_1d[loc.get_local_path()];
    }
    else
    {
        return this->get_subgrouplocal(loc.get_local_path())->get_dataset1D(loc.get_child_path());
    }
}









void HDF5Group::create_softlink(const  HDF5DataSet2DStdPtr& target, const std::string& name)
{
    H5Lcreate_soft( 
            target->get_fullname().c_str(), //const char *target_path, 
            this->group_id,                 //hid_t link_loc_id, 
            name.c_str(),                   //const char *link_name, 
            H5P_DEFAULT,                    //hid_t lcpl_id,
            H5P_DEFAULT                     //hid_t lapl_id 
            );
}


void HDF5Group::create_softlink(const  HDF5DataSet1DStdPtr& target, const std::string& name)
{
    H5Lcreate_soft( 
            target->get_fullname().c_str(), //const char *target_path, 
            this->group_id,                 //hid_t link_loc_id, 
            name.c_str(),                   //const char *link_name, 
            H5P_DEFAULT,                    //hid_t lcpl_id,
            H5P_DEFAULT                     //hid_t lapl_id 
            );
}
























void HDF5File::init()
{
        root_group = HDF5GroupPtr( new HDF5Group("/",  HDF5FilePtrWeak(this->shared_from_this() ), HDF5GroupPtrWeak()  ) );
}


HDF5File::HDF5File(const string& filename)
        : filename(filename)
{
        //cout << "HDFFile( " << filename << " )";
        file_id = H5Fcreate(filename.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
}


HDF5File::~HDF5File()
{
    root_group.reset();


    H5Fclose(this->file_id);
    cout << "\nHDF-jive:closed file: " << filename << "\n" << std::flush;
}


HDF5GroupPtr HDF5File::get_group(const string& location)
{

    if(!root_group)
    {
        init();
    }

    return this->root_group->get_subgroup(location);

}


HDF5DataSet2DStdPtr HDF5File::get_dataset2D(const string& location)
{
    if(!root_group)
    {
        init();
    }

    return this->root_group->get_dataset2D(location);
}






//herr_t my_hdf5_error_handler (void *unused)
herr_t my_hdf5_error_handler (hid_t estack_id, void *unused)
{
   fprintf (stderr, "An HDF5 error was detected. Bye.\n");
   H5Eprint2(H5E_DEFAULT, stderr);
   assert(0);
   exit (1);
}

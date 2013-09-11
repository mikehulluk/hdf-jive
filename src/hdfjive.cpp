
#include "hdfjive.h"





//#include <boost/log/core.hpp>
//#include <boost/log/trivial.hpp>
//#include <boost/log/expressions.hpp>










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








HDF5DataSet2DStd::HDF5DataSet2DStd( const string& name, HDF5GroupPtrWeak pParent, const HDF5DataSet2DStdSettings& settings)
    :name(name), pParent(pParent), settings(settings)
{

    hsize_t data_dims[2] = {0, settings.size};
    hsize_t data_max_dims[2] = {H5S_UNLIMITED, settings.size} ;
    dataspace_id = H5Screate_simple(2, data_dims, data_max_dims);

    hsize_t chunk_dims[2] = {50, settings.size}; 
    hid_t prop = H5Pcreate(H5P_DATASET_CREATE);
    H5Pset_chunk (prop, 2, chunk_dims);


    dataset_id = H5Dcreate2 (pParent.lock()->group_id, name.c_str(), settings.type, dataspace_id, H5P_DEFAULT, prop, H5P_DEFAULT);


    H5Pclose (prop);

}




HDF5DataSet2DStd::~HDF5DataSet2DStd()
{
    //cout << "\nClosing DataSet:" << name  << " \n";
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);
}

std::string HDF5DataSet2DStd::get_fullname() const
{
    return pParent.lock()->get_fullname() + "/" + name;
}





template<typename T>
void _append_to_array(hid_t datatype, T* pData, size_t n, hid_t dataset_id)
{
    //cout << "\nWriting: ";
    //for(size_t i=0;i<n;i++) cout << pData[i] << ", ";


    // How big is the array:?
    hsize_t dims[2], max_dims[2];
    hid_t dataspace = H5Dget_space(dataset_id);
    H5Sget_simple_extent_dims(dataspace, dims, max_dims);
    H5Sclose(dataspace);

    assert(dims[1] == n);

    int curr_size = dims[0];

    // Extend the table:
    hsize_t new_data_dims[2] = {curr_size+1, dims[1] };
    H5Dextend (dataset_id, new_data_dims);

    //cout << "\n   - New dimension: " << curr_size+1;

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

}



void HDF5DataSet2DStd::append_buffer( float* pData )
{
    assert(settings.type==H5T_NATIVE_FLOAT);
    _append_to_array<float>(H5T_NATIVE_FLOAT, pData, settings.size, dataset_id);
}


void HDF5DataSet2DStd::append_buffer( double* pData )
{
    assert(settings.type==H5T_NATIVE_DOUBLE);
    _append_to_array<double>(H5T_NATIVE_DOUBLE, pData, settings.size, dataset_id);
}

void HDF5DataSet2DStd::append_buffer( int* pData )
{
    assert(settings.type==H5T_NATIVE_INT);
    _append_to_array<int>(H5T_NATIVE_INT, pData, settings.size, dataset_id);
}

void HDF5DataSet2DStd::append_buffer( long* pData )
{
    assert(settings.type==H5T_NATIVE_FLOAT);
    _append_to_array<long>(H5T_NATIVE_LONG, pData, settings.size, dataset_id);
}





template<typename T>
void _write_to_array(hid_t datatype, T* pData, size_t M, size_t N, hid_t dataset_id)
{

    // How big is the array:?
    //hsize_t dims[2], max_dims[2];
    //hid_t dataspace = H5Dget_space(dataset_id);
    //H5Sget_simple_extent_dims(dataspace, dims, max_dims);
    //H5Sclose(dataspace);

    //assert(dims[1] == N);

    //int curr_size = dims[0];

    // Extend the table:
    hsize_t new_data_dims[2] = {M,N}; //curr_size+1, dims[1] };
    H5Dextend (dataset_id, new_data_dims);

    //cout << "\n   - New dimension: " << curr_size+1;

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

}


void HDF5DataSet2DStd::set_data(size_t m, size_t n, float* pData)
{
    assert(settings.type==H5T_NATIVE_FLOAT);
    assert(m==settings.size);
    _write_to_array<float>(H5T_NATIVE_FLOAT, pData, m, n, dataset_id);
}
void HDF5DataSet2DStd::set_data(size_t m, size_t n, double* pData)
{
    assert(settings.type==H5T_NATIVE_DOUBLE);
    _write_to_array<double>(H5T_NATIVE_DOUBLE, pData, m, n, dataset_id);
}
void HDF5DataSet2DStd::set_data(size_t m, size_t n, int* pData)
{
    assert(settings.type==H5T_NATIVE_INT);
    _write_to_array<int>(H5T_NATIVE_INT, pData, m, n, dataset_id);
}
void HDF5DataSet2DStd::set_data(size_t m, size_t n, long* pData)
{
    assert(settings.type==H5T_NATIVE_LONG);
    _write_to_array<long>(H5T_NATIVE_LONG, pData, m, n, dataset_id);
}











void HDF5Group::add_attribute(const string& name, const string& value)
{
    hid_t datatype_id = H5Tcopy (H5T_C_S1);
    H5Tset_size (datatype_id, value.size());

    hid_t space=H5Screate (H5S_SCALAR);
    //hsize_t dims[] ={value.size()};
    //hid_t space = H5Screate_simple (1, dims, NULL);
    hid_t attr_id = H5Acreate (group_id, name.c_str(), datatype_id, space, H5P_DEFAULT);
    
    const char* attrs_data = value.c_str(); //"HelloWrodl";
    H5Awrite(attr_id, datatype_id, attrs_data);


//    HDF5Group
////DataSpace attr_dataspace = DataSpace(H5S_SCALAR);
////StrType strdatatype(PredType::C_S1, 256); // of length 256 characters
////const H5std_string strwritebuf ("This attribute is of type StrType");
//
//    H5Acreate_by_name( 
//            group_id, 
//            ".",
//            name.c_str(),
//            H5T_STRING,





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
        //cout << "\nCreating Root Group: " << location;
    }
    else
    {
        //cout << "\nCreating Group: " << location;

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
    datasets.clear();
    groups.clear();

    //cout << "\nShutting down group: " << location << "\n";
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







HDF5DataSet2DStdPtr HDF5Group::create_dataset(const string& name, const HDF5DataSet2DStdSettings& settings)
{
    assert( datasets.find(name) == datasets.end() );

    datasets[name] = HDF5DataSet2DStdPtr( new HDF5DataSet2DStd(name, HDF5GroupPtrWeak(shared_from_this()), settings ) );
    return datasets[name];

}


HDF5DataSet2DStdPtr HDF5Group::get_dataset(const string& name)
{
    _HDF5Location loc(name);
    // Sanity checks:
    if( loc.is_absolute() ) assert(this->is_root() );


    if(loc.is_local())
    {
        assert( datasets.find(loc.get_local_path()) != datasets.end() );
        return datasets[loc.get_local_path()];
    }
    else
    {
        return this->get_subgrouplocal(loc.get_local_path())->get_dataset(loc.get_child_path());
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

















void HDF5File::init()
{
        root_group = HDF5GroupPtr( new HDF5Group("/",  HDF5FilePtrWeak(this->shared_from_this() ), HDF5GroupPtrWeak()  ) );
}


HDF5File::HDF5File(const string& filename)
        : filename(filename)
{
        cout << "HDFFile( " << filename << " )";
        file_id = H5Fcreate(filename.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
}


HDF5File::~HDF5File()
{
    cout << "\nClosing HDF file: " << filename << "\n";
    //cout << "\n - Releasing groups: ";
    root_group.reset();

    //cout << "\n - Releasing handle";
    H5Fclose(this->file_id);
    cout << "\n(OK)" << std::flush;
}


HDF5GroupPtr HDF5File::get_group(const string& location)
{

    if(!root_group)
    {
        init();
    }

    return this->root_group->get_subgroup(location);

}


HDF5DataSet2DStdPtr HDF5File::get_dataset(const string& location)
{
    if(!root_group)
    {
        init();
    }

    return this->root_group->get_dataset(location);
}






herr_t my_hdf5_error_handler (void *unused)
{
   fprintf (stderr, "An HDF5 error was detected. Bye.\n");
   H5Eprint(stderr);
   assert(0);
   exit (1);
}

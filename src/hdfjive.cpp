
#include "hdfjive.h"


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
    :length(0), name(name), pParent(pParent), settings(settings)
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
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);
}

std::string HDF5DataSet2DStd::get_fullname() const
{
    return pParent.lock()->get_fullname() + "/" + name;
}





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



void HDF5DataSet2DStd::append_buffer( const float* pData )
{
    assert(settings.type==H5T_NATIVE_FLOAT);
    length = _append_to_array_2D<float>(H5T_NATIVE_FLOAT, pData, settings.size, dataset_id);
}


void HDF5DataSet2DStd::append_buffer( const double* pData )
{
    assert(settings.type==H5T_NATIVE_DOUBLE);
    length = _append_to_array_2D<double>(H5T_NATIVE_DOUBLE, pData, settings.size, dataset_id);
}

void HDF5DataSet2DStd::append_buffer( const int* pData )
{
    assert(settings.type==H5T_NATIVE_INT);
    length = _append_to_array_2D<int>(H5T_NATIVE_INT, pData, settings.size, dataset_id);
}

void HDF5DataSet2DStd::append_buffer( const long* pData )
{
    assert(settings.type==H5T_NATIVE_FLOAT);
    length = _append_to_array_2D<long>(H5T_NATIVE_LONG, pData, settings.size, dataset_id);
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


void HDF5DataSet2DStd::set_data(size_t m, size_t n, const float* pData)
{
    assert(settings.type==H5T_NATIVE_FLOAT);
    assert(n==settings.size);
    length = _write_to_array_2D<float>(H5T_NATIVE_FLOAT, pData, m, n, dataset_id);
}


void HDF5DataSet2DStd::set_data(size_t m, size_t n, const double* pData)
{
    assert(settings.type==H5T_NATIVE_DOUBLE);
    assert(n==settings.size);
    length = _write_to_array_2D<double>(H5T_NATIVE_DOUBLE, pData, m, n, dataset_id);
}
void HDF5DataSet2DStd::set_data(size_t m, size_t n, const int* pData)
{
    assert(settings.type==H5T_NATIVE_INT);
    assert(n==settings.size);
    length = _write_to_array_2D<int>(H5T_NATIVE_INT, pData, m, n, dataset_id);
}
void HDF5DataSet2DStd::set_data(size_t m, size_t n, const long* pData)
{
    assert(settings.type==H5T_NATIVE_LONG);
    assert(n==settings.size);
    length = _write_to_array_2D<long>(H5T_NATIVE_LONG, pData, m, n, dataset_id);
}



























HDF5DataSet1DStd::HDF5DataSet1DStd( const string& name, HDF5GroupPtrWeak pParent, const HDF5DataSet1DStdSettings& settings)
    : length(0), name(name), pParent(pParent), settings(settings)
{
    hsize_t data_dims[1] = {0};
    hsize_t data_max_dims[1] = {H5S_UNLIMITED} ;
    dataspace_id = H5Screate_simple(1, data_dims, data_max_dims);

    hsize_t chunk_dims[1] = {50}; 
    hid_t prop = H5Pcreate(H5P_DATASET_CREATE);
    H5Pset_chunk (prop, 1, chunk_dims);

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



void HDF5DataSet1DStd::append( float data )
{
    assert(settings.type==H5T_NATIVE_FLOAT);
    length = _append_to_array_1D<float>(H5T_NATIVE_FLOAT, data, dataset_id);
}


void HDF5DataSet1DStd::append( double data )
{
    assert(settings.type==H5T_NATIVE_DOUBLE);
    length = _append_to_array_1D<double>(H5T_NATIVE_DOUBLE, data, dataset_id);
}

void HDF5DataSet1DStd::append( int data )
{
    assert(settings.type==H5T_NATIVE_INT);
    length = _append_to_array_1D<int>(H5T_NATIVE_INT, data, dataset_id);
}

void HDF5DataSet1DStd::append( long data )
{
    assert(settings.type==H5T_NATIVE_LONG);
    length = _append_to_array_1D<long>(H5T_NATIVE_LONG, data, dataset_id);
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


void HDF5DataSet1DStd::set_data(size_t n, const float* pData)
{
    assert(settings.type==H5T_NATIVE_FLOAT);
    length = _write_to_array_1D<float>(H5T_NATIVE_FLOAT, pData, n, dataset_id);
}


void HDF5DataSet1DStd::set_data(size_t n, const double* pData)
{
    assert(settings.type==H5T_NATIVE_DOUBLE);
    length = _write_to_array_1D<double>(H5T_NATIVE_DOUBLE, pData, n, dataset_id);
}
void HDF5DataSet1DStd::set_data(size_t n, const int* pData)
{
     assert(settings.type==H5T_NATIVE_INT);
    length = _write_to_array_1D<int>(H5T_NATIVE_INT, pData, n, dataset_id);
}
void HDF5DataSet1DStd::set_data(size_t n, const long* pData)
{
    assert(settings.type==H5T_NATIVE_LONG);
    length = _write_to_array_1D<long>(H5T_NATIVE_LONG, pData, n, dataset_id);
}






























void HDF5Group::add_attribute(const string& name, const string& value)
{
    hid_t datatype_id = H5Tcopy (H5T_C_S1);
    H5Tset_size (datatype_id, value.size());

    hid_t space=H5Screate (H5S_SCALAR);
    hid_t attr_id = H5Acreate2(group_id, name.c_str(), datatype_id, space, H5P_DEFAULT, H5P_DEFAULT);
    
    const char* attrs_data = value.c_str(); 
    H5Awrite(attr_id, datatype_id, attrs_data);
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




// Convienance methods:
HDF5DataSet1DStdPtr HDF5Group::create_dataset1D(const string& name, const FloatBuffer1D& data)
{
    HDF5DataSet1DStdPtr pDataSet = create_empty_dataset1D(name, HDF5DataSet1DStdSettings(H5T_NATIVE_FLOAT) );
    pDataSet->set_data(data);
    return pDataSet;
}

HDF5DataSet1DStdPtr HDF5Group::create_dataset1D(const string& name, const IntBuffer1D& data)
{
    HDF5DataSet1DStdPtr pDataSet = create_empty_dataset1D(name, HDF5DataSet1DStdSettings(H5T_NATIVE_INT) );
    pDataSet->set_data(data);
    return pDataSet;
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


#include "hdfjive.h"
#include "hdfjive-neuro.h"

#include <iterator>

#include <boost/format.hpp>
#include <boost/algorithm/string/join.hpp>

SimulationResults::SimulationResults(HDF5FilePtr file, const std::string& simulationname)
    : n_shared_time_buffers(0), pSimulationGroup( file->get_group(simulationname)  )
{
}










template<typename TIMEDATATYPE>
SharedTimeBufferPtr SimulationResults::write_shared_time_buffer(size_t length, TIMEDATATYPE* pData)
{
    const std::string& array_name = (boost::format("time_array%01d")%n_shared_time_buffers++).str();
    HDF5DataSet2DStdPtr pDataSet = pSimulationGroup->get_group("shared_time_arrays")->create_empty_dataset2D(array_name, HDF5DataSet2DStdSettings(CPPTypeToHDFType<TIMEDATATYPE>::get_hdf_type(), 1));
    pDataSet->set_data( length, 1, pData);

    return SharedTimeBufferPtr(new SharedTimeBuffer(pDataSet) );
}


template<typename TIMEDATATYPE>
SharedTimeBufferPtr SimulationResults::write_shared_time_buffer(size_t length, TIMEDATATYPE dt)
{
    vector<TIMEDATATYPE> data(length);
    for(size_t i=0;i<length;i++)
        data[i] = i*dt;

    return this->write_shared_time_buffer(length, &(data[0]));
}









template<typename TIMEDATATYPE>
void SimulationResults::write_trace( const std::string& populationname, int index, const std::string& record_name, SharedTimeBufferPtr times,  TIMEDATATYPE* pData, const TagList& tags_in )
{
    HDF5GroupPtr pNodeGroup = pSimulationGroup
        ->get_group(populationname)
        ->get_group((boost::format("%04d")%index).str() )
        ->get_group("variables")
        ->get_group(record_name);

    HDF5GroupPtr pDataGroup = pNodeGroup
        ->get_group("raw");

    // Create a list of tags, including those specified:
    TagList tags(tags_in);
    tags.insert(record_name);
    tags.insert((boost::format("POPINDEX:%04d")%index).str() );
    tags.insert((boost::format("POPNAME:%s")%populationname).str() );

    // Add the tags to the node-group:
    pNodeGroup->add_attribute("hdf-jive", "trace");
    if(tags.size() != 0) pNodeGroup->add_attribute("hdf-jive:tags", boost::algorithm::join(tags, ","));

    // Soft-link the time:
    pDataGroup->create_softlink(times->get_dataset(), "time");

    // Create the data:
    HDF5DataSet2DStdPtr pDataSet = pDataGroup->create_empty_dataset2D("data", HDF5DataSet2DStdSettings(CPPTypeToHDFType<TIMEDATATYPE>::get_hdf_type(), 1));
    pDataSet->set_data( times->get_size(), 1, pData);
}


template<typename FwdIt>
void SimulationResults::write_trace( const std::string& populationname, int index, const std::string& record_name, SharedTimeBufferPtr times, FwdIt it, FwdIt end, const TagList& tags)
{
    typedef typename std::iterator_traits<FwdIt>::value_type T;

    // Copy the data into a vector, so that its contiguous:
    vector<T> data(it, end);
    assert(data.size() == times->get_size());

    write_trace<T>(populationname, index, record_name, times,  &data[0], tags);
}



template<typename FwdIt>
SharedTimeBufferPtr SimulationResults::write_shared_time_buffer(FwdIt it, FwdIt end)
{
    typedef typename std::iterator_traits<FwdIt>::value_type T;

    // Copy the data into a vector, so that its contiguous:
    vector<T> data(it, end);

    return write_shared_time_buffer<T>(data.size(), &(data[0]));
}









void SimulationResults::write_outputevents( const std::string& populationname, int index, const std::string& record_name, const FloatBuffer1D& times, const TagList& tags )
{
    HDF5GroupPtr pGroup = pSimulationGroup
        ->get_group(populationname)
        ->get_group((boost::format("%04d")%index).str() )
        ->get_group("output_events")
        ->get_group(record_name);

    // Add the tags to the node-group:
    pGroup->add_attribute("hdf-jive", "events");
    pGroup->add_attribute("hdf-jive:tags", boost::algorithm::join(tags, ", "));

    // Create a dataset here with the data:
    HDF5DataSet2DStdPtr pDataSet = pGroup->create_empty_dataset2D(record_name, HDF5DataSet2DStdSettings(H5T_NATIVE_FLOAT, 1) );
    pDataSet->set_data( times.size(), 1, times.get_data_pointer());
}


void SimulationResults::write_inputevents( const std::string& populationname, int index, const std::string& record_name, const FloatBuffer1D& times, const TagList& tags )
{
    HDF5GroupPtr pGroup = pSimulationGroup
        ->get_group(populationname)
        ->get_group((boost::format("%04d")%index).str() )
        ->get_group("input_events")
        ->get_group(record_name);

    // Add the tags to the node-group:
    pGroup->add_attribute("hdf-jive", "events");
    pGroup->add_attribute("hdf-jive:tags", boost::algorithm::join(tags, ", "));

    // Create a dataset here with the data:
    HDF5DataSet2DStdPtr pDataSet = pGroup->create_empty_dataset2D(record_name, HDF5DataSet2DStdSettings(H5T_NATIVE_FLOAT, 1) );
    pDataSet->set_data( times.size(), 1, times.get_data_pointer());
}




SimulationResultsFile::SimulationResultsFile(const std::string& filename)
    : file( HDFManager::getInstance().get_file(filename) )
{
}

SimulationResultsPtr SimulationResultsFile::Simulation(const std::string& simulationname)
{
    return SimulationResultsPtr( new SimulationResults(this->file, simulationname) );
}






































#include "hdfjive-neuro_tmpl-inst.cpp"

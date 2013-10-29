
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

















 // Simple, a pointer to an array of spike-times:
template<typename TIMEDATATYPE>
void SimulationResults::write_outputevents_onlytimes( const std::string& populationname, int index, const std::string& record_name, size_t n_events, TIMEDATATYPE* times, const TagList& tags)
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
    HDF5DataSet1DStdPtr pDataSet = pGroup->create_empty_dataset1D("event_times", HDF5DataSet1DStdSettings( CPPTypeToHDFType<TIMEDATATYPE>::get_hdf_type() ) );
    if(n_events > 0)
    {
        pDataSet->set_data( n_events, times);
    }
}



// STL container of Event-objects
template<typename FwdIt>
void SimulationResults::write_outputevents_onlytimes( const std::string& populationname, int index, const std::string& record_name, FwdIt it, FwdIt end, const TagList& tags)
{
    typedef typename std::iterator_traits<FwdIt>::value_type T;
    vector<T> data( it, end);
    write_outputevents_onlytimes( populationname, index, record_name, data.size(), &data[0], tags);
}

// // B. With parameters, storing events as objects:
// template<typename FwdIt>
// void SimulationResults::write_outputevents_byobjects(const std::string& populationname, int index, const std::string& record_name, FwdIt start, FwdIt stop, const TagList& tags )
// {
//     typedef typename std::iterator_traits<FwdIt>::value_type EVENTTYPE;
// 
//     HDF5GroupPtr pGroup = pSimulationGroup
//     ->get_group(populationname)
//     ->get_group((boost::format("%04d")%index).str() )
//     ->get_group("output_events")
//     ->get_group(record_name);
// 
//     // Add the tags to the node-group:
//     pGroup->add_attribute("hdf-jive", "events");
//     pGroup->add_attribute("hdf-jive:tags", boost::algorithm::join(tags, ", "));
// 
// 
//     typedef typename EVENTTYPE::DATATYPE DTYPE;
// 
//     const size_t n_params = EVENTTYPE::NPARAMS;
//     const size_t n_events = std::distance(start,stop);
// 
//     // Copy all the data into indivudla arrays:
//     DTYPE times[n_events];
//     DTYPE parameters[n_events][n_params];
// 
//     size_t i=0;
//     for(FwdIt it=start; it!= stop;it++, i++)
//     {
//         times[i] = it->time;
//         for(size_t p=0;p<n_params;p++)
//             (parameters[p])[i] = it->parameters[i];
//     }
// 
// 
//     // Create datasets with the data:
//     HDF5DataSet1DStdPtr pEventTimes = pGroup->create_empty_dataset1D("times",    HDF5DataSet1DStdSettings( CPPTypeToHDFType<DTYPE>::get_hdf_type() ) );
//     pEventTimes->set_data(n_events, times);
// 
//     for(size_t p=0;p<n_params;p++)
//     {
//         string pname = (boost::format("param-%d")%p).str();
//         HDF5DataSet1DStdPtr pEventData  = pGroup->create_empty_dataset1D(pname, HDF5DataSet1DStdSettings( CPPTypeToHDFType<DTYPE>::get_hdf_type()  ) );
//         pEventData->set_data(n_events, parameters[p] );
//     }
// }





/**
 *  Saving 'input' events. These are in general similar to the 'output' event, but they can also contain a reference to the 'output' event that caused it:
 */

 // A. With no parameters (no reference to input events):
 // i. Simple, a pointer to an array of spike-times:
template<typename DATATYPE> void SimulationResults::write_inputevents_onlytimes(const std::string& populationname, int index, const std::string& record_name, size_t n_events, DATATYPE*, const TagList& tags )
{
    //assert(0);
    cout << "ERROR Not saving!!";
}





// ii. STL container of times
template<typename FwdIt> void SimulationResults::write_inputevents_onlytimes(const std::string& populationname, int index, const std::string& record_name, FwdIt start, FwdIt stop, const TagList& tags)
{
    //assert(0);
    cout << "ERROR Not saving!!";
}




//// B. With parameters, storing events as objects:
//template<typename FwdIt> void SimulationResults::write_inputevents_byobjects(const std::string& populationname, int index, const std::string& record_name, FwdIt start, FwdIt stop, const TagList& tags )
//{
//    typedef typename std::iterator_traits<FwdIt>::value_type INEVENTTYPE;
//
//    HDF5GroupPtr pGroup = pSimulationGroup
//    ->get_group(populationname)
//    ->get_group((boost::format("%04d")%index).str() )
//    ->get_group("input_events")
//    ->get_group(record_name);
//
//    // Add the tags to the node-group:
//    pGroup->add_attribute("hdf-jive", "events");
//    pGroup->add_attribute("hdf-jive:tags", boost::algorithm::join(tags, ", "));
//
//
//    typedef typename INEVENTTYPE::EVENTTYPE::DATATYPE DTYPE;
//
//    const size_t n_params = INEVENTTYPE::EVENTTYPE::NPARAMS;
//    const size_t n_events = std::distance(start,stop);
//
//    // Copy all the data into individual arrays:
//    DTYPE times[n_events];
//    DTYPE parameters[n_events][n_params];
//    // Sources will be a 4xn events array
//    int sources[n_events][4];
//
//    size_t i=0;
//    for(FwdIt it=start; it!= stop;it++, i++)
//    {
//        times[i] = it->evt_details.time;
//        for(size_t p=0;p<n_params;p++)
//            (parameters[p])[i] = it->evt_details.parameters[i];
//
//        (sources[0])[i] = it->evt_src.src_population_index;
//        (sources[1])[i] = it->evt_src.src_neuron_index;
//        (sources[2])[i] = it->evt_src.src_evtport_index;
//        (sources[3])[i] = it->evt_src.src_event_index;
//
//    }
//
//    // Create datasets with the data:
//    HDF5DataSet1DStdPtr pEventTimes = pGroup->create_empty_dataset1D("times",    HDF5DataSet1DStdSettings( CPPTypeToHDFType<DTYPE>::get_hdf_type() ) );
//    pEventTimes->set_data(n_events, times);
//
//    for(size_t p=0;p<n_params;p++)
//    {
//        string pname = (boost::format("param-%d")%p).str();
//        HDF5DataSet1DStdPtr pEventData  = pGroup->create_empty_dataset1D(pname, HDF5DataSet1DStdSettings( CPPTypeToHDFType<DTYPE>::get_hdf_type()  ) );
//        pEventData->set_data(n_events, parameters[p] );
//    }
//    
//    HDF5DataSet2DStdPtr pEventSrcs  = pGroup->create_empty_dataset2D("srcs", HDF5DataSet2DStdSettings( CPPTypeToHDFType<int>::get_hdf_type(), 4) );
//    pEventSrcs->set_data(n_events, 4, &sources[0][0]);
//
//
//    cout << "ERROR Not saving!!";
//    cout << "ERROR Not saving!!";
//}





































#include "hdfjive-neuro_tmpl-inst.cpp"


#ifndef __HDFJIVENEURO_GUARD_H__
#define __HDFJIVENEURO_GUARD_H__


// Standard includes:
// ===================
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <type_traits>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <boost/algorithm/string/join.hpp>





// Forward declarations:
// =====================
class SimulationResults;
class SimulationResultsFile;
class SharedTimeBuffer;
class EventDataSetTuple;


typedef  boost::shared_ptr<SimulationResults> SimulationResultsPtr;
typedef  boost::shared_ptr<SimulationResultsFile> SimulationResultsFilePtr;
typedef  boost::shared_ptr<SharedTimeBuffer>  SharedTimeBufferPtr;

typedef std::set<std::string> TagList;






#include "hdfjive.h"





class SharedTimeBuffer
{
    HDF5DataSet2DStdPtr pArray;

public:
    SharedTimeBuffer(HDF5DataSet2DStdPtr pArray) : pArray(pArray) {}
    HDF5DataSet2DStdPtr get_dataset() const { return pArray; }
    size_t get_size() const { return pArray->get_length();  }

};



struct EventDataSetTuple
{
    HDF5DataSet1DStdPtr spiketimes;

    EventDataSetTuple(HDF5DataSet1DStdPtr spiketimes)
        : spiketimes(spiketimes)
    {}
};


class SimulationResults
{

    size_t n_shared_time_buffers;
    HDF5GroupPtr pSimulationGroup;


    std::map<std::string, size_t> population_indices;



public:
    //! Nutshell constructor
    SimulationResults(HDF5FilePtr , const std::string& simulationname);



    /**
     * Define the time buffer based on a fixed-size.
     */
    template<typename TIMEDATATYPE>
    SharedTimeBufferPtr write_shared_time_buffer(size_t length, TIMEDATATYPE dt)
    {
        std::vector<TIMEDATATYPE> data(length);
        for(size_t i=0;i<length;i++)
            data[i] = i*dt;

        return this->write_shared_time_buffer(length, &(data[0]));
    }

    /**
     * Define the time buffer using an array of time-points.
     */
    template<typename TIMEDATATYPE>
    SharedTimeBufferPtr write_shared_time_buffer(size_t length, TIMEDATATYPE* pData, const std::string dataset_name=std::string("raw") )
    {
        std::string array_name = (boost::format("timearray_%1% ") % n_shared_time_buffers++).str();
        HDF5GroupPtr pGroup = pSimulationGroup
            ->get_group("shared_time_arrays")
            ->get_group(array_name);

        HDF5DataSet2DStdPtr pDataSet = pGroup->create_empty_dataset2D(dataset_name, HDF5DataSet2DStdSettings(hdfjive::util::CPPTypeToHDFType<TIMEDATATYPE>::get_hdf_type(), 1));
            
        pDataSet->set_data( length, 1, pData);
        return SharedTimeBufferPtr(new SharedTimeBuffer(pDataSet) );
    }

    /**
     * Define the time buffer using an STL container
     */
    template<typename FwdIt>
    SharedTimeBufferPtr write_shared_time_buffer(FwdIt it, FwdIt end)
    {
        typedef typename std::iterator_traits<FwdIt>::value_type T;
        // Copy the data into a vector, so that its contiguous:
        std::vector<T> data(it, end);
        return write_shared_time_buffer<T>(data.size(), &(data[0]));
    }





    /**
     * Record a trace to the hdfjive file, using a pointer to the raw data. The length of the array should be the same as the time-buffer.
     */
    template<typename TIMEDATATYPE>
    HDF5DataSet2DStdPtr write_trace(const std::string& populationname, size_t index, const std::string& record_name, SharedTimeBufferPtr times, TIMEDATATYPE* pData, const TagList& tags_in=TagList())
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
        HDF5DataSet2DStdPtr pDataSet = pDataGroup->create_empty_dataset2D("data", HDF5DataSet2DStdSettings(hdfjive::util::CPPTypeToHDFType<TIMEDATATYPE>::get_hdf_type(), 1));
        pDataSet->set_data( times->get_size(), 1, pData);

        return pDataSet;
    }



    /**
     * Record a trace to the hdfjive file from an STL container. The length of the container should be the same as the time-buffer.
     */
    template<typename FwdIt>
    HDF5DataSet2DStdPtr write_trace(const std::string& populationname, size_t index, const std::string& record_name, SharedTimeBufferPtr times, FwdIt it, FwdIt end, const TagList& tags=TagList())
    {
        typedef typename std::iterator_traits<FwdIt>::value_type T;

        // Copy the data into a vector, so that its contiguous:
        std::vector<T> data(it, end);
        assert(data.size() == times->get_size());

        return write_trace<T>(populationname, index, record_name, times,  &data[0], tags);
    }






    /**
     *  Saving 'output' events. We do not store a reference for these events
     */

     // A. With no parameters:
     // i. Simple, a pointer to an array of spike-times:
    template<typename DATATYPE>
    EventDataSetTuple write_outputevents_onlytimes( const std::string& populationname, size_t index, const std::string& record_name, size_t n_events, DATATYPE* times, const TagList& tags=TagList() )
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
        HDF5DataSet1DStdPtr pDataSet = pGroup->create_empty_dataset1D("event_times", HDF5DataSet1DStdSettings( hdfjive::util::CPPTypeToHDFType<DATATYPE>::get_hdf_type() ) );
        if(n_events > 0)
        {
            pDataSet->set_data( n_events, times);
        }

        return EventDataSetTuple(pDataSet);
    }

    // ii. STL container of times
    template<typename FwdIt>
    EventDataSetTuple write_outputevents_onlytimes( const std::string& populationname, size_t index, const std::string& record_name, FwdIt it, FwdIt end, const TagList& tags=TagList() )
    {
        typedef typename std::iterator_traits<FwdIt>::value_type T;
        std::vector<T> data( it, end);
        return write_outputevents_onlytimes( populationname, index, record_name, data.size(), &data[0], tags);
    }


    template<typename EXTRACTORTYPE, typename FwdIt>
    EventDataSetTuple write_outputevents_byobjects_extractor(const std::string& populationname, size_t index, const std::string& record_name, FwdIt start, FwdIt stop, const TagList& tags=TagList() )
    {
        // Check that the thing being iterated over, and the extractor take the same type:
        static_assert(std::is_same<typename std::iterator_traits<FwdIt>::value_type, typename EXTRACTORTYPE::EVENTTYPE>::value, "jklkjl");
        typedef typename std::iterator_traits<FwdIt>::value_type EVENTTYPE;

        HDF5GroupPtr pGroup = pSimulationGroup
        ->get_group(populationname)
        ->get_group((boost::format("%04d")%index).str() )
        ->get_group("output_events")
        ->get_group(record_name);

        // Add the tags to the node-group:
        pGroup->add_attribute("hdf-jive", "events");
        pGroup->add_attribute("hdf-jive:tags", boost::algorithm::join(tags, ", "));


        typedef typename EXTRACTORTYPE::DTYPE DTYPE;

        const size_t n_params = EXTRACTORTYPE::NPARAMS;
        const size_t n_events = std::distance(start,stop);

        // Copy all the data into indivudla arrays:
        DTYPE times[n_events];
        DTYPE parameters[n_events][n_params];

        size_t i=0;
        for(FwdIt it=start; it!= stop;it++, i++)
        {
            times[i] = EXTRACTORTYPE::get_time(*it);
            for(size_t p=0;p<n_params;p++)
                (parameters[p])[i] = EXTRACTORTYPE::get_parameter_value(*it, p);
        }

        // Create datasets with the data:
        HDF5DataSet1DStdPtr pEventTimes = pGroup->create_empty_dataset1D("times",    HDF5DataSet1DStdSettings( hdfjive::util::CPPTypeToHDFType<DTYPE>::get_hdf_type() ) );
        pEventTimes->set_data(n_events, times);

        for(size_t p=0;p<n_params;p++)
        {
            std::string pname = EXTRACTORTYPE::get_parameter_name(p); (boost::format("param-%d")%p).str();
            HDF5DataSet1DStdPtr pEventData  = pGroup->create_empty_dataset1D(pname, HDF5DataSet1DStdSettings( hdfjive::util::CPPTypeToHDFType<DTYPE>::get_hdf_type()  ) );
            pEventData->set_data(n_events, parameters[p] );
        }

        return EventDataSetTuple(pEventTimes);
    }




    /**
     *  Saving 'input' events. These are in general similar to the 'output' event, but they can also contain a reference to the 'output' event that caused it:
     */
     // A. With no parameters (no reference to input events):
     // i. Simple, a pointer to an array of spike-times:
    template<typename DATATYPE>
    EventDataSetTuple write_inputevents_onlytimes( const std::string& populationname, size_t index, const std::string& record_name, size_t n_events, DATATYPE* times, const TagList& tags=TagList() )
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
        HDF5DataSet1DStdPtr pDataSet = pGroup->create_empty_dataset1D("event_times", HDF5DataSet1DStdSettings( hdfjive::util::CPPTypeToHDFType<DATATYPE>::get_hdf_type() ) );
        if(n_events > 0)
        {
            pDataSet->set_data( n_events, times);
        }
        return EventDataSetTuple(pDataSet);
    }
    
    // ii. STL container of times
    template<typename FwdIt>
    EventDataSetTuple write_inputevents_onlytimes( const std::string& populationname, size_t index, const std::string& record_name, FwdIt it, FwdIt end, const TagList& tags=TagList() )
    {
        typedef typename std::iterator_traits<FwdIt>::value_type T;
        std::vector<T> data( it, end);
        return write_inputevents_onlytimes( populationname, index, record_name, data.size(), &data[0], tags);
    }

    // B. With parameters, storing events as objects:
    template<typename EXTRACTORTYPE, typename FwdIt>
    EventDataSetTuple write_inputevents_byobjects_extractor(const std::string& populationname, size_t index, const std::string& record_name, FwdIt start, FwdIt stop, const TagList& tags=TagList() )
    {
        // Check that the thing being iterated over, and the extractor take the same type:
        static_assert(std::is_same<typename std::iterator_traits<FwdIt>::value_type, typename EXTRACTORTYPE::EVENTTYPE>::value, "jklkjl");
        typedef typename std::iterator_traits<FwdIt>::value_type EVENTTYPE;

        HDF5GroupPtr pGroup = pSimulationGroup
        ->get_group(populationname)
        ->get_group((boost::format("%04d")%index).str() )
        ->get_group("input_events")
        ->get_group(record_name);

        // Add the tags to the node-group:
        pGroup->add_attribute("hdf-jive", "events");
        pGroup->add_attribute("hdf-jive:tags", boost::algorithm::join(tags, ", "));

        typedef typename EXTRACTORTYPE::DTYPE DTYPE;

        const size_t n_params = EXTRACTORTYPE::NPARAMS;
        const size_t n_events = std::distance(start,stop);

        // Copy all the data into individual arrays:
        DTYPE times[n_events];
        DTYPE parameters[n_events][n_params];

        size_t i=0;
        for(FwdIt it=start; it!= stop;it++, i++)
        {
            times[i] = EXTRACTORTYPE::get_time(*it);
            for(size_t p=0;p<n_params;p++)
                (parameters[p])[i] = EXTRACTORTYPE::get_parameter_value(*it, p);
        }

        // Create datasets with the data:
        HDF5DataSet1DStdPtr pEventTimes = pGroup->create_empty_dataset1D("times",    HDF5DataSet1DStdSettings( hdfjive::util::CPPTypeToHDFType<DTYPE>::get_hdf_type() ) );
        pEventTimes->set_data(n_events, times);

        for(size_t p=0;p<n_params;p++)
        {
            std::string pname = EXTRACTORTYPE::get_parameter_name(p); (boost::format("param-%d")%p).str();
            HDF5DataSet1DStdPtr pEventData  = pGroup->create_empty_dataset1D(pname, HDF5DataSet1DStdSettings( hdfjive::util::CPPTypeToHDFType<DTYPE>::get_hdf_type()  ) );
            pEventData->set_data(n_events, parameters[p] );
        }


        
        if( EXTRACTORTYPE::NSRCINDICES > 0)
        {
            size_t sources[n_events][EXTRACTORTYPE::NSRCINDICES];
            for(FwdIt it=start; it!= stop;it++, i++)
            {
                for(size_t x=0;x<EXTRACTORTYPE::NSRCINDICES;x++)
                {
                    (sources[x])[i] = EXTRACTORTYPE::get_srcindex_value(*it, x); 
                }
            }
            
            HDF5DataSet2DStdPtr pEventSrcs  = pGroup->create_empty_dataset2D("srcs", HDF5DataSet2DStdSettings( hdfjive::util::CPPTypeToHDFType<size_t>::get_hdf_type(), EXTRACTORTYPE::NSRCINDICES) );
            pEventSrcs->set_data(n_events, 4, &sources[0][0]);
        }

        return EventDataSetTuple(pEventTimes);
    }








};


class SimulationResultsFile
{
    HDF5FilePtr file;

public:
    SimulationResultsFile(const std::string& filename);
    SimulationResultsPtr Simulation(const std::string& simulationname);
};






#endif


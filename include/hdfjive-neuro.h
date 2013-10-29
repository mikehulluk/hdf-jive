
#ifndef __HDFJIVENEURO_GUARD_H__
#define __HDFJIVENEURO_GUARD_H__


#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <boost/enable_shared_from_this.hpp>


#include <type_traits>


using namespace std;



#include "hdfjive.h"
#include "hdfjive-events.h"


#include <boost/format.hpp>
#include <boost/algorithm/string/join.hpp>


class SimulationResults;
class SimulationResultsFile;
class SharedTimeBuffer;


typedef  boost::shared_ptr<SimulationResults> SimulationResultsPtr;
typedef  boost::shared_ptr<SimulationResultsFile> SimulationResultsFilePtr;
typedef  boost::shared_ptr<SharedTimeBuffer>  SharedTimeBufferPtr;

typedef std::set<std::string> TagList;











class SharedTimeBuffer
{
    HDF5DataSet2DStdPtr pArray;
    
public:
    SharedTimeBuffer(HDF5DataSet2DStdPtr pArray) : pArray(pArray) {}
    HDF5DataSet2DStdPtr get_dataset() const { return pArray; }
    size_t get_size() const { return pArray->get_length();  }
    
};


class SimulationResults
{

    int n_shared_time_buffers;
    HDF5GroupPtr pSimulationGroup;

    
    std::map<string, size_t> population_indices;
    


public:
    //! Nutshell constructor
    SimulationResults(HDF5FilePtr , const std::string& simulationname);



    /**
     * Define the time buffer based on a fixed-size.
     */ 
    template<typename TIMEDATATYPE>
    SharedTimeBufferPtr write_shared_time_buffer(size_t length, TIMEDATATYPE dt);

    /**
     * Define the time buffer using an array of time-points.
     */ 
    template<typename TIMEDATATYPE>
    SharedTimeBufferPtr write_shared_time_buffer(size_t length, TIMEDATATYPE* pData);

    /**
     * Define the time buffer using an STL container
     */ 
    template<typename FwdIt>
    SharedTimeBufferPtr write_shared_time_buffer(FwdIt it, FwdIt end);


    /**
     * Record a trace to the hdfjive file, using a pointer to the raw data. The length of the array should be the same as the time-buffer.
     */ 
    template<typename TIMEDATATYPE>
    void write_trace(const std::string& populationname, int index, const std::string& record_name, SharedTimeBufferPtr times, TIMEDATATYPE* pData, const TagList& tags=TagList());

    /**
     * Record a trace to the hdfjive file from an STL container. The length of the container should be the same as the time-buffer.
     */ 
    template<typename FwdIt>
    void write_trace(const std::string& populationname, int index, const std::string& record_name, SharedTimeBufferPtr times, FwdIt it, FwdIt end, const TagList& tags=TagList());



    /** 
     *  Saving 'output' events. We do not store a reference for these events
     */

     // A. With no parameters:
     // i. Simple, a pointer to an array of spike-times:
    template<typename DATATYPE> void write_outputevents_onlytimes( const std::string& populationname, int index, const std::string& record_name, size_t n_events, DATATYPE*, const TagList& tags=TagList() );
    // ii. STL container of times
    template<typename FwdIt>
    void write_outputevents_onlytimes( const std::string& populationname, int index, const std::string& record_name, FwdIt it, FwdIt end, const TagList& tags=TagList() );



    template<typename EXTRACTORTYPE, typename FwdIt>
    void write_outputevents_byobjects_extractor(const std::string& populationname, int index, const std::string& record_name, FwdIt start, FwdIt stop, const TagList& tags=TagList() )
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
        HDF5DataSet1DStdPtr pEventTimes = pGroup->create_empty_dataset1D("times",    HDF5DataSet1DStdSettings( CPPTypeToHDFType<DTYPE>::get_hdf_type() ) );
        pEventTimes->set_data(n_events, times);

        for(size_t p=0;p<n_params;p++)
        {
            string pname = EXTRACTORTYPE::get_parameter_name(p); (boost::format("param-%d")%p).str();
            HDF5DataSet1DStdPtr pEventData  = pGroup->create_empty_dataset1D(pname, HDF5DataSet1DStdSettings( CPPTypeToHDFType<DTYPE>::get_hdf_type()  ) );
            pEventData->set_data(n_events, parameters[p] );
        }

        cout << "\n\nH YEAH!";


    }






    // B. With parameters, storing events as objects:
    template<typename FwdIt>
    void write_outputevents_byobjects(const std::string& populationname, int index, const std::string& record_name, FwdIt it, FwdIt end, const TagList& tags=TagList() );
    

    // C. With parameters, storing events parameters in arrays:
    /*
    template<typename DATATYPE>void write_outputeventsNEW2(const std::string& populationname, int nrn_index, const std::string& record_name, size_t, DATATYPE* pTimes, const TagList& tags=TagList() );
    template<typename DATATYPE>void write_outputeventsNEW2(const std::string& populationname, int nrn_index, const std::string& record_name, size_t, DATATYPE* pTimes, DATATYPE* p0, const TagList& tags=TagList() );
    template<typename DATATYPE>void write_outputeventsNEW2(const std::string& populationname, int nrn_index, const std::string& record_name, size_t, DATATYPE* pTimes, DATATYPE* p0, DATATYPE* p1, const TagList& tags=TagList() );
    template<typename DATATYPE>void write_outputeventsNEW2(const std::string& populationname, int nrn_index, const std::string& record_name, size_t, DATATYPE* pTimes, DATATYPE* p0, DATATYPE* p1, DATATYPE* p2, const TagList& tags=TagList() );
    template<typename DATATYPE>void write_outputeventsNEW2(const std::string& populationname, int nrn_index, const std::string& record_name, size_t, DATATYPE* pTimes, DATATYPE* p0, DATATYPE* p1, DATATYPE* p2, DATATYPE* p3, const TagList& tags=TagList() );
    template<typename DATATYPE>void write_outputeventsNEW2(const std::string& populationname, int nrn_index, const std::string& record_name, size_t, DATATYPE* pTimes, DATATYPE* p0, DATATYPE* p1, DATATYPE* p2, DATATYPE* p3, DATATYPE* p4, const TagList& tags=TagList() );
    */

    


    /** 
     *  Saving 'input' events. These are in general similar to the 'output' event, but they can also contain a reference to the 'output' event that caused it:
     */

     // A. With no parameters (no reference to input events):
     // i. Simple, a pointer to an array of spike-times:
    template<typename DATATYPE> void write_inputevents_onlytimes( const std::string& populationname, int index, const std::string& record_name, size_t n_events, DATATYPE*, const TagList& tags=TagList() );
    // ii. STL container of times
    template<typename FwdIt> void write_inputevents_onlytimes( const std::string& populationname, int index, const std::string& record_name, FwdIt it, FwdIt end, const TagList& tags=TagList() );

    // B. With parameters, storing events as objects:
    template<typename FwdIt> void write_inputevents_byobjects(const std::string& populationname, int index, const std::string& record_name, FwdIt it, FwdIt end, const TagList& tags=TagList() );

    // C. With parameters, storing events parameters in arrays:
    /*
    template<typename DATATYPE>void write_inputeventsNEW2(const std::string& populationname, int nrn_index, const std::string& record_name,   size_t, SrcEventReference* pSrcs, DATATYPE* pTimes, const TagList& tags=TagList() );
    template<typename DATATYPE>void write_inputeventsNEW2(const std::string& populationname, int nrn_index, const std::string& record_name,   size_t, SrcEventReference* pSrcs, DATATYPE* pTimes, DATATYPE* p0, const TagList& tags=TagList() );
    template<typename DATATYPE>void write_inputeventsNEW2(const std::string& populationname, int nrn_index, const std::string& record_name,   size_t, SrcEventReference* pSrcs, DATATYPE* pTimes, DATATYPE* p0, DATATYPE* p1, const TagList& tags=TagList() );
    template<typename DATATYPE>void write_inputeventsNEW2(const std::string& populationname, int nrn_index, const std::string& record_name,   size_t, SrcEventReference* pSrcs, DATATYPE* pTimes, DATATYPE* p0, DATATYPE* p1, DATATYPE* p2, const TagList& tags=TagList() );
    template<typename DATATYPE>void write_inputeventsNEW2(const std::string& populationname, int nrn_index, const std::string& record_name,   size_t, SrcEventReference* pSrcs, DATATYPE* pTimes, DATATYPE* p0, DATATYPE* p1, DATATYPE* p2, DATATYPE* p3, const TagList& tags=TagList() );
    template<typename DATATYPE>void write_outputeventsNEW2(const std::string& populationname, int nrn_index, const std::string& record_name,  size_t, SrcEventReference* pSrcs, DATATYPE* pTimes, DATATYPE* p0, DATATYPE* p1, DATATYPE* p2, DATATYPE* p3, DATATYPE* p4, const TagList& tags=TagList() );
    */


    



    
    void write_outputevents( const std::string& populationname, int index, const std::string& record_name, const FloatBuffer1D& times, const TagList& tags );
    void write_inputevents( const std::string& populationname, int index, const std::string& record_name, const FloatBuffer1D& times, const TagList& tags );



    

    
    
};


class SimulationResultsFile
{
    HDF5FilePtr file;

    
public:          
    SimulationResultsFile(const std::string& filename);
    SimulationResultsPtr Simulation(const std::string& simulationname);
};






#endif


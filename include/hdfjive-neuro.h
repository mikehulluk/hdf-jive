
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
using namespace std;



#include "hdfjive.h"



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
     * Define the time buffer using an array of time-points.
     */ 
    //void write_trace( const std::string& populationname, int index, const std::string& record_name, SharedTimeBufferPtr times, const FloatBuffer1D& data, const TagList& tags );

    template<typename TIMEDATATYPE>
    void write_trace( const std::string& populationname, int index, const std::string& record_name, SharedTimeBufferPtr times, TIMEDATATYPE* pData, const TagList& tags=TagList() );

    
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


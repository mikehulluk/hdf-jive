
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <boost/enable_shared_from_this.hpp>
using namespace std;





class SimulationResults;
class SimulationResultsFile;
class SharedTimeBuffer;


typedef  boost::shared_ptr<SimulationResults> SimulationResultsPtr;
typedef  boost::shared_ptr<SimulationResultsFile> SimulationResultsFilePtr;
typedef  boost::shared_ptr<SharedTimeBuffer>  SharedTimeBufferPtr;

typedef std::list<std::string> TagList;





class SharedTimeBuffer
{
public:
    HDF5DataSet2DStdPtr pArray;
    
public:
    SharedTimeBuffer(HDF5DataSet2DStdPtr pArray) : pArray(pArray) {}


};


class SimulationResults
{

    int n_shared_time_buffers;
    HDF5GroupPtr pSimulationGroup;

public:
    SimulationResults(HDF5FilePtr , const std::string& simulationname);

    SharedTimeBufferPtr write_shared_time_buffer(const FloatBuffer1D& b);
    void write_trace( const std::string populationname, int index, const std::string& record_name, SharedTimeBufferPtr times, const FloatBuffer1D& data, const TagList& tags );
    void write_outputevents( const std::string populationname, int index, const std::string& record_name, const FloatBuffer1D& times, const TagList& tags );
    void write_inputevents( const std::string populationname, int index, const std::string& record_name, const FloatBuffer1D& times, const TagList& tags );

};


class SimulationResultsFile
{
    HDF5FilePtr file;

    
public:          
    SimulationResultsFile(const std::string& filename);
    SimulationResultsPtr Simulation(const std::string& simulationname);
};





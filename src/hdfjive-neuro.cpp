
#include "hdfjive.h"
#include "hdfjive-neuro.h"

#include <iterator>

#include <boost/format.hpp>
#include <boost/algorithm/string/join.hpp>

SimulationResults::SimulationResults(HDF5FilePtr file, const std::string& simulationname)
    : n_shared_time_buffers(0), pSimulationGroup( file->get_group(simulationname)  )
{
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

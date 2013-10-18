

#include "hdfjive.h"
#include "hdfjive-neuro.h"


#include <boost/assign/list_of.hpp> // for 'list_of()'
#include <boost/assert.hpp> 
#include <list>
using namespace std;
using namespace boost::assign; 


void test_neuro_interface()
{
    float time_data[] = {-1,-2,-3,-4} ;
    FloatBuffer1D time_buff(time_data, 4);
    
    float v0_data[] = {2.4, .3,4, 4.6, 9.6} ;
    FloatBuffer1D v0_buff(v0_data, 4);

    const list<string> tags1 = list_of("A1")("B1")("C1");
    const list<string> tags2 = list_of("A2")("B2")("C2");
    const list<string> tags3 = list_of("A3")("B3")("C3");
    
    SimulationResultsPtr output = SimulationResultsFile("MyResults.hdf").Simulation("Sim1");
    SharedTimeBufferPtr times = output->write_shared_time_buffer(time_buff);

    for(int i=0;i<5;i++)
    {
        output->write_trace("population-dINs-RHS", 78+i, "V", times, v0_buff, tags1);
        output->write_inputevents("population-dINs-RHS", 78+i, "spike_in", FB()|45.f|25.f, tags2);
        output->write_outputevents("population-dINs-RHS", 78+i, "spike_out", FB()|200.0f|23.f, tags3);
    }


}

int main()
{
    HDFManager::getInstance().remove_file("myfile.hdf");
    HDFManager::getInstance().get_file("myfile.hdf");
    HDFManager::getInstance().get_file("myfile.hdf")->get_group("/SimulationResults/P1");
    HDFManager::getInstance().get_file("myfile.hdf")->get_group("/SimulationResults/P1/P2");

    HDF5GroupPtr pGroup = HDFManager::getInstance().get_file("myfile.hdf")->get_group("/SimulationResults/P1/P2/");
    pGroup->create_empty_dataset2D("d1", HDF5DataSet2DStdSettings(4, H5T_NATIVE_FLOAT ));
    HDF5DataSet2DStdPtr ds = pGroup->get_dataset2D("d1");

    float data[] = {2.4, .3,4, 4.6, 9.6} ;
    ds->append_buffer(data);
    ds->append_buffer(data);
    ds->append_buffer(data);
    ds->append_buffer(data);
    ds->append_buffer(FB() | 2.4f | 4.6f | 9.6f | 4.5f );
    ds->append_buffer(FB() | 2.4f | 4.6f | 4.5f | 9.6f );


    HDFManager::getInstance().get_file("myfile.hdf")->get_dataset2D("/SimulationResults/P1/P2/d1")->append_buffer( FB() | 1.1f | 2.2f | 3.3f | 4.4f );

    pGroup->create_empty_dataset2D("d2", HDF5DataSet2DStdSettings(1, H5T_NATIVE_INT) );
    pGroup->get_dataset2D("d2")->append(30);
    pGroup->get_dataset2D("d2")->append(40);
    pGroup->get_dataset2D("d2")->append(50);


    cout << "\n     **** FINISHED OK **** \n";




    test_neuro_interface();



}





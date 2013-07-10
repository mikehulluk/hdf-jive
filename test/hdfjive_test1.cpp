

#include "hdfjive.h"




int main()
{

HDFManager::getInstance().remove_file("myfile.hdf");
HDFManager::getInstance().get_file("myfile.hdf");
HDFManager::getInstance().get_file("myfile.hdf")->get_group("/SimulationResults/P1");
HDFManager::getInstance().get_file("myfile.hdf")->get_group("/SimulationResults/P1/P2");

HDF5GroupPtr pGroup = HDFManager::getInstance().get_file("myfile.hdf")->get_group("/SimulationResults/P1/P2/");
pGroup->create_dataset("d1", HDF5DataSet2DStdSettings(4, H5T_NATIVE_FLOAT ));
HDF5DataSet2DStdPtr ds = pGroup->get_dataset("d1");

float data[] = {2.4, .3,4, 4.6, 9.6} ;
ds->append_buffer(data);
ds->append_buffer(data);
ds->append_buffer(data);
ds->append_buffer(data);
ds->append_buffer(FB() | 2.4f | 4.6f | 9.6f | 4.5f );
ds->append_buffer(FB() | 2.4f | 4.6f | 4.5f | 9.6f );


HDFManager::getInstance().get_file("myfile.hdf")->get_dataset("/SimulationResults/P1/P2/d1")->append_buffer( FB() | 1.1f | 2.2f | 3.3f | 4.4f );

pGroup->create_dataset("d2", HDF5DataSet2DStdSettings(1, H5T_NATIVE_INT) );
pGroup->get_dataset("d2")->append(30);
pGroup->get_dataset("d2")->append(40);
pGroup->get_dataset("d2")->append(50);


cout << "\n     **** FINISHED OK **** \n";
}





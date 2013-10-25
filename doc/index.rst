.. hdf-jive documentation master file, created by
   sphinx-quickstart on Tue Oct 22 16:03:08 2013.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.




Contents:

.. contents::
   :depth: 2




HDF5 file format overview
--------------------------

hdfjive is a simple format designed to make it easy to save and visualise output from neuronal simulations, in which the results of many values from large populations of neurons may be recorded. It consists of high-level APIs in C++ and Python to write the results from simulations to hdf5 and a set of commandline tools for query and visualise the results.


HDF5 is a format that allows data to be stored hierachically.


.. todo::

    Explanation of file-format.



Quickstart
-----------

Some examples of how to create hdf-jive files are given below.


Using C++
~~~~~~~~~

The following code blocks creates a new HDF file and writes data into it (which would typically come from a simulation).


.. todo::

    Make it correct!



.. code-block:: c

    #incldue

    void test_neuro_interface()
    {
        float time_data[] = {-1,-2,-3,-4} ;
        FloatBuffer1D time_buff(time_data, 4);

        float v0_data[] = {2.4, .3,4, 4.6, 9.6} ;
        FloatBuffer1D v0_buff(v0_data, 4);

        SimulationResultsPtr output = SimulationResultsFile("MyResults.hdf").Simulation("Sim1");
        SharedTimeBufferPtr times = output->write_shared_time_buffer(time_buff);

        for(int i=0;i<5;i++)
        {
            output->write_trace("population-dINs-RHS", i, "V", times, v_buff, list_of("Voltage") );
            output->write_trace("population-dINs-RHS", i, "i", times, i_buff, list_of("Current") );
            //output->write_inputevents("population-dINs-RHS", 78+i, "spike_in",   FB( list_of(45.f)(25.f) ), list_of("A3")("B3")("C3") ) ;
            //output->write_outputevents("population-dINs-RHS", 78+i, "spike_out", FB( list_of(200.f)(23.f) ), list_of("A3")("B3")("C3") );
        }
    }





.. doxygenclass:: HDF5DataSet1DStd
   :project: hdfjive
   :members:





Using Python
~~~~~~~~~~~~

.. todo::

    Make it correct!



Using Java
~~~~~~~~~~

.. todo::

    Make it correct!




Using Python
~~~~~~~~~~~~~

.. todo::

    Make it correct!




Using the command-line
~~~~~~~~~~~~~~~~~~~~~~

Once the hdf5 file has been generate, it can be viewed from the commandline using:

.. code-block:: bash

    # Using paths:
    $ hdfjive plot "PATH: Sim1/population-dINs-RHS/0000/soma/VARIABLES/Voltage"

    # Using 'tags':
    $ hdfjive plot "TAGS: ALL{POPINDEX:0000,Voltage}"




Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`


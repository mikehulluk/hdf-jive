
import pylab
import hdfjive


import numpy as np



def build_subparser(subparsers):
    print 'Building Compare Parser'

    parser_a = subparsers.add_parser('compare')
    parser_a.add_argument('filenames', type=str, nargs='+', help='filenames')
    parser_a.set_defaults(func=_run_compare)
    


def _run_compare(args):

    hdf5files = [hdfjive.HDF5SimulationResultFile(f) for f in args.filenames ]
    print "Running 'compare'"


    print 'Walking over arrays file:'
    
    f0 = hdf5files[0].h5file.root

    for arr in  hdf5files[0].h5file.walk_nodes(where="/", classname="EArray"):
        f0_data = arr.read()
        print ' -- Inspecting', arr._v_pathname, 
        print f0_data.shape
        for fn in hdf5files[1:]:
            print '   ** Comparing to', fn, 
            fn_data =  fn.h5file.get_node(arr._v_pathname).read()
            print fn_data.shape

            diff =  f0_data == fn_data
            assert np.all( diff )
            print " >> OK"




    print
    

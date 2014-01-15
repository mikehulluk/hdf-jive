from collections import Counter


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


    sucesses = []
    failures_traces = []
    failures_events = []

    for arr in  hdf5files[0].h5file.walk_nodes(where="/", classname="EArray"):
        f0_data = arr.read()
        print ' -- Inspecting', arr._v_pathname, 
        print f0_data.shape
        for fn in hdf5files[1:]:
            print '   ** Comparing to', fn
            fn_data =  fn.h5file.get_node(arr._v_pathname).read()
            

            # Traces:
            if 'variables' in arr._v_pathname:
                diff =  f0_data == fn_data
                errs = np.where( np.logical_not( diff )  )[0]

                if len(errs):
                    failures_traces.append( (errs[0], arr._v_pathname))
                else:
                    sucesses.append( arr._v_pathname )


            # Events:
            else:
                #print f0_data.tolist()
                #print 
                c0 = Counter( f0_data.flatten().tolist() )
                cn = Counter( fn_data.flatten().tolist() )

                c0.subtract(cn)

                times = [ time for (time,cnt) in c0.items() if cnt != 0 ]
                
                if times:
                    failures_events.append( ( min( times ), arr._v_pathname))
                else:
                    sucesses.append( arr._v_pathname )





    
    if not failures_traces and not failures_events:
        print "OK! No diffs found"
    else:
        print 'Errors found, here are the first diverges:'

        print 'Traces:'
        failures_traces.sort()
        t_diff = failures_traces[0][0]
        
        for f in failures_traces:
            print f
            if f[0] != t_diff:
                break



        print 'Events:'
        failures_events.sort()
        t_diff = failures_events[0][0]
        
        for f in failures_events:
            print f
            if f[0] != t_diff:
                break  
                

    print
    

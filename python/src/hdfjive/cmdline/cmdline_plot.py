
import pylab
import hdfjive


def build_subparser(subparsers):
    print 'Building Plot Parser'

    parser_a = subparsers.add_parser('plot')
    parser_a.add_argument('filename', type=str, help='HDF5 filename')
    parser_a.add_argument('--additional-filename', type=str, action='append', help='HDF5 filename')
    
    parser_a.add_argument('tagstrings', type=str, nargs='+', help='The Tagstring')

    parser_a.add_argument('--xmin', type=float, default=None, help="Start-time (in 's')")
    parser_a.add_argument('--xmax', type=float, default=None, help="End-time (in 's')")


    parser_a.add_argument('--in-ms', action='store_true',  help="Dsiplay x-axis in ms")

    parser_a.add_argument('--ymin', type=float, default=None, help="Y-Axis limits (in base si-units)")
    parser_a.add_argument('--ymax', type=float, default=None, help="Y-Axis limits (in base si-units)")

    parser_a.add_argument('--save-to', type=str, default=None, help="where to store the image files")

    parser_a.set_defaults(func=_run_plot)
    


def _run_plot(args):
    import mreorg
    mreorg.PlotManager.autosave_default_image_filename_tmpl = """_output-figures/%s/{figtype}/fig{fignum:03d}_{figname}.{figtype}""" % ( args.save_to) 
    
    print "Running 'plot'"

    print
    print args
    print

    hdffiles = hdfjive.HDF5SimulationResultFileSet([args.filename] + (args.additional_filename if args.additional_filename else []))


    # Controlling x-limits:
    xlim = None
    if args.xmin is not None:
        assert args.xmax is not None
    if args.xmax:
        xlim = ( (args.xmin if args.xmin is not None else 0.0),  args.xmax)

    # Controlling y-limits:
    ylim = None
    if args.ymin is not None:
        assert args.ymax is not None
    if args.ymax:
        ylim = ( (args.ymin if args.ymin is not None else 0.0),  args.ymax)


    xscale = 1000.0 if args.in_ms else 1.0
    xlabel = 'Time (ms)' if args.in_ms else 'Time (s)'


    # And plot:
    hdffiles.plot(trace_filters = args.tagstrings, legend=True, xlim=xlim, ylim=ylim, xlabel=xlabel, xscale=xscale)

    pylab.show()

    

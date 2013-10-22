



def build_subparser(subparsers):
    print 'Building Plot Parser'

    parser_a = subparsers.add_parser('plot')
    parser_a.add_argument('filename', type=str, help='HDF5 filename')
    parser_a.set_defaults(func=_run_plot)
    


def _run_plot(args):
    print 'Running plot'
    print args

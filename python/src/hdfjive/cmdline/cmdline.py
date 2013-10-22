
import argparse


import cmdline_plot




def build_argparser():

    parser = argparse.ArgumentParser(description='??')

    subparsers = parser.add_subparsers(help='sub-command help')
    
    cmdline_plot.build_subparser(subparsers)
    
    return parser


def main():
    print 'hdfjive commandline interface'

    parser = build_argparser()
    
    args = parser.parse_args()

    # Run the subcommand:
    args.func(args)
    










if __name__ == '__main__':
    main()

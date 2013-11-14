
import argparse


import cmdline_plot
import cmdline_plotraster
import cmdline_compare




def build_argparser():

    parser = argparse.ArgumentParser(description='HDF-jive command-line tools')
    subparsers = parser.add_subparsers(help='sub-command help')
    cmdline_plot.build_subparser(subparsers)
    cmdline_plotraster.build_subparser(subparsers)
    cmdline_compare.build_subparser(subparsers)
    return parser


def main():
    parser = build_argparser()
    args = parser.parse_args()

    # Run the subcommand:
    args.func(args)
    










if __name__ == '__main__':
    main()

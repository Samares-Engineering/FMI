#!/usr/bin/env python

'''
fmu2aadl: convert .fmu model into an AADL model

Usage:
   fmu2aadl.py <fmu_file>
'''

################################################################################

from docopt import docopt
import fmu2aadl

def main():
    # Read command line arguments
    args = docopt(__doc__, version='eprintsCV 0.1')
    fmu_file = args['<fmu_file>']

    fmu2aadl.fmu2aadl(fmu_file)

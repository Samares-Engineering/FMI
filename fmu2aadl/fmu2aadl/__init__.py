#!/usr/bin/env python

from lxml import etree

import zipfile
import shutil, sys, os

################################################################################
def _unzipModelDescriptionFile(path):
    '''Unzip FMU and extract the model description XML file

    :param path: full path to FMU file
    :type path: string
    '''

    zip_ref = zipfile.ZipFile(path, 'r')
    zip_ref.extract("modelDescription.xml", "", "")
    zip_ref.close()

################################################################################
def FMU2AADL_Prologue(root, file):
    '''Build the prologue of an AADL package

    :param root: root of the FMU XML tree
    :param file: file to output

    '''

    file.write('-- This file has been automatically generated. DO NOT EDIT\n')
    file.write('\n')
    file.write('package ' + root.get('modelName') + '_FMU\n')
    file.write('public\n')
    file.write(3 * ' ' + 'with Base_Types;\n')
    file.write('\n')

################################################################################
def FMU2AADL_Epilogue(root, file):
    '''Build the epilogue of an AADL package

    :param root: root of the FMU XML tree
    :param file: file to output

    '''
    file.write('end ' + root.get('modelName') + '_FMU;\n')
    file.close()

################################################################################
def FMU2AADL_MapScalarVariable(tree, file,thread_port):

    # The following dictionnaries define XML to AADL text mappings

    causality_map = { 'input' : '_in : in ',
                      'output' : '_out : out ' }

    variability_map = { 'continuous' : 'data port ',
                        'discrete' : 'even port ' }

    type_map = { 'real' : 'Base_Types::Float',
                 'integer' : 'Base_Types::Integer',
                 'boolean' : 'Base_Types::Boolean' }

    fmu_type=''

    # Iterate over the set of ScalarVariable nodes
    # Note: we map only inputs and outpus, parameters are discarded from now

    for svar in tree.xpath("/fmiModelDescription/ModelVariables/ScalarVariable"):
        if svar.get('causality') == 'input' or \
           svar.get('causality') == 'output':

            # Get the actual type, it is one child node of the current node

            for elt in svar:
                tag = elt.tag.lower()
                if tag in {'real', 'boolean','integer'}:
                    fmu_type = tag

            # Map the node to an AADL feature

            file.write(6 * ' ' + svar.get('name'))               # port name
            file.write(causality_map[svar.get('causality')])     # direction
            if (thread_port):                                    # category
                file.write(variability_map[svar.get('variability')])
            else:
                file.write("parameter ")

            file.write(type_map[fmu_type])                       # port type
            file.write ('; \n')

################################################################################
def FMU2AADL_Thread(root,tree,file):
    file.write(3 * ' ' + 'thread ' + root.get('modelName') + '_thread \n')
    file.write(3 * ' ' + 'features \n')

    FMU2AADL_MapScalarVariable(tree, file, True)

    file.write(3 * ' ' + 'properties\n')
    file.write(6 * ' ' + 'Dispatch_Protocol => Periodic;\n')
    file.write(6 * ' ' + 'Period => 1 sec;\n')
    file.write(3 * ' ' + 'end ' + root.get('modelName') + '_thread;\n')
    file.write('\n')

################################################################################
def FMU2AADL_Thread_Impl(root,tree,file):
    file.write(3 * ' ' + 'thread implementation ' + root.get('modelName')
               + '_thread.impl \n')
    file.write(3 * ' ' + 'calls C: { \n')
    file.write(6 * ' ' + 'P_Spg : subprogram '
               + root.get('modelName') + '_spg;\n')
    file.write(3 * ' ' + '};\n')

    file.write(3 * ' ' + 'connections\n')

    cnx_index = 0
    for svar in tree.xpath("/fmiModelDescription/ModelVariables/ScalarVariable"):
        if svar.get('causality') == 'input':
            file.write(6 * ' ' + 'C' + str(int(cnx_index)) +': port '
                       + svar.get('name') + '_in -> P_Spg.'
                       + svar.get('name') + '_in;\n')
            cnx_index = cnx_index + 1

        if svar.get('causality') == 'output':
            file.write(6 * ' ' + 'C' + str(cnx_index) + ': port P_Spg.'
                       + svar.get('name') + '_out -> ' + svar.get('name')
                       + '_out;\n')
            cnx_index = cnx_index + 1

    file.write('\n')
    file.write(3 * ' ' + 'end ' + root.get('modelName') + '_thread.impl;\n')
    file.write('\n')

################################################################################
def FMU2AADL_Subprogram(root,tree,file):
    file.write(3 * ' ' + 'subprogram ' + root.get('modelName') + '_spg \n')
    file.write(3 * ' ' + 'features \n')

    FMU2AADL_MapScalarVariable(tree, file, False)

    file.write(3 * ' ' + 'properties\n')
    file.write(6 * ' ' + 'Source_Language => (C);\n')
    file.write(6 * ' ' + 'Source_Name => "' + root.get('modelName').lower()
               + '_fmu_entrypoint";\n')
    file.write(6 * ' ' + 'Source_Text => ("' + root.get('modelName').lower()
               + '_fmu_wrapper.c");\n')
    file.write(3 * ' ' + 'end ' + root.get('modelName') + '_spg;\n')
    file.write('\n')

################################################################################
def fmu2aadl(fmu_file):
    '''
    Map a FMU to an AADL package

    :param fmu_file: full path to FMU file
    :type fmu_file: string

    '''

    print os.path.dirname(__file__)

    # Unzip FMU

    _unzipModelDescriptionFile(fmu_file)

    # Parse XML FMU description

    tree = etree.parse("modelDescription.xml")
    root = tree.getroot()

    # Build output AADL file, name is deduced from FMU name

    aadlFile = root.get('modelName').lower() + '_fmu.aadl'
    file = open(aadlFile,'w')
    print "Generating AADL file: " + aadlFile

    FMU2AADL_Prologue(root, file)
    FMU2AADL_Subprogram(root,tree,file)
    FMU2AADL_Thread(root,tree,file)
    FMU2AADL_Thread_Impl(root,tree,file)
    FMU2AADL_Epilogue(root, file)

    # Copy required runtime files

    shutil.copy(os.path.dirname(__file__) + "/fmu_wrapper.c", ".")
    shutil.copy(os.path.dirname(__file__) + "/fmu_wrapper.h", ".")
    shutil.copy(os.path.dirname(__file__) + "/userdefined.mk", ".")
    print "Copied fmu_wrapper.(c|h) and userdefined.mk to current directory"

    # Clean-up

    os.remove("modelDescription.xml")

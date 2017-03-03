'''
Created on Feb 22, 2017

@author: jmgauthier
'''
from lxml import etree
import zipfile
import sys, os

def _unzipModelDescriptionFile(path):
    zip_ref = zipfile.ZipFile(path, 'r')
    zip_ref.extract("modelDescription.xml", "", "")
    zip_ref.close()
 
def _parseRoot(root, file):
    file.write('process ' + root.get('modelName') + '\n')
    file.write('    features \n')

def _parseScalarVariable(tree, file):
    for svar in tree.xpath("/fmiModelDescription/ModelVariables/ScalarVariable"):
        if(svar.get('causality') == 'input'):
            file.write('        ' + svar.get('name') + '_in: in ')
        if(svar.get('causality') == 'output'):
            file.write('        ' + svar.get('name') + '_out: out ')
        if(svar.get('variability') == 'continuous'):
                file.write('data port; \n')
        if (svar.get('variability') == 'discrete'):
                file.write('event port; \n')

def _main():
    if(len(sys.argv)<2):
        print("python xmlparser.py <fmuFilePath>") 
        sys.exit(2)
    else:
        path = sys.argv[1]
        
        _unzipModelDescriptionFile(path)
        
        tree = etree.parse("modelDescription.xml")
        root = tree.getroot()
        aadlFile = root.get('modelName') + '.aadl'
        file = open(aadlFile,'w') 
        
        
        _parseRoot(root, file)
        _parseScalarVariable(tree, file)
        
        file.write('end ' + root.get('modelName') + ';')
        file.close()
        
        os.remove("modelDescription.xml") 
         
_main()
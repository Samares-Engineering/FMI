'''
Created on Feb 22, 2017

@author: jmgauthier
'''
from lxml import etree

tree = etree.parse("modelDescription.xml")

aadlFile = tree.getroot().get('modelName') + '.aadl'

file = open(aadlFile,'w') 

def _parseScalarVariable():
    for svar in tree.xpath("/fmiModelDescription/ModelVariables/ScalarVariable"):
        if(svar.get('causality') == 'parameter'):
            file.write('Parameter:' + svar.get('name') + '\n')
        if(svar.get('causality') == 'input'):
            file.write('Input:' + svar.get('name') + '\n')
        if(svar.get('causality') == 'output'):
            file.write('Output:' + svar.get('name') + '\n')
        if(svar.get('causality') == 'continuous'):
            file.write('Continuous:' + svar.get('name') + '\n')
        if(svar.get('causality') == 'discrete'):
            file.write('Discrete:' + svar.get('name') + '\n')

_parseScalarVariable()

file.close()
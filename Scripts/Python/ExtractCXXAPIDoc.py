## 
# ExtractCXXAPIDoc.py 
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; see the file COPYING. If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
##


import sys
import glob
import pickle

from os import path
from xml.dom.minidom import parse


def getChildNodes(parent_node, tag_name):
    children = []
    
    for node in parent_node.getElementsByTagName(tag_name):
        if node.parentNode == parent_node:
            children.append(node)

    return children

def outputTableRow(parent_node):
    rc = [ ' <tr>' ]

    for node in parent_node.childNodes:
        if node.nodeName == 'entry':
            if node.attributes['thead'].value == 'yes':
                rc.append('<th>')
            else:
                rc.append('<td>')
                
            rc.append(getTextRecursive(node).strip())

            if node.attributes['thead'].value == 'yes':
                rc.append('</th>')
            else:
                rc.append('</td>')
    
    rc.append('</tr>\n')
    
    return ''.join(rc)

def outputTable(parent_node):
    rc = [ '<table>\n' ]

    for node in parent_node.childNodes:
        if node.nodeName == 'row':
            rc.append(outputTableRow(node))

    rc.append('</table>')

    return ''.join(rc)

def outputList(parent_node):
    rc = [ '\n' ]
    
    for node in parent_node.childNodes:
        if node.nodeName == 'listitem':
            rc.append(' - ')
            rc.append(getTextRecursive(node).strip())
            rc.append('\n')
            
    return ''.join(rc)

def outputParameterListItem(node, throw):
    rc = []

    if throw:
        rc.append('\\throw ')
    else:
        rc.append('\\param ')

    rc.append(getTextRecursive(node.getElementsByTagName('parametername')[0]).strip())
    rc.append(' ')
    rc.append(getTextRecursive(node.getElementsByTagName('parameterdescription')[0]).strip())
    rc.append('\n')

    return ''.join(rc)

def outputParameterList(parent_node):
    rc = [] #[ '\n' ]
    throw = False
    
    if 'kind' in parent_node.attributes and parent_node.attributes['kind'].value == 'exception':
        throw = True
    
    for node in parent_node.childNodes:
        if node.nodeName == 'parameteritem':
            rc.append(outputParameterListItem(node, throw))
            
    return ''.join(rc)

def getTextRecursive(parent_node):
    rc = []
    
    for node in parent_node.childNodes:
        if node.nodeType == node.TEXT_NODE:
            rc.append(node.data)
        elif node.nodeName == 'para':
            rc.append(getTextRecursive(node))
        elif node.nodeName == 'computeroutput':
            rc.append('<tt>')
            rc.append(getTextRecursive(node))
            rc.append('</tt>')
        elif node.nodeName == 'emphasis':
            rc.append('<em>')
            rc.append(getTextRecursive(node))
            rc.append('</em>')
        elif node.nodeName == 'heading':
            rc.append(getTextRecursive(node).strip() + '\n')
            rc.append('-' * len(rc[-1]) + '\n')
        elif node.nodeName == 'bold':
            rc.append('<b>')
            rc.append(getTextRecursive(node))
            rc.append('</b>')
        elif node.nodeName == 'superscript':
            rc.append('<sup>')
            rc.append(getTextRecursive(node))
            rc.append('</sup>')
        elif node.nodeName == 'subscript':
            rc.append('<sub>')
            rc.append(getTextRecursive(node))
            rc.append('</sub>')
        elif node.nodeName == 'ref':
            rc.append('\\ref ')
            rc.append(getTextRecursive(node))
        elif node.nodeName == 'Aring':
            rc.append('&Aring;')
        elif node.nodeName == 'eacute':
            rc.append('&eacute;')
        elif node.nodeName == 'table':
            rc.append(outputTable(node))
        elif node.nodeName == 'parameterlist':
            if node.attributes['kind'].value == 'templateparam':
                continue
            rc.append(outputParameterList(node))
        elif node.nodeName == 'simplesect':
            kind = node.attributes['kind'].value
            
            if kind == 'see':
                rc.append('\\see ')
            elif kind  == 'return':
                rc.append('\\return ')
            elif kind == 'note':
                rc.append('\\note ')
            elif kind == 'pre':
                rc.append('\\pre ')
            elif kind == 'post':
                rc.append('\\post ')
            else:
                print('Warning: unknown simplesect type: ' + node.attributes['kind'].value)
            rc.append(getTextRecursive(node))
        elif node.nodeName == 'itemizedlist':
            rc.append(outputList(node))
        elif node.nodeName == 'ulink':
            rc.append('<a href="')
            rc.append(node.attributes['url'].value)
            rc.append('">')
            rc.append(getTextRecursive(node).strip())
            rc.append('</a>')
        elif node.nodeName == 'image':
            rc.append('\\image ')
            rc.append(node.attributes['type'].value + ' ')
            rc.append(node.attributes['name'].value + ' ')
            rc.append('"' +  getTextRecursive(node) + '"')
        elif node.nodeName == 'linebreak':
            rc.append('<br>')
        elif node.nodeName == 'sp':
            rc.append(' ')
        elif node.nodeName == 'formula':
            rc.append(getTextRecursive(node))
        elif node.nodeName == 'programlisting':
            rc.append('\n\\code\n/* FIXME! */\n')
            rc.append(getTextRecursive(node))
            rc.append('\\endcode')
        elif node.nodeName == 'codeline' or node.nodeName == 'highlight':
            rc.append(getTextRecursive(node))
        else:
            print('Warning: unknown node name: ' + node.nodeName)
            rc.append(getTextRecursive(node))
        
    return ''.join(rc)

def getBriefDocText(node):
    doc_text = getTextRecursive(getChildNodes(node, 'briefdescription')[0]).strip()

    if not doc_text:
        return doc_text

    return '\\brief ' + doc_text + '\n'

def getDetailedDocParaText(node):
    return '\n\n' + getTextRecursive(node).strip()

def getDetailedDocText(parent_node):
    rc = []
    parent_node = getChildNodes(parent_node, 'detaileddescription')[0]

    for node in parent_node.childNodes:
        if node.nodeType == node.TEXT_NODE:
            rc.append(node.data)
            continue

        rc.append(getDetailedDocParaText(node))

    doc_text = ''.join(rc).strip()

    if not doc_text:
        return doc_text

    return doc_text + '\n'

def getDocText(node):
    doc_text = getBriefDocText(node)

    if not doc_text:
        return doc_text
    
    detailed_doc = getDetailedDocText(node)

    if detailed_doc:
        doc_text += '\n' + detailed_doc

    return doc_text\
        .replace(' \\ref ', ' ').replace('\n\\ref ', '\n').replace('>\\ref ', '>')\
        .replace('(\\ref ', '(').replace('$', '\\f$').replace('::', '.').replace('std.size_t', 'int')\
        .replace('double', 'float').replace('<tt>non-const</tt> ', '').replace('pointer', 'reference')\
        .replace('non-<tt>const</tt> ', '').replace('<tt>const</tt> ', '')
    
def processCXXAPIDocFile(file_path, api_doc_db):
    print('Processing file: %s...' % path.basename(file_path))
    
    dom = parse(file_path)
    comp_def = dom.getElementsByTagName('compounddef')[0]
    comp_name = getTextRecursive(comp_def.getElementsByTagName('compoundname')[0]).replace('::', '.')
    doc_text = getDocText(comp_def)

    if doc_text:
        api_doc_db[comp_name] = doc_text

    sup_mem_kinds = [ 'function', 'variable' ]
        
    for mem_def in comp_def.getElementsByTagName('memberdef'):
        mem_kind = mem_def.attributes['kind'].value

        if mem_kind not in sup_mem_kinds:
            continue

        doc_text = getDocText(mem_def)

        if not doc_text:
            continue
        
        mem_name = getTextRecursive(mem_def.getElementsByTagName('name')[0]).strip()
        
        if mem_kind == 'function':
            num_args = len(mem_def.getElementsByTagName('param'))

            if mem_name.startswith('~'):
                mem_name = '__del__'
            else:
                comp_name_uq = comp_name.split('.')[-1]

                if comp_name_uq == mem_name:
                    mem_name = '__init__'
                elif mem_name == 'operator=':
                    mem_name = 'assign'
                elif mem_name == 'operator<':
                    mem_name = '__lt__'
                elif mem_name == 'operator>':
                    mem_name = '__gt__'
                elif mem_name == 'operator<=':
                    mem_name = '__le__'
                elif mem_name == 'operator>=':
                    mem_name = '__ge__'
                elif mem_name == 'operator!=':
                    mem_name = '__ne__'
                elif mem_name == 'operator==':
                    mem_name = '__eq__'
                    
            mem_name += '(' + str(num_args) + ')'

        api_doc_db[comp_name + '.' + mem_name] = doc_text
        
def extractCXXAPIDoc():
    if len(sys.argv) < 2:
        print('Usage:', sys.argv[0], '[C++ API doc. XML dir] [output file]', file=sys.stderr)
        sys.exit(2)

    api_doc_db = {}
        
    for f in glob.glob(path.join(sys.argv[1], '*.xml')):
        if 'hpp' in f or 'spacestd' in f or 'spaceboost' in f:
            continue
        
        if 'struct' in f or 'class' in f or 'namespace' in f:
            processCXXAPIDocFile(f, api_doc_db)

    out_file = open(sys.argv[2], 'w')

    for k, v in api_doc_db.items():
        out_file.write('>> ' + k + '\n')
        out_file.write(v + '\n')
    
    #pickle.dump(api_doc_db, out_file, protocol=pickle.DEFAULT_PROTOCOL)
    out_file.close()

if __name__ == '__main__':
    extractCXXAPIDoc()

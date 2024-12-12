## 
# GenDocSourceFiles.py 
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


from __future__ import print_function 

import sys
import inspect
import re
import pickle

import CDPL
import CDPL.Base
import CDPL.Util
import CDPL.Math
import CDPL.Chem
import CDPL.Vis
import CDPL.Pharm
import CDPL.Shape
import CDPL.Grid
import CDPL.ForceField
import CDPL.ConfGen
import CDPL.Biomol
import CDPL.Descr
import CDPL.MolProp
import CDPL.GRAIL


HIDE_SELF_ARG = True
DOC_FILE_EXT = '.doc.py'

FILE_HEADER = \
"""#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas Seidel <thomas.seidel@univie.ac.at>
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
#
"""

DOC_BLOCKS = []
CPP_API_DOC_BLOCKS = {}
CPP_API_DOC_MERGE_INFO = []
CPP_API_DOC_STR_REPLACEMENTS = []


def readLine(in_file):
    while True:
        line = in_file.readline()

        if not line:
            return None

        if line.startswith('#'):
            continue

        return line
        
def loadDocBlocks(file_name):
    global DOC_BLOCKS

    doc_ipt = open(file_name)

    while True:
        line = readLine(doc_ipt)

        if not line:
            break

        line = line.strip()

        if len(line) == 0:
            continue

        entry = []

        entry.append(line)

        while True:
            line = readLine(doc_ipt)

            if not line:
                break

            if line.startswith('$$$$'):
                break

            entry.append(line)
            
        DOC_BLOCKS.append(entry)
        
def parseStringReplacement(line):
    str_rpl = line.split('%')

    for i in range(2):
        str_rpl[i] = str_rpl[i].strip().replace('\\n', '\n')

        if str_rpl[i].startswith('\''):
            str_rpl[i] = str_rpl[i][1:]

        if str_rpl[i].endswith('\''):
            str_rpl[i] = str_rpl[i][:-1]

    return str_rpl
            
def loadCPPAPIDocMergeInfo(file_name):
    global CPP_API_DOC_MERGE_INFO
    global CPP_API_DOC_STR_REPLACEMENTS
    
    info_ipt = open(file_name)
    gen_repl_read = False
        
    while True:
        line = readLine(info_ipt)

        if not line:
            break

        if len(line.strip()) == 0:
            continue

        if not gen_repl_read:
            while True:
                if not line:
                    return

                if len(line.strip()) == 0:
                    break
                    
                CPP_API_DOC_STR_REPLACEMENTS.append(parseStringReplacement(line))
                line = readLine(info_ipt)
                
            gen_repl_read = True
            continue
                
        entry = line.split('%')

        entry[0] = entry[0].strip()
        entry[1] = entry[1].strip()

        entry.append([])

        while True:
            line = readLine(info_ipt)

            if not line:
                break

            if len(line.strip()) == 0:
                break

            entry[2].append(parseStringReplacement(line))
            
        CPP_API_DOC_MERGE_INFO.append(entry)

def getDocBlockEntry(key):
    for entry in DOC_BLOCKS:
        if entry[0].endswith('^'):
            if key.endswith(entry[0][0:-1]):
                return entry
            
        if key.find(entry[0]) != -1:
            return entry

    return None
      
def getProvidedDocBlock(key, func_data, func_name, class_name, is_static):
    if not is_static and class_name and func_data and len(func_data['arg_names']) == 2:
        if func_name == '__init__':
            if func_data['arg_types'][1].endswith(class_name):
                key = key.replace('.__init__(', '.__copy__init__(')
                
        elif func_name == 'assign':
            key = key.replace('.assign(', '.__copy__assign(')

    doc_block = getDocBlockEntry(key)

    if not doc_block:
        return None

    if not func_data:
        if not class_name:
            return ''.join(doc_block[1:])
        
        return ''.join([l.replace('@CN@', class_name) for l in doc_block[1:]])
    
    proc_args = []
    rc = []
    
    for line in doc_block[1:]:
        if not is_static and HIDE_SELF_ARG and line.lstrip().startswith('\\param @A0@'):
            continue
 
        line = line.replace('@CN@', class_name).replace('@MN@', func_name).replace('@RT@', func_data['ret_type'])
       
        if '@ARGS@' in line:
            for i in range(0, len(func_data['arg_names'])):
                if not is_static and HIDE_SELF_ARG and i == 0:
                    continue
                if func_data['arg_names'][i] in proc_args:
                    continue

                rc.append(line.replace('@ARGS@', func_data['arg_names'][i]))

            continue
            
        for i in range(0, len(func_data['arg_names'])):
            tmp_line = line.replace('@A' + str(i) + '@', func_data['arg_names'][i])

            if tmp_line != line:
                proc_args.append(func_data['arg_names'][i])
                
            line = tmp_line

        for i in range(0, len(func_data['arg_types'])):
            line = line.replace('@AT' + str(i) + '@', func_data['arg_types'][i])
                
        rc.append(line)
        
    return ''.join(rc)
      
def performGenericCPPAPIDocFixes(doc_block):
    for entry in CPP_API_DOC_STR_REPLACEMENTS:
        doc_block = doc_block.replace(entry[0], entry[1])

    return doc_block
    
def getAPIDocBlock(key, ident = '', func_data = None, func_name = None, class_name = None, is_static = True, verbatim_key = False):
    if not verbatim_key:
        key = sys.argv[1] + '.' + key

    doc_block = None
    
    for entry in CPP_API_DOC_MERGE_INFO:
        mod_key = key.replace(entry[0], entry[1])

        if mod_key in CPP_API_DOC_BLOCKS:
            doc_block = performGenericCPPAPIDocFixes(CPP_API_DOC_BLOCKS[mod_key])

            for str_repl in entry[2]:
                doc_block = doc_block.replace(str_repl[0], str_repl[1])

            break
                
    if not doc_block:
        if key in CPP_API_DOC_BLOCKS:
            doc_block = performGenericCPPAPIDocFixes(CPP_API_DOC_BLOCKS[key])
        else:
            doc_block = getProvidedDocBlock(key, func_data, func_name, class_name, is_static)

    if not doc_block:
        return None
    
    rc = [ ident ]

    rc.append('##\n')

    for line in doc_block.split('\n'):
        rc.append(ident)
        rc.append('# ')
        rc.append(line)
        rc.append('\n')

    return ''.join(rc)
    
def isProperty(obj):
    return type(obj).__name__ == 'property'

def isStaticProperty(class_obj, obj_name):
    if not obj_name in class_obj.__dict__.keys():
        return False

    return type(class_obj.__dict__[obj_name]).__name__ == 'StaticProperty'
    
def isClass(obj):
    return inspect.isclass(obj)

def isFunction(obj):
    return inspect.isfunction(obj) or type(obj).__name__ == 'function'

def isMethod(obj):
    return inspect.ismethod(obj) or isFunction(obj)

def isModule(obj):
    return inspect.ismodule(obj)

def isStaticMethod(class_obj, method_name):
    if not method_name in class_obj.__dict__.keys():
        return False
    
    return type(class_obj.__dict__[method_name]).__name__ == 'staticmethod'

def isVariable(obj):
    return not isFunction(obj) and not isClass(obj) and not isMethod(obj) and not isModule(obj)

def isEnumeration(obj):
    return isClass(obj) and obj.__bases__[0].__name__ == 'enum' 

def openOutputFile(name):
    out_file_name = sys.argv[2] + '/' + name + DOC_FILE_EXT
    out_file = open(out_file_name, 'w')

    out_file.write(FILE_HEADER)
    
    return out_file

def stripExtModuleName(name):
    name = name.replace('._chem', '')
    name = name.replace('._vis', '')
    name = name.replace('._util', '')
    name = name.replace('._base', '')
    name = name.replace('._math', '')
    name = name.replace('._util', '')
    name = name.replace('._pharm', '')
    name = name.replace('._biomol', '')
    name = name.replace('._forcefield', '')
    name = name.replace('._grid', '')
    name = name.replace('._shape', '')
    name = name.replace('._confgen', '')
    name = name.replace('._descr', '')
    name = name.replace('._molprop', '')
    name = name.replace('._grail', '')

    if sys.argv[1] != 'CDPL.Base':
        name = name.replace('CDPL.Base.OpenMode', 'Base.IOStream.OpenMode')
    else:
        name = name.replace('CDPL.Base.OpenMode', 'IOStream.OpenMode')
                
    name = name.replace('OpenMode24', 'OpenMode(24)')
    name = name.replace('OpenMode60', 'OpenMode(60)')
    name = name.replace('OpenMode12', 'OpenMode(12)')
    
    return name
    
def cleanModuleName(name):
    name = stripExtModuleName(name)

    name = name.replace('.Exceptions', '')
    #name = name.replace('__builtin__', '')
    name = name.replace('sre_parse', '')
    name = name.replace(sys.argv[1], '')
    name = name.replace('CDPL.', '')
    
    if len(name) > 0:
        name = name + '.'

    return name

def getBases(class_obj):
    bases = ''

    for base in class_obj.__bases__:
        if len(bases) > 0:
               bases = bases + ', '

        mod_name = cleanModuleName(base.__module__)
        
        bases = bases + mod_name + base.__name__

    return bases

def printMethod(class_obj, func_obj, method_name, out_file, ident, scope):
    is_static = isStaticMethod(class_obj, method_name)
    overloads = None

    if is_static == True:
        overloads = getFuncOverloads(getattr(class_obj, method_name), method_name)
    else:    
        overloads = getFuncOverloads(func_obj, method_name)

    if len(overloads) > 0:
        for func_data in overloads:
            if not is_static and func_data['ret_type'] == 'None' and func_data['arg_names'][0] == 'arg1':
                continue
            
            out_file.write('\n')

            if HIDE_SELF_ARG and not is_static:
                idx = func_data['arg_list'].find(',')

                if idx == -1:
                    func_data['arg_list'] = ''
                else:
                    func_data['arg_list'] = func_data['arg_list'][idx + 2:]

            doc_block = getAPIDocBlock(scope + getFunctionKey(func_data, not is_static), ident, func_data, method_name, class_obj.__name__, is_static)

            if doc_block:
                out_file.write(doc_block)
            else:
                out_file.write(ident + '##\n')
                #out_file.write(ident + '# \\brief ' + method_name + '.\n')
                out_file.write(ident + '# \\brief \n')

                if not is_static and not HIDE_SELF_ARG:
                    out_file.write(ident + '# \\param self The \\e %' + class_obj.__name__ + ' instance this method is called upon.\n')

                for arg_name in func_data['arg_names']:
                    if arg_name == 'self': continue

                    out_file.write(ident + '# \\param ' + arg_name + ' \n')

                if func_data['ret_type'] != 'None':
                    out_file.write(ident + '# \\return \n')

                out_file.write(ident + '#\n')

            if is_static:
                out_file.write(ident + '@staticmethod\n')

            if func_data['name'] == '__init__':
                func_data['ret_type'] = 'None'
                
            out_file.write(ident +'def ' + func_data['name'] + '(' + func_data['arg_list'] + ') -> ' + func_data['ret_type'] + ': pass\n')
    else:        
        args = ''
        out_file.write('\n')

        args = class_obj.__name__ + ' self'
        out_file.write(ident + '##\n')
        #out_file.write(ident + '# \\brief ' + method_name + '. FIXME!\n')
        out_file.write(ident + '# \\brief FIXME!\n')

        if not is_static and not HIDE_SELF_ARG:
            out_file.write(ident + '# \\param self The \\e %' + class_obj.__name__ + ' instance this method is called upon.\n')

        out_file.write(ident + '#\n')

        if is_static:
            out_file.write(ident + '@staticmethod\n')

        out_file.write(ident + 'def ' + method_name + '(' + args + '): -> None: pass\n')

def printEnumeration(enum_obj, out_file = None, ident = '', scope = ''):
    enum_name = enum_obj.__name__
    enum_name = enum_name.split('.')[-1]
    new_file = False

    if out_file == None:
        new_file = True
        out_file = openOutputFile(enum_name)
        printPackageHeader(out_file)

    out_file.write('\n')

    doc_block = getAPIDocBlock(scope + enum_name, ident, class_name=enum_obj.__name__)

    if doc_block:
        out_file.write(doc_block)
    else:
        out_file.write(ident + '##\n')
        #out_file.write(ident + '# \\brief Enumeration ' + enum_name + '.\n')
        out_file.write(ident + '# \\brief \n')
        out_file.write(ident + '#\n')

    out_file.write(ident + 'class ' + enum_name + '(' + getBases(enum_obj) + '):\n')

    for v, k in enum_obj.values.items():
        out_file.write('\n')

        doc_block = getAPIDocBlock(scope + enum_name + '.' + str(k), ident + '    ')

        if doc_block:
            out_file.write(doc_block)
        else:
            out_file.write(ident + '    ' + '##\n')
            out_file.write(ident + '    ' + '# \\brief ' + str(k) + '.\n')
            #out_file.write(ident + '    ' + '# \\brief \n')
            out_file.write(ident + '    ' + '#\n')

        out_file.write(ident + '    ' + str(k) + ' = ' + str(v) + '\n')

def printProperty(class_obj, prop_obj, property_name, out_file, ident, scope):
    cap_name = property_name[0].upper() + property_name[1:]
    rw_prop = (prop_obj.fset != None)
    get_meth_name = 'get' + cap_name
    set_meth_name = 'set' + cap_name
    get_meth_found = (get_meth_name in class_obj.__dict__.keys() )

    if not get_meth_found:
        db_entry = getDocBlockEntry(scope + property_name + '.value')

        if db_entry:
            get_meth_name = db_entry[1].strip()

            if rw_prop:
                set_meth_name = db_entry[2].strip()

            get_meth_found = True
        
    out_file.write('\n')  

    if not get_meth_found:
        out_file.write(ident + '##\n')
        out_file.write(ident + '# \\brief FIXME!\n')
        out_file.write(ident + '#\n')
        
    out_file.write(ident + property_name + ' = property(' + get_meth_name)

    if rw_prop:
        out_file.write(', ' + set_meth_name)
    
    out_file.write(')\n')

def getValueString(obj, is_prop = True):
    value = obj

    if is_prop:
        value = obj.fget()

    if value == None:
        return 'None'
    
    type_name = type(value).__name__

    if type_name == 'str':
        return "'" + value.replace('\n', '\\n').replace('\t', '\\t').replace('\r', '\\r')  + "'"

    value = str(value)

    if value.startswith('<'):
        return '_HIDDEN_VALUE_'

    return value.replace(sys.argv[1] + '.', '').replace('=true', '=True').replace('=false', '=False')

def getValueType(obj, is_prop = True):
    value = obj
    
    if is_prop:
        value = obj.fget()

    type_name = type(value).__name__

    if hasattr(value, '__module__'):
        mod_name = cleanModuleName(value.__module__)    
        type_name = mod_name + type_name

    return type_name

def printStaticProperty(property_obj, property_name, out_file, ident, scope, class_name):
    out_file.write('\n')

    doc_block = getAPIDocBlock(scope + property_name, ident, class_name=class_name)
    value_str = getValueString(property_obj)

    if value_str == '_HIDDEN_VALUE_':
        db_entry = getDocBlockEntry(scope + property_name + '.value')

        if db_entry:
            value_str = db_entry[1].strip()
        
    if doc_block:
        out_file.write(doc_block)
    else:
        out_file.write(ident + '##\n')
        out_file.write(ident + '# \\brief \n')
        out_file.write(ident + '#\n')

    out_file.write(ident + property_name + ' = ' + value_str + '\n')

def printClass(class_obj, out_file = None, ident = '', scope = ''):
    if out_file == None:
        out_file = openOutputFile(class_obj.__name__)

    ignored_names = [ '__doc__', '__file__', '__name__', '__path__', '__module__', '__class__', '__dict__', '__bases__', '__reduce__' ]
    
    out_file.write('\n')

    doc_block = getAPIDocBlock(scope + class_obj.__name__, ident, class_name=class_obj.__name__)

    if doc_block:
        out_file.write(doc_block)
    else:
        out_file.write(ident + '##\n')
        #out_file.write(ident + '# \\brief ' + class_obj.__name__ + '.\n')
        out_file.write(ident + '# \\brief \n')
        out_file.write(ident + '#\n')
    
    out_file.write(ident + 'class ' + class_obj.__name__ + '(' + getBases(class_obj) + '):\n')

    members = class_obj.__dict__.items()

    properties = list()
    static_properties = list()
    methods = list()
    enumerations = list()
    classes = list()
    constructors = list()
    special_methods = list()
    have_members = False
    
    for name, obj in members:
        if name in ignored_names:
            continue

        if name.startswith('_' + class_obj.__name__ + '_'):
            continue

        if len(name) > 1 and name.startswith('_') and name[1] != '_': # 'private' methods
            continue
        
        if isProperty(obj):
            properties.append((obj, name))
        elif isStaticProperty(class_obj, name):
            static_properties.append((obj, name))
        elif isMethod(obj) or isStaticMethod(class_obj, name):
            if name == '__init__':
                constructors.append((obj, name))
            elif name.startswith('__') and name.endswith('__'):
                special_methods.append((obj, name))
            else:    
                methods.append((obj, name))
        elif isEnumeration(obj):
            enumerations.append(obj)
        elif isClass(obj):
            classes.append(obj)

    mem_scope = scope + class_obj.__name__ + '.'
    mem_ident = ident + '    '
    
    for enum_obj in enumerations:
        have_members = True
        printEnumeration(enum_obj, out_file, mem_ident, mem_scope)

    for class_obj2 in classes:
        have_members = True
        printClass(class_obj2, out_file, mem_ident, mem_scope)

    for prop_data in static_properties:
        have_members = True
        printStaticProperty(prop_data[0], prop_data[1], out_file, mem_ident, mem_scope, class_obj.__name__ )    

    for method_data in constructors:
        have_members = True
        printMethod(class_obj, method_data[0], method_data[1], out_file, mem_ident, mem_scope)    

    for method_data in methods:
        have_members = True
        printMethod(class_obj, method_data[0], method_data[1], out_file, mem_ident, mem_scope)    

    for method_data in special_methods:
        have_members = True
        printMethod(class_obj, method_data[0], method_data[1], out_file, mem_ident, mem_scope)    

    for prop_data in properties:
        have_members = True
        printProperty(class_obj, prop_data[0], prop_data[1], out_file, mem_ident, mem_scope)    

    if not have_members:
        out_file.write(ident + '    pass\n')

def getFirstArgType(func_data):
    if len(func_data['arg_types']) == 0:
        return 'Misc'

    return func_data['arg_types'][0]

def getFunctionKey(func_data, mem_func=False):
    rc = [ func_data['name'] ]

    rc.append('(')

    for arg_name in func_data['arg_names']:
        if mem_func and arg_name == 'self':
            continue
        
        if len(rc) > 2:
            rc.append(',')
            
        rc.append(arg_name)

    rc.append(')')
    
    return ''.join(rc)

def printFunctions(func_objects):
    if len(func_objects) == 0:
        return

    out_file = None
    class_funcs = {}
    
    for func_obj in func_objects:
        overloads = getFuncOverloads(func_obj, func_obj.__name__)
    
        if len(overloads) > 0:
            for func_data in overloads:
                class_name = getFirstArgType(func_data)

                if not class_name in class_funcs:
                    class_funcs[class_name] = []

                class_funcs[class_name].append(func_data)
        else:
            if not out_file:
                out_file = openOutputFile('Functions')
                
            out_file.write('\n')
            out_file.write('##\n')
            #out_file.write('# \\brief ' + func_data['name'] + '. FIXME!\n')
            out_file.write('# \\brief FIXME!\n')
            out_file.write('#\n')
            out_file.write('def ' + func_data['name'] + '() -> None: pass\n')

    def func_sort_key(func_data):
        return func_data['name'][::-1]
    
    for class_name, func_list in class_funcs.items():
        out_file = openOutputFile(class_name + '_Functions')

        for func_data in sorted(func_list, key=func_sort_key):
            out_file.write('\n')

            doc_block = getAPIDocBlock(getFunctionKey(func_data), func_data=func_data, func_name=func_data['name'], class_name='')
        
            if doc_block:
                out_file.write(doc_block)
            else:
                out_file.write('##\n')
                #out_file.write('# \\brief ' + func_data['name'] + '.\n')
                out_file.write('# \\brief \n')
    
                for arg_name in func_data['arg_names']:
                    out_file.write('# \\param ' + arg_name + ' \n')

                if func_data['ret_type'] != 'None':
                    out_file.write('# \\return \n')

                out_file.write('#\n')
                    
            out_file.write('def ' + func_data['name'] + '(' + func_data['arg_list'] + ') -> ' + func_data['ret_type'] + ': pass\n')
            
def getFuncOverloads(func_obj, func_name):
    overloads = list()

    if func_obj.__doc__ is None:
        return overloads    

    for line in func_obj.__doc__.splitlines():
        line = line.strip()    
        
        if re.match(func_name + '\(.*\) -> .* :', line):
            arg_list, sep, ret_type = line.rpartition(' -> ')
            
            ret_type = ret_type.rstrip(':').rstrip()

            arg_list = arg_list.replace(func_name + '(', '')
            arg_list = arg_list.replace('(', '')
            arg_list = arg_list.replace(')', ' ')
            arg_list = arg_list.replace(' [', '')
            arg_list = arg_list.replace('[ ', '')
            arg_list = arg_list.replace(']', '')
            arg_list = arg_list.strip()

            func_arg_types = extractFuncArgTypes(arg_list)
            is_duplicate = False

            for func_data in overloads:
                if func_arg_types == func_data['arg_types']:
                    is_duplicate = True    
                    break    

            if not is_duplicate:    
                func_data = dict()
                
                func_data['name'] = func_name
                func_data['ret_type'] = extendByModuleName(ret_type)
                func_data['arg_list'] = addModulesToFuncArgTypes(arg_list)
                func_data['arg_types'] = func_arg_types
                func_data['arg_names'] = extractFuncArgNames(arg_list)                

                overloads.append(func_data)
    
    return overloads

def extractFuncArgTypes(arg_list):
    arg_types = list()

    for arg_type_and_name in arg_list.split(', '):
        arg_type, sep, name = arg_type_and_name.partition(' ')    
        arg_type = arg_type.strip()

        arg_types.append(arg_type)

    return arg_types

def extractFuncArgNames(arg_list):
    arg_names = list()

    for arg_type_and_name in arg_list.split(', '):
        arg_type, sep, name = arg_type_and_name.partition(' ')    

        if '=' in name:
            name, sep, def_val = name.partition('=')    

        name = name.strip()

        arg_names.append(name)

    return arg_names

def addModulesToFuncArgTypes(arg_list):
    new_arg_list = ''
    
    for arg_type_and_name in arg_list.split(', '):
        arg_type, sep, name = arg_type_and_name.partition(' ')
        def_val = None

        if '=' in name:
            name, sep, def_val = name.partition('=')
            name = name.strip()
            def_val = def_val.strip()
        
        arg_type = arg_type.strip()

        if len(new_arg_list) > 0:
            new_arg_list += ', '

        if name != 'self':
            arg_type = extendByModuleName(arg_type)
            
        if def_val:
            new_arg_list += name + ': ' + arg_type + ' = ' + stripExtModuleName(def_val)
        else:
            new_arg_list += name + ': ' + arg_type

    return new_arg_list

def printVariables(variable_objects):
    if len(variable_objects) == 0:
        return
    
    out_file = openOutputFile('Variables')

    for var_obj, name in variable_objects:
        if '__' in name or name == 'absolute_import':
            continue

        out_file.write('\n')
 
        doc_block = getAPIDocBlock(name)
        value_str = getValueString(var_obj, False)

        if value_str == '_HIDDEN_VALUE_':
            db_entry = getDocBlockEntry(sys.argv[1] + '.' + name + '.value')

            if db_entry:
                value_str = db_entry[1]

        if doc_block:
            out_file.write(doc_block)
        else:
            out_file.write('##\n')
            out_file.write('# \\brief \n')
            out_file.write('#\n')
        
        out_file.write(name)
        out_file.write(' = ' + value_str + '\n')

def outputPackageDoc():
    doc_block = getAPIDocBlock(sys.argv[1], verbatim_key=True)

    if not doc_block:
        return
    
    out_file = openOutputFile('Package')

    out_file.write('\n##\n')
    out_file.write('# \\package ')
    out_file.write(sys.argv[1])
    out_file.write('\n')
    
    for line in doc_block.split('\n')[1:]:
        out_file.write(line)
        out_file.write('\n')
    
def extendByModuleName(type_name):
    ignored_types = [ 'int', 'object', 'float', 'None', 'str', 'bool', 'list', 'tuple', 'dict' ]

    if type_name in ignored_types:
        return type_name
        
    for module in sys.modules.values():
        if module != None:
            if type_name in module.__dict__.keys():
                return cleanModuleName(module.__name__) +  type_name

    return type_name

def genPythonAPIDocFiles():
    if len(sys.argv) < 5:
        print('Usage:', sys.argv[0], '[package] [output dir] [c++ API doc blocks] [c++ API doc merge info] [[predef. doc blocks file], ...] ', file=sys.stderr)
        sys.exit(2)
   
    global CPP_API_DOC_BLOCKS
    
    CPP_API_DOC_BLOCKS = pickle.load(open(sys.argv[3], 'rb'))

    loadCPPAPIDocMergeInfo(sys.argv[4])
    
    if len(sys.argv) > 5:
        for file_name in sys.argv[5:]:
            loadDocBlocks(file_name.strip())
        
    __import__(sys.argv[1])

    module = sys.modules[sys.argv[1]]

    functions = []
    variables = []
    ignored_names = [ '__builtins__', '__doc__', '__file__', '__name__', '__path__', '_grid', '_forcefield',
                      '_chem', '_pharm', '_biomol', '_base', '_math', '_util', '_vis', '_descr', '_molprop', '__package__' ]
    exported_names = []

    if hasattr(module, '__all__'):
        exported_names = module.__all__    

    members = inspect.getmembers(module)

    for name, obj in members:
        if name in ignored_names:
            continue
        
        if len(exported_names) > 0 and not (name in exported_names):
            continue    

        if isFunction(obj):
            functions.append(obj)
        elif isVariable(obj):
            variables.append((obj, name))
        elif isEnumeration(obj):
            printEnumeration(obj, None, '', cleanModuleName(sys.argv[1]))
        elif isClass(obj):
            printClass(obj, None, '', cleanModuleName(sys.argv[1]))

    printFunctions(functions)
    printVariables(variables)
    outputPackageDoc()

if __name__ == '__main__':
    genPythonAPIDocFiles()

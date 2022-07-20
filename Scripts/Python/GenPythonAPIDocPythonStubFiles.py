# -*- mode: python; tab-width: 4 -*- 

## 
# GenPythonAPIDocFiles.py 
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


doc_file_ext = '.py'

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
    out_file_name = sys.argv[2] + '/pkg_' + name + doc_file_ext
    out_file = open(out_file_name, 'w')

    out_file.write('##\n' + \
    '# pkg_' + name + doc_file_ext + '\n' + \
    '#\n' + \
    '# This file is part of the Chemical Data Processing Toolkit\n' + \
    '#\n' + \
    '# Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>\n' + \
    '#\n' + \
    '# This program is free software; you can redistribute it and/or\n' + \
    '# modify it under the terms of the GNU Lesser General Public\n' + \
    '# License as published by the Free Software Foundation; either\n' + \
    '# version 2 of the License, or (at your option) any later version.\n' + \
    '#\n' + \
    '# This program is distributed in the hope that it will be useful,\n' + \
    '# but WITHOUT ANY WARRANTY; without even the implied warranty of\n' + \
    '# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU\n' + \
    '# Lesser General Public License for more details.\n' + \
    '#\n' + \
    '# You should have received a copy of the GNU Lesser General Public License\n' + \
    '# along with this program; see the file COPYING. If not, write to\n' + \
    '# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,\n' + \
    '# Boston, MA 02111-1307, USA.\n' + \
    '##\n')
    
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
    name = name.replace('OpenMode24', 'OpenMode(24)')

    return name
    
def cleanModuleName(name):
    name = stripExtModuleName(name)

    name = name.replace('.Exceptions', '')
    name = name.replace('__builtin__', '')
    name = name.replace('sre_parse', '')
    name = name.replace('builtins', '')
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

def printMethod(class_obj, func_obj, method_name, out_file, ident):
    is_static = isStaticMethod(class_obj, method_name)
    overloads = None

    if is_static == True:
        overloads = getFuncOverloads(getattr(class_obj, method_name), method_name)
    else:    
        overloads = getFuncOverloads(func_obj, method_name)

    if len(overloads) > 0:
        for func_data in overloads:
            out_file.write('\n')

            if is_static == False:
                out_file.write(ident + '##\n')
                out_file.write(ident + '# \\brief ' + method_name + '.\n')
                out_file.write(ident + '# \\param self The <tt>%' + class_obj.__name__ + '</tt> instance.\n')

                for name in func_data['arg_names']:
                    if name == 'self': continue

                    out_file.write(ident + '# \\param ' + name + '\n')

                if func_data['ret_type'] != 'None':
                    out_file.write(ident + '# \\return \n')

                out_file.write(ident + '#\n')
            else:    
                out_file.write(ident + '##\n')
                out_file.write(ident + '# \\brief ' + method_name + '.\n')

                for name in func_data['arg_names']:
                    out_file.write(ident + '# \\param ' + name + '\n')

                out_file.write(ident + '#\n')
                out_file.write(ident + '@staticmethod\n')

            out_file.write(ident +'def ' + func_data['name'] + '(' + func_data['arg_list'] + ') -> ' + func_data['ret_type'] + ': pass\n')
    else:        
        args = ''
        out_file.write('\n')

        if is_static == False:
            args = class_obj.__name__ + ' self'
            out_file.write(ident + '##\n')
            out_file.write(ident + '# \\brief ' + method_name + '. FIXME!\n')
            out_file.write(ident + '# \\param self The <tt>%' + class_obj.__name__ + '</tt> instance.\n')
            out_file.write(ident + '#\n')
        else:
            out_file.write(ident + '##\n')
            out_file.write(ident + '# \\brief ' + method_name + '. FIXME!\n')
            out_file.write(ident + '#\n')
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
    out_file.write(ident + '##\n')
    out_file.write(ident + '# \\brief ' + enum_name + '.\n')
    out_file.write(ident + '#\n')
    out_file.write(ident + 'class ' + enum_name + '(' + getBases(enum_obj) + '):\n')

    for v, k in enum_obj.values.items():
        out_file.write('\n')
        out_file.write(ident + '    ' + '##\n')
        out_file.write(ident + '    ' + '# \\brief ' + str(k) + '.\n')
        out_file.write(ident + '    ' + '#\n')
        out_file.write(ident + '    ' + str(k) + ' = ' + str(v) + '\n')

def printProperty(class_obj, prop_obj, property_name, out_file, ident):
    out_file.write('\n')
    out_file.write(ident + '##\n')
    out_file.write(ident + '# \\brief ' + property_name + '. FIXME!\n')
    out_file.write(ident + '# \\param self The <tt>%' + class_obj.__name__ + '</tt> instance.\n')
    out_file.write(ident + '#\n')
    out_file.write(ident + '@property\n')
    out_file.write(ident + 'def ' + property_name + '(self: ' + class_obj.__name__ + '): pass\n')

def getValueString(prop_obj):
    value = prop_obj.fget()
    type_name = type(value).__name__

    if type_name == 'str':
        return '"' + value + '"'

    value = str(value)

    if value.startswith('<'):
        return None

    return value.replace(sys.argv[1] + '.', '')

def getPropertyValueType(prop_obj):
    try:
        value = prop_obj.fget()
        type_name = type(value).__name__

        if hasattr(value, '__module__'):
            mod_name = cleanModuleName(value.__module__)    
            type_name = mod_name + type_name

        return type_name

    except:
        return 'None'

def getVariableValueType(var_obj):
    try:
        type_name = type(var_obj).__name__

        if hasattr(var_obj, '__module__'):
            mod_name = cleanModuleName(var_obj.__module__)    
            type_name = mod_name + type_name

        return type_name

    except:
        return 'None'

def printStaticProperty(property_obj, property_name, out_file, ident):
    out_file.write('\n')
    out_file.write(ident + '##\n')

    value_str = getValueString(property_obj)

    if value_str != None:
        out_file.write(ident + '# \\brief ' + property_name + '.\n')
    else:
        out_file.write(ident + '# \\brief ' + property_name + '. FIXME!\n')

    out_file.write(ident + '# \\valuetype ' + getPropertyValueType(property_obj) + '\n')
    out_file.write(ident + '#\n')
    out_file.write(ident + property_name)
 
    if value_str != None:
        out_file.write(' = ' + value_str + '\n')
    else:
        out_file.write(' = None\n')

def printClass(class_obj, out_file = None, ident = '', scope = ''):
    if out_file == None:
        out_file = openOutputFile(class_obj.__name__)

    ignored_names = [ '__doc__', '__file__', '__name__', '__path__', '__module__', '__class__', '__dict__', '__bases__', '__reduce__' ]
    
    out_file.write('\n')
    out_file.write(ident + '##\n')
    out_file.write(ident + '# \\brief ' + class_obj.__name__ + '.\n')
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

    for enum_obj in enumerations:
        have_members = True
        printEnumeration(enum_obj, out_file, ident + '    ', scope + class_obj.__name__ + '.')

    for class_obj2 in classes:
        have_members = True
        printClass(class_obj2, out_file, ident + '    ', scope + class_obj.__name__ + '.')

    for prop_data in static_properties:
        have_members = True
        printStaticProperty(prop_data[0], prop_data[1], out_file, ident + '    ')    

    for method_data in constructors:
        have_members = True
        printMethod(class_obj, method_data[0], method_data[1], out_file, ident + '    ')    

    for method_data in methods:
        have_members = True
        printMethod(class_obj, method_data[0], method_data[1], out_file, ident + '    ')    

    for method_data in special_methods:
        have_members = True
        printMethod(class_obj, method_data[0], method_data[1], out_file, ident + '    ')    

    for prop_data in properties:
        have_members = True
        printProperty(class_obj, prop_data[0], prop_data[1], out_file, ident + '    ')    

    if not have_members:
        out_file.write(ident + '    pass\n')
        
def printFunctions(func_objects):
    if len(func_objects) == 0:
        return

    out_file = openOutputFile('Functions')

    for func_obj in func_objects:
        overloads = getFuncOverloads(func_obj, func_obj.__name__)
    
        if len(overloads) > 0:
            for func_data in overloads:
                out_file.write('\n')
                out_file.write('##\n')
                out_file.write('# \\brief ' + func_obj.__name__ + '.\n')
    
                for name in func_data['arg_names']:
                    out_file.write('# \\param ' + name + '\n')

                if func_data['ret_type'] != 'None':
                    out_file.write('# \\return \n')

                out_file.write('#\n')
                out_file.write('def ' + func_data['name'] + '(' + func_data['arg_list'] + ') -> ' + func_data['ret_type'] + ': pass\n')
        else:        
            out_file.write('\n')
            out_file.write('##\n')
            out_file.write('# \\brief ' + func_obj.__name__ + '. FIXME!\n')
            out_file.write('#\n')
            out_file.write('def ' + func_obj.__name__ + '() -> None: pass\n')

def getFuncOverloads(func_obj, func_name):
    overloads = list()

    if func_obj.__doc__ is None:
        return overloads    

    for line in func_obj.__doc__.splitlines():
        line = line.strip()    
        
        if re.match(func_name + '\(.*\) -> .* :', line):
            arg_list, sep, ret_type = line.rpartition(' -> ')
            
            ret_type = ret_type.rstrip(':').rstrip()

            arg_list = arg_list.replace(func_name, '')
            arg_list = arg_list.replace('(', '')
            arg_list = arg_list.replace(')', ' ')
            arg_list = arg_list.replace(' [', '')
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
        out_file.write('##\n')

        value_str = getVariableValueString(var_obj)

        if value_str != None:
            out_file.write('# \\brief ' + name + '.\n')
        else:
            out_file.write('# \\brief ' + name + '. FIXME!\n')

        out_file.write('# \\valuetype ' + getVariableValueType(var_obj) + '\n')
        out_file.write('#\n')
        out_file.write(name)

        if value_str != None:
            out_file.write(' = ' + value_str + '\n')
        else:
            out_file.write(' = None\n')

def extendByModuleName(type_name):
    for module in sys.modules.values():
        if module != None:
            if type_name in module.__dict__.keys():
                return cleanModuleName(module.__name__) + type_name

    return type_name    

def genPythonAPIDocFiles():
    if len(sys.argv) < 2:
        print('Usage:', sys.argv[0], '[package] [output dir]', file=sys.stderr)
        sys.exit(2)

    __import__(sys.argv[1])

    module = sys.modules[sys.argv[1]]

    functions = []
    variables = []
    
    ignored_names = [ '__builtins__', '__doc__', '__file__', '__name__', '__path__', '_grid', '_forcefield', '_chem', '_pharm', '_biomol', '_base', '_math', '_util', '_vis', '__package__' ]
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

if __name__ == '__main__':
    genPythonAPIDocFiles()

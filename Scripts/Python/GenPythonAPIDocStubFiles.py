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


HIDE_SELF_ARG = True
DOC_FILE_EXT = '.py'
FILE_HEADER = \
"""#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

__init__DOC_TEMPLATE = \
"""##
# \\brief Initializes the \\e %@CN@ instance.
# \\param @A0@ The \\e %@CN@ instance to initialize.
# \\param @ARGS@ 
#
"""

__str__DOC_TEMPLATE = \
"""##
# \\brief Returns a string representation of the \\e %@CN@ instance.
# \\param @A0@ The \\e %@CN@ instance this method is called upon.
# \\return The generated string representation.
#
"""

__lt__DOC_TEMPLATE = \
"""##
# \\brief Returns the result of the comparison operation <tt>@A0@ < @A1@</tt>.
# \\param @A0@ The \\e %@CN@ instance this method is called upon.
# \\param @A1@ The \\e %@AT1@ instance to be compared with.
# \\return The result of the comparison operation.
#
"""

__le__DOC_TEMPLATE = \
"""##
# \\brief Returns the result of the comparison operation <tt>@A0@ <= @A1@</tt>.
# \\param @A0@ The \\e %@CN@ instance this method is called upon.
# \\param @A1@ The \\e %@AT1@ instance to be compared with.
# \\return The result of the comparison operation.
#
"""

__gt__DOC_TEMPLATE = \
"""##
# \\brief Returns the result of the comparison operation <tt>@A0@ > @A1@</tt>.
# \\param @A0@ The \\e %@CN@ instance this method is called upon.
# \\param @A1@ The \\e %@AT1@ instance to be compared with.
# \\return The result of the comparison operation.
#
"""

__ge__DOC_TEMPLATE = \
"""##
# \\brief Returns the result of the comparison operation <tt>@A0@ >= @A1@</tt>.
# \\param @A0@ The \\e %@CN@ instance this method is called upon.
# \\param @A1@ The \\e %@AT1@ instance to be compared with.
# \\return The result of the comparison operation.
#
"""

__ne__DOC_TEMPLATE = \
"""##
# \\brief Returns the result of the comparison operation <tt>@A0@ != @A1@</tt>.
# \\param @A0@ The \\e %@CN@ instance this method is called upon.
# \\param @A1@ The \\e %@AT1@ instance to be compared with.
# \\return The result of the comparison operation.
#
"""

__eq__DOC_TEMPLATE = \
"""##
# \\brief Returns the result of the comparison operation <tt>@A0@ == @A1@</tt>.
# \\param @A0@ The \\e %@CN@ instance this method is called upon.
# \\param @A1@ The \\e %@AT1@ instance to be compared with.
# \\return The result of the comparison operation.
#
"""

__contains__DOC_TEMPLATE = \
"""##
# \\brief Returns the result of the membership test operation <tt>@A1@ in @A0@</tt>.
# \\param @A0@ The \\e %@CN@ instance this method is called upon.
# \\param @A1@ The value to test for membership.
# \\return The result of the membership test operation.
#
"""

__iadd__DOC_TEMPLATE = \
"""##
# \\brief Performs the in-place addition operation <tt>@A0@ += @A1@</tt>.
# \\param @A0@ The \\e %@CN@ instance acting as in-place addend.
# \\param @A1@ Specifies the second addend.
# \\return The updated \\e %@RT@ instance \\a @A0@.
#
"""

__isub__DOC_TEMPLATE = \
"""##
# \\brief Performs the in-place subtraction operation <tt>@A0@ -= @A1@</tt>.
# \\param @A0@ The \\e %@CN@ instance acting as in-place minuend.
# \\param @A1@ Specifies the subtrahend.
# \\return The updated \\e %@RT@ instance \\a @A0@.
#
"""

__imul__DOC_TEMPLATE = \
"""##
# \\brief Performs the in-place multiplication operation <tt>@A0@ *= @A1@</tt>.
# \\param @A0@ The \\e %@CN@ instance acting as in-place multiplicand.
# \\param @A1@ Specifies the multiplier.
# \\return The updated \\e %@RT@ instance \\a @A0@.
#
"""

__idiv__DOC_TEMPLATE = \
"""##
# \\brief Performs the in-place division operation <tt>@A0@ /= @A1@</tt>.
# \\param @A0@ The \\e %@CN@ instance acting as in-place dividend.
# \\param @A1@ Specifies the divisor.
# \\return The updated \\e %@RT@ instance \\a @A0@.
#
"""

__add__DOC_TEMPLATE = \
"""##
# \\brief Returns the result of the addition operation <tt>@A0@ + @A1@</tt>.
# \\param @A0@ The \\e %@CN@ instance representing the first addend.
# \\param @A1@ Specifies the second addend.
# \\return A \\e %@RT@ instance holding the result of the addition.
#
"""

__sub__DOC_TEMPLATE = \
"""##
# \\brief Returns the result of the subtraction operation <tt>@A0@ - @A1@</tt>.
# \\param @A0@ The \\e %@CN@ instance acting as minuend.
# \\param @A1@ Specifies the subtrahend.
# \\return A \\e %@CN@ instance holding the result of the subtraction.
#
"""

__mul__DOC_TEMPLATE = \
"""##
# \\brief Returns the result of the multiplication operation <tt>@A0@ * @A1@</tt>.
# \\param @A0@ The \\e %@CN@ instance acting as multiplicand.
# \\param @A1@ Specifies the multiplier.
# \\return A \\e %@RT@ instance holding the result of the multiplication.
#
"""

__div__DOC_TEMPLATE = \
"""##
# \\brief Returns the result of the division operation <tt>@A0@ / @A1@</tt>.
# \\param @A0@ The \\e %@CN@ instance acting as dividend.
# \\param @A1@ Specifies the divisor.
# \\return A \\e %@RT@ instance holding the result of the division.
#
"""

assign_DOC_TEMPLATE = \
"""##
# \\brief Replaces the current state of \\a @A0@ with a copy of the state of the \\e %@AT1@ instance \\a @A1@.
# \\param @A0@ The \\e %@CN@ instance this method is called upon.
# \\param @A1@ The \\e %@AT1@ instance to copy.
# \\return \\a @A0@
#
"""

getObjectID_DOC_TEMPLATE = \
"""##
# \\brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
# \\param @A0@ The \\e %@CN@ instance this method is called upon.
#
# Different Python \\e %@CN@ instances may reference the same underlying C++ class instance. The commonly used Python expression
# <tt>a is not b</tt> thus cannot tell reliably whether the two \\e %@CN@ instances \\e a and \\e b reference different C++ objects. 
# The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
# <tt>a.getObjectID() != b.getObjectID()</tt>.
#
# \\return The numeric ID of the internally referenced C++ class instance.
#
"""


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
    out_file_name = sys.argv[2] + '/pkg_' + name + DOC_FILE_EXT
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
    name = name.replace('OpenMode24', 'OpenMode(24)')
    name = name.replace('OpenMode60', 'OpenMode(60)')

    return name
    
def cleanModuleName(name):
    name = stripExtModuleName(name)

    name = name.replace('.Exceptions', '')
    #name = name.replace('__builtin__', '')
    name = name.replace('sre_parse', '')
    name = name.replace(sys.argv[1], '')
    #name = name.replace('CDPL.', '')
    
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

def printSpecialMethodDoc(class_obj, func_obj, method_name, out_file, ident, func_data, is_static):
    mn_to_doc_tmplts = { '__str__': __str__DOC_TEMPLATE, '__ne__': __ne__DOC_TEMPLATE, \
                         '__eq__': __eq__DOC_TEMPLATE, '__init__': __init__DOC_TEMPLATE, \
                         '__lt__': __lt__DOC_TEMPLATE, '__le__': __le__DOC_TEMPLATE, \
                         '__gt__': __gt__DOC_TEMPLATE, '__ge__': __ge__DOC_TEMPLATE, \
                         '__contains__': __contains__DOC_TEMPLATE, '__iadd__': __iadd__DOC_TEMPLATE, \
                         '__isub__': __isub__DOC_TEMPLATE, '__imul__': __imul__DOC_TEMPLATE, \
                         '__idiv__': __idiv__DOC_TEMPLATE, '__add__': __add__DOC_TEMPLATE, \
                         '__sub__': __sub__DOC_TEMPLATE, '__mul__': __mul__DOC_TEMPLATE, \
                         '__div__': __div__DOC_TEMPLATE, 'assign': assign_DOC_TEMPLATE,
                         'getObjectID': getObjectID_DOC_TEMPLATE }

    if method_name not in mn_to_doc_tmplts:
        return False

    tmplt = mn_to_doc_tmplts[method_name]
    proc_args = []
   
    for line in tmplt.splitlines(True):
        if not is_static and HIDE_SELF_ARG and line.lstrip().startswith('# \\param @A0@'):
            continue
 
        line = line.replace('@CN@', class_obj.__name__).replace('@MN@', method_name).replace('@RT@', func_data['ret_type'])
       
        if '@ARGS@' in line:
            for i in range(0, len(func_data['arg_names'])):
                if not is_static and HIDE_SELF_ARG and i == 0:
                    continue
                if func_data['arg_names'][i] in proc_args:
                    continue

                out_file.write(ident + line.replace('@ARGS@', func_data['arg_names'][i]))

            continue
            
        for i in range(0, len(func_data['arg_names'])):
            tmp_line = line.replace('@A' + str(i) + '@', func_data['arg_names'][i])

            if tmp_line != line:
                proc_args.append(func_data['arg_names'][i])
                
            line = tmp_line

        for i in range(0, len(func_data['arg_types'])):
            line = line.replace('@AT' + str(i) + '@', func_data['arg_types'][i])
                
        out_file.write(ident + line)
        
    return True
    
def printMethod(class_obj, func_obj, method_name, out_file, ident):
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
                    
            if not printSpecialMethodDoc(class_obj, func_obj, method_name, out_file, ident, func_data, is_static):
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
    out_file.write(ident + '##\n')
    #out_file.write(ident + '# \\brief Enumeration ' + enum_name + '.\n')
    out_file.write(ident + '# \\brief \n')
    out_file.write(ident + '#\n')
    out_file.write(ident + 'class ' + enum_name + '(' + getBases(enum_obj) + '):\n')

    for v, k in enum_obj.values.items():
        out_file.write('\n')
        out_file.write(ident + '    ' + '##\n')
        out_file.write(ident + '    ' + '# \\brief ' + str(k) + '.\n')
        #out_file.write(ident + '    ' + '# \\brief \n')
        out_file.write(ident + '    ' + '#\n')
        out_file.write(ident + '    ' + str(k) + ' = ' + str(v) + '\n')

def printProperty(class_obj, prop_obj, property_name, out_file, ident):
    cap_name = property_name[0].upper() + property_name[1:]
    rw_prop = (prop_obj.fset != None)
    get_meth_name = 'get' + cap_name
    set_meth_name = 'set' + cap_name
    get_meth_found = (get_meth_name in class_obj.__dict__.keys() )
    
    out_file.write('\n')
    out_file.write(ident + '##\n')

    if not get_meth_found:
        out_file.write(ident + '# \\brief FIXME!\n')
    else:
        out_file.write(ident + '# \\brief \n')

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
        return '_UNKNOWN_VALUE_'

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

def printStaticProperty(property_obj, property_name, out_file, ident):
    out_file.write('\n')
    out_file.write(ident + '##\n')

    value_str = getValueString(property_obj)

    if value_str != '_UNKNOWN_VALUE_':
        #out_file.write(ident + '# \\brief ' + property_name + '.\n')
        out_file.write(ident + '# \\brief \n')
    else:
        #out_file.write(ident + '# \\brief ' + property_name + '. FIXME!\n')
        out_file.write(ident + '# \\brief FIXME!\n')

    #out_file.write(ident + '# \\valuetype ' + getValueType(property_obj) + '\n')
    out_file.write(ident + '#\n')
    out_file.write(ident + property_name)
    out_file.write(' = ' + value_str + '\n')

def printClass(class_obj, out_file = None, ident = '', scope = ''):
    if out_file == None:
        out_file = openOutputFile(class_obj.__name__)

    ignored_names = [ '__doc__', '__file__', '__name__', '__path__', '__module__', '__class__', '__dict__', '__bases__', '__reduce__' ]
    
    out_file.write('\n')
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

def getFirstArgType(func_data):
    if len(func_data['arg_types']) == 0:
        return 'Misc'

    return func_data['arg_types'][0]

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
        out_file.write('##\n')

        value_str = getValueString(var_obj, False)

        if value_str != '_UNKNOWN_VALUE_':
            #out_file.write('# \\brief ' + name + '.\n')
            out_file.write('# \\brief \n')
        else:
            #out_file.write('# \\brief ' + name + '. FIXME!\n')
            out_file.write('# \\brief FIXME!\n')

        #out_file.write('# \\valuetype ' + getValueType(var_obj, False) + '\n')
        out_file.write('#\n')
        out_file.write(name)
        out_file.write(' = ' + value_str + '\n')

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

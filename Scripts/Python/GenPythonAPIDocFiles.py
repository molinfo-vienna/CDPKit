# -*- mode: python; tab-width: 4 -*- 

## 
# GenPythonAPIDocFiles.py 
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003-2008 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
import inspect
import re


header_line = '/* -*- mode: java; tab-width: 4 -*- */\n'
doc_file_ext = '.doc'

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

def printPackageHeader(out_file):
	out_file.write('\n')
	out_file.write('package ' + sys.argv[1] + ';\n')

def openOutputFile(name):
	out_file_name = sys.argv[2] + '/' + name + doc_file_ext
	out_file = open(out_file_name, 'w')
	out_file.write(header_line)

	return out_file

def cleanModuleName(name):
	name = name.replace(sys.argv[1], '')
	name = name.replace('CDPL.', '')
	name = name.replace('._chem', '')
	name = name.replace('._vis', '')
	name = name.replace('._util', '')
	name = name.replace('._base', '')
	name = name.replace('._math', '')
	name = name.replace('._util', '')
	name = name.replace('.Exceptions', '')
	name = name.replace('__builtin__', '')

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
				out_file.write(ident + '/**\n')
				out_file.write(ident + ' * \\brief ' + method_name + '.\n')
				out_file.write(ident + ' * \\param self The <tt>%' + class_obj.__name__ + '</tt> instance.\n')
				out_file.write(ident + ' */\n')
			else:	
				out_file.write(ident + '/**\n')
				out_file.write(ident + ' * \\brief ' + method_name + '.\n')
				out_file.write(ident + ' */\n')

			out_file.write(ident + 'public ')

			if is_static == True:
				out_file.write('static ')
		
			out_file.write(func_data['ret_type'] + ' ' + func_data['name'] + '(' + func_data['arg_list'] + ') {}\n')
	else:		
		args = ''
		out_file.write('\n')

		if is_static == False:
			args = class_obj.__name__ + ' self'
			out_file.write(ident + '/**\n')
			out_file.write(ident + ' * \\brief ' + method_name + '.\n')
			out_file.write(ident + ' * \\param self The <tt>%' + class_obj.__name__ + '</tt> instance.\n')
			out_file.write(ident + ' */\n')
		else:
			out_file.write(ident + '/**\n')
			out_file.write(ident + ' * \\brief ' + method_name + '.\n')
			out_file.write(ident + ' */\n')

		out_file.write(ident + 'public ')

		if is_static == True:
			out_file.write('static ')

		out_file.write('None ' + method_name + '(' + args + ') {}\n')

def printEnumeration(enum_obj, out_file = None, ident = '', scope = ''):
	enum_name = enum_obj.__name__
	enum_name = enum_name.split('.')[-1]
	new_file = False

	if out_file == None:
		new_file = True
		out_file = openOutputFile(enum_name)
		printPackageHeader(out_file)

	out_file.write('\n')
	out_file.write(ident + '/**\n')
	out_file.write(ident + ' * \\brief ' + enum_name + '.\n')
	out_file.write(ident + ' */\n')
	out_file.write(ident + 'public static class ' + enum_name + ' extends ' + getBases(enum_obj) + ' {\n')

	for v, k in enum_obj.values.items():
		out_file.write('\n')
		out_file.write(ident + '\t' + '/**\n')
		out_file.write(ident + '\t' + ' * \\brief ' + str(k) + '.\n')
		out_file.write(ident + '\t' + ' */\n')
		out_file.write(ident + '\tpublic static ' + enum_name + ' ' + str(k) + ';\n')

	out_file.write(ident + '}\n')	

	for v, k in enum_obj.values.items():
		out_file.write('\n')
		out_file.write(ident + '/**\n')
		out_file.write(ident + ' * \\brief See ' + enum_name + '.' + str(k) + '.\n')
		out_file.write(ident + ' */\n')
		out_file.write(ident)

		if new_file == False:
			out_file.write('public static ')

		out_file.write(scope + enum_name + ' ' + str(k) + ';\n')

def printProperty(property_name, out_file, ident):
	out_file.write('\n')
	out_file.write(ident + '/**\n')
	out_file.write(ident + ' * \\brief ' + property_name + '.\n')
	out_file.write(ident + ' */\n')
	out_file.write(ident + 'public None ' + property_name + ';\n')

def getPropertyValueString(prop_obj):
	value = prop_obj.fget()
	type_name = type(value).__name__

	if type_name == 'str':
		return '"' + value + '"'

	if type_name == 'int' or type_name == 'float' or type_name == 'long' or type_name == 'bool':
		return str(value)

	return None

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

def getVariableValueString(var_obj):
	type_name = type(var_obj).__name__

	if type_name == 'str':
		return '"' + var_obj + '"'

	if type_name == 'int' or type_name == 'float' or type_name == 'long' or type_name == 'bool':
		return str(var_obj)

	return None

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
	out_file.write(ident + '/**\n')
	out_file.write(ident + ' * \\brief ' + property_name + '.\n')
	out_file.write(ident + ' */\n')
	out_file.write(ident + 'public static ' + getPropertyValueType(property_obj) + ' ' + property_name)

	value_str = getPropertyValueString(property_obj)

	if value_str != None:
		out_file.write(' = ' + value_str + ';\n')
	else:
		out_file.write(';\n')

def printClass(class_obj, out_file = None, ident = '', scope = ''):
	if out_file == None:
		out_file = openOutputFile(class_obj.__name__)
		printPackageHeader(out_file)

	ignored_names = [ '__doc__', '__file__', '__name__', '__path__', '__module__', '__class__', '__dict__', '__bases__', '__reduce__' ]
	
	out_file.write('\n')
	out_file.write(ident + '/**\n')
	out_file.write(ident + ' * \\brief ' + class_obj.__name__ + '.\n')
	out_file.write(ident + ' */\n')
	out_file.write(ident + 'public class ' + class_obj.__name__ + ' extends ' + getBases(class_obj) + ' {\n')

	members = class_obj.__dict__.items()

	properties = list()
	static_properties = list()
	methods = list()
    enumerations = list()
	classes = list()
	constructors = list()
	special_methods = list()

	for name, obj in members:
		if name in ignored_names:
			continue

		if isProperty(obj):
			properties.append(name)
			#printProperty(name, out_file, ident + '\t')
		elif isStaticProperty(class_obj, name):
			static_properties.append((obj, name))
			#printStaticProperty(obj, name, out_file, ident + '\t')
		elif isMethod(obj) or isStaticMethod(class_obj, name):
			if name == '__init__':
				constructors.append((obj, name))
			elif name.startswith('__') and name.endswith('__'):
				special_methods.append((obj, name))
			else:	
				methods.append((obj, name))
			#printMethod(class_obj, obj, name, out_file, ident + '\t')
		elif isEnumeration(obj):
			enumerations.append(obj)
			#printEnumeration(obj, out_file, ident + '\t', scope + class_obj.__name__ + '.')
		elif isClass(obj):
			classes.append(obj)
			#printClass(obj, out_file, ident + '\t', scope + class_obj.__name__ + '.')

	for enum_obj in enumerations:
		printEnumeration(enum_obj, out_file, ident + '\t', scope + class_obj.__name__ + '.')

	for class_obj2 in classes:
		printClass(class_obj2, out_file, ident + '\t', scope + class_obj.__name__ + '.')

	for prop_data in static_properties:
		printStaticProperty(prop_data[0], prop_data[1], out_file, ident + '\t')	

	for method_data in constructors:
		printMethod(class_obj, method_data[0], method_data[1], out_file, ident + '\t')	

	for method_data in methods:
		printMethod(class_obj, method_data[0], method_data[1], out_file, ident + '\t')	

	for method_data in special_methods:
		printMethod(class_obj, method_data[0], method_data[1], out_file, ident + '\t')	

	for prop_name in properties:
		printProperty(prop_name, out_file, ident + '\t')	

	out_file.write(ident + '}\n')

def printFunctions(func_objects):
	if len(func_objects) == 0:
		return

	out_file = openOutputFile('Functions')
	printPackageHeader(out_file)

	for func_obj in func_objects:
		overloads = getFuncOverloads(func_obj, func_obj.__name__)
	
		if len(overloads) > 0:
			for func_data in overloads:
				out_file.write('\n')
				out_file.write('/**\n')
				out_file.write(' * \\brief ' + func_obj.__name__ + '.\n')
				out_file.write(' */\n')
				out_file.write(func_data['ret_type'] + ' ' + func_data['name'] + '(' + func_data['arg_list'] + ') {}\n')
		else:		
			out_file.write('\n')
			out_file.write('/**\n')
			out_file.write(' * \\brief ' + func_obj.__name__ + '.\n')
			out_file.write(' */\n')
			out_file.write('None ' + func_obj.__name__ + '() {}\n')

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
			arg_list = arg_list.replace('=', ' = ')
			arg_list = arg_list.strip()

			func_arg_types = extractFuncArgTypes(arg_list)
			is_duplicate = False

			for func_data in overloads:
				if func_arg_types == func_data['func_arg_types']:
					is_duplicate = True	
					break	

			if not is_duplicate:	
				func_data = dict()
				
				func_data['name'] = func_name
				func_data['ret_type'] = extendByModuleName(ret_type)
				func_data['arg_list'] = addModulesToFuncArgTypes(arg_list)
				func_data['func_arg_types'] = func_arg_types
				
				overloads.append(func_data)
	
	return overloads

def extractFuncArgTypes(arg_list):
    arg_types = list()

	for arg_type_and_name in arg_list.split(', '):
		arg_type, sep, name = arg_type_and_name.partition(' ')	
		arg_type = arg_type.strip()

		arg_types.append(arg_type)

	return arg_types

def addModulesToFuncArgTypes(arg_list):
	new_arg_list = ''
	
	for arg_type_and_name in arg_list.split(', '):
		arg_type, sep, name = arg_type_and_name.partition(' ')	
		arg_type = arg_type.strip()

		if len(new_arg_list) > 0:
			new_arg_list += ', '
			
		new_arg_list += extendByModuleName(arg_type) + ' ' + name

	return new_arg_list

def printVariables(variable_objects):
	if len(variable_objects) == 0:
		return
	
	out_file = openOutputFile('Variables')
	printPackageHeader(out_file)

	for var_obj, name in variable_objects:
		out_file.write('\n')
		out_file.write('/**\n')
		out_file.write(' * \\brief ' + name + '.\n')
		out_file.write(' */\n')
		out_file.write(getVariableValueType(var_obj) + ' ' + name)

		value_str = getVariableValueString(var_obj)

		if value_str != None:
			out_file.write(' = ' + value_str + ';\n')
		else:
			out_file.write(';\n')

def extendByModuleName(type_name):
	for module in sys.modules.values():
		if module != None:
			if module.__dict__.has_key(type_name):
				return cleanModuleName(module.__name__) + type_name

	return type_name	

def genPythonAPIDocFiles():
	if len(sys.argv) < 3:
		print >> sys.stderr, 'Usage:', sys.argv[0], 'package output-dir'
		sys.exit(2)

	__import__(sys.argv[1])

	module = sys.modules[sys.argv[1]]

	functions = []
	variables = []
	
	ignored_names = [ '__builtins__', '__doc__', '__file__', '__name__', '__path__', '_chem', '_base', '_math', '_util', '_vis', '__package__' ]
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

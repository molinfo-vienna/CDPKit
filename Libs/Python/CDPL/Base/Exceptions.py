# -*- mode: python; tab-width: 4 -*-

## 
# Exceptions.py 
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


from __future__ import absolute_import

try:
    import exceptions
except ImportError:
    import builtins as exceptions

from . import _base


class Exception(exceptions.Exception):

    def __init__(self, msg = ''):
        "__init__(Exception self, str msg='') -> None :"
        exceptions.Exception.__init__(self, msg)
        self.message = msg

    def what(self):
        "what(Exception self) -> str :"
        return self.message

    def __str__(self):
        "__str__(Exception self) -> str :"
        return self.message


class ValueError(Exception, exceptions.ValueError):
    pass


class NullPointerException(ValueError):
    pass


class RangeError(ValueError):
    pass


class SizeError(ValueError):
    pass


class IndexError(RangeError, exceptions.IndexError):
    pass


class ItemNotFound(Exception):
    pass


class BadCast(Exception):
    pass


class OperationFailed(Exception):
    pass


class CalculationFailed(OperationFailed):
    pass


class IOError(OperationFailed, exceptions.IOError):
    pass


_base._ExceptionMapping.Exception = Exception
_base._ExceptionMapping.ValueError = ValueError
_base._ExceptionMapping.SizeError = SizeError
_base._ExceptionMapping.NullPointerException = NullPointerException
_base._ExceptionMapping.RangeError = RangeError
_base._ExceptionMapping.IndexError = IndexError
_base._ExceptionMapping.ItemNotFound = ItemNotFound
_base._ExceptionMapping.BadCast = BadCast
_base._ExceptionMapping.OperationFailed = OperationFailed
_base._ExceptionMapping.CalculationFailed = CalculationFailed
_base._ExceptionMapping.IOError = IOError

#
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

##
# \brief A wrapper class for various types of callable objects.
# 
class VoidDataIOBaseFunctor(Boost.Python.instance):

    ##
    # \brief Initializes the \c VoidDataIOBaseFunctor instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c VoidDataIOBaseFunctor instance \a func.
    # \param func The \c VoidDataIOBaseFunctor instance to copy.
    # 
    def __init__(func: VoidDataIOBaseFunctor) -> None: pass

    ##
    # \brief Initializes the \c VoidDataIOBaseFunctor instance for the specified callable object.
    # \param callable The callable object to wrap.
    # 
    def __init__(callable: object) -> None: pass

    ##
    # \brief Invokes the wrapped callable object with the given arguments.
    # \param arg1 The first argument to forward.
    # \param arg2 The second argument to forward.
    # \return The obtained return value.
    # 
    def __call__(arg1: DataIOBase, arg2: float) -> None: pass

    ##
    # \brief Tells whether the instance holds a callable object.
    # \return \c True if the instance holds a callable object, and \c False otherwise.
    # 
    def __bool__() -> bool: pass

    ##
    # \brief Tells whether the instance holds a callable object.
    # \return \c True if the instance holds a callable object, and \c False otherwise.
    # 
    def __nonzero__() -> bool: pass

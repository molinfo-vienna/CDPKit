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
# \brief A generic wrapper class used to store a user-defined callback functions.
# 
class LogMessageCallbackFunction(Boost.Python.instance):

    ##
    # \brief Initializes the \e %LogMessageCallbackFunction instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %LogMessageCallbackFunction instance \a func.
    # \param func The \e %LogMessageCallbackFunction instance to copy.
    # 
    def __init__(func: LogMessageCallbackFunction) -> None: pass

    ##
    # \brief Initializes the \e %LogMessageCallbackFunction instance.
    # \param callable 
    # 
    def __init__(callable: object) -> None: pass

    ##
    # \brief 
    # \param arg1 
    #
    def __call__(arg1: str) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def __bool__() -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def __nonzero__() -> bool: pass

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
# \brief Provides infrastructure for the registration of I/O callback functions.
# 
# The purpose of <tt>DataIOBase</tt> is to provide methods for the registration of I/O callback functions to subclasses implementing the input and output of data objects (see Base.DataReader and Base.DataWriter). I/O callbacks allow client code to be notified whenever a data object was read, written or skipped. I/O callbacks are registered by calling the method registerIOCallback() with an argument of type DataIOBase.IOCallbackFunction. DataIOBase.IOCallbackFunction is a generic functor implementation that is able to wrap any compatible (in terms of return and argument type) function reference or function object. Therefore, no special requirements beside return and argument types are imposed on the type of the used I/O callback target function.
# 
class DataIOBase(ControlParameterContainer):

    ##
    # \brief Default constructor.
    # 
    def __init__() -> None: pass

    ##
    # \brief Registers an I/O callback target function.
    # 
    # \param func A DataIOBase.IOCallbackFunction instance wrapping the target function.
    # 
    # \return An identifier for the registered callback.
    # 
    def registerIOCallback(func: VoidDataIOBaseFunctor) -> int: pass

    ##
    # \brief Unregisters the I/O callback function specified by <em>id</em>.
    # 
    # If a registered callback with the identifier <em>id</em> does not exist, the method has no effect.
    # 
    # \param id The identifier of the callback function to unregister.
    # 
    def unregisterIOCallback(id: int) -> None: pass

    ##
    # \brief Invokes all registered I/O callback functions with the argument <tt>self</tt>.
    # 
    # \param progress An indicator for the progress of the current I/O operation in the range [0, 1].
    # 
    def invokeIOCallbacks(progress: float) -> None: pass

    ##
    # \brief Clears all registered I/O callback functions.
    # 
    def clearIOCallbacks() -> None: pass

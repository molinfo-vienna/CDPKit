#
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

##
# \brief 
#
class SizeSpecification(Boost.Python.instance):

    ##
    # \brief Initializes the \e %SizeSpecification instance.
    # \param self The \e %SizeSpecification instance to initialize.
    # \param spec 
    #
    def __init__(self: object, spec: SizeSpecification) -> None: pass

    ##
    # \brief Initializes the \e %SizeSpecification instance.
    # \param self The \e %SizeSpecification instance to initialize.
    # \param value 
    # \param relative 
    # \param input_scaling 
    # \param output_scaling 
    #
    def __init__(self: object, value: float = 0.0, relative: bool = False, input_scaling: bool = False, output_scaling: bool = False) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %SizeSpecification instance this method is called upon.
    #
    # Different Python \e %SizeSpecification instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %SizeSpecification instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: SizeSpecification) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %SizeSpecification instance \a spec.
    # \param self The \e %SizeSpecification instance this method is called upon.
    # \param spec The \e %SizeSpecification instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: SizeSpecification, spec: SizeSpecification) -> SizeSpecification: pass

    ##
    # \brief 
    # \param self The \e %SizeSpecification instance this method is called upon.
    # \return 
    #
    def followsInputScaling(self: SizeSpecification) -> bool: pass

    ##
    # \brief 
    # \param self The \e %SizeSpecification instance this method is called upon.
    # \param follow 
    #
    def followInputScaling(self: SizeSpecification, follow: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %SizeSpecification instance this method is called upon.
    # \return 
    #
    def followsOutputScaling(self: SizeSpecification) -> bool: pass

    ##
    # \brief 
    # \param self The \e %SizeSpecification instance this method is called upon.
    # \param follow 
    #
    def followOutputScaling(self: SizeSpecification, follow: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %SizeSpecification instance this method is called upon.
    # \return 
    #
    def isRelative(self: SizeSpecification) -> bool: pass

    ##
    # \brief 
    # \param self The \e %SizeSpecification instance this method is called upon.
    # \param relative 
    #
    def setRelative(self: SizeSpecification, relative: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %SizeSpecification instance this method is called upon.
    # \return 
    #
    def getValue(self: SizeSpecification) -> float: pass

    ##
    # \brief 
    # \param self The \e %SizeSpecification instance this method is called upon.
    # \param value 
    #
    def setValue(self: SizeSpecification, value: float) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == spec</tt>.
    # \param self The \e %SizeSpecification instance this method is called upon.
    # \param spec The \e %SizeSpecification instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: SizeSpecification, spec: SizeSpecification) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != spec</tt>.
    # \param self The \e %SizeSpecification instance this method is called upon.
    # \param spec The \e %SizeSpecification instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: SizeSpecification, spec: SizeSpecification) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %SizeSpecification instance.
    # \param self The \e %SizeSpecification instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: SizeSpecification) -> str: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief FIXME!
    #
    inputScaling = property(getInputScaling, setInputScaling)

    ##
    # \brief FIXME!
    #
    outputScaling = property(getOutputScaling, setOutputScaling)

    ##
    # \brief FIXME!
    #
    relative = property(getRelative, setRelative)

    ##
    # \brief 
    #
    value = property(getValue, setValue)

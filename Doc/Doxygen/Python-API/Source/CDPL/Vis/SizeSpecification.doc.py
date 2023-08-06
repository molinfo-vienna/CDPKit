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
# \brief Specifies the value and type of a size attribute and defines how the value may change during processing steps.
# 
class SizeSpecification(Boost.Python.instance):

    ##
    # \brief Initializes the \e %SizeSpecification instance with a copy of the state of the \e %SizeSpecification instance \a spec.
    # \param spec The \e %SizeSpecification instance to copy.
    # 
    def __init__(spec: SizeSpecification) -> None: pass

    ##
    # \brief Constructs a <tt>SizeSpecification</tt> object with the given attributes.
    # 
    # \param value The value of the specified size.
    # \param relative <tt>True</tt> if the size specification is relative (proportional) to another size, and <tt>False</tt> otherwise.
    # \param input_scaling <tt>True</tt> if the specified size has to follow input scaling, and <tt>False</tt> otherwise.
    # \param output_scaling <tt>True</tt> if the specified size has to follow output scaling, and <tt>False</tt> otherwise.
    # 
    # \see setValue(), setRelative(), followInputScaling(), followOutputScaling()
    # 
    def __init__(value: float = 0.0, relative: bool = False, input_scaling: bool = False, output_scaling: bool = False) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %SizeSpecification instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %SizeSpecification instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %SizeSpecification instance \a spec.
    # \param spec The \e %SizeSpecification instance to copy.
    # \return \a self
    # 
    def assign(spec: SizeSpecification) -> SizeSpecification: pass

    ##
    # \brief Tells if the specified size follows input scaling operations.
    # 
    # \return <tt>True</tt> if the specified size follows input scaling operations, and <tt>False</tt> otherwise. 
    # 
    # \see followInputScaling()
    # 
    def followsInputScaling() -> bool: pass

    ##
    # \brief Specifies whether the specified size has to follow input scaling operations.
    # 
    # Input scaling is a pre-processing step (performed by some other part of the system) where an input size quantity is scaled to fulfill a certain constraint. An example is the scaling of input atom coordinates to obtain a certain average bond length for the 2D depiction of a chemical structure or reaction.
    # 
    # \param follow <tt>True</tt> if the specified size has to follow input scaling operations, and <tt>False</tt> otherwise.
    # 
    def followInputScaling(follow: bool) -> None: pass

    ##
    # \brief Tells if the specified size follows output scaling operations.
    # 
    # \return <tt>True</tt> if the specified size follows output scaling operations, and <tt>False</tt> otherwise. 
    # 
    # \see followOutputScaling()
    # 
    def followsOutputScaling() -> bool: pass

    ##
    # \brief Specifies whether the specified size has to follow output scaling operations.
    # 
    # Output scaling is a post-processing step (performed by some other part of the system) where an output size quantity is scaled to fulfill a certain constraint. An example is the scaling of output atom coordinates to fit the 2D depiction of a chemical structure or reaction into the viewport area.
    # 
    # \param follow <tt>True</tt> if the specified size has to follow output scaling operations, and <tt>False</tt> otherwise.
    # 
    def followOutputScaling(follow: bool) -> None: pass

    ##
    # \brief Tells if the size specification is absolute or relative to another size.
    # 
    # \return <tt>True</tt> if the size specification is relative, and <tt>False</tt> otherwise. 
    # 
    # \see setRelative()
    # 
    def isRelative() -> bool: pass

    ##
    # \brief Specifies if the size specification is absolute or relative to another size.
    # 
    # If the size specification is relative (proportional) to another size, the size value is interpreted as a scaling factor for the absolute value of the other size.
    # 
    # \param relative <tt>True</tt> if the size specification is relative, and <tt>False</tt> otherwise.
    # 
    # \see setValue()
    # 
    def setRelative(relative: bool) -> None: pass

    ##
    # \brief Returns the value of the specified size.
    # 
    # \return The value of the specified size. 
    # 
    # \see setValue()
    # 
    def getValue() -> float: pass

    ##
    # \brief Sets value of the specified size.
    # 
    # \param value The value of the specified size.
    # 
    def setValue(value: float) -> None: pass

    ##
    # \brief Equality comparison operator.
    # 
    # \param spec The other <tt>SizeSpecification</tt> object to be compared with.
    # 
    # \return <tt>True</tt> if all attributes compare equal, and <tt>False</tt> otherwise.
    # 
    def __eq__(spec: SizeSpecification) -> bool: pass

    ##
    # \brief Inequality comparison operator.
    # 
    # The result is equivalent to <tt>!(self == spec)</tt>.
    # 
    # \param spec The other <tt>SizeSpecification</tt> object to be compared with.
    # 
    # \return <tt>True</tt> if one of the attributes compares non-equal, and <tt>False</tt> otherwise.
    # 
    def __ne__(spec: SizeSpecification) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %SizeSpecification instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    objectID = property(getObjectID)

    inputScaling = property(followsInputScaling, followInputScaling)

    outputScaling = property(followsOutputScaling, followOutputScaling)

    relative = property(isRelative, setRelative)

    value = property(getValue, setValue)

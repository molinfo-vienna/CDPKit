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
# \brief A data structure for the common storage of related atom to atom and bond to bond mappings.
# 
# <tt>AtomBondMapping</tt> is used to represent arbitrary mappings between the atoms and bonds of two (or more) molecular graphs (e.g. results of a substructure search). The atom and bond mappings are stored in respective data members of type Chem.AtomMapping and Chem.BondMapping. They can be accessed by the provided getAtomMapping() and getBondMapping() family of overloaded methods.
# 
class AtomBondMapping(Boost.Python.instance):

    ##
    # \brief Initializes the \e %AtomBondMapping instance.
    # \param self The \e %AtomBondMapping instance to initialize.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %AtomBondMapping instance.
    # \param self The \e %AtomBondMapping instance to initialize.
    # \param mapping 
    # 
    def __init__(mapping: AtomBondMapping) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %AtomBondMapping instance this method is called upon.
    # 
    # Different Python \e %AtomBondMapping instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %AtomBondMapping instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param mapping 
    # \return 
    #
    def assign(mapping: AtomBondMapping) -> AtomBondMapping: pass

    ##
    # \brief Returns a reference to the Chem.AtomMapping data member storing the atom to atom mappings.
    # 
    # \return A reference to the Chem.AtomMapping data member.
    # 
    def getAtomMapping() -> AtomMapping: pass

    ##
    # \brief Returns a reference to the Chem.BondMapping data member storing the bond to bond mappings.
    # 
    # \return A reference to the Chem.BondMapping data member.
    # 
    def getBondMapping() -> BondMapping: pass

    ##
    # \brief Removes all atom to atom and bond to bond mappings.
    # 
    def clear() -> None: pass

    ##
    # \brief Equality comparison operator.
    # 
    # \param mapping The other <tt>AtomBondMapping</tt> instance to be compared with.
    # 
    # \return <tt>True</tt> if the atom to atom and bond to bond mappings compare equal, and <tt>False</tt> otherwise.
    # 
    def __eq__(mapping: AtomBondMapping) -> bool: pass

    ##
    # \brief Inequality comparison operator.
    # 
    # The result is equivalent to <tt>!(self == mapping)</tt>.
    # 
    # \param mapping The other <tt>AtomBondMapping</tt> instance to be compared with.
    # 
    # \return <tt>True</tt> if the atom to atom and/or bond to bond mappings compare non-equal, and <tt>False</tt> otherwise. 
    # 
    # \see __eq__()
    # 
    def __ne__(mapping: AtomBondMapping) -> bool: pass

    objectID = property(getObjectID)

    atomMapping = property(getAtomMapping)

    bondMapping = property(getBondMapping)

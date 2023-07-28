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
# \brief A common interface for data-structures that support a random access to stored Chem.Bond instances.
# 
# Implementations have to guarantee that a given Chem.Bond object is stored only once and its index is unique amongst all contained Chem.Bond instances. Otherwise algorithms that rely on this behaviour may not work correctly!
# 
class BondContainer(Boost.Python.instance):

    ##
    # \brief Initializes the \e %BondContainer instance.
    # \param self The \e %BondContainer instance to initialize.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns a reference to the bond at index <em>idx</em>.
    # 
    # \param idx The zero-based index of the Chem.Bond instance to return.
    # 
    # \return A reference to the bond at the specified index. 
    # 
    # \throw Base.IndexError if the number of bonds is zero or <em>idx</em> is not in the range [0, getNumBonds() - 1].
    # 
    def getBond(idx: int) -> Bond: pass

    ##
    # \brief Tells whether the specified Chem.Bond instance is stored in this container.
    # 
    # \param bond The Chem.Bond instance to look for.
    # 
    # \return <tt>True</tt> if <em>bond</em> is stored in the container, and <tt>False</tt> otherwise.
    # 
    def containsBond(bond: Bond) -> bool: pass

    ##
    # \brief Orders the stored bonds according to criteria implemented by the provided bond comparison function.
    # 
    # \param func The bond comparison function implementing the applied ordering criteria.
    # 
    def orderBonds(func: BoolBond2Functor) -> None: pass

    ##
    # \brief Returns the index of the specified Chem.Bond instance in this container.
    # 
    # \param bond The Chem.Bond instance for which to return the index.
    # 
    # \return The zero-based index of the specified Chem.Bond instance. 
    # 
    # \throw Base.ItemNotFound if the specified Chem.Bond instance could not be found.
    # 
    def getBondIndex(bond: Bond) -> int: pass

    ##
    # \brief Returns the number of stored Chem.Bond objects.
    # 
    # \return The number of stored Chem.Bond objects.
    # 
    def getNumBonds() -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %BondContainer instance this method is called upon.
    # 
    # Different Python \e %BondContainer instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %BondContainer instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Returns the result of the membership test operation <tt>bond in self</tt>.
    # \param self The \e %BondContainer instance this method is called upon.
    # \param bond The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(bond: Bond) -> bool: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def __getitem__(idx: int) -> Bond: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    objectID = property(getObjectID)

    numBonds = property(getNumBonds)

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
# \brief A common interface for data-structures that support a random access to stored Chem.Atom instances.
# 
# Implementations have to guarantee that a given Chem.Atom object is stored only once and its index is unique amongst all contained Chem.Atom instances. Otherwise algorithms that rely on this behaviour may not work correctly!
# 
class AtomContainer(Entity3DContainer):

    ##
    # \brief Initializes the \e %AtomContainer instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns a reference to the atom at index <em>idx</em>.
    # 
    # \param idx The zero-based index of the Chem.Atom instance to return.
    # 
    # \return A reference to the atom at the specified index. 
    # 
    # \throw Base.IndexError if the number of atoms is zero or <em>idx</em> is not in the range [0, getNumAtoms() - 1].
    # 
    def getAtom(idx: int) -> Atom: pass

    ##
    # \brief Tells whether the specified Chem.Atom instance is stored in this container.
    # 
    # \param atom The Chem.Atom instance to look for.
    # 
    # \return <tt>True</tt> if <em>atom</em> is stored in the container, and <tt>False</tt> otherwise.
    # 
    def containsAtom(atom: Atom) -> bool: pass

    ##
    # \brief Returns the index of the specified Chem.Atom instance in this container.
    # 
    # \param atom The Chem.Atom instance for which to return the index.
    # 
    # \return The zero-based index of the specified Chem.Atom instance. 
    # 
    # \throw Base.ItemNotFound if the specified Chem.Atom instance could not be found.
    # 
    def getAtomIndex(atom: Atom) -> int: pass

    ##
    # \brief Returns the number of stored Chem.Atom objects.
    # 
    # \return The number of stored Chem.Atom objects.
    # 
    def getNumAtoms() -> int: pass

    ##
    # \brief Orders the stored atoms according to criteria implemented by the provided atom comparison function.
    # 
    # \param func The atom comparison function implementing the applied ordering criteria.
    # 
    def orderAtoms(func: ForceField.InteractionFilterFunction2) -> None: pass

    ##
    # \brief Returns a reference to the entity at index <em>idx</em>.
    # 
    # \param idx The zero-based index of the Chem.Entity3D instance to return.
    # 
    # \return A reference to the entity at the specified index. 
    # 
    # \throw Base.IndexError if the number of entities is zero or <em>idx</em> is not in the range [0, getNumEntities() - 1].
    # 
    def getEntity(idx: int) -> Entity3D: pass

    ##
    # \brief Returns the number of stored Chem.Entity3D objects.
    # 
    # \return The number of stored Chem.Entity3D objects.
    # 
    def getNumEntities() -> int: pass

    ##
    # \brief Returns the result of the membership test operation <tt>atom in self</tt>.
    # \param atom The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(atom: Atom) -> bool: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def __getitem__(idx: int) -> Atom: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    numAtoms = property(getNumAtoms)

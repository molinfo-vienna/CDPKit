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
# \brief Data structure representing a canonicalized molecular fragment.
# 
# A <tt>CanonicalFragment</tt> is constructed from a fragment of a parent molecular graph and stores a canonicalized copy of the fragment's atoms and bonds. Canonicalization yields a stable atom ordering and an associated hash code that uniquely identifies the topology (and, optionally, the stereochemistry) of the fragment.
# 
# \see ConfGen.FragmentLibrary
# 
class CanonicalFragment(Chem.MolecularGraph):

    ##
    # \brief Maps each atom of the fragment (in canonical order) to the corresponding atom of the parent molecular graph.
    # 
    class AtomMapping(Boost.Python.instance):

        ##
        # \brief 
        # \return 
        #
        def __len__() -> int: pass

        ##
        # \brief 
        # \param idx 
        # \return 
        #
        def __getitem__(idx: int) -> Chem.Atom: pass

    ##
    # \brief Constructs an empty <tt>CanonicalFragment</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a <tt>CanonicalFragment</tt> instance from the fragment <em>molgraph</em> of the parent molecular graph <em>parent</em>.
    # 
    # \param molgraph The molecular graph defining the fragment to canonicalize.
    # \param parent The parent molecular graph the fragment was derived from.
    # 
    def __init__(molgraph: Chem.MolecularGraph, parent: Chem.MolecularGraph) -> None: pass

    ##
    # \brief Constructs a copy of the <tt>CanonicalFragment</tt> instance <em>frag</em>.
    # 
    # \param frag The <tt>CanonicalFragment</tt> to copy.
    # 
    def __init__(frag: CanonicalFragment) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %CanonicalFragment instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %CanonicalFragment instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the contents of this fragment with a copy of <em>frag</em>.
    # 
    # \param frag The source <tt>CanonicalFragment</tt>.
    # 
    # \return \a self
    # 
    def assign(frag: CanonicalFragment) -> CanonicalFragment: pass

    ##
    # \brief Builds the canonical fragment from the fragment <em>molgraph</em> of the parent molecular graph <em>parent</em>.
    # 
    # \param molgraph The molecular graph defining the fragment to canonicalize.
    # \param parent The parent molecular graph the fragment was derived from.
    # \param modify If <tt>True</tt>, the fragment is modified prior to canonicalization (e.g. ring perception, hydrogenization).
    # \param strip_aro_subst If <tt>True</tt>, aromatic-ring substituents are stripped during fragment construction.
    # 
    def create(molgraph: Chem.MolecularGraph, parent: Chem.MolecularGraph, modify: bool = True, strip_aro_subst: bool = True) -> None: pass

    ##
    # \brief Returns the hash code of the fragment.
    # 
    # \return The fragment hash code (<em>0</em> if not yet computed).
    # 
    def getHashCode() -> int: pass

    ##
    # \brief Removes all atoms and bonds and resets the hash code.
    # 
    def clear() -> None: pass

    ##
    # \brief Returns the atom mapping from this fragment to the parent molecular graph.
    # 
    # \return A reference to the atom mapping.
    # 
    def getAtomMapping() -> Chem.AtomMapping: pass

    objectID = property(getObjectID)

    hashCode = property(getHashCode)

    atomMapping = property(getAtomMapping)

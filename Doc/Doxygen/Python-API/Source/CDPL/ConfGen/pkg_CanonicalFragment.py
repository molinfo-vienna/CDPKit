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
# \brief CanonicalFragment.
# 
class CanonicalFragment(CDPL.Chem.MolecularGraph):

    ##
    # \brief 
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
        def __getitem__(idx: int) -> CDPL.Chem.Atom: pass

    ##
    # \brief Constructs an empty <tt>CanonicalFragment</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a <tt>CanonicalFragment</tt> instance that contains the relevant atoms and bonds of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to generate the fragments.
    # \param parent The parent molecular graph the fragment is coming from.
    # 
    def __init__(molgraph: CDPL.Chem.MolecularGraph, parent: CDPL.Chem.MolecularGraph) -> None: pass

    ##
    # \brief Initializes the \e %CanonicalFragment instance.
    # \param self The \e %CanonicalFragment instance to initialize.
    # \param frag 
    # 
    def __init__(frag: CanonicalFragment) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %CanonicalFragment instance this method is called upon.
    # 
    # Different Python \e %CanonicalFragment instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %CanonicalFragment instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %CanonicalFragment instance \a frag.
    # \param self The \e %CanonicalFragment instance this method is called upon.
    # \param frag The \e %CanonicalFragment instance to copy.
    # \return \a self
    # 
    def assign(frag: CanonicalFragment) -> CanonicalFragment: pass

    ##
    # \brief 
    # \param molgraph 
    # \param parent 
    # \param modify 
    #
    def create(molgraph: CDPL.Chem.MolecularGraph, parent: CDPL.Chem.MolecularGraph, modify: bool = True) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getHashCode() -> int: pass

    ##
    # \brief 
    #
    def clear() -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getAtomMapping() -> CDPL.Chem.AtomMapping: pass

    objectID = property(getObjectID)

    hashCode = property(getHashCode)

    atomMapping = property(getAtomMapping)

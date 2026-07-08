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
# \brief Data structure representing a single entry of a conformer generation fragment library.
# 
# Each entry is identified by the hash code of the associated ConfGen.CanonicalFragment and stores the canonical <em>SMILES</em> string plus a list of ConformerData instances (one per stored conformer).
# 
class FragmentLibraryEntry(Boost.Python.instance):

    ##
    # \brief Constructs an empty <tt>FragmentLibraryEntry</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %FragmentLibraryEntry instance \a entry.
    # \param entry The \c %FragmentLibraryEntry instance to copy.
    # 
    def __init__(entry: FragmentLibraryEntry) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %FragmentLibraryEntry instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %FragmentLibraryEntry instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %FragmentLibraryEntry instance \a entry.
    # \param entry The \c %FragmentLibraryEntry instance to copy.
    # \return \a self
    # 
    def assign(entry: FragmentLibraryEntry) -> FragmentLibraryEntry: pass

    ##
    # \brief Sets the hash code identifying the entry within the FragmentLibrary.
    # 
    # \param hash_code The new hash code.
    # 
    def setHashCode(hash_code: int) -> None: pass

    ##
    # \brief Returns the hash code identifying the entry within the FragmentLibrary.
    # 
    # \return The hash code.
    # 
    def getHashCode() -> int: pass

    ##
    # \brief Sets the canonical <em>SMILES</em> string describing the stored fragment.
    # 
    # \param smiles The new <em>SMILES</em> string.
    # 
    def setSMILES(smiles: str) -> None: pass

    ##
    # \brief Returns the canonical <em>SMILES</em> string describing the stored fragment.
    # 
    # \return A reference to the <em>SMILES</em> string.
    # 
    def getSMILES() -> str: pass

    ##
    # \brief Returns the number of atoms of the stored fragment.
    # 
    # \return The number of atoms (zero if no conformer has been added yet).
    # 
    def getNumAtoms() -> int: pass

    ##
    # \brief Returns the number of stored conformers.
    # 
    # \return The number of stored conformers.
    # 
    def getNumConformers() -> int: pass

    ##
    # \brief Removes all stored conformers from the entry.
    # 
    def clearConformers() -> None: pass

    ##
    # \brief Appends the given conformer to the entry.
    # 
    # \param conf_data A smart reference to the conformer data to add.
    # 
    def addConformer(conf_data: ConformerData) -> None: pass

    ##
    # \brief Returns a reference to the stored conformer at index <em>idx</em>.
    # 
    # \param idx The zero-based conformer index.
    # 
    # \return A reference to the conformer. 
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getNumConformers()).
    # 
    def getConformer(idx: int) -> ConformerData: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def __getitem__(idx: int) -> ConformerData: pass

    objectID = property(getObjectID)

    numConformers = property(getNumConformers)

    numAtoms = property(getNumAtoms)

    hashCode = property(getHashCode, setHashCode)

    smiles = property(getSMILES, setSMILES)

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
# \brief FragmentLibraryEntry.
# 
class FragmentLibraryEntry(Boost.Python.instance):

    ##
    # \brief Constructs an empty <tt>FragmentLibraryEntry</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %FragmentLibraryEntry instance with a copy of the state of the \e %FragmentLibraryEntry instance \a entry.
    # \param entry The \e %FragmentLibraryEntry instance to copy.
    # 
    def __init__(entry: FragmentLibraryEntry) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %FragmentLibraryEntry instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FragmentLibraryEntry instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FragmentLibraryEntry instance \a entry.
    # \param entry The \e %FragmentLibraryEntry instance to copy.
    # \return \a self
    # 
    def assign(entry: FragmentLibraryEntry) -> FragmentLibraryEntry: pass

    ##
    # \brief 
    # \param hash_code 
    #
    def setHashCode(hash_code: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getHashCode() -> int: pass

    ##
    # \brief 
    # \param smiles 
    #
    def setSMILES(smiles: str) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getSMILES() -> str: pass

    ##
    # \brief 
    # \return 
    #
    def getNumAtoms() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getNumConformers() -> int: pass

    ##
    # \brief 
    #
    def clearConformers() -> None: pass

    ##
    # \brief 
    # \param conf_data 
    #
    def addConformer(conf_data: ConformerData) -> None: pass

    ##
    # \brief 
    # \param idx 
    # \return 
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

    ##
    # \brief FIXME!
    # \brief 
    #
    smiles = property(getSmiles, setSmiles)

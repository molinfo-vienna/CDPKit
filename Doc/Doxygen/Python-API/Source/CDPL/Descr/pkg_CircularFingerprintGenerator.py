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
class CircularFingerprintGenerator(Boost.Python.instance):

    ##
    # \brief 
    #
    class DefAtomIdentifierFunctor(Boost.Python.instance):

        ##
        # \brief Initializes the \e %DefAtomIdentifierFunctor instance.
        # \param flags 
        #
        def __init__(flags: int = 3166) -> None: pass

        ##
        # \brief 
        # \param atom 
        # \param molgraph 
        # \return 
        #
        def __call__(atom: CDPL.Chem.Atom, molgraph: CDPL.Chem.MolecularGraph) -> int: pass

    ##
    # \brief 
    #
    class DefBondIdentifierFunctor(Boost.Python.instance):

        ##
        # \brief Initializes the \e %DefBondIdentifierFunctor instance.
        # \param flags 
        #
        def __init__(flags: int = 10) -> None: pass

        ##
        # \brief 
        # \param bond 
        # \return 
        #
        def __call__(bond: CDPL.Chem.Bond) -> int: pass

    ##
    # \brief 
    #
    DEF_ATOM_PROPERTY_FLAGS = 3166

    ##
    # \brief 
    #
    DEF_BOND_PROPERTY_FLAGS = 10

    ##
    # \brief Initializes the \e %CircularFingerprintGenerator instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %CircularFingerprintGenerator instance.
    # \param gen 
    #
    def __init__(gen: ._descr.CircularFingerprintGenerator) -> None: pass

    ##
    # \brief Initializes the \e %CircularFingerprintGenerator instance.
    # \param molgraph 
    # \param fp 
    #
    def __init__(molgraph: CDPL.Chem.MolecularGraph, fp: CDPL.Util.BitSet) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %CircularFingerprintGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %CircularFingerprintGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param func 
    #
    def setAtomIdentifierFunction(func: CDPL.Chem.SizeTypeAtomMolecularGraphFunctor) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setBondIdentifierFunction(func: CDPL.Chem.UInt64BondFunctor) -> None: pass

    ##
    # \brief 
    # \param num_bits 
    #
    def setNumBits(num_bits: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumBits() -> int: pass

    ##
    # \brief 
    # \param num_iter 
    #
    def setNumIterations(num_iter: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumIterations() -> int: pass

    ##
    # \brief 
    # \param remove 
    #
    def removeDuplicates(remove: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def duplicatesRemoved() -> bool: pass

    ##
    # \brief 
    # \param molgraph 
    # \param fp 
    #
    def generate(molgraph: CDPL.Chem.MolecularGraph, fp: CDPL.Util.BitSet) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumFeatures() -> int: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getFeatureIdentifier(idx: int) -> int: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getFeatureSubstructure(idx: int) -> CDPL.Util.BitSet: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %CircularFingerprintGenerator instance \a gen.
    # \param gen The \e %CircularFingerprintGenerator instance to copy.
    # \return \a self
    #
    def assign(gen: ._descr.CircularFingerprintGenerator) -> ._descr.CircularFingerprintGenerator: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    numFeatures = property(getNumFeatures)

    ##
    # \brief 
    #
    numBits = property(getNumBits, setNumBits)

    ##
    # \brief 
    #
    numIterations = property(getNumIterations, setNumIterations)

    ##
    # \brief FIXME!
    #
    remDuplicates = property(getRemDuplicates, setRemDuplicates)

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
        # \param self The \e %DefAtomIdentifierFunctor instance to initialize.
        # \param flags 
        #
        def __init__(self: object, flags: int = 3166) -> None: pass

        ##
        # \brief 
        # \param self The \e %DefAtomIdentifierFunctor instance this method is called upon.
        # \param atom 
        # \param molgraph 
        # \return 
        #
        def __call__(self: DefAtomIdentifierFunctor, atom: Atom, molgraph: MolecularGraph) -> int: pass

    ##
    # \brief 
    #
    class DefBondIdentifierFunctor(Boost.Python.instance):

        ##
        # \brief Initializes the \e %DefBondIdentifierFunctor instance.
        # \param self The \e %DefBondIdentifierFunctor instance to initialize.
        # \param flags 
        #
        def __init__(self: object, flags: int = 10) -> None: pass

        ##
        # \brief 
        # \param self The \e %DefBondIdentifierFunctor instance this method is called upon.
        # \param bond 
        # \return 
        #
        def __call__(self: DefBondIdentifierFunctor, bond: Bond) -> int: pass

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
    # \param self The \e %CircularFingerprintGenerator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %CircularFingerprintGenerator instance.
    # \param self The \e %CircularFingerprintGenerator instance to initialize.
    # \param gen 
    #
    def __init__(self: object, gen: CircularFingerprintGenerator) -> None: pass

    ##
    # \brief Initializes the \e %CircularFingerprintGenerator instance.
    # \param self The \e %CircularFingerprintGenerator instance to initialize.
    # \param molgraph 
    # \param fp 
    #
    def __init__(self: object, molgraph: MolecularGraph, fp: CDPL.Util.BitSet) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %CircularFingerprintGenerator instance this method is called upon.
    #
    # Different Python \e %CircularFingerprintGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %CircularFingerprintGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: CircularFingerprintGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %CircularFingerprintGenerator instance this method is called upon.
    # \param func 
    #
    def setAtomIdentifierFunction(self: CircularFingerprintGenerator, func: SizeTypeAtomMolecularGraphFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %CircularFingerprintGenerator instance this method is called upon.
    # \param func 
    #
    def setBondIdentifierFunction(self: CircularFingerprintGenerator, func: UInt64BondFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %CircularFingerprintGenerator instance this method is called upon.
    # \param num_bits 
    #
    def setNumBits(self: CircularFingerprintGenerator, num_bits: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %CircularFingerprintGenerator instance this method is called upon.
    # \return 
    #
    def getNumBits(self: CircularFingerprintGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %CircularFingerprintGenerator instance this method is called upon.
    # \param num_iter 
    #
    def setNumIterations(self: CircularFingerprintGenerator, num_iter: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %CircularFingerprintGenerator instance this method is called upon.
    # \return 
    #
    def getNumIterations(self: CircularFingerprintGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %CircularFingerprintGenerator instance this method is called upon.
    # \param remove 
    #
    def removeDuplicates(self: CircularFingerprintGenerator, remove: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %CircularFingerprintGenerator instance this method is called upon.
    # \return 
    #
    def duplicatesRemoved(self: CircularFingerprintGenerator) -> bool: pass

    ##
    # \brief 
    # \param self The \e %CircularFingerprintGenerator instance this method is called upon.
    # \param molgraph 
    # \param fp 
    #
    def generate(self: CircularFingerprintGenerator, molgraph: MolecularGraph, fp: CDPL.Util.BitSet) -> None: pass

    ##
    # \brief 
    # \param self The \e %CircularFingerprintGenerator instance this method is called upon.
    # \return 
    #
    def getNumFeatures(self: CircularFingerprintGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %CircularFingerprintGenerator instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getFeatureIdentifier(self: CircularFingerprintGenerator, idx: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %CircularFingerprintGenerator instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getFeatureSubstructure(self: CircularFingerprintGenerator, idx: int) -> CDPL.Util.BitSet: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %CircularFingerprintGenerator instance \a gen.
    # \param self The \e %CircularFingerprintGenerator instance this method is called upon.
    # \param gen The \e %CircularFingerprintGenerator instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: CircularFingerprintGenerator, gen: CircularFingerprintGenerator) -> CircularFingerprintGenerator: pass

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

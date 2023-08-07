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
# \brief CircularFingerprintGenerator.
# 
# \see [\ref STECFP]
# 
class CircularFingerprintGenerator(Boost.Python.instance):

    ##
    # \brief The functor for the generation of ECFP atom identifiers.
    # 
    class DefAtomIdentifierFunctor(Boost.Python.instance):

        ##
        # \brief Constructs the atom identifier functor object for the specified set of atomic properties.
        # 
        # The <em>flags</em> argument is an OR combination of the constants defined in namespace Chem.AtomPropertyFlag.
        # 
        # Supported property flags are:
        #  - Chem.AtomPropertyFlag.TYPE
        #  - Chem.AtomPropertyFlag.ISOTOPE
        #  - Chem.AtomPropertyFlag.VALENCE
        #  - Chem.AtomPropertyFlag.HEAVY_BOND_COUNT
        #  - Chem.AtomPropertyFlag.VALENCE
        #  - Chem.AtomPropertyFlag.TOPOLOGY
        #  - Chem.AtomPropertyFlag.FORMAL_CHARGE
        #  - Chem.AtomPropertyFlag.AROMATICITY
        # 
        # \param flags Specifies the set of considered atomic properties.
        # 
        def __init__(flags: int = 3166) -> None: pass

        ##
        # \brief Generates an identifier for the argument atom.
        # 
        # The generated identifier depends on the set of considered atomic properties that has been specified in the constructor.
        # 
        # \param atom The atom for which to generate the identifier.
        # \param molgraph The parent molecular graph of the atom.
        # 
        # \return The generated atom identifier. \
        # 
        def __call__(atom: Chem.Atom, molgraph: Chem.MolecularGraph) -> int: pass

    ##
    # \brief The default functor for the generation of bond identifiers.
    # 
    class DefBondIdentifierFunctor(Boost.Python.instance):

        ##
        # \brief Constructs the bond identifier functor object for the specified set of bond properties.
        # 
        # The <em>flags</em> argument is an OR combination of the constants defined in namespace Chem.BondPropertyFlag.
        # 
        # Supported property flags are:
        #  - Chem.BondPropertyFlag.ORDER
        #  - Chem.BondPropertyFlag.TOPOLOGY
        #  - Chem.BondPropertyFlag.AROMATICITY
        # 
        # \param flags Specifies the set of considered bond properties.
        # 
        def __init__(flags: int = 10) -> None: pass

        ##
        # \brief Generates an identifier for the argument bond.
        # 
        # The generated identifier depends on the set of considered bond properties that has been specified in the constructor.
        # 
        # \param bond The bond for which to generate the identifier.
        # 
        # \return The generated bond identifier.
        # 
        def __call__(bond: Chem.Bond) -> int: pass

    ##
    # \brief Specifies the default set of atomic properties considered in the generation of atom identifiers by CircularFingerprintGenerator.DefAtomIdentifierFunction.
    # 
    DEF_ATOM_PROPERTY_FLAGS = 3166

    ##
    # \brief Specifies the default set of bond properties considered in the generation of bond identifiers by CircularFingerprintGenerator.DefBondIdentifierFunction.
    # 
    DEF_BOND_PROPERTY_FLAGS = 10

    ##
    # \brief Constructs the <tt>CircularFingerprintGenerator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %CircularFingerprintGenerator instance \a gen.
    # \param gen The \e %CircularFingerprintGenerator instance to copy.
    # 
    def __init__(gen: CircularFingerprintGenerator) -> None: pass

    ##
    # \brief Constructs the <tt>CircularFingerprintGenerator</tt> instance and generates the atom-centered circular substructure fingerprint of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph to process.
    # 
    def __init__(molgraph: Chem.MolecularGraph) -> None: pass

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
    # \brief Allows to specify a customized function for the generation of initial atom identifiers.
    # 
    # \param func A CircularFingerprintGenerator.AtomIdentifierFunction instance that wraps the target function.
    # 
    # \note By default, atom identifiers are generated by a CircularFingerprintGenerator.DefAtomIdentifierFunctor instance. If the generated initial identifier for an atom is <em>0</em>, the atom is regarded as not being present in the processed molecular graph.
    # 
    def setAtomIdentifierFunction(func: Chem.SizeTypeAtomMolecularGraphFunctor) -> None: pass

    ##
    # \brief Allows to specify a customized function for the generation of initial bond identifiers.
    # 
    # \param func A CircularFingerprintGenerator.BondIdentifierFunction instance that wraps the target function.
    # 
    # \note By default, bond identifiers are generated by a CircularFingerprintGenerator.DefBondIdentifierFunctor instance. If the generated initial identifier for a bond is <em>0</em>, the bond is regarded as not being present in the processed molecular graph.
    # 
    def setBondIdentifierFunction(func: Chem.UInt64BondFunctor) -> None: pass

    ##
    # \brief Allows to specify the desired number of feature substructure growing iterations.
    # 
    # \param num_iter The number of iterations.
    # 
    # \note The default number of iterations is <em>2</em>.
    # 
    def setNumIterations(num_iter: int) -> None: pass

    ##
    # \brief Returns the number of feature substructure growing iterations.
    # 
    # \return The number of iterations.
    # 
    def getNumIterations() -> int: pass

    ##
    # \brief 
    # \param include 
    #
    def includeHydrogens(include: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def hydrogensIncluded() -> bool: pass

    ##
    # \brief 
    # \param include 
    #
    def includeChirality(include: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def chiralityIncluded() -> bool: pass

    ##
    # \brief Generates the atom-centered circular substructure fingerprint of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph to process.
    # 
    def generate(molgraph: Chem.MolecularGraph) -> None: pass

    ##
    # \brief Maps previously generated feature identifiers to bit indices and sets the correponding bits of <em>bs</em>.
    # 
    # \param bs The target bitset.
    # \param reset If <em>True</em>, <em>bs</em> will be cleared before any feature bits are set.
    # 
    # \note The binary fingerprint size is specified implicitly via the size of <em>bs</em>. <br>
    #  
    # 
    # \see generate()
    # 
    def setFeatureBits(bs: Util.BitSet, reset: bool = True) -> None: pass

    ##
    # \brief Maps previously generated identifiers of structural features involving the atom specified by <em>atom_idx</em> to bit indices and sets the correponding bits of <em>bs</em>.
    # 
    # \param atom_idx The index of the atom that has to be involved in the structural features.
    # \param bs The target bitset.
    # \param reset If <em>True</em>, <em>bs</em> will be cleared before any feature bits are set.
    # 
    # \note The binary fingerprint size is specified implicitly via the size of <em>bs</em>. <br>
    #  
    # 
    # \see generate()
    # 
    def setFeatureBits(atom_idx: int, bs: Util.BitSet, reset: bool = True) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumFeatures() -> int: pass

    ##
    # \brief 
    # \param ftr_idx 
    # \return 
    #
    def getFeatureIdentifier(ftr_idx: int) -> int: pass

    ##
    # \brief 
    # \param ftr_idx 
    # \return 
    #
    def getFeatureSubstructure(ftr_idx: int) -> Util.BitSet: pass

    ##
    # \brief 
    # \param ftr_idx 
    # \param frag 
    # \param clear 
    #
    def getFeatureSubstructure(ftr_idx: int, frag: Chem.Fragment, clear: bool = True) -> None: pass

    ##
    # \brief 
    # \param bit_idx 
    # \param bs_size 
    # \param frags 
    # \param clear 
    #
    def getFeatureSubstructures(bit_idx: int, bs_size: int, frags: Chem.FragmentList, clear: bool = True) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %CircularFingerprintGenerator instance \a gen.
    # \param gen The \e %CircularFingerprintGenerator instance to copy.
    # \return \a self
    # 
    def assign(gen: CircularFingerprintGenerator) -> CircularFingerprintGenerator: pass

    objectID = property(getObjectID)

    numFeatures = property(getNumFeatures)

    numIterations = property(getNumIterations, setNumIterations)

    ##
    # \brief FIXME!
    #
    incHydrogens = property(getIncHydrogens, setIncHydrogens)

    ##
    # \brief FIXME!
    #
    incChirality = property(getIncChirality, setIncChirality)

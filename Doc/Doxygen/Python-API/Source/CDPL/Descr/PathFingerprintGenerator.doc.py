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
# \brief PathFingerprintGenerator.
# 
# \see [\ref DTPFP]
# 
class PathFingerprintGenerator(Boost.Python.instance):

    ##
    # \brief The default functor for the generation of atom descriptors.
    # 
    class DefAtomDescriptorFunctor(Boost.Python.instance):

        ##
        # \brief Constructs the atom descriptor functor object for the specified set of atomic properties.
        # 
        # The <em>flags</em> argument is an OR combination of the constants defined in namespace Chem.AtomPropertyFlag. Supported property flags are:
        #  - Chem.AtomPropertyFlag.TYPE
        #  - Chem.AtomPropertyFlag.ISOTOPE
        #  - Chem.AtomPropertyFlag.AROMATICITY
        #  - and Chem.AtomPropertyFlag.FORMAL_CHARGE
        # 
        # \param flags Specifies the set of considered atomic properties.
        # 
        def __init__(flags: int = 142) -> None: pass

        ##
        # \brief Generates a descriptor for the argument atom.
        # 
        # The generated descriptor depends on the set of considered atomic properties that has been specified in the constructor.
        # 
        # \param atom The atom for which to generate the descriptor.
        # 
        # \return The generated atom descriptor.
        # 
        def __call__(atom: Chem.Atom) -> int: pass

    ##
    # \brief The default functor for the generation of bond descriptors.
    # 
    class DefBondDescriptorFunctor(Boost.Python.instance):

        ##
        # \brief Constructs the bond descriptor functor object for the specified set of bond properties.
        # 
        # The <em>flags</em> argument is an OR combination of the constants defined in namespace Chem.BondPropertyFlag. Supported property flags are:
        #  - Chem.BondPropertyFlag.ORDER
        #  - Chem.BondPropertyFlag.TOPOLOGY
        #  - and Chem.BondPropertyFlag.AROMATICITY
        # 
        # \param flags Specifies the set of considered bond properties.
        # 
        def __init__(flags: int = 14) -> None: pass

        ##
        # \brief Generates a descriptor for the argument bond.
        # 
        # The generated descriptor depends on the set of considered bond properties that has been specified in the constructor.
        # 
        # \param bond The bond for which to generate the descriptor.
        # 
        # \return The generated bond descriptor.
        # 
        def __call__(bond: Chem.Bond) -> int: pass

    ##
    # \brief Specifies the default set of atomic properties considered in the generation of atom descriptors by PathFingerprintGenerator.DefAtomDescriptorFunction.
    # 
    DEF_ATOM_PROPERTY_FLAGS = 142

    ##
    # \brief Specifies the default set of bond properties considered in the generation of bond descriptors by PathFingerprintGenerator.DefBondDescriptorFunction.
    # 
    DEF_BOND_PROPERTY_FLAGS = 14

    ##
    # \brief Constructs the <tt>PathFingerprintGenerator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs the <tt>PathFingerprintGenerator</tt> instance and generates the fingerprint of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to generate the fingerprint.
    # \param fp The generated fingerprint.
    # 
    def __init__(molgraph: Chem.MolecularGraph, fp: Util.BitSet) -> None: pass

    ##
    # \brief Initializes a copy of the \e %PathFingerprintGenerator instance \a gen.
    # \param gen The \e %PathFingerprintGenerator instance to copy.
    # 
    def __init__(gen: PathFingerprintGenerator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %PathFingerprintGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %PathFingerprintGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %PathFingerprintGenerator instance \a gen.
    # \param gen The \e %PathFingerprintGenerator instance to copy.
    # \return \a self
    # 
    def assign(gen: PathFingerprintGenerator) -> PathFingerprintGenerator: pass

    ##
    # \brief Allows to specify a custom function for the generation of atom descriptors.
    # 
    # \param func A PathFingerprintGenerator.AtomDescriptorFunction instance that wraps the target function.
    # 
    # \note By default, atom descriptors are generated by PathFingerprintGenerator.DefAtomDescriptorFunctor.
    # 
    def setAtomDescriptorFunction(func: Chem.SizeTypeAtomFunctor) -> None: pass

    ##
    # \brief Allows to specify a custom function for the generation of bond descriptors.
    # 
    # \param func A PathFingerprintGenerator.BondDescriptorFunction instance that wraps the target function.
    # 
    # \note By default, bond descriptors are generated by PathFingerprintGenerator.DefBondDescriptorFunctor.
    # 
    def setBondDescriptorFunction(func: Chem.UInt64BondFunctor) -> None: pass

    ##
    # \brief Allows to specify the minimum length a path must have to contribute to the generated fingerprint.
    # 
    # Any path whose length (in number of bonds) is lower than the specified minimum length will not be represented by a corresponding bit in the generated fingerprint.
    # 
    # \param min_length The minimum path length in number of bonds.
    # 
    # \note By default, the minimum path length is set to <em>0</em>.
    # 
    def setMinPathLength(min_length: int) -> None: pass

    ##
    # \brief Allows to specify the maximum considered path length.
    # 
    # Any path whose length (in number of bonds) is greater than the specified maximum length will not be represented by a corresponding bit in the generated fingerprint.
    # 
    # \param max_length The maximum path length in number of bonds.
    # 
    # \note By default, the maximum considered path length is <em>5</em>.
    # 
    def setMaxPathLength(max_length: int) -> None: pass

    ##
    # \brief Allows to specify the desired fingerprint size.
    # 
    # \param num_bits The desired fingerprint size in number of bits.
    # 
    # \note By default, the generated fingerprints are <em>1024</em> bits wide.
    # 
    def setNumBits(num_bits: int) -> None: pass

    ##
    # \brief Returns the minimum length a path must have to contribute to the generated fingerprint.
    # 
    # \return The minimum path length in number of bonds. 
    # 
    # \see setMinPathLength()
    # 
    def getMinPathLength() -> int: pass

    ##
    # \brief Returns the maximum considered path length.
    # 
    # \return The maximum path length in number of bonds. 
    # 
    # \see setMaxPathLength()
    # 
    def getMaxPathLength() -> int: pass

    ##
    # \brief Returns the size of the generated fingerprints.
    # 
    # \return The fingerprint size in number of bits.
    # 
    def getNumBits() -> int: pass

    ##
    # \brief Generates the fingerprint of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to generate the fingerprint.
    # \param fp The generated fingerprint.
    # 
    def generate(molgraph: Chem.MolecularGraph, fp: Util.BitSet) -> None: pass

    objectID = property(getObjectID)

    minPathLength = property(getMinPathLength, setMinPathLength)

    maxPathLength = property(getMaxPathLength, setMaxPathLength)

    numBits = property(getNumBits, setNumBits)

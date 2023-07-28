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
# \brief CanonicalNumberingCalculator.
# 
# \see [\ref MCKAY]
# 
class CanonicalNumberingCalculator(Boost.Python.instance):

    ##
    # \brief Specifies the default set of atomic properties considered by the canonical numbering algorithm.
    # 
    DEF_ATOM_PROPERTY_FLAGS = 414

    ##
    # \brief Specifies the default set of bond properties considered by the canonical numbering algorithm.
    # 
    DEF_BOND_PROPERTY_FLAGS = 26

    ##
    # \brief Constructs the <tt>CanonicalNumberingCalculator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs the <tt>CanonicalNumberingCalculator</tt> instance and performs a canonical numbering of the atoms in the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to perform the canonical numbering.
    # \param numbering An array that contains the calculated canonical atom labels. The labels are stored in the same order as the atoms appear in the atom list of the molecular graph (i.e. the canonical number of an atom is accessible via its index).
    # 
    def __init__(molgraph: MolecularGraph, numbering: CDPL.Util.STArray) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %CanonicalNumberingCalculator instance this method is called upon.
    # 
    # Different Python \e %CanonicalNumberingCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %CanonicalNumberingCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Allows to specify the set of atomic properties that has to be considered by the canonical numering algorithm.
    # 
    # The <em>flags</em> argument is an OR combination of the constants defined in namespace Chem.AtomPropertyFlag. Supported property flags are:
    #  - Chem.AtomPropertyFlag.TYPE
    #  - Chem.AtomPropertyFlag.ISOTOPE
    #  - Chem.AtomPropertyFlag.FORMAL_CHARGE
    #  - Chem.AtomPropertyFlag.AROMATICITY
    #  - Chem.AtomPropertyFlag.CONFIGURATION
    #  - and Chem.AtomPropertyFlag.H_COUNT
    # 
    # \param flags The set of atomic properties to consider.
    # 
    # \note The default set of atomic properties is specified by CanonicalNumberingCalculator.DEF_ATOM_PROPERTY_FLAGS.
    # 
    def setAtomPropertyFlags(flags: int) -> None: pass

    ##
    # \brief Returns the set of atomic properties that gets considered by the canonical numbering algorithm.
    # 
    # \return The set of considered atomic properties. 
    # 
    # \see setAtomPropertyFlags()
    # 
    def getAtomPropertyFlags() -> int: pass

    ##
    # \brief Allows to specify the set of bond properties that has to be considered by the canonical numering algorithm.
    # 
    # The <em>flags</em> argument is an OR combination of the constants defined in namespace Chem.BondPropertyFlag. Supported property flags are:
    #  - Chem.BondPropertyFlag.ORDER
    #  - Chem.BondPropertyFlag.CONFIGURATION
    #  - and Chem.BondPropertyFlag.AROMATICITY
    # 
    # \param flags The set of bond properties to consider.
    # 
    # \note The default set of bond properties is specified by CanonicalNumberingCalculator.DEF_BOND_PROPERTY_FLAGS.
    # 
    def setBondPropertyFlags(flags: int) -> None: pass

    ##
    # \brief Returns the set of bond properties that gets considered by the canonical numbering algorithm.
    # 
    # \return The set of considered bond properties. 
    # 
    # \see setBondPropertyFlags()
    # 
    def getBondPropertyFlags() -> int: pass

    ##
    # \brief 
    # \param func 
    #
    def setHydrogenCountFunction(func: SizeTypeAtomMolecularGraphFunctor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getHydrogenCountFunction() -> SizeTypeAtomMolecularGraphFunctor: pass

    ##
    # \brief Performs a canonical numbering of the atoms in the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to perform the canonical numbering.
    # \param numbering An array that contains the calculated canonical atom labels. The labels are stored in the same order as the atoms appear in the atom list of the molecular graph (i.e. the canonical number of an atom is accessible via its index).
    # 
    def calculate(molgraph: MolecularGraph, numbering: CDPL.Util.STArray) -> None: pass

    objectID = property(getObjectID)

    atomPropertyFlags = property(getAtomPropertyFlags, setAtomPropertyFlags)

    bondPropertyFlags = property(getBondPropertyFlags, setBondPropertyFlags)

    ##
    # \brief FIXME!
    # \brief 
    #
    hydrogenCountFunc = property(getHydrogenCountFunc, setHydrogenCountFunc)

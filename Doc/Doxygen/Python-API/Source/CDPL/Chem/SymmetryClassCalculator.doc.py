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
# \brief SymmetryClassCalculator.
# 
# \see [\ref TOPSY]
# 
class SymmetryClassCalculator(Boost.Python.instance):

    ##
    # \brief Specifies the default set of atomic properties considered in the perception of topological symmetry classes.
    # 
    DEF_ATOM_PROPERTY_FLAGS = 158

    ##
    # \brief Specifies the default set of bond properties considered in the perception of topological symmetry classes.
    # 
    DEF_BOND_PROPERTY_FLAGS = 10

    ##
    # \brief Constructs the <tt>SymmetryClassCalculator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs the <tt>SymmetryClassCalculator</tt> instance and perceives the topological symmetry classes of the atoms in the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to perceive the symmetry classes.
    # \param class_ids An array containing the perceived symmetry class IDs. The class IDs are stored in the same order as the atoms appear in the atom list of the molecular graph (i.e. the symmetry class of an atom is accessible via its index).
    # 
    def __init__(molgraph: MolecularGraph, class_ids: Util.STArray) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %SymmetryClassCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %SymmetryClassCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Allows to specify the set of atomic properties that has to be considered in the perception of topological symmetry classes.
    # 
    # The <em>flags</em> argument is an OR combination of the constants defined in namespace Chem.AtomPropertyFlag. Supported property flags are:
    #  - Chem.AtomPropertyFlag.TYPE
    #  - Chem.AtomPropertyFlag.ISOTOPE
    #  - Chem.AtomPropertyFlag.FORMAL_CHARGE
    #  - Chem.AtomPropertyFlag.AROMATICITY
    #  - and Chem.AtomPropertyFlag.H_COUNT
    # 
    # \param flags The set of atomic properties to consider.
    # 
    # \note The default set of atomic properties is specified by SymmetryClassCalculator.DEF_ATOM_PROPERTY_FLAGS.
    # 
    def setAtomPropertyFlags(flags: int) -> None: pass

    ##
    # \brief Allows to specify the set of bond properties that has to be considered in the perception of topological symmetry classes.
    # 
    # The <em>flags</em> argument is an OR combination of the constants defined in namespace Chem.BondPropertyFlag. Supported property flags are:
    #  - Chem.BondPropertyFlag.ORDER
    #  - and Chem.BondPropertyFlag.AROMATICITY
    # 
    # \param flags The set of bond properties to consider.
    # 
    # \note The default set of bond properties is specified by SymmetryClassCalculator.DEF_BOND_PROPERTY_FLAGS.
    # 
    def setBondPropertyFlags(flags: int) -> None: pass

    ##
    # \brief Allows to specify whether implicit hydrogen atoms shall be ignored or treated in the same way as explicit ones.
    # 
    # \param include If <tt>True</tt>, implicit hydrogen atoms are treated as if they were explicit and are ignored otherwise.
    # 
    # \note By default, implicit hydrogen atoms are treated in the same way as explicit ones.
    # 
    def includeImplicitHydrogens(include: bool) -> None: pass

    ##
    # \brief Returns the set of atomic properties that gets considered in the perception of topological symmetry classes.
    # 
    # \return The set of considered atomic properties. 
    # 
    # \see setAtomPropertyFlags()
    # 
    def getAtomPropertyFlags() -> int: pass

    ##
    # \brief Returns the set of bond properties that gets considered in the perception of topological symmetry classes.
    # 
    # \return The set of considered bond properties. 
    # 
    # \see setBondPropertyFlags()
    # 
    def getBondPropertyFlags() -> int: pass

    ##
    # \brief Tells whether implicit hydrogen atoms are ignored or treated in the same way as explicit ones.
    # 
    # \return <tt>True</tt> if implicit hydrogen atoms are treated in the same way as explicit ones, and <tt>False</tt> if they are ignored.
    # 
    def implicitHydrogensIncluded() -> bool: pass

    ##
    # \brief Perceives the topological symmetry classes of the atoms in the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to perceive the symmetry classes.
    # \param class_ids An array containing the perceived symmetry class IDs. The class IDs are stored in the same order as the atoms appear in the atom list of the molecular graph (i.e. the symmetry class of an atom is accessible via its index).
    # 
    def calculate(molgraph: MolecularGraph, class_ids: Util.STArray) -> None: pass

    objectID = property(getObjectID)

    atomPropertyFlags = property(getAtomPropertyFlags, setAtomPropertyFlags)

    bondPropertyFlags = property(getBondPropertyFlags, setBondPropertyFlags)

    hydrogenComplete = property(implicitHydrogensIncluded, includeImplicitHydrogens)

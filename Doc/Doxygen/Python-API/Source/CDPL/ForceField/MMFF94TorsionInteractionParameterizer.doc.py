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
# \brief Generates the MMFF94 torsion interactions for the atom quadruplets defined by the bonds of a molecular graph.
# 
# For every non-filtered atom quadruplet (<em>i-<em>j-<em>k-<em>l</em>)</em> consisting</em> of</em> a central bond <em>j-<em>k</em> and</em> one neighbor each on <em>j</em> and <em>k</em> the parameterizer looks up the matching MMFF94 torsion-type-specific parameters \f$ V_1, V_2, V_3 \f$ from the supplied parameter table, falling back to the primary-to-parameter atom-type map for atoms with no exact parameter entry, and emits an MMFF94TorsionInteraction record.
# 
class MMFF94TorsionInteractionParameterizer(Boost.Python.instance):

    ##
    # \brief Constructs an <tt>MMFF94TorsionInteractionParameterizer</tt> instance using the default MMFF94 parameter tables.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %MMFF94TorsionInteractionParameterizer instance \a parameterizer.
    # \param parameterizer The \c %MMFF94TorsionInteractionParameterizer instance to copy.
    # 
    def __init__(parameterizer: MMFF94TorsionInteractionParameterizer) -> None: pass

    ##
    # \brief Constructs the parameterizer and immediately processes <em>molgraph</em> into <em>ia_list</em>.
    # 
    # \param molgraph The molecular graph for which to parameterize the torsion interactions.
    # \param ia_list Output list receiving the generated MMFF94TorsionInteraction records.
    # \param strict If <tt>True</tt>, missing/ambiguous parameters cause a parameterization failure.
    # 
    def __init__(molgraph: Chem.MolecularGraph, ia_list: MMFF94TorsionInteractionList, strict: bool) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94TorsionInteractionParameterizer instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94TorsionInteractionParameterizer instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Sets the filter function used to skip atom quadruplets during parameterization.
    # 
    # \param func The new four-atom filter function (when it returns <tt>False</tt>, the quadruplet is skipped).
    # 
    def setFilterFunction(func: InteractionFilterFunction4) -> None: pass

    ##
    # \brief Sets the function used to look up the MMFF94 numeric atom type of an atom.
    # 
    # \param func The new numeric-atom-type lookup function.
    # 
    def setAtomTypeFunction(func: MMFF94NumericAtomTypeFunction) -> None: pass

    ##
    # \brief Sets the function used to look up the MMFF94 bond-type index of a bond.
    # 
    # \param func The new bond-type-index lookup function.
    # 
    def setBondTypeIndexFunction(func: MMFF94BondTypeIndexFunction) -> None: pass

    ##
    # \brief Sets the function used to obtain the set of MMFF94-aromatic rings of the input molecular graph.
    # 
    # \param func The new aromatic-ring-set function.
    # 
    def setAromaticRingSetFunction(func: MMFF94RingSetFunction) -> None: pass

    ##
    # \brief Sets the primary table providing torsion-type-specific \f$ V_1/V_2/V_3 \f$ parameters.
    # 
    # \param table The new torsion parameter table.
    # 
    def setTorsionParameterTable(table: MMFF94TorsionParameterTable) -> None: pass

    ##
    # \brief Sets the table providing per-numeric-atom-type property data (used by the empirical fallback).
    # 
    # \param table The new atom-type property table.
    # 
    def setAtomTypePropertyTable(table: MMFF94AtomTypePropertyTable) -> None: pass

    ##
    # \brief Sets the map used to translate primary atom types into their corresponding parameter-atom types.
    # 
    # \param map The new primary-to-parameter atom-type map.
    # 
    def setParameterAtomTypeMap(map: MMFF94PrimaryToParameterAtomTypeMap) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMFF94TorsionInteractionParameterizer instance \a parameterizer.
    # \param parameterizer The \c %MMFF94TorsionInteractionParameterizer instance to copy.
    # \return \a self
    # 
    def assign(parameterizer: MMFF94TorsionInteractionParameterizer) -> MMFF94TorsionInteractionParameterizer: pass

    ##
    # \brief Generates the MMFF94 torsion interactions for <em>molgraph</em> and writes them to <em>ia_list</em>.
    # 
    # \param molgraph The molecular graph for which to parameterize the torsion interactions.
    # \param ia_list Output list receiving the generated MMFF94TorsionInteraction records.
    # \param strict If <tt>True</tt>, missing/ambiguous parameters cause a parameterization failure.
    # 
    def parameterize(molgraph: Chem.MolecularGraph, ia_list: MMFF94TorsionInteractionList, strict: bool) -> None: pass

    objectID = property(getObjectID)

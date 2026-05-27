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
# \brief Detects and parameterizes the MMFF94 bond-stretching interactions of a molecular graph.
# 
# For every non-filtered bond the parameterizer looks up the matching MMFF94 bond type-specific parameters from the supplied tables (falling back to the rule-based table when no exact match is available) and appends an MMFF94BondStretchingInteraction instance to the output list.
# 
class MMFF94BondStretchingInteractionParameterizer(Boost.Python.instance):

    ##
    # \brief Constructs an <tt>MMFF94BondStretchingInteractionParameterizer</tt> instance using the default MMFF94 parameter tables.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %MMFF94BondStretchingInteractionParameterizer instance \a parameterizer.
    # \param parameterizer The \c %MMFF94BondStretchingInteractionParameterizer instance to copy.
    # 
    def __init__(parameterizer: MMFF94BondStretchingInteractionParameterizer) -> None: pass

    ##
    # \brief Constructs the parameterizer and processes the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to parameterize the bond-stretching interactions.
    # \param ia_list Output list receiving the generated MMFF94BondStretchingInteraction instances.
    # \param strict If <tt>True</tt>, missing/ambiguous parameters cause a parameterization failure. Otherwise, in case of parameterization problems, suitable fallback parameters will be used.
    # 
    def __init__(molgraph: Chem.MolecularGraph, ia_list: MMFF94BondStretchingInteractionList, strict: bool) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94BondStretchingInteractionParameterizer instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94BondStretchingInteractionParameterizer instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Sets the filter function used to skip bonds during parameterization.
    # 
    # \param func The new filter function (when it returns <tt>False</tt> for a bond pair, the bond is skipped).
    # 
    def setFilterFunction(func: Chem.BoolAtom2Functor) -> None: pass

    ##
    # \brief Sets the function used to look up the MMFF94 numeric atom type of an atom.
    # 
    # \param func The new numeric atom type lookup function.
    # 
    def setAtomTypeFunction(func: MMFF94NumericAtomTypeFunction) -> None: pass

    ##
    # \brief Sets the function used to look up the MMFF94 bond type index of a bond.
    # 
    # \param func The new bond type index lookup function.
    # 
    def setBondTypeIndexFunction(func: MMFF94BondTypeIndexFunction) -> None: pass

    ##
    # \brief Sets the function used to obtain the set of MMFF94 aromatic rings of the input molecular graph.
    # 
    # \param func The new aromatic ring set retrieval function.
    # 
    def setAromaticRingSetFunction(func: MMFF94RingSetFunction) -> None: pass

    ##
    # \brief Sets the primary table providing bond type-specific bond-stretching parameters.
    # 
    # \param table The new bond-stretching parameter table.
    # 
    def setBondStretchingParameterTable(table: MMFF94BondStretchingParameterTable) -> None: pass

    ##
    # \brief Sets the fallback table providing rule-based bond-stretching parameters.
    # 
    # \param table The new bond-stretching rule parameter table.
    # 
    def setBondStretchingRuleParameterTable(table: MMFF94BondStretchingRuleParameterTable) -> None: pass

    ##
    # \brief Sets the table providing MMFF94 numeric atom type property data (used by the empirical fallback).
    # 
    # \param table The new atom type property table.
    # 
    def setAtomTypePropertyTable(table: MMFF94AtomTypePropertyTable) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMFF94BondStretchingInteractionParameterizer instance \a parameterizer.
    # \param parameterizer The \c %MMFF94BondStretchingInteractionParameterizer instance to copy.
    # \return \a self
    # 
    def assign(parameterizer: MMFF94BondStretchingInteractionParameterizer) -> MMFF94BondStretchingInteractionParameterizer: pass

    ##
    # \brief Perceives the MMFF94 bond-stretching interactions for <em>molgraph</em> and outputs the corresponding parameter data into <em>ia_list</em>.
    # 
    # \param molgraph The molecular graph for which to parameterize the bond-stretching interactions.
    # \param ia_list Output list receiving the generated MMFF94BondStretchingInteraction instances.
    # \param strict If <tt>True</tt>, missing/ambiguous parameters cause a parameterization failure. Otherwise, in case of parameterization problems, suitable fallback parameters will be used.
    # 
    def parameterize(molgraph: Chem.MolecularGraph, ia_list: MMFF94BondStretchingInteractionList, strict: bool) -> None: pass

    objectID = property(getObjectID)

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
# \brief Detects and parameterizes the MMFF94 stretch-bend interactions of a molecular graph.
# 
# Stretch-bend interactions couple the bending of an <em>i-<em>j-<em>k</em> bond</em> angle</em> to the stretching of the two participating bonds <em>i-<em>j</em> and</em> <em>j-<em>k</em>.</em> For every non-filtered atom triplet the parameterizer derives the stretch-bend type index from the bond type indices and angle type index of the already-parameterized bond-stretching and angle-bending interactions, looks up the matching stretch-bend force constants (falling back to the periodic-table-row-based default parameter table when no exact entry is available) and appends an MMFF94StretchBendInteraction instance to the output list.
# 
# \see [\ref MMFF94]
# 
class MMFF94StretchBendInteractionParameterizer(Boost.Python.instance):

    ##
    # \brief Constructs an <tt>MMFF94StretchBendInteractionParameterizer</tt> instance using the default MMFF94 parameter tables.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %MMFF94StretchBendInteractionParameterizer instance \a parameterizer.
    # \param parameterizer The \c %MMFF94StretchBendInteractionParameterizer instance to copy.
    # 
    def __init__(parameterizer: MMFF94StretchBendInteractionParameterizer) -> None: pass

    ##
    # \brief Constructs the parameterizer and processes the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to parameterize the stretch-bend interactions.
    # \param bs_ia_list The list of already-parameterized MMFF94 bond-stretching interactions (provides per-bond type indices and reference lengths).
    # \param ab_ia_list The list of already-parameterized MMFF94 angle-bending interactions (provides per-angle type indices and reference angles).
    # \param ia_list Output list receiving the generated MMFF94StretchBendInteraction instances.
    # \param strict If <tt>True</tt>, missing/ambiguous parameters cause a parameterization failure. Otherwise, in case of parameterization problems, suitable fallback parameters will be used.
    # 
    def __init__(molgraph: Chem.MolecularGraph, bs_ia_list: MMFF94BondStretchingInteractionList, ab_ia_list: MMFF94AngleBendingInteractionList, ia_list: MMFF94StretchBendInteractionList, strict: bool) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94StretchBendInteractionParameterizer instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94StretchBendInteractionParameterizer instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Sets the filter function used to skip atom triplets during parameterization.
    # 
    # \param func The new three-atom filter function (when it returns <tt>False</tt>, the triplet is skipped).
    # 
    def setFilterFunction(func: InteractionFilterFunction3) -> None: pass

    ##
    # \brief Sets the function used to look up the MMFF94 numeric atom type of an atom.
    # 
    # \param func The new numeric atom type lookup function.
    # 
    def setAtomTypeFunction(func: MMFF94NumericAtomTypeFunction) -> None: pass

    ##
    # \brief Sets the primary table providing stretch-bend type-specific stretch-bend parameters.
    # 
    # \param table The new stretch-bend parameter table.
    # 
    def setStretchBendParameterTable(table: MMFF94StretchBendParameterTable) -> None: pass

    ##
    # \brief Sets the fallback table providing periodic-table-row-based default stretch-bend parameters.
    # 
    # \param table The new default stretch-bend parameter table.
    # 
    def setDefaultStretchBendParameterTable(table: MMFF94DefaultStretchBendParameterTable) -> None: pass

    ##
    # \brief Sets the table providing MMFF94 numeric atom type property data (used to look up the periodic table row of an atom for the default-parameter fallback).
    # 
    # \param table The new atom type property table.
    # 
    def setAtomTypePropertyTable(table: MMFF94AtomTypePropertyTable) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMFF94StretchBendInteractionParameterizer instance \a parameterizer.
    # \param parameterizer The \c %MMFF94StretchBendInteractionParameterizer instance to copy.
    # \return \a self
    # 
    def assign(parameterizer: MMFF94StretchBendInteractionParameterizer) -> MMFF94StretchBendInteractionParameterizer: pass

    ##
    # \brief Perceives the MMFF94 stretch-bend interactions for <em>molgraph</em> and outputs the corresponding parameter data into <em>ia_list</em>.
    # 
    # \param molgraph The molecular graph for which to parameterize the stretch-bend interactions.
    # \param bs_ia_list The list of already-parameterized MMFF94 bond-stretching interactions (provides per-bond type indices and reference lengths).
    # \param ab_ia_list The list of already-parameterized MMFF94 angle-bending interactions (provides per-angle type indices and reference angles).
    # \param ia_list Output list receiving the generated MMFF94StretchBendInteraction instances.
    # \param strict If <tt>True</tt>, missing/ambiguous parameters cause a parameterization failure. Otherwise, in case of parameterization problems, suitable fallback parameters will be used.
    # 
    def parameterize(molgraph: Chem.MolecularGraph, bs_ia_list: MMFF94BondStretchingInteractionList, ab_ia_list: MMFF94AngleBendingInteractionList, ia_list: MMFF94StretchBendInteractionList, strict: bool) -> None: pass

    objectID = property(getObjectID)

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
# \brief Generates the MMFF94 electrostatic interactions for the non-bonded atom pairs of a molecular graph.
# 
# For every pair of atoms that is at least 1,4-separated (1,4-pairs use a scaling factor of 0.75; 1,5 and farther pairs use 1.0) the parameterizer emits an MMFF94ElectrostaticInteraction record carrying the partial charges, the configured dielectric constant and the configured distance exponent.
# 
class MMFF94ElectrostaticInteractionParameterizer(Boost.Python.instance):

    ##
    # \brief Default value of the distance exponent in the MMFF94 electrostatic potential (<em>1.0</em> — Coulomb form).
    # 
    DEF_DISTANCE_EXPONENT = 1.0

    ##
    # \brief Default value of the dielectric constant (<em>1.0</em> — gas-phase).
    # 
    DEF_DIELECTRIC_CONSTANT = 1.0

    ##
    # \brief Convenience constant: dielectric constant of bulk water at room temperature (<em>80.0</em>).
    # 
    DIELECTRIC_CONSTANT_WATER = 80.0

    ##
    # \brief Constructs an <tt>MMFF94ElectrostaticInteractionParameterizer</tt> instance with default settings.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %MMFF94ElectrostaticInteractionParameterizer instance \a parameterizer.
    # \param parameterizer The \c %MMFF94ElectrostaticInteractionParameterizer instance to copy.
    # 
    def __init__(parameterizer: MMFF94ElectrostaticInteractionParameterizer) -> None: pass

    ##
    # \brief Constructs the parameterizer and immediately processes <em>molgraph</em> into <em>ia_list</em>.
    # 
    # \param molgraph The molecular graph for which to parameterize the electrostatic interactions.
    # \param ia_list Output list receiving the generated MMFF94ElectrostaticInteraction records.
    # \param strict If <tt>True</tt>, missing/ambiguous parameters cause a parameterization failure.
    # 
    def __init__(molgraph: Chem.MolecularGraph, ia_list: MMFF94ElectrostaticInteractionList, strict: bool) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %MMFF94ElectrostaticInteractionParameterizer instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %MMFF94ElectrostaticInteractionParameterizer instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Sets the filter function used to skip atom pairs during parameterization.
    # 
    # \param func The new filter function (when it returns <tt>False</tt> for an atom pair, the pair is skipped).
    # 
    def setFilterFunction(func: Chem.BoolAtom2Functor) -> None: pass

    ##
    # \brief Sets the function used to look up the MMFF94 partial charge of an atom.
    # 
    # \param func The new atom-charge lookup function.
    # 
    def setAtomChargeFunction(func: MMFF94AtomChargeFunction) -> None: pass

    ##
    # \brief Sets the function used to determine the topological distance between two atoms (number of bonds along the shortest path).
    # 
    # \param func The new topological-distance function.
    # 
    def setTopologicalDistanceFunction(func: TopologicalAtomDistanceFunction) -> None: pass

    ##
    # \brief Sets the dielectric constant used by the MMFF94 electrostatic potential.
    # 
    # \param de_const The new dielectric constant.
    # 
    def setDielectricConstant(de_const: float) -> None: pass

    ##
    # \brief Sets the exponent of the MMFF94 distance-dependent electrostatic potential.
    # 
    # \param dist_expo The new distance exponent.
    # 
    def setDistanceExponent(dist_expo: float) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %MMFF94ElectrostaticInteractionParameterizer instance \a parameterizer.
    # \param parameterizer The \c %MMFF94ElectrostaticInteractionParameterizer instance to copy.
    # \return \a self
    # 
    def assign(parameterizer: MMFF94ElectrostaticInteractionParameterizer) -> MMFF94ElectrostaticInteractionParameterizer: pass

    ##
    # \brief Generates the MMFF94 electrostatic interactions for <em>molgraph</em> and writes them to <em>ia_list</em>.
    # 
    # \param molgraph The molecular graph for which to parameterize the electrostatic interactions.
    # \param ia_list Output list receiving the generated MMFF94ElectrostaticInteraction records.
    # \param strict If <tt>True</tt>, missing/ambiguous parameters cause a parameterization failure.
    # 
    def parameterize(molgraph: Chem.MolecularGraph, ia_list: MMFF94ElectrostaticInteractionList, strict: bool) -> None: pass

    objectID = property(getObjectID)

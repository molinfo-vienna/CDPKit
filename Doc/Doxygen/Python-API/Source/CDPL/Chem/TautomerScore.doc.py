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
# \brief Functor for the calculation of a heuristic stability score of a tautomeric form represented as a molecular graph.
# 
# The score is computed from contributions of atom-type, hybridization, ring-membership and specific structural motifs (amide-like nitrogens, carboxylic oxygens, exocyclic hydroxyls, 2,4-hydroxy-pyridine-like rings, etc.) and is typically used to rank tautomeric forms of a molecule from least to most stable.
# 
class TautomerScore(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>TautomerScore</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %TautomerScore instance \a score.
    # \param score The \e %TautomerScore instance to copy.
    # 
    def __init__(score: TautomerScore) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %TautomerScore instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %TautomerScore instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %TautomerScore instance \a score.
    # \param score The \c %TautomerScore instance to copy.
    # \return \a self
    # 
    def assign(score: TautomerScore) -> TautomerScore: pass

    ##
    # \brief Calculates the tautomer stability score of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph representing the tautomeric form to score.
    # 
    # \return The calculated tautomer stability score.
    # 
    def __call__(molgraph: MolecularGraph) -> float: pass

    objectID = property(getObjectID)

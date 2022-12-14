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
class PosIonizableFeatureGenerator(PatternBasedFeatureGenerator):

    ##
    # \brief Initializes the \e %PosIonizableFeatureGenerator instance.
    # \param chgd_groups_only 
    #
    def __init__(chgd_groups_only: bool) -> None: pass

    ##
    # \brief Initializes the \e %PosIonizableFeatureGenerator instance.
    # \param gen 
    #
    def __init__(gen: PosIonizableFeatureGenerator) -> None: pass

    ##
    # \brief Initializes the \e %PosIonizableFeatureGenerator instance.
    # \param molgraph 
    # \param pharm 
    # \param chgd_groups_only 
    #
    def __init__(molgraph: CDPL.Chem.MolecularGraph, pharm: Pharmacophore, chgd_groups_only: bool) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %PosIonizableFeatureGenerator instance \a gen.
    # \param gen The \e %PosIonizableFeatureGenerator instance to copy.
    # \return \a self
    #
    def assign(gen: PosIonizableFeatureGenerator) -> PosIonizableFeatureGenerator: pass

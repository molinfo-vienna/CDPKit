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
# \brief HBondDonorFeatureGenerator.
# 
class HBondDonorFeatureGenerator(PatternBasedFeatureGenerator):

    ##
    # \brief Constructs the <tt>HBondDonorFeatureGenerator</tt> instance.
    # 
    # \param static_h_bonds <tt>True</tt> if hydrogens on donor atoms connected via rotatable bonds should be considered static and emitted features modeled as defined vectors, and <tt>False</tt> otherwise.
    # 
    def __init__(static_h_bonds: bool) -> None: pass

    ##
    # \brief Initializes the \e %HBondDonorFeatureGenerator instance.
    # \param gen 
    # 
    def __init__(gen: HBondDonorFeatureGenerator) -> None: pass

    ##
    # \brief Perceives the hydrogen bond donor features of the molecular graph a\ molgraph and adds them to the pharmacophore <em>pharm</em>.
    # 
    # \param molgraph The molecular graph for which to perceive the features.
    # \param pharm The output pharmacophore where to add the generated features.
    # \param static_h_bonds <tt>True</tt> if hydrogens on donor atoms connected via rotatable bonds should be considered static and emitted features modeled as defined vectors, and <tt>False</tt> otherwise.
    # 
    def __init__(molgraph: Chem.MolecularGraph, pharm: Pharmacophore, static_h_bonds: bool) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %HBondDonorFeatureGenerator instance \a gen.
    # \param gen The \e %HBondDonorFeatureGenerator instance to copy.
    # \return \a self
    # 
    def assign(gen: HBondDonorFeatureGenerator) -> HBondDonorFeatureGenerator: pass

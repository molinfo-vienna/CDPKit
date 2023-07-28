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
# \brief Implements the extraction of all rings in the SSSR of a molecular graph that are aromatic according to MMFF94 conventions.
# 
class MMFF94AromaticSSSRSubset(CDPL.Chem.FragmentList):

    ##
    # \brief Constructs an empty <tt>MMFF94AromaticSSSRSubset</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Construct a <tt>MMFF94AromaticSSSRSubset</tt> instance that contains all aromatic rings of the SSSR of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to extract the aromatic rings.
    # 
    def __init__(molgraph: CDPL.Chem.MolecularGraph) -> None: pass

    ##
    # \brief Replaces the current set of rings by the aromatic rings in the SSSR of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to extract the aromatic rings.
    # 
    def extract(molgraph: CDPL.Chem.MolecularGraph) -> None: pass

    ##
    # \brief Replaces the current set of rings by the aromatic rings in the SSSR of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to extract the aromatic rings.
    # \param sssr The SSSR of the molecular graph <em>molgraph</em>.
    # 
    def extract(molgraph: CDPL.Chem.MolecularGraph, sssr: CDPL.Chem.FragmentList) -> None: pass

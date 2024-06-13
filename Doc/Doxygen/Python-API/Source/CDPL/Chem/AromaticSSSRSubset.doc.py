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
# \brief Implements the extraction of the aromatic rings in the SSSR of a molecular graph.
# 
class AromaticSSSRSubset(FragmentList):

    ##
    # \brief Constructs an empty <tt>AromaticSSSRSubset</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %AromaticSSSRSubset instance \a arom_sssr.
    # \param arom_sssr The \e %AromaticSSSRSubset instance to copy.
    # 
    def __init__(arom_sssr: AromaticSSSRSubset) -> None: pass

    ##
    # \brief Construct a <tt>AromaticSSSRSubset</tt> instance that contains all aromatic rings of the SSSR of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to extract the aromatic rings.
    # 
    def __init__(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %AromaticSSSRSubset instance \a arom_sssr.
    # \param arom_sssr The \e %AromaticSSSRSubset instance to copy.
    # \return \a self
    # 
    def assign(arom_sssr: AromaticSSSRSubset) -> AromaticSSSRSubset: pass

    ##
    # \brief Replaces the current set of rings by the aromatic rings in the SSSR of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to extract the aromatic rings.
    # 
    def extract(molgraph: MolecularGraph) -> None: pass

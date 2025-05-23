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
# \brief Implements the perception of the <em>Extended Smallest Set of Smallest Rings (ESSSR)</em> of a molecular graph.
# 
class ExtendedSSSR(FragmentList):

    ##
    # \brief Constructs an empty <tt>ExtendedSSSR</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %ExtendedSSSR instance \a esssr.
    # \param esssr The \e %ExtendedSSSR instance to copy.
    # 
    def __init__(esssr: ExtendedSSSR) -> None: pass

    ##
    # \brief Construct a <tt>ExtendedSSSR</tt> instance that represents the ESSSR of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to perceive the ESSSR.
    # 
    def __init__(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %ExtendedSSSR instance \a esssr.
    # \param esssr The \c %ExtendedSSSR instance to copy.
    # \return \a self
    # 
    def assign(esssr: ExtendedSSSR) -> ExtendedSSSR: pass

    ##
    # \brief Replaces the current set of rings by the ESSSR of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to perceive the ESSSR.
    # 
    def perceive(molgraph: MolecularGraph) -> None: pass

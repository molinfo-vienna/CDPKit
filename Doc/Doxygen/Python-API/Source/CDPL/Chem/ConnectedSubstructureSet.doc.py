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
# \brief ConnectedSubstructureSet.
# 
class ConnectedSubstructureSet(FragmentList):

    ##
    # \brief Constructs an empty <tt>ConnectedSubstructureSet</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs and initialzes a <tt>ConnectedSubstructureSet</tt> instance for the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph to search for connected substructures.
    # 
    def __init__(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Specifies the molecular graph that is searched for connected substructures.
    # 
    # The current substructure size is reset to zero.
    # 
    # \param molgraph The molecular graph to search for connected substructures.
    # 
    def reset(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Returns the current substructure size in terms of number of bonds.
    # 
    # The current substructure size corresponds to the size that was specified in the the last call to findSubstructures(). If findSubstructures() has not yet been called, the current substructure size is zero.
    # 
    # \return The current substructure size.
    # 
    def getSubstructureSize() -> int: pass

    ##
    # \brief Searches the specified molecular graph for connected substructures of the given size.
    # 
    # If a molecular graph has not yet been specified (in the constructor or by a prior call to reset(const Chem.MolecularGraph&)), the method has no effect. Otherwise, all connected substructures of the specified size are added as Chem.Fragment objects to the list of previously found (if any) substructures. If the specified size is zero, substructures of size <em>1</em> (i.e. the bonds of the molecular graph) will be extracted.
    # 
    # \param size The substructure size in terms of number of bonds.
    # 
    def findSubstructures(size: int) -> None: pass

    substructureSize = property(getSubstructureSize, setSubstructureSize)

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
# \brief Decomposes a molecular graph into its Bemis-Murcko framework, ring systems, linkers and side chains.
# 
# After calling analyze() the four constituent fragment sets can be queried separately via getRingSystems(), getLinkers(), getFrameworks() and getSideChains(). The framework of a molecule is the union of all ring systems together with the linker chains that connect them; side chains are the remaining acyclic substituents. Hydrogen atoms can optionally be stripped from the input.
# 
# \see [\ref BEMU] 
# 
# \since 1.1
# 
class BemisMurckoAnalyzer(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>BemisMurckoAnalyzer</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %BemisMurckoAnalyzer instance \a analyzer.
    # \param analyzer The \c %BemisMurckoAnalyzer instance to copy.
    # 
    def __init__(analyzer: BemisMurckoAnalyzer) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %BemisMurckoAnalyzer instance \a gen.
    # \param gen The \c %BemisMurckoAnalyzer instance to copy.
    # \return \a self
    # 
    def assign(gen: BemisMurckoAnalyzer) -> BemisMurckoAnalyzer: pass

    ##
    # \brief Specifies whether hydrogen atoms shall be stripped from the input before the decomposition.
    # 
    # \param strip If <tt>True</tt>, hydrogens are removed prior to analysis.
    # 
    def stripHydrogens(strip: bool) -> None: pass

    ##
    # \brief Tells whether hydrogen atoms are stripped from the input before the decomposition.
    # 
    # \return <tt>True</tt> if hydrogens are stripped, and <tt>False</tt> otherwise.
    # 
    def hydrogensStripped() -> bool: pass

    ##
    # \brief Performs the Bemis-Murcko decomposition of the molecular graph <em>molgraph</em>.
    # 
    # After this call the four fragment sets produced by the decomposition are available via getRingSystems(), getLinkers(), getFrameworks() and getSideChains().
    # 
    # \param molgraph The molecular graph to decompose.
    # 
    def analyze(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Returns the perceived ring systems of the input molecular graph.
    # 
    # \return A reference to the list of ring-system fragments.
    # 
    def getRingSystems() -> FragmentList: pass

    ##
    # \brief Returns the side chains (acyclic substituents) of the input molecular graph.
    # 
    # \return A reference to the list of side-chain fragments.
    # 
    def getSideChains() -> FragmentList: pass

    ##
    # \brief Returns the linker fragments connecting different ring systems of the input molecular graph.
    # 
    # \return A reference to the list of linker fragments.
    # 
    def getLinkers() -> FragmentList: pass

    ##
    # \brief Returns the Bemis-Murcko frameworks of the input molecular graph (union of ring systems and linkers).
    # 
    # \return A reference to the list of framework fragments.
    # 
    def getFrameworks() -> FragmentList: pass

    hydrogenStripping = property(hydrogensStripped, stripHydrogens)

    ringSystems = property(getRingSystems)

    sideChains = property(getSideChains)

    linkers = property(getLinkers)

    frameworks = property(getFrameworks)

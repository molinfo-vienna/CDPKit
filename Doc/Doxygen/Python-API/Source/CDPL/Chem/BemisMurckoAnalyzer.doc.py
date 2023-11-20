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
# \brief BemisMurckoAnalyzer.
# 
# \see [\ref BEMU] 
# 
# \since 1.1
# 
class BemisMurckoAnalyzer(Boost.Python.instance):

    ##
    # \brief Initializes the \e %BemisMurckoAnalyzer instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %BemisMurckoAnalyzer instance \a analyzer.
    # \param analyzer The \e %BemisMurckoAnalyzer instance to copy.
    # 
    def __init__(analyzer: BemisMurckoAnalyzer) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %BemisMurckoAnalyzer instance \a gen.
    # \param gen The \e %BemisMurckoAnalyzer instance to copy.
    # \return \a self
    # 
    def assign(gen: BemisMurckoAnalyzer) -> BemisMurckoAnalyzer: pass

    ##
    # \brief 
    # \param strip 
    #
    def stripHydrogens(strip: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def hydrogensStripped() -> bool: pass

    ##
    # \brief 
    # \param molgraph 
    #
    def analyze(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getRingSystems() -> FragmentList: pass

    ##
    # \brief 
    # \return 
    #
    def getSideChains() -> FragmentList: pass

    ##
    # \brief 
    # \return 
    #
    def getLinkers() -> FragmentList: pass

    ##
    # \brief 
    # \return 
    #
    def getFrameworks() -> FragmentList: pass

    ##
    # \brief FIXME!
    #
    hydrogenStripping = property(getHydrogenStripping, setHydrogenStripping)

    ringSystems = property(getRingSystems)

    sideChains = property(getSideChains)

    linkers = property(getLinkers)

    frameworks = property(getFrameworks)

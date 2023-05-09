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
# \brief 
#
class HydrophobicAtomFeatureGenerator(PatternBasedFeatureGenerator):

    ##
    # \brief 
    #
    DEF_FEATURE_TOL = 1.5

    ##
    # \brief 
    #
    DEF_FEATURE_TYPE = 1

    ##
    # \brief 
    #
    DEF_FEATURE_GEOM = 1

    ##
    # \brief 
    #
    DEF_HYD_THRESHOLD = 0.5

    ##
    # \brief Initializes the \e %HydrophobicAtomFeatureGenerator instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %HydrophobicAtomFeatureGenerator instance.
    # \param molgraph 
    # \param pharm 
    #
    def __init__(molgraph: CDPL.Chem.MolecularGraph, pharm: Pharmacophore) -> None: pass

    ##
    # \brief Initializes the \e %HydrophobicAtomFeatureGenerator instance.
    # \param gen 
    #
    def __init__(gen: HydrophobicAtomFeatureGenerator) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %HydrophobicAtomFeatureGenerator instance \a gen.
    # \param gen The \e %HydrophobicAtomFeatureGenerator instance to copy.
    # \return \a self
    #
    def assign(gen: HydrophobicAtomFeatureGenerator) -> HydrophobicAtomFeatureGenerator: pass

    ##
    # \brief 
    # \param type 
    #
    def setFeatureType(type: int) -> None: pass

    ##
    # \brief 
    # \param geom 
    #
    def setFeatureGeometry(geom: int) -> None: pass

    ##
    # \brief 
    # \param tol 
    #
    def setFeatureTolerance(tol: float) -> None: pass

    ##
    # \brief 
    # \param thresh 
    #
    def setHydrophobicityThreshold(thresh: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getFeatureType() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getFeatureGeometry() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getFeatureTolerance() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getHydrophobicityThreshold() -> float: pass

    ##
    # \brief 
    #
    featureType = property(getFeatureType, setFeatureType)

    ##
    # \brief 
    #
    featureGeometry = property(getFeatureGeometry, setFeatureGeometry)

    ##
    # \brief 
    #
    featureTolerance = property(getFeatureTolerance, setFeatureTolerance)

    ##
    # \brief FIXME!
    #
    hydThreshold = property(getHydThreshold, setHydThreshold)

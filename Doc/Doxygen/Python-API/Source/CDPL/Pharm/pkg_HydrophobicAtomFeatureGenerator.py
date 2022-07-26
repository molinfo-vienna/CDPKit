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
    # \param self The \e %HydrophobicAtomFeatureGenerator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %HydrophobicAtomFeatureGenerator instance.
    # \param self The \e %HydrophobicAtomFeatureGenerator instance to initialize.
    # \param molgraph 
    # \param pharm 
    #
    def __init__(self: object, molgraph: CDPL.Chem.MolecularGraph, pharm: Pharmacophore) -> None: pass

    ##
    # \brief Initializes the \e %HydrophobicAtomFeatureGenerator instance.
    # \param self The \e %HydrophobicAtomFeatureGenerator instance to initialize.
    # \param gen 
    #
    def __init__(self: object, gen: HydrophobicAtomFeatureGenerator) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %HydrophobicAtomFeatureGenerator instance \a gen.
    # \param self The \e %HydrophobicAtomFeatureGenerator instance this method is called upon.
    # \param gen The \e %HydrophobicAtomFeatureGenerator instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: HydrophobicAtomFeatureGenerator, gen: HydrophobicAtomFeatureGenerator) -> HydrophobicAtomFeatureGenerator: pass

    ##
    # \brief 
    # \param self The \e %HydrophobicAtomFeatureGenerator instance this method is called upon.
    # \param type 
    #
    def setFeatureType(self: HydrophobicAtomFeatureGenerator, type: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %HydrophobicAtomFeatureGenerator instance this method is called upon.
    # \param geom 
    #
    def setFeatureGeometry(self: HydrophobicAtomFeatureGenerator, geom: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %HydrophobicAtomFeatureGenerator instance this method is called upon.
    # \param tol 
    #
    def setFeatureTolerance(self: HydrophobicAtomFeatureGenerator, tol: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %HydrophobicAtomFeatureGenerator instance this method is called upon.
    # \param thresh 
    #
    def setHydrophobicityThreshold(self: HydrophobicAtomFeatureGenerator, thresh: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %HydrophobicAtomFeatureGenerator instance this method is called upon.
    # \return 
    #
    def getFeatureType(self: HydrophobicAtomFeatureGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %HydrophobicAtomFeatureGenerator instance this method is called upon.
    # \return 
    #
    def getFeatureGeometry(self: HydrophobicAtomFeatureGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %HydrophobicAtomFeatureGenerator instance this method is called upon.
    # \return 
    #
    def getFeatureTolerance(self: HydrophobicAtomFeatureGenerator) -> float: pass

    ##
    # \brief 
    # \param self The \e %HydrophobicAtomFeatureGenerator instance this method is called upon.
    # \return 
    #
    def getHydrophobicityThreshold(self: HydrophobicAtomFeatureGenerator) -> float: pass

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

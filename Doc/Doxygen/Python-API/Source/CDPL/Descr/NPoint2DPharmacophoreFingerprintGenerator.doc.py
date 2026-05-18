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
# \brief N-point pharmacophore fingerprint generator that uses topological feature distances.
# 
# The fingerprint encodes the binned topological distances between all combinations of feature tuples generated from a molecular graph. The choice of how feature-pair topological distance is computed (min, max or average over the topological distances between the underlying atoms) is configurable via FeatureDistanceType.
# 
# \since 1.2
# 
class NPoint2DPharmacophoreFingerprintGenerator(NPointPharmacophoreFingerprintGenerator):

    ##
    # \brief Specifies how the topological distance between two features is derived from the topological distances between their underlying atoms.
    # 
    class FeatureDistanceType(Boost.Python.enum):

        ##
        # \brief .
        #
         = 0

        ##
        # \brief .
        #
         = 1

        ##
        # \brief .
        #
         = 2

    ##
    # \brief Default distance bin size.
    # 
    # \since 1.3
    # 
    DEF_BIN_SIZE = 2.0

    ##
    # \brief Default feature distance type.
    # 
    DEF_FEATURE_DISTANCE_TYPE = 

    ##
    # \brief Constructs the <tt>NPoint2DPharmacophoreFingerprintGenerator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs the <tt>NPoint2DPharmacophoreFingerprintGenerator</tt> instance and generates the fingerprint of <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph.
    # \param fp The output bitset.
    # 
    def __init__(molgraph: Chem.MolecularGraph, fp: Util.BitSet) -> None: pass

    ##
    # \brief Copy constructor.
    # 
    def __init__(gen: NPoint2DPharmacophoreFingerprintGenerator) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %NPoint2DPharmacophoreFingerprintGenerator instance \a gen.
    # \param gen The \c %NPoint2DPharmacophoreFingerprintGenerator instance to copy.
    # \return \a self
    # 
    def assign(gen: NPoint2DPharmacophoreFingerprintGenerator) -> NPoint2DPharmacophoreFingerprintGenerator: pass

    ##
    # \brief Sets the type of feature-pair topological distance to use.
    # 
    # \param dist_type The feature distance type.
    # 
    def setFeatureDistanceType(dist_type: FeatureDistanceType) -> None: pass

    ##
    # \brief Returns the currently configured feature distance type.
    # 
    # \return The configured feature distance type.
    # 
    def getFeatureDistanceType() -> FeatureDistanceType: pass

    ##
    # \brief Generates the fingerprint of the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph.
    # \param fp The output bitset.
    # 
    def generate(molgraph: Chem.MolecularGraph, fp: Util.BitSet) -> None: pass

    featureDistanceType = property(getFeatureDistanceType, setFeatureDistanceType)

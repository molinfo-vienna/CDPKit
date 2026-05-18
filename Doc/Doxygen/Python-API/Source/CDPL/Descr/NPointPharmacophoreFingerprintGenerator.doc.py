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
# \brief Abstract base for N-point pharmacophore fingerprint generators.
# 
# The base class implements the common machinery for enumerating feature tuples of size in <em>[minTupleSize, maxTupleSize]</em>, binning the feature-pair distances of each tuple and setting the corresponding bits of the output fingerprint. The concrete distance (topological vs. spatial 3D) is provided by the derived class via the pure virtual <tt>getDistance()</tt> hook.
# 
# \since 1.2
# 
class NPointPharmacophoreFingerprintGenerator(Boost.Python.instance):

    ##
    # \brief Default minimum size of generated feature tuples.
    # 
    DEF_MIN_FEATURE_TUPLE_SIZE = 1

    ##
    # \brief Default maximum size of generated feature tuples.
    # 
    DEF_MAX_FEATURE_TUPLE_SIZE = 3

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %NPointPharmacophoreFingerprintGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %NPointPharmacophoreFingerprintGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %NPointPharmacophoreFingerprintGenerator instance \a gen.
    # \param gen The \c %NPointPharmacophoreFingerprintGenerator instance to copy.
    # \return \a self
    # 
    def assign(gen: NPointPharmacophoreFingerprintGenerator) -> NPointPharmacophoreFingerprintGenerator: pass

    ##
    # \brief Sets the minimum size of generated feature tuples.
    # 
    # \param min_size The minimum tuple size.
    # 
    def setMinFeatureTupleSize(min_size: int) -> None: pass

    ##
    # \brief Returns the currently configured minimum feature tuple size.
    # 
    # \return The configured minimum tuple size.
    # 
    def getMinFeatureTupleSize() -> int: pass

    ##
    # \brief Sets the maximum size of generated feature tuples.
    # 
    # \param max_size The maximum tuple size.
    # 
    def setMaxFeatureTupleSize(max_size: int) -> None: pass

    ##
    # \brief Returns the currently configured maximum feature tuple size.
    # 
    # \return The configured maximum tuple size.
    # 
    def getMaxFeatureTupleSize() -> int: pass

    ##
    # \brief Sets the size of the bins used to discretize feature-pair distances.
    # 
    # \param bin_size The bin size.
    # 
    def setBinSize(bin_size: float) -> None: pass

    ##
    # \brief Returns the currently configured distance bin size.
    # 
    # \return The configured bin size.
    # 
    def getBinSize() -> float: pass

    ##
    # \brief Specifies a predicate that selects which features participate in the fingerprint.
    # 
    # \param func The feature filter function.
    # 
    # \since 1.3
    # 
    def setFeatureFilterFunction(func: Pharm.BoolFeatureFunctor) -> None: pass

    ##
    # \brief Returns the currently configured feature filter function.
    # 
    # \return The configured feature filter function. 
    # 
    # \since 1.3
    # 
    def getFeatureFilterFunction() -> Pharm.BoolFeatureFunctor: pass

    ##
    # \brief Returns the internal pharmacophore generator used for the input molecular graph.
    # 
    # \return A reference to the pharmacophore generator.
    # 
    def getPharmacophoreGenerator() -> Pharm.PharmacophoreGenerator: pass

    objectID = property(getObjectID)

    minFeatureTupleSize = property(getMinFeatureTupleSize, setMinFeatureTupleSize)

    maxFeatureTupleSize = property(getMaxFeatureTupleSize, setMaxFeatureTupleSize)

    binSize = property(getBinSize, setBinSize)

    featureFilterFunction = property(getFeatureFilterFunction, setFeatureFilterFunction)

    pharmGenerator = property(getPharmacophoreGenerator)

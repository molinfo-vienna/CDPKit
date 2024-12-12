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
# \brief NPointPharmacophoreFingerprintGenerator.
# 
# \since 1.2
# 
class NPointPharmacophoreFingerprintGenerator(Boost.Python.instance):

    ##
    # \brief 
    #
    DEF_MIN_FEATURE_TUPLE_SIZE = 1

    ##
    # \brief 
    #
    DEF_MAX_FEATURE_TUPLE_SIZE = 3

    ##
    # \brief 
    #
    DEF_BIN_SIZE = 0.5

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %NPointPharmacophoreFingerprintGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %NPointPharmacophoreFingerprintGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %NPointPharmacophoreFingerprintGenerator instance \a gen.
    # \param gen The \e %NPointPharmacophoreFingerprintGenerator instance to copy.
    # \return \a self
    # 
    def assign(gen: NPointPharmacophoreFingerprintGenerator) -> NPointPharmacophoreFingerprintGenerator: pass

    ##
    # \brief 
    # \param min_size 
    #
    def setMinFeatureTupleSize(min_size: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMinFeatureTupleSize() -> int: pass

    ##
    # \brief 
    # \param max_size 
    #
    def setMaxFeatureTupleSize(max_size: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxFeatureTupleSize() -> int: pass

    ##
    # \brief 
    # \param bin_size 
    #
    def setBinSize(bin_size: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getBinSize() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getPharmacophoreGenerator() -> Pharm.PharmacophoreGenerator: pass

    objectID = property(getObjectID)

    minFeatureTupleSize = property(getMinFeatureTupleSize, setMinFeatureTupleSize)

    maxFeatureTupleSize = property(getMaxFeatureTupleSize, setMaxFeatureTupleSize)

    binSize = property(getBinSize, setBinSize)

    pharmGenerator = property(getPharmacophoreGenerator)

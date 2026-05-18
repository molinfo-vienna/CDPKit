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
# \brief Predicts the binding affinity of a ligand pose from its GRAIL descriptor vector.
# 
# The prediction is performed using a pre-trained regression model that takes a GRAIL descriptor as input and returns a binding affinity estimate. The targeted affinity measure ( \f$ pK_d \f$, \f$ pK_i \f$, or a combined \f$ pK_d/pK_i \f$ model) is selected at call time via the AffinityMeasure argument.
# 
class BindingAffinityCalculator(Boost.Python.instance):

    ##
    # \brief Specifies the affinity measure the prediction targets.
    # 
    class AffinityMeasure(Boost.Python.enum):

        ##
        # \brief \f$ pK_d \f$ (dissociation constant).
        # 
        PKD = 0

        ##
        # \brief \f$ pK_i \f$ (inhibition constant).
        # 
        PKI = 1

        ##
        # \brief Combined \f$ pK_d/pK_i \f$ model.
        # 
        PKD_PKI = 2

    ##
    # \brief Constructs the <tt>BindingAffinityCalculator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %BindingAffinityCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %BindingAffinityCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Predicts the binding affinity from the given GRAIL descriptor.
    # 
    # \param grail_descr The GRAIL descriptor vector of the ligand pose.
    # \param measure The targeted affinity measure.
    # 
    # \return The predicted binding affinity.
    # 
    def __call__(grail_descr: Math.DVector, measure: AffinityMeasure) -> float: pass

    objectID = property(getObjectID)

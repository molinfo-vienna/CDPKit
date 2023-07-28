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
# \brief HBondingInteractionConstraint.
# 
class HBondingInteractionConstraint(Boost.Python.instance):

    ##
    # \brief 
    #
    DEF_MIN_HB_LENGTH = 1.2

    ##
    # \brief 
    #
    DEF_MAX_HB_LENGTH = 2.8

    ##
    # \brief 
    #
    DEF_MIN_AHD_ANGLE = 130.0

    ##
    # \brief 
    #
    DEF_MAX_ACC_ANGLE = 85.0

    ##
    # \brief Initializes the \e %HBondingInteractionConstraint instance.
    # \param self The \e %HBondingInteractionConstraint instance to initialize.
    # \param constr 
    # 
    def __init__(constr: HBondingInteractionConstraint) -> None: pass

    ##
    # \brief Constructs a <tt>HBondingInteractionConstraint</tt> functor with the specified constraints.
    # 
    # \param don_acc <tt>True</tt> if the first feature argument represents the donor- and the second one the acceptor-feature, and <tt>False</tt> otherwise.
    # \param min_len The minimum allowed length of the H-bond (distance between the hydrogen-atom and acceptor-feature).
    # \param max_len The maximum allowed length of the H-bond (distance between the hydrogen-atom and acceptor-feature).
    # \param min_ahd_ang The minimum allowed angle between the acceptor-feature, hydrogen-atom and donor-feature.
    # \param max_acc_ang The maximum allowed angle between the H-bond direction and the acceptor-feature vector.
    # 
    def __init__(don_acc: bool, min_len: float = 1.2, max_len: float = 1.2, min_ahd_ang: float = 130.0, max_acc_ang: float = 85.0) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %HBondingInteractionConstraint instance this method is called upon.
    # 
    # Different Python \e %HBondingInteractionConstraint instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %HBondingInteractionConstraint instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getMinLength() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxLength() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getMinAHDAngle() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxAcceptorAngle() -> float: pass

    ##
    # \brief 
    # \param constr 
    # \return 
    #
    def assign(constr: HBondingInteractionConstraint) -> HBondingInteractionConstraint: pass

    ##
    # \brief 
    # \param ftr1 
    # \param ftr2 
    # \return 
    #
    def __call__(ftr1: Feature, ftr2: Feature) -> bool: pass

    objectID = property(getObjectID)

    minLength = property(getMinLength)

    maxLength = property(getMaxLength)

    minAHDAngle = property(getMinAHDAngle)

    maxAcceptorAngle = property(getMaxAcceptorAngle)

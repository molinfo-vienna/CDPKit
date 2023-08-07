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
# \brief FeatureGeometryMatchFunctor.
# 
class FeatureGeometryMatchFunctor(Boost.Python.instance):

    ##
    # \brief 
    #
    DEF_MAX_HBA_INTERACTION_DIR_ANGLE = 85.0

    ##
    # \brief 
    #
    DEF_MAX_HBA_ORIENTATION_DEVIATION = 45.0

    ##
    # \brief 
    #
    DEF_MAX_HBD_INTERACTION_DIR_DEVIATION = 45.0

    ##
    # \brief 
    #
    DEF_MAX_XBA_INTERACTION_DIR_DEVIATION = 45.0

    ##
    # \brief 
    #
    DEF_MAX_XBD_INTERACTION_DIR_DEVIATION = 45.0

    ##
    # \brief 
    #
    DEF_MAX_AR_ORIENTATION_DEVIATION = 45.0

    ##
    # \brief Initializes a copy of the \e %FeatureGeometryMatchFunctor instance \a func.
    # \param func The \e %FeatureGeometryMatchFunctor instance to copy.
    # 
    def __init__(func: FeatureGeometryMatchFunctor) -> None: pass

    ##
    # \brief Initializes the \e %FeatureGeometryMatchFunctor instance.
    # \param max_hba_int_dir_angle 
    # \param max_hba_orient_dev 
    # \param max_hbd_int_dir_dev 
    # \param max_xba_int_dir_dev 
    # \param max_xbd_int_dir_dev 
    # \param max_ar_orient_dev 
    # 
    def __init__(max_hba_int_dir_angle: float = 85.0, max_hba_orient_dev: float = 45.0, max_hbd_int_dir_dev: float = 45.0, max_xba_int_dir_dev: float = 45.0, max_xbd_int_dir_dev: float = 45.0, max_ar_orient_dev: float = 45.0) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %FeatureGeometryMatchFunctor instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FeatureGeometryMatchFunctor instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FeatureGeometryMatchFunctor instance \a func.
    # \param func The \e %FeatureGeometryMatchFunctor instance to copy.
    # \return \a self
    # 
    def assign(func: FeatureGeometryMatchFunctor) -> FeatureGeometryMatchFunctor: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxHBAInteractionDirAngle() -> float: pass

    ##
    # \brief 
    # \param angle 
    #
    def setMaxHBAInteractionDirAngle(angle: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxHBAOrientationDeviation() -> float: pass

    ##
    # \brief 
    # \param angle 
    #
    def setMaxHBAOrientationDeviation(angle: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxHBDInteractionDirDeviation() -> float: pass

    ##
    # \brief 
    # \param angle 
    #
    def setMaxHBDInteractionDirDeviation(angle: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxXBAInteractionDirDeviation() -> float: pass

    ##
    # \brief 
    # \param angle 
    #
    def setMaxXBAInteractionDirDeviation(angle: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxXBDInteractionDirDeviation() -> float: pass

    ##
    # \brief 
    # \param angle 
    #
    def setMaxXBDInteractionDirDeviation(angle: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxAROrientationDeviation() -> float: pass

    ##
    # \brief 
    # \param angle 
    #
    def setMaxAROrientationDeviation(angle: float) -> None: pass

    ##
    # \brief Calculates a score reflecting the goodness of the spatial feature orientation match.
    # 
    # \param ftr1 The first feature.
    # \param ftr2 The second feature.
    # 
    # \return A score from <em>0</em> (=spatial deviation outside the allowed range) and <em>1</em> (optimum match) describing the goodness of the spatial orientation match of the two features.
    # 
    def __call__(ftr1: Feature, ftr2: Feature) -> bool: pass

    ##
    # \brief Calculates a score reflecting the goodness of the spatial feature orientation match.
    # 
    # \param ftr1 The first feature.
    # \param ftr2 The second feature.
    # \param xform The transformation to apply to the spatial orientation of the second feature.
    # 
    # \return A score from <em>0</em> (=spatial deviation outside the allowed range) and <em>1</em> (optimum match) describing the goodness of the spatial orientation match of the two features.
    # 
    def __call__(ftr1: Feature, ftr2: Feature, xform: Math.Matrix4D) -> bool: pass

    objectID = property(getObjectID)

    maxHBAInteractionDirAngle = property(getMaxHBAInteractionDirAngle, setMaxHBAInteractionDirAngle)

    maxHBAOrientationDeviation = property(getMaxHBAOrientationDeviation, setMaxHBAOrientationDeviation)

    maxHBDInteractionDirDeviation = property(getMaxHBDInteractionDirDeviation, setMaxHBDInteractionDirDeviation)

    maxXBDInteractionDirDeviation = property(getMaxXBDInteractionDirDeviation, setMaxXBDInteractionDirDeviation)

    maxXBAInteractionDirDeviation = property(getMaxXBAInteractionDirDeviation, setMaxXBAInteractionDirDeviation)

    maxAROrientationDeviation = property(getMaxAROrientationDeviation, setMaxAROrientationDeviation)

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
# \brief Match functor that quantifies the goodness of the spatial orientation match between two pharmacophore features, applying type-specific tolerances for H-bond donor/acceptor, halogen-bond donor/acceptor and aromatic features.
# 
class FeatureGeometryMatchFunctor(Boost.Python.instance):

    ##
    # \brief Default maximum H-bond acceptor interaction direction angle in degrees.
    # 
    DEF_MAX_HBA_INTERACTION_DIR_ANGLE = 85.0

    ##
    # \brief Default maximum H-bond acceptor orientation deviation in degrees.
    # 
    DEF_MAX_HBA_ORIENTATION_DEVIATION = 45.0

    ##
    # \brief Default maximum H-bond donor interaction direction deviation in degrees.
    # 
    DEF_MAX_HBD_INTERACTION_DIR_DEVIATION = 45.0

    ##
    # \brief Default maximum halogen-bond acceptor interaction direction deviation in degrees.
    # 
    DEF_MAX_XBA_INTERACTION_DIR_DEVIATION = 45.0

    ##
    # \brief Default maximum halogen-bond donor interaction direction deviation in degrees.
    # 
    DEF_MAX_XBD_INTERACTION_DIR_DEVIATION = 45.0

    ##
    # \brief Default maximum aromatic feature orientation deviation in degrees.
    # 
    DEF_MAX_AR_ORIENTATION_DEVIATION = 45.0

    ##
    # \brief Initializes a copy of the \c %FeatureGeometryMatchFunctor instance \a func.
    # \param func The \c %FeatureGeometryMatchFunctor instance to copy.
    # 
    def __init__(func: FeatureGeometryMatchFunctor) -> None: pass

    ##
    # \brief Constructs a <tt>FeatureGeometryMatchFunctor</tt> with the specified per-type angle tolerances.
    # 
    # \param max_hba_int_dir_angle The maximum H-bond acceptor interaction direction angle.
    # \param max_hba_orient_dev The maximum H-bond acceptor orientation deviation.
    # \param max_hbd_int_dir_dev The maximum H-bond donor interaction direction deviation.
    # \param max_xba_int_dir_dev The maximum halogen-bond acceptor interaction direction deviation.
    # \param max_xbd_int_dir_dev The maximum halogen-bond donor interaction direction deviation.
    # \param max_ar_orient_dev The maximum aromatic feature orientation deviation.
    # 
    def __init__(max_hba_int_dir_angle: float = 85.0, max_hba_orient_dev: float = 45.0, max_hbd_int_dir_dev: float = 45.0, max_xba_int_dir_dev: float = 45.0, max_xbd_int_dir_dev: float = 45.0, max_ar_orient_dev: float = 45.0) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %FeatureGeometryMatchFunctor instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %FeatureGeometryMatchFunctor instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %FeatureGeometryMatchFunctor instance \a func.
    # \param func The \c %FeatureGeometryMatchFunctor instance to copy.
    # \return \a self
    # 
    def assign(func: FeatureGeometryMatchFunctor) -> FeatureGeometryMatchFunctor: pass

    ##
    # \brief Returns the currently configured maximum H-bond acceptor interaction direction angle.
    # 
    # \return The maximum HBA interaction direction angle in degrees.
    # 
    def getMaxHBAInteractionDirAngle() -> float: pass

    ##
    # \brief Sets the maximum H-bond acceptor interaction direction angle.
    # 
    # \param angle The new maximum HBA interaction direction angle in degrees.
    # 
    def setMaxHBAInteractionDirAngle(angle: float) -> None: pass

    ##
    # \brief Returns the currently configured maximum H-bond acceptor orientation deviation.
    # 
    # \return The maximum HBA orientation deviation in degrees.
    # 
    def getMaxHBAOrientationDeviation() -> float: pass

    ##
    # \brief Sets the maximum H-bond acceptor orientation deviation.
    # 
    # \param angle The new maximum HBA orientation deviation in degrees.
    # 
    def setMaxHBAOrientationDeviation(angle: float) -> None: pass

    ##
    # \brief Returns the currently configured maximum H-bond donor interaction direction deviation.
    # 
    # \return The maximum HBD interaction direction deviation in degrees.
    # 
    def getMaxHBDInteractionDirDeviation() -> float: pass

    ##
    # \brief Sets the maximum H-bond donor interaction direction deviation.
    # 
    # \param angle The new maximum HBD interaction direction deviation in degrees.
    # 
    def setMaxHBDInteractionDirDeviation(angle: float) -> None: pass

    ##
    # \brief Returns the currently configured maximum halogen-bond acceptor interaction direction deviation.
    # 
    # \return The maximum XBA interaction direction deviation in degrees.
    # 
    def getMaxXBAInteractionDirDeviation() -> float: pass

    ##
    # \brief Sets the maximum halogen-bond acceptor interaction direction deviation.
    # 
    # \param angle The new maximum XBA interaction direction deviation in degrees.
    # 
    def setMaxXBAInteractionDirDeviation(angle: float) -> None: pass

    ##
    # \brief Returns the currently configured maximum halogen-bond donor interaction direction deviation.
    # 
    # \return The maximum XBD interaction direction deviation in degrees.
    # 
    def getMaxXBDInteractionDirDeviation() -> float: pass

    ##
    # \brief Sets the maximum halogen-bond donor interaction direction deviation.
    # 
    # \param angle The new maximum XBD interaction direction deviation in degrees.
    # 
    def setMaxXBDInteractionDirDeviation(angle: float) -> None: pass

    ##
    # \brief Returns the currently configured maximum aromatic feature orientation deviation.
    # 
    # \return The maximum aromatic orientation deviation in degrees.
    # 
    def getMaxAROrientationDeviation() -> float: pass

    ##
    # \brief Sets the maximum aromatic feature orientation deviation.
    # 
    # \param angle The new maximum aromatic orientation deviation in degrees.
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

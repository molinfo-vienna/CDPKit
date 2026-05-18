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
# \brief Functor for the evaluation of the generalized-bell atom density contribution of an atom at a query position.
# 
# The density falls off with distance from the atom according to a generalized bell function parameterized by the atom's van der Waals radius (scaled by a configurable factor) and the radius of a probe sphere.
# 
class GeneralizedBellAtomDensity(Boost.Python.instance):

    ##
    # \brief Default scaling factor applied to atom van der Waals radii.
    # 
    DEF_RADIUS_SCALING_FACTOR = 1.0

    ##
    # \brief Default probe sphere radius.
    # 
    DEF_PROBE_RADIUS = 0.0

    ##
    # \brief Initializes a copy of the \c %GeneralizedBellAtomDensity instance \a func.
    # \param func The \c %GeneralizedBellAtomDensity instance to copy.
    # 
    def __init__(func: GeneralizedBellAtomDensity) -> None: pass

    ##
    # \brief Constructs a <tt>GeneralizedBellAtomDensity</tt> instance with the given configuration.
    # 
    # \param probe_radius The probe sphere radius.
    # \param rad_scaling_factor The scaling factor applied to atom van der Waals radii.
    # 
    def __init__(probe_radius: float = 0.0, rad_scaling_factor: float = 1.0) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %GeneralizedBellAtomDensity instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %GeneralizedBellAtomDensity instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Returns the currently configured probe sphere radius.
    # 
    # \return The configured probe sphere radius.
    # 
    def getProbeRadius() -> float: pass

    ##
    # \brief Returns the currently configured van der Waals radius scaling factor.
    # 
    # \return The configured scaling factor.
    # 
    def getRadiusScalingFactor() -> float: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %GeneralizedBellAtomDensity instance \a func.
    # \param func The \c %GeneralizedBellAtomDensity instance to copy.
    # \return \a self
    # 
    def assign(func: GeneralizedBellAtomDensity) -> GeneralizedBellAtomDensity: pass

    ##
    # \brief Evaluates the atom density contribution of <em>atom</em> at the query position <em>pos</em>.
    # 
    # \param pos The 3D query position.
    # \param atom_pos The 3D position of <em>atom</em>.
    # \param atom The atom whose density contribution is evaluated.
    # 
    # \return The calculated atom density value.
    # 
    def __call__(pos: Math.Vector3D, atom_pos: Math.Vector3D, atom: Chem.Atom) -> float: pass

    objectID = property(getObjectID)

    probeRadius = property(getProbeRadius)

    radiusScalingFactor = property(getRadiusScalingFactor)

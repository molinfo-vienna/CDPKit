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
class SurfaceAtomExtractor(Boost.Python.instance):

    ##
    # \brief 
    #
    DEF_PROBE_RADIUS = 1.2

    ##
    # \brief 
    #
    DEF_GRID_OVERSIZE = 5.0

    ##
    # \brief 
    #
    DEF_GRID_STEP_SIZE = 0.75

    ##
    # \brief 
    #
    DEF_MIN_SURFACE_ACC = 0.01

    ##
    # \brief Initializes the \e %SurfaceAtomExtractor instance.
    # \param self The \e %SurfaceAtomExtractor instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %SurfaceAtomExtractor instance.
    # \param self The \e %SurfaceAtomExtractor instance to initialize.
    # \param extractor 
    #
    def __init__(self: object, extractor: SurfaceAtomExtractor) -> None: pass

    ##
    # \brief Initializes the \e %SurfaceAtomExtractor instance.
    # \param self The \e %SurfaceAtomExtractor instance to initialize.
    # \param cntnr 
    # \param parent_molgraph 
    # \param frag 
    #
    def __init__(self: object, cntnr: AtomContainer, parent_molgraph: MolecularGraph, frag: Fragment) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %SurfaceAtomExtractor instance this method is called upon.
    #
    # Different Python \e %SurfaceAtomExtractor instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %SurfaceAtomExtractor instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: SurfaceAtomExtractor) -> int: pass

    ##
    # \brief 
    # \param self The \e %SurfaceAtomExtractor instance this method is called upon.
    # \param func 
    #
    def setAtom3DCoordinatesFunction(self: SurfaceAtomExtractor, func: Atom3DCoordinatesFunction) -> None: pass

    ##
    # \brief 
    # \param self The \e %SurfaceAtomExtractor instance this method is called upon.
    # \return 
    #
    def getAtom3DCoordinatesFunction(self: SurfaceAtomExtractor) -> Atom3DCoordinatesFunction: pass

    ##
    # \brief 
    # \param self The \e %SurfaceAtomExtractor instance this method is called upon.
    # \param radius 
    #
    def setProbeRadius(self: SurfaceAtomExtractor, radius: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %SurfaceAtomExtractor instance this method is called upon.
    # \param size 
    #
    def setGridStepSize(self: SurfaceAtomExtractor, size: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %SurfaceAtomExtractor instance this method is called upon.
    # \param size 
    #
    def setGridOversize(self: SurfaceAtomExtractor, size: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %SurfaceAtomExtractor instance this method is called upon.
    # \param min_acc 
    #
    def setMinSurfaceAccessibility(self: SurfaceAtomExtractor, min_acc: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %SurfaceAtomExtractor instance this method is called upon.
    # \param num_points 
    #
    def setNumTestPoints(self: SurfaceAtomExtractor, num_points: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %SurfaceAtomExtractor instance this method is called upon.
    # \return 
    #
    def getProbeRadius(self: SurfaceAtomExtractor) -> float: pass

    ##
    # \brief 
    # \param self The \e %SurfaceAtomExtractor instance this method is called upon.
    # \return 
    #
    def getGridStepSize(self: SurfaceAtomExtractor) -> float: pass

    ##
    # \brief 
    # \param self The \e %SurfaceAtomExtractor instance this method is called upon.
    # \return 
    #
    def getGridOversize(self: SurfaceAtomExtractor) -> float: pass

    ##
    # \brief 
    # \param self The \e %SurfaceAtomExtractor instance this method is called upon.
    # \return 
    #
    def getMinSurfaceAccessibility(self: SurfaceAtomExtractor) -> float: pass

    ##
    # \brief 
    # \param self The \e %SurfaceAtomExtractor instance this method is called upon.
    # \return 
    #
    def getNumTestPoints(self: SurfaceAtomExtractor) -> int: pass

    ##
    # \brief 
    # \param self The \e %SurfaceAtomExtractor instance this method is called upon.
    # \param cntr 
    # \param parent_molgraph 
    # \param frag 
    #
    def extract(self: SurfaceAtomExtractor, cntr: AtomContainer, parent_molgraph: MolecularGraph, frag: Fragment) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %SurfaceAtomExtractor instance \a extractor.
    # \param self The \e %SurfaceAtomExtractor instance this method is called upon.
    # \param extractor The \e %SurfaceAtomExtractor instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: SurfaceAtomExtractor, extractor: SurfaceAtomExtractor) -> SurfaceAtomExtractor: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    probeRadius = property(getProbeRadius, setProbeRadius)

    ##
    # \brief 
    #
    gridStepSize = property(getGridStepSize, setGridStepSize)

    ##
    # \brief 
    #
    gridOversize = property(getGridOversize, setGridOversize)

    ##
    # \brief 
    #
    numTestPoints = property(getNumTestPoints, setNumTestPoints)

    ##
    # \brief 
    #
    minSurfaceAccessibility = property(getMinSurfaceAccessibility, setMinSurfaceAccessibility)

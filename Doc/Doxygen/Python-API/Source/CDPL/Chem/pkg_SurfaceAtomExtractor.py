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
# \brief SurfaceAtomExtractor.
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
    # \brief Constructs the <tt>SurfaceAtomExtractor</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %SurfaceAtomExtractor instance.
    # \param self The \e %SurfaceAtomExtractor instance to initialize.
    # \param extractor 
    # 
    def __init__(extractor: SurfaceAtomExtractor) -> None: pass

    ##
    # \brief Perceives the surface accessible atoms of <em>cntnr</em> and adds them to the fragment <em>frag</em>.
    # 
    # \param cntnr The set of atoms for which to perceive the surface accessibility.
    # \param parent_molgraph The parent molecular graph which embeds the atoms in <em>cntnr</em>.
    # \param frag The output fragment where to store the perceived surface atoms.
    # 
    def __init__(cntnr: AtomContainer, parent_molgraph: MolecularGraph, frag: Fragment) -> None: pass

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
    def getObjectID() -> int: pass

    ##
    # \brief Specifies a function for the retrieval of atom 3D-coordinates.
    # 
    # \param func The atom 3D-coordinates function.
    # 
    def setAtom3DCoordinatesFunction(func: Atom3DCoordinatesFunction) -> None: pass

    ##
    # \brief Returns the function that was registered for the retrieval of atom 3D-coordinates.
    # 
    # \return The registered atom 3D-coordinates function.
    # 
    def getAtom3DCoordinatesFunction() -> Atom3DCoordinatesFunction: pass

    ##
    # \brief Specifies the radius of the probe sphere that determines the accessibility of the surface atoms.
    # 
    # \param radius The radius of the probe sphere.
    # 
    # \note The default value is specified by the constant SurfaceAtomExtractor.DEF_PROBE_RADIUS.
    # 
    def setProbeRadius(radius: float) -> None: pass

    ##
    # \brief Specifies the distance between the grid-points in space which store lists of atoms with proximal positions.
    # 
    # \param size The distance between the grid-points along each axis.
    # 
    # \note The default value is specified by the constant SurfaceAtomExtractor.DEF_GRID_STEP_SIZE.
    # 
    def setGridStepSize(size: float) -> None: pass

    ##
    # \brief Specifies the margin that gets added to each side of the molecular graph's bounding-box for the calculation of the final atom-lookup grid dimensions.
    # 
    # \param size The margin that gets added to the molecular graph's bounding-box.
    # 
    # \note The default value is specified by the constant SurfaceAtomExtractor.DEF_GRID_OVERSIZE.
    # 
    def setGridOversize(size: float) -> None: pass

    ##
    # \brief Specifies the minimum fraction of test points that have to be accessible by the probe sphere to consider an atom as a surface atom.
    # 
    # \param min_acc The minimum required fraction of accessible test points.
    # 
    # \note The default value is specified by the constant SurfaceAtomExtractor.DEF_MIN_SURFACE_ACC.
    # 
    def setMinSurfaceAccessibility(min_acc: float) -> None: pass

    ##
    # \brief Specifies the number of points on the atom surface at which a test for surface accessibility is carried out.
    # 
    # \param num_points The number of test points.
    # 
    # \note The default value is specified by the constant SurfaceAtomExtractor.DEF_NUM_TEST_POINTS.
    # 
    def setNumTestPoints(num_points: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getProbeRadius() -> float: pass

    ##
    # \brief Return the distance between the grid-points for proximal atom lookup.
    # 
    # \return The used distance between the grid-points along each axis.
    # 
    def getGridStepSize() -> float: pass

    ##
    # \brief Returns the margin that gets added to each side of the molecular graph's bounding-box for the calculation of the final atom-lookup grid dimensions.
    # 
    # \return The margin that gets added to the molecular graph's bounding-box.
    # 
    def getGridOversize() -> float: pass

    ##
    # \brief Returns the minimum fraction of test points that have to be accessible by the probe sphere to consider an atom as a surface atom.
    # 
    # \return The minimum required fraction of accessible test points.
    # 
    def getMinSurfaceAccessibility() -> float: pass

    ##
    # \brief Returns the number of points on the atom surface at which a test for surface accessibility is carried out.
    # 
    # \return The number of test points.
    # 
    def getNumTestPoints() -> int: pass

    ##
    # \brief 
    # \param cntr 
    # \param parent_molgraph 
    # \param frag 
    #
    def extract(cntr: AtomContainer, parent_molgraph: MolecularGraph, frag: Fragment) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %SurfaceAtomExtractor instance \a extractor.
    # \param self The \e %SurfaceAtomExtractor instance this method is called upon.
    # \param extractor The \e %SurfaceAtomExtractor instance to copy.
    # \return \a self
    # 
    def assign(extractor: SurfaceAtomExtractor) -> SurfaceAtomExtractor: pass

    objectID = property(getObjectID)

    probeRadius = property(getProbeRadius, setProbeRadius)

    gridStepSize = property(getGridStepSize, setGridStepSize)

    gridOversize = property(getGridOversize, setGridOversize)

    numTestPoints = property(getNumTestPoints, setNumTestPoints)

    minSurfaceAccessibility = property(getMinSurfaceAccessibility, setMinSurfaceAccessibility)

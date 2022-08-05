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
class GaussianShapeGenerator(Boost.Python.instance):

    ##
    # \brief Initializes the \e %GaussianShapeGenerator instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %GaussianShapeGenerator instance.
    # \param gen 
    #
    def __init__(gen: GaussianShapeGenerator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %GaussianShapeGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %GaussianShapeGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %GaussianShapeGenerator instance \a gen.
    # \param gen The \e %GaussianShapeGenerator instance to copy.
    # \return The assignment target \a self.
    #
    def assign(gen: GaussianShapeGenerator) -> GaussianShapeGenerator: pass

    ##
    # \brief 
    # \param gen 
    #
    def setPharmacophoreGenerator(gen: CDPL.Pharm.PharmacophoreGenerator) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getPharmacophoreGenerator() -> CDPL.Pharm.PharmacophoreGenerator: pass

    ##
    # \brief 
    # \return 
    #
    def getDefaultPharmacophoreGenerator() -> CDPL.Pharm.DefaultPharmacophoreGenerator: pass

    ##
    # \brief 
    # \param radius 
    #
    def setAtomRadius(radius: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getAtomRadius() -> float: pass

    ##
    # \brief 
    # \param hardness 
    #
    def setAtomHardness(hardness: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getAtomHardness() -> float: pass

    ##
    # \brief 
    # \param radius 
    #
    def setFeatureRadius(radius: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getFeatureRadius() -> float: pass

    ##
    # \brief 
    # \param hardness 
    #
    def setFeatureHardness(hardness: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getFeatureHardness() -> float: pass

    ##
    # \brief 
    # \param generate 
    #
    def generatePharmacophoreShape(generate: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def generatePharmacophoreShape() -> bool: pass

    ##
    # \brief 
    # \param generate 
    #
    def generateMoleculeShape(generate: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def generateMoleculeShape() -> bool: pass

    ##
    # \brief 
    # \param multi_conf 
    #
    def multiConformerMode(multi_conf: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def multiConformerMode() -> bool: pass

    ##
    # \brief 
    # \param include 
    #
    def includeHydrogens(include: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def includeHydrogens() -> bool: pass

    ##
    # \brief 
    # \param molgraph 
    # \return 
    #
    def generate(molgraph: CDPL.Chem.MolecularGraph) -> GaussianShapeSet: pass

    ##
    # \brief 
    # \return 
    #
    def getShapes() -> GaussianShapeSet: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    pharmacophoreGenerator = property(getPharmacophoreGenerator, setPharmacophoreGenerator)

    ##
    # \brief FIXME!
    #
    defPharmacophoreGenerator = property(getDefPharmacophoreGenerator)

    ##
    # \brief 
    #
    shapes = property(getShapes)

    ##
    # \brief FIXME!
    #
    genPharmacophoreShape = property(getGenPharmacophoreShape, setGenPharmacophoreShape)

    ##
    # \brief FIXME!
    #
    genMoleculeShape = property(getGenMoleculeShape, setGenMoleculeShape)

    ##
    # \brief FIXME!
    #
    multiConfMode = property(getMultiConfMode, setMultiConfMode)

    ##
    # \brief FIXME!
    #
    incHydrogens = property(getIncHydrogens, setIncHydrogens)

    ##
    # \brief 
    #
    atomRadius = property(getAtomRadius, setAtomRadius)

    ##
    # \brief 
    #
    atomHardness = property(getAtomHardness, setAtomHardness)

    ##
    # \brief 
    #
    featureRadius = property(getFeatureRadius, setFeatureRadius)

    ##
    # \brief 
    #
    featureHardness = property(getFeatureHardness, setFeatureHardness)

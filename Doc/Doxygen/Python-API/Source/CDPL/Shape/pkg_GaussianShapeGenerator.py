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
    # \param self The \e %GaussianShapeGenerator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %GaussianShapeGenerator instance.
    # \param self The \e %GaussianShapeGenerator instance to initialize.
    # \param gen 
    #
    def __init__(self: object, gen: GaussianShapeGenerator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %GaussianShapeGenerator instance this method is called upon.
    #
    # Different Python \e %GaussianShapeGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %GaussianShapeGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: GaussianShapeGenerator) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %GaussianShapeGenerator instance \a gen.
    # \param self The \e %GaussianShapeGenerator instance this method is called upon.
    # \param gen The \e %GaussianShapeGenerator instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: GaussianShapeGenerator, gen: GaussianShapeGenerator) -> GaussianShapeGenerator: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeGenerator instance this method is called upon.
    # \param gen 
    #
    def setPharmacophoreGenerator(self: GaussianShapeGenerator, gen: CDPL.Pharm.PharmacophoreGenerator) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeGenerator instance this method is called upon.
    # \return 
    #
    def getPharmacophoreGenerator(self: GaussianShapeGenerator) -> CDPL.Pharm.PharmacophoreGenerator: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeGenerator instance this method is called upon.
    # \return 
    #
    def getDefaultPharmacophoreGenerator(self: GaussianShapeGenerator) -> CDPL.Pharm.DefaultPharmacophoreGenerator: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeGenerator instance this method is called upon.
    # \param radius 
    #
    def setAtomRadius(self: GaussianShapeGenerator, radius: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeGenerator instance this method is called upon.
    # \return 
    #
    def getAtomRadius(self: GaussianShapeGenerator) -> float: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeGenerator instance this method is called upon.
    # \param hardness 
    #
    def setAtomHardness(self: GaussianShapeGenerator, hardness: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeGenerator instance this method is called upon.
    # \return 
    #
    def getAtomHardness(self: GaussianShapeGenerator) -> float: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeGenerator instance this method is called upon.
    # \param radius 
    #
    def setFeatureRadius(self: GaussianShapeGenerator, radius: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeGenerator instance this method is called upon.
    # \return 
    #
    def getFeatureRadius(self: GaussianShapeGenerator) -> float: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeGenerator instance this method is called upon.
    # \param hardness 
    #
    def setFeatureHardness(self: GaussianShapeGenerator, hardness: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeGenerator instance this method is called upon.
    # \return 
    #
    def getFeatureHardness(self: GaussianShapeGenerator) -> float: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeGenerator instance this method is called upon.
    # \param generate 
    #
    def generatePharmacophoreShape(self: GaussianShapeGenerator, generate: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeGenerator instance this method is called upon.
    # \return 
    #
    def generatePharmacophoreShape(self: GaussianShapeGenerator) -> bool: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeGenerator instance this method is called upon.
    # \param generate 
    #
    def generateMoleculeShape(self: GaussianShapeGenerator, generate: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeGenerator instance this method is called upon.
    # \return 
    #
    def generateMoleculeShape(self: GaussianShapeGenerator) -> bool: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeGenerator instance this method is called upon.
    # \param multi_conf 
    #
    def multiConformerMode(self: GaussianShapeGenerator, multi_conf: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeGenerator instance this method is called upon.
    # \return 
    #
    def multiConformerMode(self: GaussianShapeGenerator) -> bool: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeGenerator instance this method is called upon.
    # \param include 
    #
    def includeHydrogens(self: GaussianShapeGenerator, include: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeGenerator instance this method is called upon.
    # \return 
    #
    def includeHydrogens(self: GaussianShapeGenerator) -> bool: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeGenerator instance this method is called upon.
    # \param molgraph 
    # \return 
    #
    def generate(self: GaussianShapeGenerator, molgraph: CDPL.Chem.MolecularGraph) -> GaussianShapeSet: pass

    ##
    # \brief 
    # \param self The \e %GaussianShapeGenerator instance this method is called upon.
    # \return 
    #
    def getShapes(self: GaussianShapeGenerator) -> GaussianShapeSet: pass

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

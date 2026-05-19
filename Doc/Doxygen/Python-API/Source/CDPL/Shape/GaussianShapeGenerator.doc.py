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
# \brief Generates Shape.GaussianShape instances from molecular graphs.
# 
# The generator can emit shape representations of the molecule itself (one sphere per atom), of a pharmacophore derived from the molecule (one sphere per feature), or both. In multi-conformer mode, one Gaussian shape is generated per conformer.
# 
class GaussianShapeGenerator(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>GaussianShapeGenerator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %GaussianShapeGenerator instance \a gen.
    # \param gen The \c %GaussianShapeGenerator instance to copy.
    # 
    def __init__(gen: GaussianShapeGenerator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %GaussianShapeGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %GaussianShapeGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %GaussianShapeGenerator instance \a gen.
    # \param gen The \c %GaussianShapeGenerator instance to copy.
    # \return \a self
    # 
    def assign(gen: GaussianShapeGenerator) -> GaussianShapeGenerator: pass

    ##
    # \brief Specifies the pharmacophore generator used when emitting pharmacophore shapes.
    # 
    def setPharmacophoreGenerator(gen: Pharm.PharmacophoreGenerator) -> None: pass

    ##
    # \brief Returns the currently configured pharmacophore generator.
    # 
    def getPharmacophoreGenerator() -> Pharm.PharmacophoreGenerator: pass

    ##
    # \brief Returns the built-in default pharmacophore generator (mutable).
    # 
    def getDefaultPharmacophoreGenerator() -> Pharm.DefaultPharmacophoreGenerator: pass

    ##
    # \brief Sets the sphere radius used for all atoms (negative value: use atom-specific van der Waals radii).
    # 
    def setAtomRadius(radius: float) -> None: pass

    ##
    # \brief Returns the currently configured atom sphere radius.
    # 
    def getAtomRadius() -> float: pass

    ##
    # \brief Sets the Gaussian hardness used for all atom spheres.
    # 
    def setAtomHardness(hardness: float) -> None: pass

    ##
    # \brief Returns the currently configured atom Gaussian hardness.
    # 
    def getAtomHardness() -> float: pass

    ##
    # \brief Sets the sphere radius used for all features (negative value: use feature-specific tolerances).
    # 
    def setFeatureRadius(radius: float) -> None: pass

    ##
    # \brief Returns the currently configured feature sphere radius.
    # 
    def getFeatureRadius() -> float: pass

    ##
    # \brief Sets the Gaussian hardness used for all feature spheres.
    # 
    def setFeatureHardness(hardness: float) -> None: pass

    ##
    # \brief Returns the currently configured feature Gaussian hardness.
    # 
    def getFeatureHardness() -> float: pass

    ##
    # \brief Specifies whether a pharmacophore (feature-based) shape shall be generated.
    # 
    def generatePharmacophoreShape(generate: bool) -> None: pass

    ##
    # \brief Tells whether a pharmacophore (feature-based) shape is generated.
    # 
    def generatePharmacophoreShape() -> bool: pass

    ##
    # \brief Specifies whether a molecular (atom-based) shape shall be generated.
    # 
    def generateMoleculeShape(generate: bool) -> None: pass

    ##
    # \brief Tells whether a molecular (atom-based) shape is generated.
    # 
    def generateMoleculeShape() -> bool: pass

    ##
    # \brief Specifies whether to emit one shape per conformer (instead of using the first conformer only).
    # 
    def multiConformerMode(multi_conf: bool) -> None: pass

    ##
    # \brief Tells whether the generator runs in multi-conformer mode.
    # 
    def multiConformerMode() -> bool: pass

    ##
    # \brief Specifies whether hydrogens are included when generating the molecular shape.
    # 
    def includeHydrogens(include: bool) -> None: pass

    ##
    # \brief Tells whether hydrogens are included when generating the molecular shape.
    # 
    def includeHydrogens() -> bool: pass

    ##
    # \brief Generates the set of Gaussian shapes for <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph.
    # 
    # \return A reference to the generated Shape.GaussianShapeSet.
    # 
    def generate(molgraph: Chem.MolecularGraph) -> GaussianShapeSet: pass

    ##
    # \brief Returns the shapes produced by the most recent call to generate().
    # 
    # \return A reference to the produced Shape.GaussianShapeSet.
    # 
    def getShapes() -> GaussianShapeSet: pass

    objectID = property(getObjectID)

    pharmacophoreGenerator = property(getPharmacophoreGenerator, setPharmacophoreGenerator)

    defPharmacophoreGenerator = property(getDefaultPharmacophoreGenerator)

    shapes = property(getShapes)

    genPharmacophoreShape = property(generatePharmacophoreShape, generatePharmacophoreShape)

    genMoleculeShape = property(generateMoleculeShape, generateMoleculeShape)

    multiConfMode = property(multiConformerMode, multiConformerMode)

    incHydrogens = property(includeHydrogens, includeHydrogens)

    atomRadius = property(getAtomRadius, setAtomRadius)

    atomHardness = property(getAtomHardness, setAtomHardness)

    featureRadius = property(getFeatureRadius, setFeatureRadius)

    featureHardness = property(getFeatureHardness, setFeatureHardness)

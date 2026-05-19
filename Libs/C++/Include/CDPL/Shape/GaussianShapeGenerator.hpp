/* 
 * GaussianShapeGenerator.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/**
 * \file
 * \brief Definition of class CDPL::Shape::GaussianShapeGenerator.
 */

#ifndef CDPL_SHAPE_GAUSSIANSHAPEGENERATOR_HPP
#define CDPL_SHAPE_GAUSSIANSHAPEGENERATOR_HPP

#include <vector>
#include <memory>

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Shape/GaussianShapeSet.hpp"
#include "CDPL/Pharm/DefaultPharmacophoreGenerator.hpp"
#include "CDPL/Pharm/BasicPharmacophore.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Atom;
    }

    namespace Shape
    {

        /**
         * \brief Generates Shape::GaussianShape instances from molecular graphs.
         *
         * The generator can emit shape representations of the molecule itself (one sphere per atom),
         * of a pharmacophore derived from the molecule (one sphere per feature), or both. In
         * multi-conformer mode, one Gaussian shape is generated per conformer.
         */
        class CDPL_SHAPE_API GaussianShapeGenerator
        {

          public:
            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %GaussianShapeGenerator instances. */
            typedef std::shared_ptr<GaussianShapeGenerator> SharedPointer;

            /**
             * \brief Constructs the \c %GaussianShapeGenerator instance.
             */
            GaussianShapeGenerator();

            /**
             * \brief Specifies whether a molecular (atom-based) shape shall be generated.
             * \param generate \c true to enable the generation of the molecular shape, and \c false to disable it.
             */
            void generateMoleculeShape(bool generate);

            /**
             * \brief Tells whether a molecular (atom-based) shape is generated.
             * \return \c true if the molecular shape is generated, and \c false otherwise.
             */
            bool generateMoleculeShape() const;

            /**
             * \brief Specifies whether a pharmacophore (feature-based) shape shall be generated.
             * \param generate \c true to enable the generation of the pharmacophore shape, and \c false to disable it.
             */
            void generatePharmacophoreShape(bool generate);

            /**
             * \brief Tells whether a pharmacophore (feature-based) shape is generated.
             * \return \c true if the pharmacophore shape is generated, and \c false otherwise.
             */
            bool generatePharmacophoreShape() const;

            /**
             * \brief Specifies whether to emit one shape per conformer (instead of using the first conformer only).
             * \param multi_conf \c true to enable multi-conformer mode, and \c false to use the first conformer only.
             */
            void multiConformerMode(bool multi_conf);

            /**
             * \brief Tells whether the generator runs in multi-conformer mode.
             * \return \c true if multi-conformer mode is enabled, and \c false otherwise.
             */
            bool multiConformerMode() const;

            /**
             * \brief Specifies whether hydrogens are included when generating the molecular shape.
             * \param include \c true to include hydrogens, and \c false to ignore them.
             */
            void includeHydrogens(bool include);

            /**
             * \brief Tells whether hydrogens are included when generating the molecular shape.
             * \return \c true if hydrogens are included, and \c false otherwise.
             */
            bool includeHydrogens() const;

            /**
             * \brief Sets the sphere radius used for all atoms (negative value: use atom-specific van der Waals radii).
             * \param radius The new atom sphere radius.
             */
            void setAtomRadius(double radius);

            /**
             * \brief Returns the currently configured atom sphere radius.
             * \return The atom sphere radius.
             */
            double getAtomRadius() const;

            /**
             * \brief Sets the Gaussian hardness used for all atom spheres.
             * \param hardness The new atom Gaussian hardness.
             */
            void setAtomHardness(double hardness);

            /**
             * \brief Returns the currently configured atom Gaussian hardness.
             * \return The atom Gaussian hardness.
             */
            double getAtomHardness();

            /**
             * \brief Sets the sphere radius used for all features (negative value: use feature-specific tolerances).
             * \param radius The new feature sphere radius.
             */
            void setFeatureRadius(double radius);

            /**
             * \brief Returns the currently configured feature sphere radius.
             * \return The feature sphere radius.
             */
            double getFeatureRadius() const;

            /**
             * \brief Sets the Gaussian hardness used for all feature spheres.
             * \param hardness The new feature Gaussian hardness.
             */
            void setFeatureHardness(double hardness);

            /**
             * \brief Returns the currently configured feature Gaussian hardness.
             * \return The feature Gaussian hardness.
             */
            double getFeatureHardness();

            /**
             * \brief Specifies the pharmacophore generator used when emitting pharmacophore shapes.
             * \param gen The pharmacophore generator.
             */
            void setPharmacophoreGenerator(Pharm::PharmacophoreGenerator& gen);

            /**
             * \brief Returns the currently configured pharmacophore generator.
             * \return A reference to the pharmacophore generator.
             */
            Pharm::PharmacophoreGenerator& getPharmacophoreGenerator() const;

            /**
             * \brief Returns the built-in default pharmacophore generator.
             * \return A \c const reference to the default pharmacophore generator.
             */
            const Pharm::DefaultPharmacophoreGenerator& getDefaultPharmacophoreGenerator() const;

            /**
             * \brief Returns the built-in default pharmacophore generator (mutable).
             * \return A reference to the default pharmacophore generator.
             */
            Pharm::DefaultPharmacophoreGenerator& getDefaultPharmacophoreGenerator();

            /**
             * \brief Generates the set of Gaussian shapes for \a molgraph.
             * \param molgraph The molecular graph.
             * \return A \c const reference to the generated Shape::GaussianShapeSet.
             */
            const GaussianShapeSet& generate(const Chem::MolecularGraph& molgraph);

            /**
             * \brief Returns the shapes produced by the most recent call to generate().
             * \return A \c const reference to the produced Shape::GaussianShapeSet.
             */
            const GaussianShapeSet& getShapes() const;

          private:
            typedef std::vector<const Chem::Atom*> AtomList;

            template <typename CoordsFunc>
            void createShape(const Chem::MolecularGraph& molgraph, const CoordsFunc& coords_func,
                             GaussianShape& shape);

            template <typename CoordsFunc>
            void createShape(const CoordsFunc& coords_func, GaussianShape& shape) const;

            Pharm::DefaultPharmacophoreGenerator defPharmGen;
            Pharm::PharmacophoreGenerator*       pharmGen;
            bool                                 genMolShape;
            bool                                 genPharmShape;
            bool                                 incHydrogens;
            bool                                 multiConf;
            double                               atomRadius;
            double                               atomHardness;
            double                               ftrRadius;
            double                               ftrHardness;
            GaussianShapeSet                     shapes;
            Pharm::BasicPharmacophore            pharm;
            AtomList                             shapeAtoms;
        };
    } // namespace Shape
} // namespace CDPL

#endif // CDPL_SHAPE_GAUSSIANSHAPEGENERATOR_HPP

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

            /** \brief Constructs the \c %GaussianShapeGenerator instance. */
            GaussianShapeGenerator();

            /** \brief Specifies whether a molecular (atom-based) shape shall be generated. */
            void generateMoleculeShape(bool generate);

            /** \brief Tells whether a molecular (atom-based) shape is generated. */
            bool generateMoleculeShape() const;

            /** \brief Specifies whether a pharmacophore (feature-based) shape shall be generated. */
            void generatePharmacophoreShape(bool generate);

            /** \brief Tells whether a pharmacophore (feature-based) shape is generated. */
            bool generatePharmacophoreShape() const;

            /** \brief Specifies whether to emit one shape per conformer (instead of using the first conformer only). */
            void multiConformerMode(bool multi_conf);

            /** \brief Tells whether the generator runs in multi-conformer mode. */
            bool multiConformerMode() const;

            /** \brief Specifies whether hydrogens are included when generating the molecular shape. */
            void includeHydrogens(bool include);

            /** \brief Tells whether hydrogens are included when generating the molecular shape. */
            bool includeHydrogens() const;

            /** \brief Sets the sphere radius used for all atoms (negative value: use atom-specific van der Waals radii). */
            void setAtomRadius(double radius);

            /** \brief Returns the currently configured atom sphere radius. */
            double getAtomRadius() const;

            /** \brief Sets the Gaussian hardness used for all atom spheres. */
            void setAtomHardness(double hardness);

            /** \brief Returns the currently configured atom Gaussian hardness. */
            double getAtomHardness();

            /** \brief Sets the sphere radius used for all features (negative value: use feature-specific tolerances). */
            void setFeatureRadius(double radius);

            /** \brief Returns the currently configured feature sphere radius. */
            double getFeatureRadius() const;

            /** \brief Sets the Gaussian hardness used for all feature spheres. */
            void setFeatureHardness(double hardness);

            /** \brief Returns the currently configured feature Gaussian hardness. */
            double getFeatureHardness();

            /** \brief Specifies the pharmacophore generator used when emitting pharmacophore shapes. */
            void setPharmacophoreGenerator(Pharm::PharmacophoreGenerator& gen);

            /** \brief Returns the currently configured pharmacophore generator. */
            Pharm::PharmacophoreGenerator& getPharmacophoreGenerator() const;

            /** \brief Returns the built-in default pharmacophore generator. */
            const Pharm::DefaultPharmacophoreGenerator& getDefaultPharmacophoreGenerator() const;

            /** \brief Returns the built-in default pharmacophore generator (mutable). */
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

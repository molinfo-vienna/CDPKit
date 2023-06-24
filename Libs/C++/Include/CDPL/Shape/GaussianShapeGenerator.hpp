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
 * \brief Definition of the class CDPL::Shape::GaussianShapeGenerator.
 */

#ifndef CDPL_SHAPE_GAUSSIANSHAPEGENERATOR_HPP
#define CDPL_SHAPE_GAUSSIANSHAPEGENERATOR_HPP

#include <vector>
#include <memory>

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Shape/GaussianShapeSet.hpp"
#include "CDPL/Pharm/DefaultPharmacophoreGenerator.hpp"
#include "CDPL/Pharm/BasicPharmacophore.hpp"
#include "CDPL/Util/ObjectStack.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Atom;
    }

    namespace Shape
    {

        class CDPL_SHAPE_API GaussianShapeGenerator
        {

          public:
            typedef std::shared_ptr<GaussianShapeGenerator> SharedPointer;

            GaussianShapeGenerator();

            void generateMoleculeShape(bool generate);

            bool generateMoleculeShape() const;

            void generatePharmacophoreShape(bool generate);

            bool generatePharmacophoreShape() const;

            void multiConformerMode(bool multi_conf);

            bool multiConformerMode() const;

            void includeHydrogens(bool include);

            bool includeHydrogens() const;

            void setAtomRadius(double radius);

            double getAtomRadius() const;

            void setAtomHardness(double hardness);

            double getAtomHardness();

            void setFeatureRadius(double radius);

            double getFeatureRadius() const;

            void setFeatureHardness(double hardness);

            double getFeatureHardness();

            void setPharmacophoreGenerator(Pharm::PharmacophoreGenerator& gen);

            Pharm::PharmacophoreGenerator& getPharmacophoreGenerator() const;

            const Pharm::DefaultPharmacophoreGenerator& getDefaultPharmacophoreGenerator() const;

            Pharm::DefaultPharmacophoreGenerator& getDefaultPharmacophoreGenerator();

            const GaussianShapeSet& generate(const Chem::MolecularGraph& molgraph);

            const GaussianShapeSet& getShapes() const;

          private:
            typedef std::vector<const Chem::Atom*> AtomList;

            template <typename CoordsFunc>
            void createShape(const Chem::MolecularGraph& molgraph, const CoordsFunc& coords_func,
                             GaussianShape& shape);

            template <typename CoordsFunc>
            void createShape(const CoordsFunc& coords_func, GaussianShape& shape) const;

            typedef Util::ObjectStack<GaussianShape> ShapeCache;

            ShapeCache                           shapeCache;
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

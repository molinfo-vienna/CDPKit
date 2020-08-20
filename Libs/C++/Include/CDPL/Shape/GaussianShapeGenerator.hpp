/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeGenerator.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include <boost/shared_ptr.hpp>

#include "CDPL/Shape/APIPrefix.hpp"
#include "CDPL/Shape/GaussianShape.hpp"
#include "CDPL/Pharm/DefaultPharmacophoreGenerator.hpp"
#include "CDPL/Pharm/BasicPharmacophore.hpp"


namespace CDPL 
{

    namespace Shape
    {
		
		class GaussianShapeSet;

		/**
		 * \addtogroup CDPL_SHAPE_GENERATION
		 * @{
		 */

		class CDPL_SHAPE_API GaussianShapeGenerator
		{
			
		  public:
			typedef boost::shared_ptr<GaussianShapeGenerator> SharedPointer;

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

			void generate(const Chem::MolecularGraph& molgraph, GaussianShapeSet& shapes, bool append = false);

		  private:
			template <typename CoordsFunc>
			void createShape(const Chem::MolecularGraph& molgraph, const CoordsFunc& coords_func, GaussianShape& shape);

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
			Pharm::BasicPharmacophore            pharm;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_SHAPE_GAUSSIANSHAPEGENERATOR_HPP

/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SurfaceXVolumeCoatGenerator.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Chem::SurfaceXVolumeCoatGenerator.
 */

#ifndef CDPL_CHEM_SURFACEXVOLUMECOATGENERATOR_HPP
#define CDPL_CHEM_SURFACEXVOLUMECOATGENERATOR_HPP

#include <vector>
#include <cstddef>

#include <boost/shared_ptr.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/FeatureType.hpp"
#include "CDPL/Chem/FeatureGeometry.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

    namespace Chem
    {

		/**
		 * \addtogroup CDPL_CHEM_PHARMACOPHORE_PERCEPTION
		 * @{
		 */

		class MolecularGraph;
		class AtomContainer;
		class Pharmacophore;

		/**
		 * \brief SurfaceXVolumeCoatGenerator.
		 */
		class CDPL_CHEM_API SurfaceXVolumeCoatGenerator
		{

		  public:
			static const unsigned int DEF_FEATURE_TYPE    = FeatureType::X_VOLUME;
			static const unsigned int DEF_FEATURE_GEOM    = FeatureGeometry::SPHERE;
			static const double       DEF_PROBE_RADIUS    = 1.2;
			static const double       DEF_GRID_OVERSIZE   = 5.0;
			static const double       DEF_GRID_STEP_SIZE  = 0.75;
			static const double       DEF_MIN_SURFACE_ACC = 0.01;
			static const std::size_t  DEF_NUM_TEST_POINTS = 250;

			/**
			 * \brief Constructs the \c %SurfaceXVolumeCoatGenerator instance.
			 */
			SurfaceXVolumeCoatGenerator();

			/**
			 * \brief Generates an excluded volume coat representing the accessible surface of \a cntnr and adds 
			 *        them to the pharmacophore \a pharm.
			 * \param cntnr The set of atoms for which to generate the excluded volume coat.
			 * \param parent_molgraph The parent molecular graph which contains the atoms in \a cntnr.
			 * \param pharm The output pharmacophore where to add the generated excluded volumes.
			 */
			SurfaceXVolumeCoatGenerator(const AtomContainer& cntnr, const MolecularGraph& parent_molgraph, Pharmacophore& pharm);

			/**
			 * \brief Specifies the value of the feature type property that has to be set on newly generated excluded volumes.
			 * \param type The value of the feature type property.
			 * \note The default type is specified by the constant SurfaceXVolumeCoatGenerator::DEF_FEATURE_TYPE.
			 * \see FeatureProperty::TYPE
			 */			
			void setFeatureType(unsigned int type);

			/**
			 * \brief Returns the value of the feature type property that gets set on newly generated excluded volumes.
			 * \return The used value of the feature type property.
			 * \see FeatureProperty::TYPE
			 */
			unsigned int getFeatureType() const;

			/**
			 * \brief Specifies the value of the feature geometry property that has to be set on newly generated excluded volumes.
			 * \param geom The value of the feature geometry property.
			 * \note The default type is specified by the constant SurfaceXVolumeCoatGenerator::DEF_FEATURE_GEOM.
			 * \see FeatureProperty::GEOMETRY
			 */
			void setFeatureGeometry(unsigned int geom);

			/**
			 * \brief Returns the value of the feature geometry property that gets set on newly generated excluded volumes.
			 * \return The used value of the feature geometry property.
			 * \see FeatureProperty::GEOMETRY
			 */
			unsigned int getFeatureGeometry() const;

			/**
			 * \brief Specifies the radius of the probe sphere that determines the accessibility of the surface atoms.
			 * \param radius The radius of the probe sphere.
			 * \note The default value is specified by the constant SurfaceXVolumeCoatGenerator::DEF_PROBE_RADIUS.
			 */
			void setProbeRadius(double radius);

			/*
			 * \brief Returns the radius of the probe sphere that determines the accessibility of the surface atoms.
			 * \return The used probe sphere radius.
			 */
			double getProbeRadius() const;

			/**
			 * \brief Specifies the distance between the grid-points in space which store lists of atoms with proximal positions.
			 * \param size The distance between the grid-points along each axis.
			 * \note The default value is specified by the constant SurfaceXVolumeCoatGenerator::DEF_GRID_STEP_SIZE.
			 */
			void setGridStepSize(double size);

			/**
			 * \brief Return the distance between the grid-points for proximal atom lookup.
			 * \return The used distance between the grid-points along each axis.
			 */
			double getGridStepSize() const;

			/**
			 * \brief Specifies the margin that gets added to each side of the molecular graph's bounding-box for the calculation
			 *        of the final atom-lookup grid dimensions.
			 * \param size The margin that gets added to the molecular graph's bounding-box.
			 * \note The default value is specified by the constant SurfaceXVolumeCoatGenerator::DEF_GRID_OVERSIZE.
			 */
			void setGridOversize(double size);

			/**
			 * \brief Returns the margin that gets added to each side of the molecular graph's bounding-box for the calculation
			 *        of the final atom-lookup grid dimensions.
			 * \return The margin that gets added to the molecular graph's bounding-box.
			 */
			double getGridOversize() const;

			/**
			 * \brief Specifies the minimum percentage of test points that have to be accessible by the probe sphere 
			 *        to consider an atom as a surface atom.
			 * \param min_acc The minimum required percentage of accessible test points.
			 * \note The default value is specified by the constant SurfaceXVolumeCoatGenerator::DEF_MIN_SURFACE_ACC.
			 */
			void setMinSurfaceAccessibility(double min_acc);

			double getMinSurfaceAccessibility() const;

			/**
			 * \brief Specifies the number of points on the atom surface at which a test for surface accessibility is carried out.
			 * \param num_points The number of test points.
			 * \note The default value is specified by the constant SurfaceXVolumeCoatGenerator::DEF_NUM_TEST_POINTS.
			 */
			void setNumTestPoints(std::size_t num_points);

			/**
			 * \brief Returns the number of points on the atom surface at which a test for surface accessibility is carried out.
			 * \return The number of test points.
			 */
			std::size_t getNumTestPoints() const;

			/**
			 * \brief Generates an excluded volume coat representing the accessible surface of \a cntnr and adds 
			 *        them to the pharmacophore \a pharm.
			 * \param cntnr The set of atoms for which to generate the excluded volume coat.
			 * \param parent_molgraph The parent molecular graph which contains the atoms in \a cntnr.
			 * \param pharm The output pharmacophore where to add the generated excluded volumes.
			 */
			void generate(const AtomContainer& cntnr, const MolecularGraph& parent_molgraph, Pharmacophore& pharm);

		  private:
			/** \cond CDPL_PRIVATE_SECTION_DOC */

			typedef std::vector<double> AtomRadiusTable;
			typedef std::vector<std::size_t> AtomIndexList;
			typedef boost::shared_ptr<AtomIndexList> AtomIndexListPtr;
			typedef std::vector<AtomIndexListPtr> GridAtomLookupTable;

			bool init(const AtomContainer& cntnr, const MolecularGraph& parent_molgraph);

			void xformCoordinates();
			void calcBoundingBox();
			void initGridAtomLookupTable();
			void extractSurfaceAtoms();
			void generateXVolumes(Pharmacophore&);

			void initTestPoints();

			unsigned int          featureType;
			unsigned int          featureGeom;
			double                probeRadius;
			double                gridOversize;
			double                gridStepSize;
			double                minSurfAcc;
			std::size_t           numTestPoints;
			const AtomContainer*  atomContainer;
			const MolecularGraph* parentMolGraph;
			AtomRadiusTable       atomRadii; 
			AtomIndexList         atomIndices; 
			Math::Matrix<double>  svdU;
			Math::Vector3DArray   atomCoords;
			Math::Vector3DArray   testPoints;
			Math::Vector3D        bBoxMin;
			Math::Vector3D        bBoxMax;
			std::size_t           gridXSize;
			std::size_t           gridYSize;
			std::size_t           gridZSize;
			GridAtomLookupTable   gridAtomLookup;
			AtomIndexList         surfaceAtoms;
			Util::BitSet          surfAtomMask;

			/** \endcond */
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CHEM_SURFACEXVOLUMECOATGENERATOR_HPP

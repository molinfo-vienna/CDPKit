/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * InteractionScoreGridCalculator.hpp 
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
 * \brief Definition of the class CDPL::Pharm::InteractionScoreGridCalculator.
 */

#ifndef CDPL_PHARM_INTERACTIONSCOREGRIDCALCULATOR_HPP
#define CDPL_PHARM_INTERACTIONSCOREGRIDCALCULATOR_HPP

#include <cstddef>
#include <map>
#include <set>
#include <vector>
#include <utility>

#include <boost/function.hpp>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/BasicPharmacophore.hpp"
#include "CDPL/Pharm/DefaultPharmacophoreGenerator.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunction.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;
		class AtomContainer;
        class Atom;
	}

    namespace Pharm
    {

		class InteractionScoreGridSet;

		/**
		 * \addtogroup CDPL_PHARM_INTERACTION_SCORE_GRID_CALCULATION
		 * @{
		 */

		/**
		 * \brief InteractionScoreGridCalculator.
		 */
		class CDPL_PHARM_API InteractionScoreGridCalculator
		{

		  public:
			typedef boost::function2<double, const Feature&, const Feature&> InteractionScoringFunction;
			typedef boost::function1<double, const Math::DVector&> FinalInteractionScoreFunction;
			typedef boost::function3<double, const Math::Vector3D&, const Chem::AtomContainer&, const Chem::Atom3DCoordinatesFunction&> StericClashFactorFunction;

			InteractionScoreGridCalculator();

			InteractionScoreGridCalculator(double step_size, std::size_t x_size, std::size_t y_size, std::size_t z_size);

			InteractionScoreGridCalculator(double x_step_size, double y_step_size, double z_step_size, 
										   std::size_t x_size, std::size_t y_size, std::size_t z_size);

			virtual ~InteractionScoreGridCalculator() {}

			const Math::Matrix4D& getCoordinatesTransform() const;

			template <typename T>
			void setCoordinatesTransform(const T& xform) {
				coordsTransform = xform;
			}

			double getXStepSize() const;

			void setXStepSize(double size);

			double getYStepSize() const;

			void setYStepSize(double size);

			double getZStepSize() const;

			void setZStepSize(double size);

			std::size_t getGridXSize() const;

			void setGridXSize(std::size_t size);

			std::size_t getGridYSize() const;

			void setGridYSize(std::size_t size);

			std::size_t getGridZSize() const;

			void setGridZSize(std::size_t size);

			void enableInteraction(unsigned int ftr_type, unsigned int tgt_ftr_type, bool enable);

			bool isInteractionEnabled(unsigned int ftr_type, unsigned int tgt_ftr_type) const;

			void clearEnabledInteractions();

			void setInteractionScoringFunction(unsigned int ftr_type, unsigned int tgt_ftr_type, const InteractionScoringFunction& func);

			const InteractionScoringFunction& getInteractionScoringFunction(unsigned int ftr_type, unsigned int tgt_ftr_type) const;

			void removeInteractionScoringFunction(unsigned int ftr_type, unsigned int tgt_ftr_type);

			/**
			 * \brief Specifies a function for the retrieval of atom 3D-coordinates for feature generation.
			 * \param func The atom 3D-coordinates function.
			 */
			void setAtom3DCoordinatesFunction(const Chem::Atom3DCoordinatesFunction& func);

			void setFinalInteractionScoreFunction(const FinalInteractionScoreFunction& func);

			void setStericClashFactorFunction(const StericClashFactorFunction& func);

			void calculate(const Chem::MolecularGraph& molgraph, InteractionScoreGridSet& grid_set);

			void calculate(const Chem::MolecularGraph& molgraph, const FeatureContainer& features, InteractionScoreGridSet& grid_set);

			void calculate(const FeatureContainer& features, InteractionScoreGridSet& grid_set);

		  private:
			typedef std::pair<unsigned int, unsigned int> FeatureTypePair;
			typedef std::map<FeatureTypePair, InteractionScoringFunction> InteractionScoringFuncMap;
			typedef std::set<FeatureTypePair> EnabledInteractionsMap;
			typedef std::vector<const Feature*> FeatureList;

			double                          xStepSize;          
			double                          yStepSize;          
			double                          zStepSize;          
			std::size_t                     gridXSize;
			std::size_t                     gridYSize;
			std::size_t                     gridZSize;
            Math::Matrix4D                  coordsTransform;
			BasicPharmacophore              gridPharmacophore;			
			BasicPharmacophore              molPharmacophore;
			DefaultPharmacophoreGenerator   pharmGenerator;
			FeatureList                     tgtFeatures;
			Chem::Atom3DCoordinatesFunction atomCoordsFunc;
			InteractionScoringFuncMap       scoringFuncMap;
			EnabledInteractionsMap          enabledInteractions;
			FinalInteractionScoreFunction   finalScoreFunc;
			StericClashFactorFunction       stericClashFactorFunc;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_PHARM_INTERACTIONSCOREGRIDCALCULATOR_HPP

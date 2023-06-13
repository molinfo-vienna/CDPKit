/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ScreeningProcessor.hpp 
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
 * \brief Definition of the class CDPL::Pharm::ScreeningProcessor.
 */

#ifndef CDPL_PHARM_SCREENINGPROCESSOR_HPP
#define CDPL_PHARM_SCREENINGPROCESSOR_HPP

#include <memory>
#include <cstddef>

#include <boost/function.hpp>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Math/Matrix.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class Molecule;
	}

    namespace Pharm
    {

		class FeatureContainer;
		class ScreeningDBAccessor;
		class ScreeningProcessorImpl;

		/**
		 * \brief ScreeningProcessor.
		 */
		class CDPL_PHARM_API ScreeningProcessor
		{

		  public:
			enum HitReportMode
			{

			  FIRST_MATCHING_CONF,
			  BEST_MATCHING_CONF,
			  ALL_MATCHING_CONFS
			};

			class CDPL_PHARM_API SearchHit
			{

			public:
				SearchHit(const ScreeningProcessor& hit_prov, const FeatureContainer& qry_pharm,
						  const FeatureContainer& hit_pharm, const Chem::Molecule& mol, 
						  const Math::Matrix4D& xform, std::size_t pharm_idx, 
						  std::size_t mol_idx, std::size_t conf_idx);

				const ScreeningProcessor& getHitProvider() const;

				const FeatureContainer& getQueryPharmacophore() const;

				const FeatureContainer& getHitPharmacophore() const;
				
				const Chem::Molecule& getHitMolecule() const;
				
				const Math::Matrix4D& getHitAlignmentTransform() const; 

				std::size_t getHitPharmacophoreIndex() const;

				std::size_t getHitMoleculeIndex() const;

				std::size_t getHitConformationIndex() const;

			private:
				const ScreeningProcessor*     provider;
				const FeatureContainer*       qryPharm;
				const FeatureContainer*       hitPharm;
				const Chem::Molecule*         molecule;
				const Math::Matrix4D*         almntTransform;
				std::size_t                   pharmIndex;
				std::size_t                   molIndex;
				std::size_t                   confIndex;
			};

			typedef std::shared_ptr<ScreeningProcessor> SharedPointer;

			typedef boost::function2<bool, const SearchHit&, double> HitCallbackFunction;
			typedef boost::function1<double, const SearchHit&> ScoringFunction;
			typedef boost::function2<bool, std::size_t, std::size_t> ProgressCallbackFunction;

			/**
			 * \brief Constructs the \c %ScreeningProcessor instance for the given
			 *        screening database accessor \a db_acc.
			 * \param db_acc An accessor for the database to screen.
			 */
			ScreeningProcessor(ScreeningDBAccessor& db_acc);

			/**
			 * Destructor.
			 */
			~ScreeningProcessor();

			void setDBAccessor(ScreeningDBAccessor& db_acc);

			ScreeningDBAccessor& getDBAccessor() const;

			void setHitReportMode(HitReportMode mode);

			HitReportMode getHitReportMode() const;

			void setMaxNumOmittedFeatures(std::size_t max_num);

			std::size_t getMaxNumOmittedFeatures() const;

			void checkXVolumeClashes(bool check);

			bool xVolumeClashesChecked() const;

			void seekBestAlignments(bool seek_best);

			bool bestAlignmentsSeeked() const;

			void setHitCallback(const HitCallbackFunction& func);

			const HitCallbackFunction& getHitCallback() const;

			void setProgressCallback(const ProgressCallbackFunction& func);

			const ProgressCallbackFunction& getProgressCallback() const;

			void setScoringFunction(const ScoringFunction& func);

			const ScoringFunction& getScoringFunction() const;

			std::size_t searchDB(const FeatureContainer& query, std::size_t mol_start_idx = 0, std::size_t mol_end_idx = 0);

		  private:
			typedef std::auto_ptr<ScreeningProcessorImpl> ImplementationPointer;

			ScreeningProcessor(const ScreeningProcessor& proc);
	
			ScreeningProcessor& operator=(const ScreeningProcessor& proc);

			ImplementationPointer impl;
		};
    }
}

#endif // CDPL_PHARM_SCREENINGPROCESSOR_HPP

/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ScreeningDBProcessor.hpp 
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
 * \brief Definition of the class CDPL::Pharm::ScreeningDBProcessor.
 */

#ifndef CDPL_PHARM_SCREENINGDBPROCESSOR_HPP
#define CDPL_PHARM_SCREENINGDBPROCESSOR_HPP

#include <memory>
#include <cstddef>

#include <boost/shared_ptr.hpp>
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

		class Pharmacophore;
		class ScreeningDBAccessor;

		/**
		 * \addtogroup CDPL_PHARM_PHARMACOPHORE_PERCEPTION
		 * @{
		 */

		/**
		 * \brief ScreeningDBProcessor.
		 */
		class CDPL_PHARM_API ScreeningDBProcessor
		{

		  public:
			enum HitReportMode
			{

			  FIRST_MATCHING_CONF,
			  BEST_MATCHING_CONF,
			  ALL_MATCHING_CONFS
			};

			class SearchHit
			{

			public:
				SearchHit(const ScreeningDBProcessor& db_proc, const Pharmacophore& qry_pharm,
						  const Pharmacophore& hit_pharm, const Chem::Molecule& mol, 
						  const Math::Matrix4D& xform, std::size_t pharm_idx, 
						  std::size_t mol_idx, std::size_t conf_idx);

				const ScreeningDBProcessor& getDBProcessor() const;

				const Pharmacophore& getQueryPharmacophore() const;

				const Pharmacophore& getHitPharmacophore() const;
				
				const Chem::Molecule& getHitMolecule() const;
				
				const Math::Matrix4D& getHitAlignmentTransform() const; 

				std::size_t getHitPharmacophoreIndex() const;

				std::size_t getHitMoleculeIndex() const;

				std::size_t getHitConformationIndex() const;

			private:
				const ScreeningDBProcessor& dbProcessor;
				const Pharmacophore&        qryPharm;
				const Pharmacophore&        hitPharm;
				const Chem::Molecule&       molecule;
				const Math::Matrix4D&       almntXForm;
				std::size_t                 pharmIndex;
				std::size_t                 molIndex;
				std::size_t                 confIndex;
			};

			typedef boost::shared_ptr<ScreeningDBProcessor> SharedPointer;

			typedef boost::function2<bool, const SearchHit&, double> HitCallbackFunction;
			typedef boost::function1<double, const SearchHit&> ScoringFunction;
			typedef boost::function2<bool, std::size_t, std::size_t> ProgressCallbackFunction;

			/**
			 * \brief Constructs the \c %ScreeningDBProcessor instance for the given
			 *        screening database accessor \a db_acc.
			 * \param db_acc An accessor for the database to screen.
			 */
			ScreeningDBProcessor(ScreeningDBAccessor& db_acc);

			/**
			 * Destructor.
			 */
			~ScreeningDBProcessor();

			void setDBAccessor(ScreeningDBAccessor& db_acc);

			ScreeningDBAccessor& getDBAccessor() const;

			void setHitReportMode(HitReportMode mode);

			HitReportMode getHitReportMode() const;

			void setMaxNumOmittedFeatures(std::size_t max_num);

			std::size_t getMaxNumOmittedFeatures() const;

			void checkXVolumeClashes(bool check);

			bool checkXVolumeClashes() const;

			void seekBestAlignments(bool seek_best);

			bool seekBestAlignments() const;

			void setHitCallbackFunction(const HitCallbackFunction& func);

			const HitCallbackFunction& getHitCallbackFunction() const;

			void setProgressCallbackFunction(const ProgressCallbackFunction& func);

			const ProgressCallbackFunction& getProgressCallbackFunction() const;

			void setScoringFunction(const ScoringFunction& func);

			const ScoringFunction& getScoringFunction() const;

			std::size_t searchDB(const Pharmacophore& query, std::size_t mol_start_idx = 0, std::size_t mol_end_idx = 0);

		  private:
			class Implementation;

			typedef std::auto_ptr<Implementation> ImplPointer;

			ScreeningDBProcessor(const ScreeningDBProcessor& proc);
	
			ScreeningDBProcessor& operator=(const ScreeningDBProcessor& proc);

			ImplPointer impl;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_PHARM_SCREENINGDBPROCESSOR_HPP

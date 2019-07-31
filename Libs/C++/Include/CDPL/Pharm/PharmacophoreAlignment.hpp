/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmacophoreAlignment.hpp 
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
 * \brief Definition of the class CDPL::Pharm::PharmacophoreAlignment.
 */

#ifndef CDPL_PHARM_PHARMACOPHOREALIGNMENT_HPP
#define CDPL_PHARM_PHARMACOPHOREALIGNMENT_HPP

#include <vector>
#include <utility>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Chem/GeometricalEntityAlignment.hpp"


namespace CDPL 
{

    namespace Pharm
    {

		class Feature;
		class FeatureContainer;

		/**
		 * \addtogroup CDPL_PHARM_ALIGNMENT
		 * @{
		 */

		/**
		 * \brief FeaturePairList.
		 */
		class FeaturePairList
		{

			typedef std::vector<std::pair<const Feature*, const Feature*> > StorageType;

		public:
			typedef StorageType::value_type Entry;
			typedef StorageType::const_iterator ConstEntryIterator;

			void clear() {
				data.clear();
			}

			StorageType::size_type getSize() const {
				return data.size();
			}

			void insertEntry(const Entry& entry) {
				data.push_back(entry);
			}

			ConstEntryIterator getEntriesBegin() const {
				return data.begin();
			}
		
			ConstEntryIterator getEntriesEnd() const {
				return data.end();
			}

			const Feature* getValue(const Feature* ftr) const {
				for (StorageType::const_iterator it = data.begin(), end = data.end(); it != end; ++it)
					if (it->first == ftr)
						return it->second;

				return 0;
			}

		private:
			StorageType data;
		};

		/**
		 * \brief PharmacophoreAlignment.
		 */
		class CDPL_PHARM_API PharmacophoreAlignment : public Chem::GeometricalEntityAlignment<Feature, FeaturePairList>
		{

		  public:
			/**
			 * \brief Constructs the \c %PharmacophoreAlignment instance.
			 * \param query_mode If \c true, the features of the first set are interpreted as a query pharmacophore
			 *                   and the features of the second have to match this query after alignment. If \c false,
			 *                   there is no distinction between the features of the first and second set in various
			 *                   performed intermediate checks.
			 */
			PharmacophoreAlignment(bool query_mode);

			/**
			 * \brief Adds the features of the feature container \a cntnr to the specified alignment feature set.
			 * \param cntnr The feature container containing features to add.
			 * \param first_set If \c true, the features are added to the first feature set, if \c false to the second one.
			 */
			void addFeatures(const FeatureContainer& cntnr, bool first_set);
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_PHARM_PHARMACOPHOREALIGNMENT_HPP

/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondStereoFlagGenerator.hpp 
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
 * \brief Definition of the class CDPL::Chem::BondStereoFlagGenerator.
 */

#ifndef CDPL_CHEM_BONDSTEREOFLAGGENERATOR_HPP
#define CDPL_CHEM_BONDSTEREOFLAGGENERATOR_HPP

#include <cstddef>
#include <vector>
#include <utility>

#include <boost/shared_ptr.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Util/Array.hpp"
#include "CDPL/Math/VectorArray.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;
		class Atom;
		class Bond;

		/**
		 * \addtogroup CDPL_CHEM_BOND_STEREO_FLAGS
		 * @{
		 */

		/**
		 * \brief BondStereoFlagGenerator.
		 */
		class CDPL_CHEM_API BondStereoFlagGenerator 
		{

		public:
			/**
			 * \brief Constructs the \c %BondStereoFlagGenerator instance.
			 */
			BondStereoFlagGenerator();

			/**
			 * \brief Constructs the \c %BondStereoFlagGenerator instance and generates the 2D stereo flags of the
			 *        bonds in the molecular graph \a molgraph.
			 *
			 * The generated stereo flags can be retrieved by a call to getResult().
			 *
			 * \param molgraph The molecular graph for which to generate the stereo flags. 
			 */
			BondStereoFlagGenerator(const MolecularGraph& molgraph);

			/**
			 * \brief Constructs the \c %BondStereoFlagGenerator instance and generates the 2D stereo flags of the
			 *        bonds in the molecular graph \a molgraph using the atom coordinates \a coords.
			 *
			 * The generated stereo flags can be retrieved by a call to getResult().
			 *
			 * \param molgraph The molecular graph for which to generate the stereo flags. 
			 * \param coords The atom coordinates to use for the calculation. 
			 */
			BondStereoFlagGenerator(const MolecularGraph& molgraph, const Math::Vector2DArray& coords);

			/**
			 * \brief Generates the 2D stereo flags of the bonds in the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to generate the stereo flags. 
			 * \return An array containing the generated stereo flags (possible values are defined
			 *         as constants in namespace Chem::BondStereoFlag). The stereo flags
			 *         are stored in the same order as the bonds appear in the bond list of
			 *         the molecular graph (i.e. the 2D stereo flag of a bond is accessible via
			 *         its index).
			 */
			const Util::UIArray& generate(const MolecularGraph& molgraph);

			/**
			 * \brief Generates the 2D stereo flags of the bonds in the molecular graph \a molgraph
			 *        using the atom coordinates \a coords.
			 * \param molgraph The molecular graph for which to generate the stereo flags. 
			 * \param coords The atom coordinates to use for the calculation. 
			 * \return An array containing the generated stereo flags (possible values are defined
			 *         as constants in namespace Chem::BondStereoFlag). The stereo flags
			 *         are stored in the same order as the bonds appear in the bond list of
			 *         the molecular graph (i.e. the 2D stereo flag of a bond is accessible via
			 *         its index).
			 */
			const Util::UIArray& generate(const MolecularGraph& molgraph, const Math::Vector2DArray& coords);

			/**
			 * \brief Returns the result of the last 2D bond stereo flag calculation.
			 * \return An array containing the generated stereo flags (possible values are defined
			 *         as constants in namespace Chem::BondStereoFlag). If a calculation
			 *         has not yet been performed, the returned array is empty.
			 * \see generate()
			 */
			const Util::UIArray& getResult() const;

		private:
			/** \cond CDPL_PRIVATE_SECTION_DOC */

			class StereoAtomInfo;

			BondStereoFlagGenerator(const BondStereoFlagGenerator&);

			BondStereoFlagGenerator& operator=(const BondStereoFlagGenerator&);

			void init(const MolecularGraph&, const Math::Vector2DArray*);

			void assignStereoFlags();

			void assignFlagsForEitherDoubleBonds();
			void assignFlagsForIsolatedCenter(const StereoAtomInfo*);
			bool assignFlagsForNonIsolatedCenters(std::size_t, std::size_t);

			void switchStereoFlag(std::size_t);

			class StereoAtomInfo
			{

			public:
				typedef boost::shared_ptr<StereoAtomInfo> SharedPointer;

				StereoAtomInfo(const MolecularGraph*, const Math::Vector2DArray*,
							   const Atom*, unsigned int, std::size_t, const Atom**, const Bond**);

				unsigned int getConfiguration() const;

				void findBestBondOrder(const Util::BitSet&, const Util::BitSet&);

				bool hasStereoAtomNbrs() const;

				bool configMatches(const Util::UIArray&) const;

				std::size_t getNumBonds() const;

				std::size_t getBondIndex(std::size_t) const;
				std::size_t getNbrAtomIndex(std::size_t) const;

				std::size_t getAtomIndex() const;

			private:
				typedef std::pair<const Atom*, std::size_t> Ligand;

				const MolecularGraph* molGraph;
				const Atom*           atom;
				unsigned int          configuration;
				std::size_t           numBonds;
				bool                  hasStereoNbrs;
				double                configCalcTerms[4];         
				bool                  bondEndFlags[4];         
				Ligand                ligands[4];
				Ligand                orderedLigands[4];
			};

			typedef std::vector<StereoAtomInfo*> StereoAtomInfoList;
			typedef std::vector<StereoAtomInfo::SharedPointer> StereoAtomInfoPtrTable;
			typedef std::vector<const Bond*> BondList;

			const MolecularGraph*      molGraph;
			Util::UIArray              stereoFlags;
			Util::UIArray              currentStereoFlags;
			StereoAtomInfoPtrTable     stereoAtomTable;
			StereoAtomInfoList         stereoAtomList;
			BondList                   eitherBondList;
			Util::BitSet               stereoAtomMask;
			Util::BitSet               configMatchMask;
			Util::BitSet               stereoDBAtomMask;
			Util::BitSet               ringBondMask;
			Util::BitSet               singleBondMask;
			std::size_t                numMismatchingCtrs;
			std::size_t                minNumMismatchingCtrs;

			/** \endcond */
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_BONDSTEREOFLAGGENERATOR_HPP
 

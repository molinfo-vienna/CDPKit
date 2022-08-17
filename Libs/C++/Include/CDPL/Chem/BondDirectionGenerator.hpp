/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondDirectionGenerator.hpp 
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
 * \brief Definition of the class CDPL::Chem::BondDirectionGenerator.
 */

#ifndef CDPL_CHEM_BONDDIRECTIONGENERATOR_HPP
#define CDPL_CHEM_BONDDIRECTIONGENERATOR_HPP

#include <cstddef>
#include <vector>
#include <functional>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Util/Array.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;
		class Atom;
		class Bond;

		/**
		 * \brief BondDirectionGenerator.
		 * \see [\ref SMILES]
		 */
		class CDPL_CHEM_API BondDirectionGenerator 
		{

		public:
			/**
			 * \brief Construcst the \c %BondDirectionGenerator instance.
			 */
			BondDirectionGenerator();

			/**
			 * \brief Constructs the \c %BondDirectionGenerator instance and generates direction flags for a minimum set of
			 *        directional bonds that unambiguously define the configuration of double bonds in the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to generate the bond direction flags.
			 * \param dirs An array containing the generated bond direction flags (possible
			 *         values are defined as constants in namespace Chem::BondDirection). The
			 *         directions are stored in the same order as the bonds appear in the bond list of
			 *         the molecular graph (i.e. the direction flag of a bond is accessible via
			 *         its index).
			 */
			BondDirectionGenerator(const MolecularGraph& molgraph, Util::UIArray& dirs);

			/**
			 * \brief Allows to specify whether or not the configuration of ring double bonds shall also be regarded in the
			 *        performed bond direction calculations.
			 * \param include If \c true, ring double bond geometries will be taken into consideration and get ignored otherwise.
			 * \note By default, the configuration of ring double bonds is taken into consideration.
			 * \see setRingSizeLimit()
			 */
			void includeRingBonds(bool include);

			/**
			 * \brief Tells whether the configuration of ring double bonds is also regarded in the performed
			 *        bond direction calculations.
			 * \return \c true if ring double bond geometries are taken into consideration, and \a false otherwise.
			 * \see setRingSizeLimit()
			 */
			bool ringBondsIncluded() const;

			/**
			 * \brief Sets the minimum ring size that is required for ring double bonds to be considered in
			 *        the performed bond direction calculations.
			 * \param min_size The minimum required ring size.
			 * \note The default minimum ring size is set to \e 8. This settings is only effective when the general
			 *       inclusion of ring double bonds is not disabled (see includeRingBonds()).
			 */
			void setRingSizeLimit(std::size_t min_size);

			/**
			 * \brief Returns the minimum ring size that is required for ring double bonds to be considered in
			 *        the performed bond direction calculations.
			 * \return The minimum required ring size.
			 */			
			std::size_t getRingSizeLimit() const;

			/**
			 * \brief Generates direction flags for a minimum set of directional bonds that unambiguously define the configuration
			 *        of double bonds in the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to generate the bond direction flags.
			 * \param dirs An array containing the generated bond direction flags (possible
			 *         values are defined as constants in namespace Chem::BondDirection). The
			 *         directions are stored in the same order as the bonds appear in the bond list of
			 *         the molecular graph (i.e. the direction flag of a bond is accessible via
			 *         its index).
			 */
			void generate(const MolecularGraph& molgraph, Util::UIArray& dirs);

		private:
			class StereoBond;

			class StereoBondOrderingFunction : public std::binary_function<const StereoBond*, const StereoBond*, bool>
			{

			public:
				StereoBondOrderingFunction(const BondDirectionGenerator& gen): generator(gen) {}

				bool operator()(const StereoBond*, const StereoBond*) const;

			private:
				const BondDirectionGenerator& generator;
			};

			BondDirectionGenerator(const BondDirectionGenerator&);

			BondDirectionGenerator& operator=(const BondDirectionGenerator&);

			void init(const MolecularGraph&, Util::UIArray&);

			bool assignDirections(std::size_t, Util::UIArray&);

			void switchDirection(unsigned int&);

			class StereoBond
			{

			public:
				StereoBond(const Bond&);

				const Bond& getBond() const;

				unsigned int getConfiguration() const;
				void setConfiguration(unsigned int);

				void setConfigRefBondIndex(std::size_t, std::size_t);

				std::size_t getNumNeighbors(std::size_t) const;

				std::size_t getNeighborBondIndex(std::size_t, std::size_t) const;
				std::size_t getNeighborAtomIndex(std::size_t, std::size_t) const;

				void addNeighborIndices(std::size_t, std::size_t, std::size_t);

				bool hasDirBonds(const Util::UIArray&, std::size_t) const;

				bool configMatches(const Util::UIArray&) const;

			private:
				const Bond*  bond;
				std::size_t  nbrBondCounts[2];
				std::size_t  nbrAtomIndices[2][2];
				std::size_t  nbrBondIndices[2][2];
				unsigned int configuration;
			};

			typedef std::vector<StereoBond> StereoBondArray;
			typedef std::vector<StereoBond*> StereoBondPtrArray;

			const MolecularGraph*  molGraph;
			bool                   incRingBonds;
			std::size_t            minRingSize;
			StereoBondArray        stereoBonds;
			StereoBondPtrArray     orderedStereoBonds;
			StereoBondPtrArray     atomStereoBondTable;
			Util::UIArray          workingDirs;
			Util::BitSet           configMatchMask;
			std::size_t            numMismatches;
			std::size_t            minNumMismatches;
			std::size_t            numDirBonds;
			std::size_t            minNumDirBonds;
		};
	}
}

#endif // CDPL_CHEM_BONDDIRECTIONGENERATOR_HPP
 

/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CircularFingerprintGenerator.hpp 
 *
 * Implementation of SciTegic style Circular Fingerprints
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
 * \brief Definition of the class CDPL::Chem::CircularFingerprintGenerator.
 */

#ifndef CDPL_CHEM_CIRCULARFINGERPRINTGENERATOR_HPP
#define CDPL_CHEM_CIRCULARFINGERPRINTGENERATOR_HPP

#include <cstddef>
#include <vector>
#include <utility>

#include <boost/function.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/BondPropertyFlag.hpp"
#include "CDPL/Base/IntegerTypes.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;
		class Atom;
		class Bond;

		/**
		 * \addtogroup CDPL_CHEM_FINGERPRINTS
		 * @{
		 */

		/**
		 * \brief CircularFingerprintGenerator.
		 * \see [\ref STECFP]
		 */
		class CDPL_CHEM_API CircularFingerprintGenerator
		{

		public:
			/**
			 * \brief Specifies the default set of atomic properties considered in the generation
			 *        of atom identifiers by CircularFingerprintGenerator::DefAtomIdentifierFunction.
			 */
			static const unsigned int DEF_ATOM_PROPERTY_FLAGS = 
				Chem::AtomPropertyFlag::HEAVY_BOND_COUNT | Chem::AtomPropertyFlag::VALENCE | Chem::AtomPropertyFlag::TYPE |
				Chem::AtomPropertyFlag::ISOTOPE | Chem::AtomPropertyFlag::FORMAL_CHARGE |
				Chem::AtomPropertyFlag::H_COUNT | Chem::AtomPropertyFlag::TOPOLOGY;

			/**
			 * \brief Specifies the default set of bond properties considered in the generation
			 *        of bond identifiers by CircularFingerprintGenerator::DefBondIdentifierFunction.
			 */
			static const unsigned int DEF_BOND_PROPERTY_FLAGS = 
				Chem::BondPropertyFlag::ORDER | Chem::BondPropertyFlag::AROMATICITY;

			/**
			 * \brief The functor for the generation of ECFP atom identifiers.
			 */
			class CDPL_CHEM_API DefAtomIdentifierFunctor
			{

			public:
				/**
				 * \brief Constructs the atom identifier functor object for the specified set of atomic properties.
				 *
				 * The \a flags argument is an OR combination of the constants defined in namespace
				 * Chem::AtomPropertyFlag. Supported property flags are:
				 *  - Chem::AtomPropertyFlag::TYPE
				 *  - Chem::AtomPropertyFlag::ISOTOPE
				 *  - Chem::AtomPropertyFlag::VALENCE
				 *  - Chem::AtomPropertyFlag::HEAVY_BOND_COUNT
				 *  - Chem::AtomPropertyFlag::VALENCE
				 *  - Chem::AtomPropertyFlag::TOPOLOGY
				 *  - Chem::AtomPropertyFlag::CIP_CONFIGURATION
				 *  - and Chem::AtomPropertyFlag::FORMAL_CHARGE
				 *
				 * \param flags Specifies the set of considered atomic properties.
				 */
				DefAtomIdentifierFunctor(unsigned int flags = DEF_ATOM_PROPERTY_FLAGS):
					flags(flags) {}
 
				/**
				 * \brief Generates an identifier for the argument atom.
				 *
				 * The generated identifier depends on the set of considered atomic properties that has been
				 * specified in the constructor.
				 *
				 * \param atom The atom for which to generate the identifier.
				 * \param molgraph The parent molecular graph of the atom.
				 * \return The generated atom identifier.
				 */
				Base::uint64 operator()(const Atom& atom, const MolecularGraph& molgraph) const;

			private:
				unsigned int flags;
			};

			/**
			 * \brief The default functor for the generation of bond identifiers.
			 */
			class CDPL_CHEM_API DefBondIdentifierFunctor
			{

			public:
				/**
				 * \brief Constructs the bond identifier functor object for the specified set of bond properties.
				 *
				 * The \a flags argument is an OR combination of the constants defined in namespace
				 * Chem::BondPropertyFlag. Supported property flags are:
				 *  - Chem::BondPropertyFlag::ORDER
				 *  - Chem::BondPropertyFlag::TOPOLOGY
				 *  - Chem::BondPropertyFlag::CIP_CONFIGURATION
				 *  - and Chem::BondPropertyFlag::AROMATICITY
				 *
				 * \param flags Specifies the set of considered bond properties.
				 */
				DefBondIdentifierFunctor(unsigned int flags = DEF_BOND_PROPERTY_FLAGS): 
					flags(flags) {}

				/**
				 * \brief Generates an identifier for the argument bond.
				 *
				 * The generated identifier depends on the set of considered bond properties that has been
				 * specified in the constructor.
				 *
				 * \param bond The bond for which to generate the identifier.
				 * \return The generated bond identifier.
				 */
				Base::uint64 operator()(const Bond& bond) const;

			private:
				unsigned int flags;
			};

			/**
			 * \brief Type of the generic functor class used to store user-defined functions or function objects
			 *        for the generation of atom identifiers.
			 *
			 * Functions or function objects for the generation of atom identifiers are required to take
			 * the atom (as a \c const reference to Chem::Atom) and containing molecular graph (as a \c const reference to Chem::MolecularGraph) as
			 * argument and return the identifier as an integer of type Base::uint64. For details refer to the <em>Boost.Function</em> documentation [\ref BFUN]. 
			 */
			typedef boost::function2<Base::uint64, const Atom&, const MolecularGraph&> AtomIdentifierFunction;

			/**
			 * \brief Type of the generic functor class used to store user-defined functions or function objects
			 *        for the generation of bond identifiers.
			 *
			 * Functions or function objects for the generation of bond identifiers are required to take
			 * the bond (as a \c const reference to Chem::Bond) as argument and return the identifier as
			 * an integer of type Base::uint64. For details refer to the <em>Boost.Function</em> documentation [\ref BFUN]. 
			 */
			typedef boost::function1<Base::uint64, const Bond&> BondIdentifierFunction;

			/**
			 * \brief Constructs the \c %CircularFingerprintGenerator instance.
			 */
			CircularFingerprintGenerator();

			/**
			 * \brief Constructs the \c %CircularFingerprintGenerator instance and generates the fingerprint of the
			 *        molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to generate the fingerprint.
			 * \param fp The generated fingerprint.
			 */
			CircularFingerprintGenerator(const MolecularGraph& molgraph, Util::BitSet& fp);

			/**
			 * \brief Allows to specify a custom function for the generation of atom identifiers.
			 * \param func A CircularFingerprintGenerator::AtomIdentifierFunction instance that wraps the target function.
			 * \note By default, atom identifiers are generated by CircularFingerprintGenerator::DefAtomIdentifierFunctor.
			 */
			void setAtomIdentifierFunction(const AtomIdentifierFunction& func);

			/**
			 * \brief Allows to specify a custom function for the generation of bond identifiers.
			 * \param func A CircularFingerprintGenerator::BondIdentifierFunction instance that wraps the target function.
			 * \note By default, bond identifiers are generated by CircularFingerprintGenerator::DefBondIdentifierFunctor.
			 */
			void setBondIdentifierFunction(const BondIdentifierFunction& func);

			/**
			 * \brief Allows to specify the desired number of substructure growing iterations.
			 * \param num_iter The desired number of growing iterations.
			 * \note The default number of iterations is \e 2.
			 */
			void setNumIterations(std::size_t num_iter);

			/**
			 * \brief Returns the number of substructure growing iterations.
			 * \return The number of iterations.
			 */
			std::size_t getNumIterations() const;

			/**
			 * \brief Allows to specify the desired fingerprint size.
			 * \param num_bits The desired fingerprint size in number of bits.
			 * \note By default, the generated fingerprints are \e 1024 bits wide.
			 */
			void setNumBits(std::size_t num_bits);

			/**
			 * \brief Returns the size of the generated fingerprints.
			 * \return The fingerprint size in number of bits.
			 */
			std::size_t getNumBits() const;

			void removeDuplicates(bool remove);

			bool duplicatesRemoved() const;

			/**
			 * \brief Generates the fingerprint of the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to generate the fingerprint.
			 * \param fp The generated fingerprint.
			 */
			void generate(const MolecularGraph& molgraph, Util::BitSet& fp);

			/**
			 * \brief Enumerates the features of the molecular graph \a molgraph .
			 * \param molgraph The molecular graph for which to enumerate the features.
			 */
			void generate(const MolecularGraph& molgraph);

			std::size_t getNumFeatures() const;

			Base::uint64 getFeatureIdentifier(std::size_t idx) const;

			const Util::BitSet& getFeatureSubstructure(std::size_t idx) const;

		private:
			class Feature
			{

			public:
				typedef std::pair<std::size_t, std::size_t> NeighborData;
				typedef std::vector<NeighborData> NeighborList;

				Feature(Base::uint64 init_id): currentID(init_id), nextID(0), duplicate(false) {}

				void addNeighbor(std::size_t bond_idx, std::size_t nbr_idx);

				const NeighborList& getNeighborList() const;

				void update();

				Base::uint64 getID() const;
				const Util::BitSet& getBondSet() const;

				void setNextID(Base::uint64 next_id);
				void setNextBondSet(const Util::BitSet& bond_set);

				void setDuplicateFlag(bool flag);
				bool isDuplicate() const;

			private:
				Base::uint64 currentID;
				Base::uint64 nextID;
				Util::BitSet currentBondSet;
				Util::BitSet nextBondSet;
				NeighborList nbrList;
				bool         duplicate;
			};

			struct UInt64PairLessCmpFunc;
		
			void generateFingerprintSet(const MolecularGraph& molgraph);

			void init(const MolecularGraph& molgraph);
			void performIteration(std::size_t iter_num);

			void extendFeatures(std::size_t iter_num);
			void emitFingerprintSetEntries();

			void extendFeature(std::size_t iter_num, Feature& feature);

			void setFeatureBits(Util::BitSet& fp);

			bool fingerprintSetContainsSubstruct(const Util::BitSet& bs) const;

			typedef std::vector<Feature> FeatureList;
			typedef std::pair<Base::uint64, Util::BitSet> FingerprintSetEntry;
			typedef std::vector<FingerprintSetEntry> FingerprintSet;
			typedef std::vector<Base::uint64> UInt64Array;
			typedef std::pair<Base::uint64, Base::uint64> UInt64Pair;
			typedef std::vector<UInt64Pair> UInt64PairArray;
	
			const MolecularGraph*  molGraph;
			std::size_t            numBits;
			std::size_t            numIterations;
			bool                   remDuplicates;
			AtomIdentifierFunction atomIdentifierFunc;
			BondIdentifierFunction bondIdentifierFunc;
			UInt64Array            bondIdentifiers;
			FeatureList            features;
			FingerprintSet         fingerprintSet;
			UInt64Array            idCalculationData;
			UInt64PairArray        nbrFeatureData;
			Util::BitSet           bondSet;
		}; 

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_CIRCULARFINGERPRINTGENERATOR_HPP

/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * HashCodeCalculator.hpp 
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
 * \brief Definition of the class CDPL::Chem::HashCodeCalculator.
 */

#ifndef CDPL_CHEM_HASHCODECALCULATOR_HPP
#define CDPL_CHEM_HASHCODECALCULATOR_HPP

#include <cstddef>
#include <cstdint>
#include <vector>

#include <boost/function.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/BondPropertyFlag.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;
		class Atom;
		class Bond;

		/**
		 * \brief HashCodeCalculator.
		 * \see [\ref MHASH]
		 */
		class CDPL_CHEM_API HashCodeCalculator
		{

		public:
			/**
			 * \brief Specifies the default set of atomic properties considered in the generation
			 *        of initial atom hash codes by HashCodeCalculator::DefAtomHashSeedFunction.
			 */
			static constexpr unsigned int DEF_ATOM_PROPERTY_FLAGS = 
				AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE |
				AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
				AtomPropertyFlag::CIP_CONFIGURATION | AtomPropertyFlag::AROMATICITY;

			/**
			 * \brief Specifies the default set of bond properties considered in the generation
			 *        of initial bond hash codes by HashCodeCalculator::DefBondHashSeedFunction.
			 */
			static constexpr unsigned int DEF_BOND_PROPERTY_FLAGS = 
				BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY |
				BondPropertyFlag::AROMATICITY | BondPropertyFlag::CIP_CONFIGURATION;

			/**
			 * \brief The default functor for the generation of atom hash seeds.
			 */
			class CDPL_CHEM_API DefAtomHashSeedFunctor
			{

			public:
				/**
				 * \brief Constructs the atom hash seed functor object for the specified set of atomic properties.
				 *
				 * The \a flags argument is an OR combination of the constants defined in namespace
				 * Chem::AtomPropertyFlag. Supported property flags are:
				 *  - Chem::AtomPropertyFlag::TYPE
				 *  - Chem::AtomPropertyFlag::ISOTOPE
				 *  - Chem::AtomPropertyFlag::H_COUNT
				 *  - Chem::AtomPropertyFlag::FORMAL_CHARGE
				 *  - Chem::AtomPropertyFlag::AROMATICITY
				 *  - and Chem::AtomPropertyFlag::CIP_CONFIGURATION
				 *
				 * \param calculator The \c %HashCodeCalculator instance that 'owns' the functor object.
				 * \param flags Specifies the set of considered atomic properties.
				 */
				DefAtomHashSeedFunctor(const HashCodeCalculator& calculator, unsigned int flags = DEF_ATOM_PROPERTY_FLAGS): 
					calculator(calculator), flags(flags) {}
 
				/**
				 * \brief Generates an initial hash code value (seed) for the specified atom.
				 *
				 * The generated hash seed depends on the set of considered atomic properties that has been
				 * specified in the constructor.
				 *
				 * \param atom The atom for which to generate the initial hash code.
				 * \return The generated atom hash seed.
				 */
				std::uint64_t operator()(const Atom& atom) const;

			private:
				std::uint64_t getAtomTypeHashSeed(const Atom&) const;
				std::uint64_t getAtomIsotopeHashSeed(const Atom&) const;
				std::uint64_t getAtomChargeHashSeed(const Atom&) const;
				std::uint64_t getAtomHCountHashSeed(const Atom&) const;
				std::uint64_t getAtomConfigHashSeed(const Atom&) const;
				std::uint64_t getAtomAromaticityHashSeed(const Atom&) const;

				const HashCodeCalculator& calculator;
				unsigned int              flags;
			};

			/**
			 * \brief The default functor for the generation of bond hash seeds.
			 */
			class CDPL_CHEM_API DefBondHashSeedFunctor
			{

			public:
				/**
				 * \brief Constructs the bond hash seed functor object for the specified set of bond properties.
				 *
				 * The \a flags argument is an OR combination of the constants defined in namespace
				 * Chem::BondPropertyFlag. Supported property flags are:
				 *  - Chem::BondPropertyFlag::ORDER
				 *  - Chem::BondPropertyFlag::TOPOLOGY
				 *  - Chem::BondPropertyFlag::AROMATICITY
				 *  - and Chem::BondPropertyFlag::CIP_CONFIGURATION
				 *
				 * \param flags Specifies the set of considered bond properties.
				 */
				DefBondHashSeedFunctor(unsigned int flags = DEF_BOND_PROPERTY_FLAGS): flags(flags) {}

				/**
				 * \brief Generates an initial hash code value (seed) for the specified bond.
				 *
				 * The generated hash seed depends on the set of considered bond properties that has been
				 * specified in the constructor.
				 *
				 * \param bond The bond for which to generate the initial hash code.
				 * \return The generated bond hash seed.
				 */
				std::uint64_t operator()(const Bond& bond) const;

			private:
				std::uint64_t getBondTypeHashSeed(const Bond&) const;
				std::uint64_t getBondConfigHashSeed(const Bond&) const;
				std::uint64_t getBondTopologyHashSeed(const Bond&) const;

				unsigned int flags;
			};

			/**
			 * \brief Type of the generic functor class used to store user-defined functions or function objects
			 *        for the generation of initial atom hash codes.
			 *
			 * Functions or function objects for the generation of atom hash seeds are required to take
			 * the atom (as a \c const reference to Chem::Atom) as argument and return the hash seed as
			 * an integer of type std::uint64_t. For details refer to the <em>Boost.Function</em> documentation [\ref BFUN]. 
			 */
			typedef boost::function1<std::uint64_t, const Atom&> AtomHashSeedFunction;

			/**
			 * \brief Type of the generic functor class used to store user-defined functions or function objects
			 *        for the generation of initial bond hash codes.
			 *
			 * Functions or function objects for the generation of bond hash seeds are required to take
			 * the bond (as a \c const reference to Chem::Bond) as argument and return the hash seed as
			 * an integer of type std::uint64_t. For details refer to the <em>Boost.Function</em> documentation [\ref BFUN]. 
			 */
			typedef boost::function1<std::uint64_t, const Bond&> BondHashSeedFunction;

			/**
			 * \brief Constructs the \c %HashCodeCalculator instance.
			 */
			HashCodeCalculator();

			/**
			 * \brief Constructs the \c %HashCodeCalculator instance and calculates the
			 *        hash code of the molecular graph \a molgraph.
			 *
			 * The calculated hash code can be retrieved by a call to getResult().
			 *
			 * \param molgraph The molecular graph for which the hash code has to be calculated.
			 */
			HashCodeCalculator(const MolecularGraph& molgraph);

			/**
			 * \brief Allows to specify a custom function for the generation of initial atom hash codes.
			 * \param func A HashCodeCalculator::AtomHashSeedFunction instance that wraps the target function.
			 * \note By default, atom hash seeds are generated by HashCodeCalculator::DefAtomHashSeedFunctor.
			 */
			void setAtomHashSeedFunction(const AtomHashSeedFunction& func);

			/**
			 * \brief Allows to specify a custom function for the generation of initial bond hash codes.
			 * \param func A HashCodeCalculator::BondHashSeedFunction instance that wraps the target function.
			 * \note By default, bond hash seeds are generated by HashCodeCalculator::DefBondHashSeedFunctor.
			 */
			void setBondHashSeedFunction(const BondHashSeedFunction& func);

			/**
			 * \brief Allows to specify whether or not global stereochemical features shall have an influence on
			 *        the calculated hash codes.
			 *
			 * When global stereochemical features are considered, the hash code of a molecular
			 * graph will not only depend on basic atom and bond properties but also on additional stereochemical characteristics
			 * like the relative spatial arrangement of substituents. The mutual spatial arrangement of substituents may be the only
			 * feature that allows the differentiation of stereoisomers with a plane of symmetry. Diastereoisomers like
			 * <em>cis-1,4-Cyclohexanediol</em> and <em>trans-1,4-Cyclohexanediol</em> are typical examples for such corner cases.
			 *
			 * \param include If \c true, global stereochemical features will be considered and get ignored otherwise.
			 * \note By default, global stereochemical features are included in the hash code calculation.
			 */
			void includeGlobalStereoFeatures(bool include);

			/**
			 * \brief Tells whether or not global stereochemical features influence the calculated hash codes.
			 * \return \c true if global stereochemical features of a molecular graph are considered, and \c false otherwise.
			 * \see includeGlobalStereoFeatures()
			 */
			bool globalStereoFeaturesIncluded() const;

			/**
			 * \brief Calculates the hash code of the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to calculate the hash code.
			 * \return The hash code of the molecular graph \a molgraph.
			 */
			std::uint64_t calculate(const MolecularGraph& molgraph);

			/**
			 * \brief Returns the result of the last hash code calculation.
			 * \return The result of the last hash code calculation, or zero if a calculation has not yet been performed.
			 */
			std::uint64_t getResult() const;

		private:
			HashCodeCalculator(const HashCodeCalculator&);

			HashCodeCalculator& operator=(const HashCodeCalculator&);

			void init(const MolecularGraph&);

			void calcAtomHashCodes();
			void calcBondHashCodes();
			void calcSHAHashCode();
	
			void perceiveGlobalStereoFeatures();

			void perceiveGlobalStereoReferenceAtoms();
			void perceiveGlobalStereoReferenceAtom(const Atom&);

			void perceiveGlobalStereoReferenceBonds();
			void perceiveGlobalStereoReferenceBond(const Bond&);

			typedef std::vector<std::uint64_t> UInt64Array;
 			typedef std::vector<std::size_t> IndexList;

			const MolecularGraph*    molGraph;
			AtomHashSeedFunction     atomHashSeedFunc;
			BondHashSeedFunction     bondHashSeedFunc;
			UInt64Array              atomHashCodes;
			UInt64Array              bondHashCodes;
			UInt64Array              tmpHashCodes1;
			UInt64Array              tmpHashCodes2;
			UInt64Array              shaInput;
			IndexList                globalStereoAtoms;
			IndexList                globalStereoBonds;
			IndexList                globalStereoReferenceAtoms;
			IndexList                globalStereoReferenceBonds;
			bool                     incGlobalStereoFeatures;
			std::uint8_t             shaHashCode[20];
		}; 
	}
}

#endif // CDPL_CHEM_HASHCODECALCULATOR_HPP

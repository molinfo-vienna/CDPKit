/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CircularFingerprintGenerator.hpp 
 *
 * Implementation of SciTegic style Circular Fingerprints
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
 * \brief Definition of the class CDPL::Descr::CircularFingerprintGenerator.
 */

#ifndef CDPL_DESCR_CIRCULARFINGERPRINTGENERATOR_HPP
#define CDPL_DESCR_CIRCULARFINGERPRINTGENERATOR_HPP

#include <cstddef>
#include <vector>
#include <utility>

#include <boost/function.hpp>
#include <boost/random/linear_congruential.hpp>

#include "CDPL/Descr/APIPrefix.hpp"
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
		class Fragment;
		class FragmentList;
	}
	
	namespace Descr
	{

		/**
		 * \brief CircularFingerprintGenerator.
		 * \see [\ref STECFP]
		 */
		class CDPL_DESCR_API CircularFingerprintGenerator
		{

		  public:
			/**
			 * \brief Specifies the default set of atomic properties considered in the generation
			 *        of atom identifiers by CircularFingerprintGenerator::DefAtomIdentifierFunction.
			 */
			static const unsigned int DEF_ATOM_PROPERTY_FLAGS = 
			  Chem::AtomPropertyFlag::HEAVY_BOND_COUNT | Chem::AtomPropertyFlag::VALENCE | Chem::AtomPropertyFlag::TYPE |
			  Chem::AtomPropertyFlag::FORMAL_CHARGE |Chem::AtomPropertyFlag::H_COUNT | Chem::AtomPropertyFlag::TOPOLOGY |
			  Chem::AtomPropertyFlag::ISOTOPE;

			/**
			 * \brief Specifies the default set of bond properties considered in the generation
			 *        of bond identifiers by CircularFingerprintGenerator::DefBondIdentifierFunction.
			 */
			static const unsigned int DEF_BOND_PROPERTY_FLAGS = 
			  Chem::BondPropertyFlag::ORDER | Chem::BondPropertyFlag::AROMATICITY;

			/**
			 * \brief The functor for the generation of ECFP atom identifiers.
			 */
			class CDPL_DESCR_API DefAtomIdentifierFunctor
		    {

			  public:
				/**
				 * \brief Constructs the atom identifier functor object for the specified set of atomic properties.
				 *
				 * The \a flags argument is an OR combination of the constants defined in namespace
				 * Chem::AtomPropertyFlag. 
				 *
				 * Supported property flags are:
				 *  - Chem::AtomPropertyFlag::TYPE
				 *  - Chem::AtomPropertyFlag::ISOTOPE
				 *  - Chem::AtomPropertyFlag::VALENCE
				 *  - Chem::AtomPropertyFlag::HEAVY_BOND_COUNT
				 *  - Chem::AtomPropertyFlag::VALENCE
				 *  - Chem::AtomPropertyFlag::TOPOLOGY
				 *  - Chem::AtomPropertyFlag::FORMAL_CHARGE
				 *  - Chem::AtomPropertyFlag::AROMATICITY
				 *
				 * \param flags Specifies the set of considered atomic properties.
				 */
				DefAtomIdentifierFunctor(unsigned int flags = DEF_ATOM_PROPERTY_FLAGS): flags(flags) {}
 
				/**
				 * \brief Generates an identifier for the argument atom.
				 *
				 * The generated identifier depends on the set of considered atomic properties that has been
				 * specified in the constructor.
				 *
				 * \param atom The atom for which to generate the identifier.
				 * \param molgraph The parent molecular graph of the atom.
				 * \return The generated atom identifier.
				 * \
				 */
				Base::uint64 operator()(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph) const;

			  private:
				unsigned int flags;
			};

			/**
			 * \brief The default functor for the generation of bond identifiers.
			 */
			class CDPL_DESCR_API DefBondIdentifierFunctor
		    {

			  public:
				/**
				 * \brief Constructs the bond identifier functor object for the specified set of bond properties.
				 *
				 * The \a flags argument is an OR combination of the constants defined in namespace
				 * Chem::BondPropertyFlag. 
				 *
				 * Supported property flags are:
				 *  - Chem::BondPropertyFlag::ORDER
				 *  - Chem::BondPropertyFlag::TOPOLOGY
				 *  - Chem::BondPropertyFlag::AROMATICITY
				 *
				 * \param flags Specifies the set of considered bond properties.
				 */
				DefBondIdentifierFunctor(unsigned int flags = DEF_BOND_PROPERTY_FLAGS): flags(flags) {}

				/**
				 * \brief Generates an identifier for the argument bond.
				 *
				 * The generated identifier depends on the set of considered bond properties that has been
				 * specified in the constructor.
				 *
				 * \param bond The bond for which to generate the identifier.
				 * \return The generated bond identifier.
				 */
				Base::uint64 operator()(const Chem::Bond& bond) const;

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
			typedef boost::function2<Base::uint64, const Chem::Atom&, const Chem::MolecularGraph&> AtomIdentifierFunction;

			/**
			 * \brief Type of the generic functor class used to store user-defined functions or function objects
			 *        for the generation of bond identifiers.
			 *
			 * Functions or function objects for the generation of bond identifiers are required to take
			 * the bond (as a \c const reference to Chem::Bond) as argument and return the identifier as
			 * an integer of type Base::uint64. For details refer to the <em>Boost.Function</em> documentation [\ref BFUN]. 
			 */
			typedef boost::function1<Base::uint64, const Chem::Bond&> BondIdentifierFunction;

			/**
			 * \brief Constructs the \c %CircularFingerprintGenerator instance.
			 */
			CircularFingerprintGenerator();

			/**
			 * \brief Constructs the \c %CircularFingerprintGenerator instance and generates the atom-centered circular 
			 *        substructure fingerprint of the molecular graph \a molgraph.
			 * \param molgraph The molecular graph to process.
			 */
			CircularFingerprintGenerator(const Chem::MolecularGraph& molgraph);

			/**
			 * \brief Allows to specify a customized function for the generation of initial atom identifiers.
			 * \param func A CircularFingerprintGenerator::AtomIdentifierFunction instance that wraps the target function.
			 * \note By default, atom identifiers are generated by a CircularFingerprintGenerator::DefAtomIdentifierFunctor instance.
			 *       If the generated initial identifier for an atom is \e 0, the atom is regarded as not being present in the
			 *       processed molecular graph.
			 */
			void setAtomIdentifierFunction(const AtomIdentifierFunction& func);

			/**
			 * \brief Allows to specify a customized function for the generation of initial bond identifiers.
			 * \param func A CircularFingerprintGenerator::BondIdentifierFunction instance that wraps the target function.
			 * \note By default, bond identifiers are generated by a CircularFingerprintGenerator::DefBondIdentifierFunctor instance.
			 *       If the generated initial identifier for a bond is \e 0, the bond is regarded as not being present in the
			 *       processed molecular graph.
			 */
			void setBondIdentifierFunction(const BondIdentifierFunction& func);

			/**
			 * \brief Allows to specify the desired number of feature substructure growing iterations.
			 * \param num_iter The number of iterations.
			 * \note The default number of iterations is \e 2.
			 */
			void setNumIterations(std::size_t num_iter);

			/**
			 * \brief Returns the number of feature substructure growing iterations.
			 * \return The number of iterations.
			 */
			std::size_t getNumIterations() const;

			void includeHydrogens(bool include);

			bool hydrogensIncluded() const;

			void includeChirality(bool include);

			bool chiralityIncluded() const;
		
			/**
			 * \brief Generates the atom-centered circular substructure fingerprint of the molecular graph \a molgraph.
			 * \param molgraph The molecular graph to process.
			 */
			void generate(const Chem::MolecularGraph& molgraph);
			
			/**
			 * \brief Maps previously generated feature identifiers to bit indices and sets the correponding bits of \a bs.
			 * \param bs The target bitset.
			 * \param reset If \e true, \a bs will be cleared before any feature bits are set.
			 * \note The binary fingerprint size is specified implicitly via the size of \a bs.  
			 * \see generate()
			 */
			void setFeatureBits(Util::BitSet& bs, bool reset = true) const;

			/**
			 * \brief Maps previously generated identifiers of structural features involving the atom specified by \a atom_idx
			 *        to bit indices and sets the correponding bits of \a bs.
			 * \param atom_idx The index of the atom that has to be involved in the structural features.
			 * \param bs The target bitset.
			 * \param reset If \e true, \a bs will be cleared before any feature bits are set.
			 * \note The binary fingerprint size is specified implicitly via the size of \a bs.  
			 * \see generate()
			 */
			void setFeatureBits(std::size_t atom_idx, Util::BitSet& bs, bool reset = true) const;

			std::size_t getNumFeatures() const;

			Base::uint64 getFeatureIdentifier(std::size_t ftr_idx) const;

			const Util::BitSet& getFeatureSubstructure(std::size_t ftr_idx) const;

			void getFeatureSubstructure(std::size_t ftr_idx, Chem::Fragment& frag, bool clear = true) const;

			void getFeatureSubstructures(std::size_t bit_idx, std::size_t bs_size, Chem::FragmentList& frags, bool clear = true) const;

		  private:
			typedef std::pair<std::pair<Base::uint64, Base::uint64>, const Chem::Atom*> NeighborData;

			void init(const Chem::MolecularGraph& molgraph);

			void performIteration(std::size_t iter_num);

			unsigned int getStereoFlag(const Chem::Atom& ctr_atom) const;
			
			void bitSetToFragment(const Util::BitSet& ab_mask, Chem::Fragment& frag) const;

			static bool compareNeighborData(const NeighborData& nbr1, const NeighborData& nbr2);
			
			typedef std::pair<Base::uint64, Util::BitSet> Feature;
			typedef std::vector<Feature> FeatureArray;
			typedef std::vector<const Feature*> FeaturePtrList;
			typedef std::vector<Base::uint64> UInt64Array;
			typedef std::vector<NeighborData> NeighborDataList;
	
			const Chem::MolecularGraph*  molGraph;
			std::size_t                  numIterations;
			AtomIdentifierFunction       atomIdentifierFunc;
			BondIdentifierFunction       bondIdentifierFunc;
			bool                         incHydrogens;
			bool                         incChirality;
			boost::rand48                randGenerator;
			UInt64Array                  bondIdentifiers;
			FeatureArray                 features;
			FeaturePtrList               outputFeatures;
			UInt64Array                  idCalculationData;
			NeighborDataList             neighborData;
			Util::BitSet                 duplicateMask;
		}; 
	}
}

#endif // CDPL_DESCR_CIRCULARFINGERPRINTGENERATOR_HPP

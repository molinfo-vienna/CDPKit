/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Reactor.hpp 
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
 * \brief Definition of the class CDPL::Chem::Reactor.
 */

#ifndef CDPL_CHEM_REACTOR_HPP
#define CDPL_CHEM_REACTOR_HPP

#include <map>
#include <vector>
#include <utility>
#include <functional>
#include <cstddef>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/ReactionSubstructureSearch.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

	namespace Chem
	{

		/**
		 * \addtogroup CDPL_CHEM_REACTION_TRANSFORMATIONS
		 * @{
		 */

		/**
		 * \brief Reactor.
		 */
		class CDPL_CHEM_API Reactor
		{

		public:
			/**
			 * \brief Stores information about perceived reaction-sites.
			 */
			typedef AtomBondMapping ReactionSite;

			/**
			 * \brief A mutable random access iterator used to iterate over the perceived reaction-sites.
			 */
			typedef ReactionSubstructureSearch::MappingIterator ReactionSiteIterator;

			/**
			 * \brief A constant random access iterator used to iterate over the perceived reaction-sites.
			 */
			typedef ReactionSubstructureSearch::ConstMappingIterator ConstReactionSiteIterator;

			/**
			 * \brief Constructs and initializes a \c %Reactor instance.
			 */
			Reactor();
		
			/**
			 * \brief Constructs and initializes a \c %Reactor instance for the specified reaction pattern.
			 * \param rxn_pattern The reaction pattern describing the transformation of reactants to products. 
			 */
			Reactor(const Reaction& rxn_pattern);

			/**
			 * \brief Destructor.
			 *
			 * Destroys the \c %Reactor instance and frees all allocated resources.
			 */
			~Reactor();

			/**
			 * \brief Allows to specify a new reaction pattern for the transformation of reactants to products.
			 * \param rxn_pattern The reaction pattern describing the transformation of reactants to products.
			 */
			void setReactionPattern(const Reaction& rxn_pattern);

			/**
			 * \brief Perceives all possible reaction-sites on the reactants of the given reaction target where
			 *        the specified reaction pattern can be applied.
			 *
			 * The specified Chem::Reaction instance \a rxn_target serves both as a provider for the starting materials
			 * (reactant components) in a later reaction transformation (see performReaction()) as well as a container for
			 * the generated reaction products.
			 *
			 * \param rxn_target The reaction target providing the reactants to be transformed.
			 * \return \c true if matching reaction-sites were found, and \c false otherwise. 
			 * \note Any reaction-site mappings that were recorded in a previous call to findReactionSites() will be
			 *       discarded.
			 * \see performReaction()
			 */
			bool findReactionSites(Reaction& rxn_target);

			/**
			 * \brief Returns the number of recorded reactions-sites in the last call to findReactionSites().
			 * \return The number of recorded reactions-sites in the last call to findReactionSites().
			 */
			std::size_t getNumReactionSites() const;

			/**
			 * \brief Returns a non-\c const reference to the stored reaction-site data object at index \a idx.
			 * \param idx The zero-based index of the reaction-site data object to return.
			 * \return A non-\c const reference to the reaction-site data object at index \a idx.
			 * \throw Base::IndexError if no reactions-site data objects are available or \a idx is not in
			 *        the range [0, getNumReactionSites() - 1].
			 */
			ReactionSite& getReactionSite(std::size_t idx);

			/**
			 * \brief Returns a \c const reference to the stored reaction-site data object at index \a idx.
			 * \param idx The zero-based index of the reaction-site data object to return.
			 * \return A \c const reference to the reaction-site data object at index \a idx.
			 * \throw Base::IndexError if no reactions-site data objects are available or \a idx is not in
			 *        the range [0, getNumReactionSites() - 1].
			 */
			const ReactionSite& getReactionSite(std::size_t idx) const;

			/**
			 * \brief Returns a mutable iterator pointing to the beginning of the stored reaction-site data objects.
			 * \return A mutable iterator pointing to the beginning of the stored reaction-site data objects.
			 */
			ReactionSiteIterator getReactionSitesBegin();

			/**
			 * \brief Returns a constant iterator pointing to the beginning of the stored reaction-site data objects.
			 * \return A constant iterator pointing to the beginning of the stored reaction-site data objects.
			 */
			ConstReactionSiteIterator getReactionSitesBegin() const;

			/**
			 * \brief Returns a mutable iterator pointing to the end of the stored reaction-site data objects.
			 * \return A mutable iterator pointing to the end of the stored reaction-site data objects.
			 */
			ReactionSiteIterator getReactionSitesEnd();

			/**
			 * \brief Returns a constant iterator pointing to the end of the stored reaction-site data objects.
			 * \return A constant iterator pointing to the end of the stored reaction-site data objects.
			 */
			ConstReactionSiteIterator getReactionSitesEnd() const;

			/**
			 * \brief Performs a transformation of the target reactants to corresponding products at the specified 
			 *        reaction-site.
			 *
			 * The reactant components of the Chem::Reaction object specified in a prior call to findReactionSites()
			 * serve as starting materials for the reaction transformation into corresponding product molecules (according
			 * to the set reaction pattern). The input molecules are left unchanged by the transformation. New molecules will be
			 * generated that are directly stored as the product components of the given target reaction object. Note that the
			 * product molecules generated in a previous call will not be discarded and are still accessible after new products
			 * have been generated.
			 * 
			 * \param rxn_site Specifies the reaction-site where the transformation shall take place.
			 * \see setReactionPattern(), findReactionSites()
			 */
			void performReaction(const ReactionSite& rxn_site);
	
		private:
			Reactor(const Reactor&);

			Reactor& operator=(const Reactor&);

			void init();

			void createAtoms(Molecule*);
			void createBonds(Molecule*);

			void deleteBonds(const ReactionSite&, Molecule*) const;
			void deleteAtoms(const ReactionSite&, Molecule*) const;

			void editAtoms() const;
			void editBonds() const;

			void editStereoProperties() const;

			void editProdAtomStereoDescriptor(const Atom*, Atom*) const;
			void editProdBondStereoDescriptor(const Bond*, Bond*) const;

			template <typename T>
			void copyProperty(const T*, T*, const Base::LookupKey&) const;

			const Base::Variant& getProperty(const Atom*, const Base::LookupKey&) const;
			const Base::Variant& getProperty(const Bond*, const Base::LookupKey&) const;

			Molecule* copyReactants(const ReactionSite&);

			Atom* getMappedTgtProdAtom(const Atom*) const;
			Bond* getMappedTgtProdBond(const Bond*) const;

			typedef std::pair<std::size_t, std::size_t> IDPair;

			struct IDPairLessCmpFunc : public std::binary_function<IDPair, IDPair, bool>
			{

				bool operator()(const IDPair&, const IDPair&) const;
			};

			typedef std::pair<const Atom*, const Atom*> AtomPair;
			typedef std::pair<const Bond*, const Bond*> BondPair;
			typedef std::map<std::size_t, const Atom*> IDAtomMap;
			typedef std::map<IDPair, const Bond*, IDPairLessCmpFunc> IDPairBondMap;
			typedef std::map<const Atom*, Atom*> AtomMap;
			typedef std::map<const Bond*, Bond*> BondMap;
			typedef std::vector<AtomPair> AtomPairList;
			typedef std::vector<BondPair> BondPairList;

			const Reaction*            rxnPattern;
			Reaction*                  rxnTarget;
			ReactionSubstructureSearch rxnSiteSearch;
			IDAtomMap                  reacAtomsToDelete;
			IDAtomMap                  prodAtomsToCreate;
			IDPairBondMap              reacBondsToDelete;
			IDPairBondMap              prodBondsToCreate;
			AtomPairList               ptnAtomMapping;
			BondPairList               ptnBondMapping;
			AtomMap                    tgtAtomMapping;
			BondMap                    tgtBondMapping;
			Util::BitSet               mappedAtomMask;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_REACTOR_HPP

/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AutomorphismGroupSearch.hpp 
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
 * \brief Definition of the class CDPL::Chem::AutomorphismGroupSearch.
 */

#ifndef CDPL_CHEM_AUTOMORPHISMGROUPSEARCH_HPP
#define CDPL_CHEM_AUTOMORPHISMGROUPSEARCH_HPP

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/SubstructureSearch.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/BondPropertyFlag.hpp"
#include "CDPL/Chem/MatchExpression.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"


namespace CDPL 
{

    namespace Chem
    {

		/**
		 * \addtogroup CDPL_CHEM_GRAPH_AUTOMORPHISM_SEARCH
		 * @{
		 */

		/**
		 * \brief AutomorphismGroupSearch.
		 */
		class CDPL_CHEM_API AutomorphismGroupSearch
		{
		  public:
			/**
			 * \brief Specifies the default set of atomic properties considered for atom matching.
			 */
			static const unsigned int DEF_ATOM_PROPERTY_FLAGS = 
				AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE |
				AtomPropertyFlag::H_COUNT | AtomPropertyFlag::FORMAL_CHARGE |
				AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::AROMATICITY |
				AtomPropertyFlag::EXPLICIT_BOND_COUNT | AtomPropertyFlag::HYBRIDIZATION_STATE;

			/**
			 * \brief Specifies the default set of bond properties considered for bond matching.
			 */
			static const unsigned int DEF_BOND_PROPERTY_FLAGS = 
				BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY |
				BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION;

			typedef boost::shared_ptr<AutomorphismGroupSearch> SharedPointer;

			/**
			 * \brief A mutable random access iterator used to iterate over the stored atom/bond mapping objects.
			 */
			typedef SubstructureSearch::MappingIterator MappingIterator;

			/**
			 * \brief A constant random access iterator used to iterate over the stored atom/bond mapping objects.
			 */
			typedef SubstructureSearch::ConstMappingIterator ConstMappingIterator;

			typedef boost::function2<bool, const MolecularGraph&, const AtomBondMapping&> MappingCallbackFunction;

			/**
			 * \brief Constructs and initializes a \c %AutomorphismGroupSearch instance.
			 */
			AutomorphismGroupSearch(unsigned int atom_flags = DEF_ATOM_PROPERTY_FLAGS, 
									unsigned int bond_flags = DEF_BOND_PROPERTY_FLAGS);
		  
			void setAtomPropertyFlags(unsigned int flags);

			unsigned int getAtomPropertyFlags() const;

			void setBondPropertyFlags(unsigned int flags);
	
			unsigned int getBondPropertyFlags() const;

			void includeIdentityMapping(bool include);

			bool identityMappingIncluded() const;

			/**
			 * \brief Searches for the possible atom/bond mappings in the automorphism group of the given molecular graph.
			 *
			 * The method will store all found mappings up to the maximum number of recorded mappings specified
			 * by setMaxNumMappings(). 
			 *
			 * \param molgraph The molecular graph that has to be searched for automorphisms.
			 * \return \c true if any mappings of the specified molecular graph have been found, and \c false
			 *         otherwise.
			 * \note Any atom/bond mappings that were recorded in a previous call to findMappings() will be
			 *       discarded.
			 */
			bool findMappings(const MolecularGraph& molgraph);

			/**
			 * \brief Returns the number of atom/bond mappings that were recorded in the last call to findMappings().
			 * \return The number of atom/bond mappings that were recorded in the last call to findMappings().
			 */
			std::size_t getNumMappings() const;

			/**
			 * \brief Returns a non-\c const reference to the stored atom/bond mapping object at index \a idx.
			 * \param idx The zero-based index of the atom/bond mapping object to return.
			 * \return A non-\c const reference to the atom/bond mapping object at index \a idx.
			 * \throw Base::IndexError if no mappings are available or \a idx is not in the range [0, getNumMappings() - 1].
			 */
			AtomBondMapping& getMapping(std::size_t idx);

			/**
			 * \brief Returns a \c const reference to the stored atom/bond mapping object at index \a idx.
			 * \param idx The zero-based index of the atom/bond mapping object to return.
			 * \return A \c const reference to the atom/bond mapping object at index \a idx.
			 * \throw Base::IndexError if no mappings are available or \a idx is not in the range [0, getNumMappings() - 1].
			 */
			const AtomBondMapping& getMapping(std::size_t idx) const;

			/**
			 * \brief Returns a mutable iterator pointing to the beginning of the stored atom/bond mapping objects.
			 * \return A mutable iterator pointing to the beginning of the stored atom/bond mapping objects.
			 */
			MappingIterator getMappingsBegin();

			/**
			 * \brief Returns a constant iterator pointing to the beginning of the stored atom/bond mapping objects.
			 * \return A constant iterator pointing to the beginning of the stored atom/bond mapping objects.
			 */
			ConstMappingIterator getMappingsBegin() const;

			/**
			 * \brief Returns a mutable iterator pointing to the end of the stored atom/bond mapping objects.
			 * \return A mutable iterator pointing to the end of the stored atom/bond mapping objects.
			 */
			MappingIterator getMappingsEnd();

			/**
			 * \brief Returns a constant iterator pointing to the end of the stored atom/bond mapping objects.
			 * \return A constant iterator pointing to the end of the stored atom/bond mapping objects.
			 */
			ConstMappingIterator getMappingsEnd() const;

			/**
			 * \brief Allows to specify a limit on the number of stored atom/bond mappings.
			 *
			 * In a call to findMappings() the automorphism search will terminate as soon as the specified maximum number of stored
			 * atom/bond mappings has been reached. A previously set limit on the number of mappings can be disabled
			 * by providing zero for the value of \a max_num_mappings.
			 *
			 * \param max_num_mappings The maximum number of atom/bond mappings to store.
			 * \note By default, no limit is imposed on the number of stored mappings.
			 */
			void setMaxNumMappings(std::size_t max_num_mappings);

			/**
			 * \brief Returns the specified limit on the number of stored atom/bond mappings.
			 * \return The specified maximum number of stored atom/bond mappings.
			 * \see setMaxNumMappings(), findMappings() 
			 */
			std::size_t getMaxNumMappings() const;

			void setFoundMappingCallback(const MappingCallbackFunction& func);

			const MappingCallbackFunction& getFoundMappingCallback() const;

		  private:
			AutomorphismGroupSearch(const AutomorphismGroupSearch&);

			AutomorphismGroupSearch& operator=(const AutomorphismGroupSearch&);
	
			const MatchExpression<Atom, MolecularGraph>::SharedPointer&
			getAtomMatchExpression(const Atom& atom) const;

			const MatchExpression<Bond, MolecularGraph>::SharedPointer&
			getBondMatchExpression(const Bond& bond) const;

			const MatchExpression<MolecularGraph>::SharedPointer&
			getMolGraphMatchExpression(const MolecularGraph& molgraph) const;
	
			class AtomMatchExpression : public MatchExpression<Atom, MolecularGraph>
			{

			public:
				AtomMatchExpression(AutomorphismGroupSearch* parent): parent(parent), stereoDescr(0) {}

				bool requiresAtomBondMapping() const;

				bool operator()(const Atom& query_atom, const MolecularGraph& query_molgraph, 
								const Atom& target_atom, const MolecularGraph& target_molgraph,
								const Base::Variant& aux_data) const;

				bool operator()(const Atom& query_atom, const MolecularGraph& query_molgraph, 
								const Atom& target_atom, const MolecularGraph& target_molgraph, 
								const AtomBondMapping& mapping, const Base::Variant& aux_data) const;
			private:
				AutomorphismGroupSearch*       parent;
				mutable unsigned int           type;
				mutable unsigned int           hybState;
				mutable std::size_t            isotope;
				mutable std::size_t            hCount;
				mutable long                   charge;
				mutable bool                   aromatic;
				mutable std::size_t            expBondCount;
				mutable StereoDescriptor       stereoDescr;
			};
	 
			class BondMatchExpression : public MatchExpression<Bond, MolecularGraph>
			{
			
			public:
				BondMatchExpression(AutomorphismGroupSearch* parent): parent(parent), stereoDescr(0) {}
			
				bool requiresAtomBondMapping() const;

				bool operator()(const Bond& query_bond, const MolecularGraph& query_molgraph, 
								const Bond& target_bond, const MolecularGraph& target_molgraph, 
								const Base::Variant& aux_data) const;

				bool operator()(const Bond& query_bond, const MolecularGraph& query_molgraph, 
								const Bond& target_bond, const MolecularGraph& target_molgraph, 
								const AtomBondMapping& mapping, const Base::Variant& aux_data) const;
			private:
				AutomorphismGroupSearch*       parent;
				mutable std::size_t            order;
				mutable bool                   inRing;
				mutable bool                   aromatic;
				mutable StereoDescriptor       stereoDescr;
			};

			class MolGraphMatchExpression : public MatchExpression<MolecularGraph>
			{
			
			public:
				MolGraphMatchExpression(const AutomorphismGroupSearch* parent): parent(parent) {}

				bool requiresAtomBondMapping() const;

				bool operator()(const MolecularGraph& query_molgraph, 
								const MolecularGraph& target_molgraph, 
								const Base::Variant& aux_data) const;

				bool operator()(const MolecularGraph& query_molgraph, 
								const MolecularGraph& target_molgraph, 
								const AtomBondMapping& mapping, const Base::Variant& aux_data) const;

			private:
				const AutomorphismGroupSearch* parent;
			};

			typedef MatchExpression<Atom, MolecularGraph>::SharedPointer AtomMatchExprPtr;
			typedef MatchExpression<Bond, MolecularGraph>::SharedPointer BondMatchExprPtr;
			typedef MatchExpression<MolecularGraph>::SharedPointer MolGraphMatchExprPtr;

			SubstructureSearch           substructSearch;
			bool                         incIdentityMapping;
			unsigned int                 atomPropFlags;
			unsigned int                 bondPropFlags;
			AtomMatchExprPtr             atomMatchExpr;
			BondMatchExprPtr             bondMatchExpr;
			MolGraphMatchExprPtr         molGraphMatchExpr;
			MappingCallbackFunction      mappingCallbackFunc;
			const Atom*                  lastQueryAtom;
			const Bond*                  lastQueryBond;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CHEM_AUTOMORPHISMGROUPSEARCH_HPP

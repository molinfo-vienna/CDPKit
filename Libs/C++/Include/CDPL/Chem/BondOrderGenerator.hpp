/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondOrderGenerator.hpp 
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
 * \brief Definition of the class CDPL::Chem::BondOrderGenerator.
 */

#ifndef CDPL_CHEM_BONDORDERGENERATOR_HPP
#define CDPL_CHEM_BONDORDERGENERATOR_HPP

#include <cstddef>
#include <vector>
#include <utility>

#include <boost/shared_ptr.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Util/Array.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class SubstructureSearch;
		class Fragment;
		class MolecularGraph;
		class Atom;
		class Bond;
		class AtomBondMapping;

		/**
		 * \addtogroup CDPL_CHEM_BOND_ORDERS
		 * @{
		 */

		/**
		 * \brief BondOrderGenerator.
		 */
		class CDPL_CHEM_API BondOrderGenerator 
		{

		public:
			/**
			 * \brief Constructs the \c %BondOrderGenerator instance.
			 */
			BondOrderGenerator();

			/**
			 * \brief Constructs the \c %BondOrderGenerator instance and perceives the order of the bonds
			 *        in the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to perceive the bond orders.
			 * \param orders An array containing the perceived bond orders. The orders are stored in the same sequence
			 *         as the bonds appear in the input molecular graph, i.e. the order of a particular bond is
			 *         accessible via its index in the molecular graph.
			 * \param undef_only Specifies whether or not to perceive only undefined (= unset) bond orders.
			 */
			BondOrderGenerator(const MolecularGraph& molgraph, Util::STArray& orders, bool undef_only = true);

			/**
			 * \brief Allows to specify whether already defined bond orders should be left unchanged.
			 * \param undef_only Specifies whether or not to perceive only undefined (= unset) bond orders.
			 * \note The default setting is to perceive only the order of undefined bonds.
			 */
			void undefinedOnly(bool undef_only);
			
			/**
			 * \brief Tells whether or not only undefined bond orders have to be perceived.
			 * \return \c true if only undefined (= unset) bond orders are perceived, and  \c false otherwise.
			 */
			bool undefinedOnly() const;

			/**
			 * \brief Perceives the order of the bonds in the molecular graph \a molgraph from its 3D structure 
			 *        and atom connectivity.
			 * \param molgraph The molecular graph for which to perceive the bond orders.
			 * \param orders An array containing the perceived bond orders. The orders are stored in the same sequence
			 *         as the bonds appear in the input molecular graph, i.e. the order of a particular bond is
			 *         accessible via its index in the molecular graph.
			 */
			void generate(const MolecularGraph& molgraph, Util::STArray& orders);

		private:
			/** \cond CDPL_PRIVATE_SECTION_DOC */

			enum Geometry {
			
			  UNDEF,
			  TERMINAL,
			  LINEAR,
			  TRIG_PLANAR,
			  TETRAHEDRAL
			};

			typedef boost::shared_ptr<MolecularGraph> MolecularGraphPtr;
			typedef boost::shared_ptr<SubstructureSearch> SubstructureSearchPtr;
			typedef std::vector<const Bond*> BondList;
			typedef std::vector<const Atom*> AtomList;
			typedef std::vector<std::size_t> UIntTable;
			typedef std::vector<Geometry> GeometryTable;
			typedef std::vector<MolecularGraphPtr> MolecularGraphPtrList;
			typedef std::vector<std::pair<double, const AtomBondMapping*> > ABMappingList;

			class AtomMatchExpression;
			class BondMatchExpression;

			friend class BondMatchExpression;

			void init(const MolecularGraph& molgraph, Util::STArray& orders);

			void calcFreeAtomValences(Util::STArray& orders);
			void perceiveAtomGeometries(Util::STArray& orders);
			void assignBondOrders(Util::STArray& orders);

			void assignTetrahedralAtomBondOrders(Util::STArray& orders);
			void assignFunctionalGroupBondOrders(Util::STArray& orders);
			void assignConjRingBondOrders(Util::STArray& orders);
			void assignRemainingBondOrders(Util::STArray& orders);

			void assignFragBondOrders(std::size_t depth, Util::STArray& orders);

			double calcHybridizationMatchScore();
			double calcMappingScore(const AtomBondMapping& mapping) const;

			void markConjRingBonds(Util::STArray& orders);

			Geometry perceiveInitialGeometry(const Atom& atom);
			void fixRingAtomGeometries(const Fragment& ring);
			void postprocessGeometry(const Atom& atom, Util::STArray& orders);
			
			void assignNbrBondOrders(const Atom& atom, Util::STArray& orders);

			void getNeighborAtoms(const Atom& atom, AtomList& atom_list, const Atom* exclude_atom) const;
			std::size_t countBondsWithOrder(const Atom& atom, std::size_t order, const UIntTable& order_table) const;

			template <typename Pred>
			void getUndefBondFragment(const Atom& atom, bool add_atoms, const Pred& bond_pred);

			double calcAvgBondAngle(const Atom& atom, const AtomList& nbr_atoms) const;
			double calcDihedralAngle(const Atom& atom1, const Atom& atom2, const Atom& atom3, const Atom& atom4) const;
			double calcDihedralAngle(const Math::Vector3D& atom1_pos, const Math::Vector3D& atom2_pos, 
									 const Math::Vector3D& atom3_pos, const Math::Vector3D& atom4_pos) const;
			double calcAvgTorsionAngle(const Fragment& ring) const;

			bool isConjRingBond(const Bond& bond) const;
	
			const MolecularGraph*  molGraph;
			bool                   undefOnly;
			Util::BitSet           defOrderMask;
			Util::BitSet           multibondAtomMask;
			UIntTable              freeAtomValences;
			GeometryTable          atomGeometries;
			BondList               undefBonds;
			BondList               fragBondList;
			AtomList               fragAtomList;
			AtomList               nbrAtomList1;
			AtomList               nbrAtomList2;
			UIntTable              fragBondOrders;
			UIntTable              workingBondOrders;
			double                 currOrderAssmentScore;
			double                 bestOrderAssmentScore;
			SubstructureSearchPtr  substructSearch;
			MolecularGraphPtrList  funcGroupPatterns;
			ABMappingList          funcGroupMappings;
			Util::BitSet           procMappingMask;
			Util::BitSet           bondMappingMask1;
			Util::BitSet           bondMappingMask2;
			Util::BitSet           conjRingBondMask;

			/** \endcond */
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_BONDORDERGENERATOR_HPP
 

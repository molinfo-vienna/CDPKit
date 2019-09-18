/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SymmetryClassCalculator.hpp 
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
 * \brief Definition of the class CDPL::Chem::SymmetryClassCalculator.
 */

#ifndef CDPL_CHEM_SYMMETRYCLASSCALCULATOR_HPP
#define CDPL_CHEM_SYMMETRYCLASSCALCULATOR_HPP

#include <vector>
#include <functional>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/BondPropertyFlag.hpp"
#include "CDPL/Util/Array.hpp"
#include "CDPL/Util/ObjectStack.hpp"
#include "CDPL/Base/IntegerTypes.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;

		/**
		 * \addtogroup CDPL_CHEM_SYMMETRY_CLASSES
		 * @{
		 */

		/**
		 * \brief SymmetryClassCalculator.
		 * \see [\ref TOPSY]
		 */
		class CDPL_CHEM_API SymmetryClassCalculator 
		{

		public:
			/**
			 * \brief Specifies the default set of atomic properties considered in the perception
			 *        of topological symmetry classes.
			 */
			static const unsigned int DEF_ATOM_PROPERTY_FLAGS = 
				AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::H_COUNT |
				AtomPropertyFlag::AROMATICITY | AtomPropertyFlag::FORMAL_CHARGE;

			/**
			 * \brief Specifies the default set of bond properties considered in the perception
			 *        of topological symmetry classes.
			 */
			static const unsigned int DEF_BOND_PROPERTY_FLAGS = 
				BondPropertyFlag::ORDER | BondPropertyFlag::AROMATICITY;

			/**
			 * \brief Constructs the \c %SymmetryClassCalculator instance.
			 */
			SymmetryClassCalculator();

			/**
			 * \brief Constructs the \c %SymmetryClassCalculator instance and perceives the topological symmetry
			 *        classes of the atoms in the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to perceive the symmetry classes.
			 * \param class_ids An array containing the perceived symmetry class IDs. The class IDs
			 *         are stored in the same order as the atoms appear in the atom list of the molecular graph
			 *         (i.e. the symmetry class of an atom is accessible via its index).
			 */
			SymmetryClassCalculator(const MolecularGraph& molgraph, Util::STArray& class_ids);

			/**
			 * \brief Allows to specify the set of atomic properties that has to be considered in the perception of
			 *        topological symmetry classes.
			 *
			 * The \a flags argument is an OR combination of the constants defined in namespace
			 * Chem::AtomPropertyFlag. Supported property flags are:
			 *  - Chem::AtomPropertyFlag::TYPE
			 *  - Chem::AtomPropertyFlag::ISOTOPE
			 *  - Chem::AtomPropertyFlag::FORMAL_CHARGE
			 *  - Chem::AtomPropertyFlag::AROMATICITY
			 *  - and Chem::AtomPropertyFlag::H_COUNT
			 *
			 * \param flags The set of atomic properties to consider.
			 * \note The default set of atomic properties is specified by SymmetryClassCalculator::DEF_ATOM_PROPERTY_FLAGS.
			 */
			void setAtomPropertyFlags(unsigned int flags);

			/**
			 * \brief Returns the set of atomic properties that gets considered in the perception of
			 *        topological symmetry classes.
			 * \return The set of considered atomic properties.
			 * \see setAtomPropertyFlags()
			 */
			unsigned int getAtomPropertyFlags() const;

			/**
			 * \brief Allows to specify the set of bond properties that has to be considered in the perception of
			 *        topological symmetry classes.
			 *
			 * The \a flags argument is an OR combination of the constants defined in namespace
			 * Chem::BondPropertyFlag. Supported property flags are:
			 *  - Chem::BondPropertyFlag::ORDER
			 *  - and Chem::BondPropertyFlag::AROMATICITY
			 *
			 * \param flags The set of bond properties to consider.
			 * \note The default set of bond properties is specified by SymmetryClassCalculator::DEF_BOND_PROPERTY_FLAGS.
			 */
			void setBondPropertyFlags(unsigned int flags);

			/**
			 * \brief Returns the set of bond properties that gets considered in the perception of
			 *        topological symmetry classes.
			 * \return The set of considered bond properties.
			 * \see setBondPropertyFlags()
			 */
			unsigned int getBondPropertyFlags() const;

			/**
			 * \brief Allows to specify whether implicit hydrogen atoms shall be ignored or treated in the same way as
			 *        explicit ones.
			 * \param include If \c true, implicit hydrogen atoms are treated as if they were explicit and are ignored otherwise.
			 * \note By default, implicit hydrogen atoms are treated in the same way as explicit ones.
			 */
			void includeImplicitHydrogens(bool include);

			/**
			 * \brief Tells whether implicit hydrogen atoms are ignored or treated in the same way as explicit ones.
			 * \return \c true if implicit hydrogen atoms are treated in the same way as explicit ones, and \c false if they
			 *         are ignored.
			 */
			bool implicitHydrogensIncluded() const;

			/**
			 * \brief Perceives the topological symmetry classes of the atoms in the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to perceive the symmetry classes.
			 * \param class_ids An array containing the perceived symmetry class IDs. The class IDs
			 *         are stored in the same order as the atoms appear in the atom list of the molecular graph
			 *         (i.e. the symmetry class of an atom is accessible via its index).
			 */
			void calculate(const MolecularGraph& molgraph, Util::STArray& class_ids);

		private:
			SymmetryClassCalculator(const SymmetryClassCalculator&);

			SymmetryClassCalculator& operator=(const SymmetryClassCalculator&);

			void init(const MolecularGraph&, Util::STArray&);

			void calcSVMNumbers();
			void perceiveSymClasses(const MolecularGraph&, Util::STArray&);

			class AtomNode;

			AtomNode* allocNode(Base::uint64 class_id);

			typedef std::vector<AtomNode*> NodeList;

			class AtomNode
			{

			public:
				void clear();

				void addNbrNode(AtomNode*);

				void setSVMNumber(Base::uint64);

				void calcNextSVMNumber();
				void updateSVMNumber();
				void updateSVMHistory();

				void setNextSymClassID(Base::uint64);

				void update();

				std::size_t getSymClassID() const;
				void setSymClassID(Base::uint64 class_id);

				struct SymClassCmpFunc : public std::binary_function<const AtomNode*, const AtomNode*, bool>
				{

					bool operator()(const AtomNode*, const AtomNode*) const;
				};

				struct SVMNumberCmpFunc : public std::binary_function<const AtomNode*, const AtomNode*, bool>
				{

					bool operator()(const AtomNode*, const AtomNode*) const;
				};

			private:
				typedef std::vector<Base::uint64> SVMNumberList;
 
				Base::uint64  symClassID;
				Base::uint64  nextSymClassID;
				Base::uint64  nbrSymClassIDProd;
				Base::uint64  svmNumber;
				Base::uint64  nextSVMNumber;
				SVMNumberList svmNumberHistory;
				NodeList      nbrNodes;
			};

			typedef Util::ObjectStack<AtomNode> NodeCache;

			NodeCache      nodeCache;
			unsigned int   atomPropertyFlags;
			unsigned int   bondPropertyFlags;
			bool           hComplete;
			NodeList       hAtomNodes;
			NodeList       atomNodes;
			NodeList       sortedAtomNodes;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_SYMMETRYCLASSCALCULATOR_HPP
 

/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CanonicalNumberingCalculator.hpp 
 *
 * B.D. McKay, Practical graph isomorphism. Proceedings of
 * the 10th Manitoba Conference on Numerical Maths and
 * Computing. Congressus Numerantium, 30 (1981) 45-87.
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
 * \brief Definition of the class CDPL::Chem::CanonicalNumberingCalculator.
 */

#ifndef CDPL_CHEM_CANONICALNUMBERINGCALCULATOR_HPP
#define CDPL_CHEM_CANONICALNUMBERINGCALCULATOR_HPP

#include <cstddef>
#include <cstdint>
#include <vector>
#include <utility>
#include <functional>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/BondPropertyFlag.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Util/Array.hpp"
#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Util/ObjectStack.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;
		class Fragment;
		class Atom;
		class Bond;

		/**
		 * \brief CanonicalNumberingCalculator.
		 * \see [\ref MCKAY]
		 */
		class CDPL_CHEM_API CanonicalNumberingCalculator 
		{

		public:
			/**
			 * \brief Specifies the default set of atomic properties considered by the canonical
			 *        numbering algorithm.
			 */
			static constexpr unsigned int DEF_ATOM_PROPERTY_FLAGS = 
				AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE |
				AtomPropertyFlag::AROMATICITY | AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::H_COUNT;

			/**
			 * \brief Specifies the default set of bond properties considered by the canonical
			 *        numbering algorithm.
			 */
			static constexpr unsigned int DEF_BOND_PROPERTY_FLAGS = 
				BondPropertyFlag::ORDER | BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION;

			typedef std::function<std::size_t(const Atom&, const MolecularGraph&)> HydrogenCountFunction;

			/**
			 * \brief Constructs the \c %CanonicalNumberingCalculator instance.
			 */
			CanonicalNumberingCalculator();

			/**
			 * \brief Constructs the \c %CanonicalNumberingCalculator instance and performs a canonical numbering
			 *        of the atoms in the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to perform the canonical numbering.
			 * \param numbering An array that contains the calculated canonical atom labels. The labels
			 *         are stored in the same order as the atoms appear in the atom list of the molecular graph
			 *         (i.e. the canonical number of an atom is accessible via its index).
			 */
			CanonicalNumberingCalculator(const MolecularGraph& molgraph, Util::STArray& numbering);
		
			/**
			 * \brief Allows to specify the set of atomic properties that has to be considered by the
			 *        canonical numering algorithm.
			 *
			 * The \a flags argument is an OR combination of the constants defined in namespace
			 * Chem::AtomPropertyFlag. Supported property flags are:
			 *  - Chem::AtomPropertyFlag::TYPE
			 *  - Chem::AtomPropertyFlag::ISOTOPE
			 *  - Chem::AtomPropertyFlag::FORMAL_CHARGE
			 *  - Chem::AtomPropertyFlag::AROMATICITY
			 *  - Chem::AtomPropertyFlag::CONFIGURATION
			 *  - and Chem::AtomPropertyFlag::H_COUNT
			 *
			 * \param flags The set of atomic properties to consider.
			 * \note The default set of atomic properties is specified by CanonicalNumberingCalculator::DEF_ATOM_PROPERTY_FLAGS.
			 */
			void setAtomPropertyFlags(unsigned int flags);

			/**
			 * \brief Returns the set of atomic properties that gets considered by the canonical numbering
			 *        algorithm.
			 * \return The set of considered atomic properties.
			 * \see setAtomPropertyFlags()
			 */
			unsigned int getAtomPropertyFlags() const;

			/**
			 * \brief Allows to specify the set of bond properties that has to be considered by the
			 *        canonical numering algorithm.
			 *
			 * The \a flags argument is an OR combination of the constants defined in namespace
			 * Chem::BondPropertyFlag. Supported property flags are:
			 *  - Chem::BondPropertyFlag::ORDER
			 *  - Chem::BondPropertyFlag::CONFIGURATION
			 *  - and Chem::BondPropertyFlag::AROMATICITY
			 *
			 * \param flags The set of bond properties to consider.
			 * \note The default set of bond properties is specified by CanonicalNumberingCalculator::DEF_BOND_PROPERTY_FLAGS.
			 */
			void setBondPropertyFlags(unsigned int flags);

			/**
			 * \brief Returns the set of bond properties that gets considered by the canonical numbering
			 *        algorithm.
			 * \return The set of considered bond properties.
			 * \see setBondPropertyFlags()
			 */
			unsigned int getBondPropertyFlags() const;

			void setHydrogenCountFunction(const HydrogenCountFunction& func);

			const HydrogenCountFunction& getHydrogenCountFunction();

			/**
			 * \brief Performs a canonical numbering of the atoms in the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to perform the canonical numbering.
			 * \param numbering An array that contains the calculated canonical atom labels. The labels
			 *         are stored in the same order as the atoms appear in the atom list of the molecular graph
			 *         (i.e. the canonical number of an atom is accessible via its index).
			 */
			void calculate(const MolecularGraph& molgraph, Util::STArray& numbering);

		private:
			class AtomNode;
			class Edge;

			typedef CanonicalNumberingCalculator Calculator;
			typedef std::vector<Edge*> EdgeList;

			CanonicalNumberingCalculator(const CanonicalNumberingCalculator&);

			CanonicalNumberingCalculator& operator=(const CanonicalNumberingCalculator&);

			typedef std::vector<std::uint64_t> ConnectionTable;

			void init(const MolecularGraph&, Util::STArray&);
			void setup(const MolecularGraph&);

			void canonicalize(const MolecularGraph&, Util::STArray&);			
			void canonicalize(std::size_t);

			void processNewSolution();

			int testNewSolution();

			void buildConnectionTable(ConnectionTable& ctab) const;
			void appendAtomConfigs(ConnectionTable& ctab);
			void appendBondConfigs(ConnectionTable& ctab);

			void establishCanonNumbering(Util::STArray&);

			void saveState();
			void restoreState();

			AtomNode* allocNode(Calculator* calculator, const Atom* atom, std::uint64_t label, std::size_t id);

			Edge* allocEdge(const Calculator* calculator, const Bond* bond, std::uint64_t label,
							AtomNode* nbr_node, std::size_t id);

			class AtomNode
			{

			public:
				typedef EdgeList::const_iterator EdgeIterator;

				AtomNode();

				void init(Calculator* calculator, const Atom* atom, std::uint64_t label, std::size_t id);

				const Atom* getAtom() const;

				void addEdge(Edge* edge);

				std::uint64_t getLabel() const;

				void setLabel(std::uint64_t label);
				void setNewLabel(std::size_t label);

				void updateLabel();

				std::size_t getID() const;

				void sortEdges();

				std::size_t getNumEdges() const;

				EdgeIterator getEdgesBegin() const;
				EdgeIterator getEdgesEnd() const;

				void appendConnectivityData(ConnectionTable& ctab) const;
				void appendBondConfigData(ConnectionTable& ctab) const;
				void appendAtomConfigData(ConnectionTable& ctab);

				bool involvedInStereocenter();

				bool isEquivalent(const AtomNode* node) const;
				bool isNonEquivalent(const AtomNode* node) const;

				void addToEquivalenceSet(const AtomNode* node);
				void addToNonEquivalenceSet(const AtomNode* node);

				static bool terminalAndOnCommonNonStereoNode(const AtomNode* node1, const AtomNode* node2);

				struct LessCmpFunc
				{

					bool operator()(const AtomNode*, const AtomNode*) const;
				};

			private:
				bool initConfigurationData();

				Calculator*       calculator;
				const Atom*       atom;
				std::uint64_t     initialLabel;
				std::uint64_t     label;
				std::size_t       newLabel;
				std::size_t       id;
				Util::BitSet      equivNodeMask;
				EdgeList          edges;
				StereoDescriptor  stereoDescr;
				bool              hasConfiguration;
				bool              configDataValid;
				bool              partOfStereocenter;
				bool              partOfStereocenterValid;
			};
		 
			class Edge
			{

			public:
				Edge();

				void init(const Calculator* calculator, const Bond* bond, std::uint64_t label, 
						  AtomNode* nbr_node, std::size_t id);

				void appendBondData(ConnectionTable&) const;
				void appendConfigurationData(const AtomNode* node, ConnectionTable& ctab);

				AtomNode* getNeighborNode() const;

				bool representsStereoBond(const AtomNode* node);

				std::size_t getID() const;

				struct LessCmpFunc
				{

					bool operator()(const Edge*, const Edge*) const;
				};

			private:
				bool initConfigurationData(const AtomNode* node);

				const Calculator*  calculator;
				const Bond*        bond;
				AtomNode*          nbrNode;
				std::uint64_t      label;
				std::size_t        id;
				StereoDescriptor   stereoDescr;
				bool               hasConfiguration;
				bool               configDataValid;
			};

			typedef std::pair<const Fragment*, const ConnectionTable*> CanonComponentInfo;

			struct ComponentCmpFunc
			{
					
				bool operator()(const CanonComponentInfo&, const CanonComponentInfo&) const;
			};

			typedef std::pair<AtomNode*, std::uint64_t> NodeLabelingState;
			typedef std::vector<NodeLabelingState> NodeLabelingStack;
			typedef std::vector<AtomNode*> NodeList;
			typedef std::vector<ConnectionTable> ConnectionTableList;
			typedef std::vector<CanonComponentInfo> CanonComponentList;
			typedef Util::ObjectStack<AtomNode> NodeCache;
			typedef Util::ObjectStack<Edge> EdgeCache;

			NodeCache              nodeCache;
			EdgeCache              edgeCache;
			unsigned int           atomPropertyFlags;
			unsigned int           bondPropertyFlags;
			HydrogenCountFunction  hCountFunc;
			bool                   foundStereogenicAtoms;
			bool                   foundStereogenicBonds;
			const MolecularGraph*  molGraph;
			NodeList               allocNodes;
			EdgeList               allocEdges;
			NodeList               nodeList;
			NodeList               equivNodeStack;
			NodeLabelingStack      nodeLabelingStack;
			ConnectionTableList    compConnectionTables;
			ConnectionTableList    levelConnectionTables;
			ConnectionTable        testConnectionTable;
			NodeList               minNodeList;
			CanonComponentList     canonComponentList;
			Util::BitSet           visitedEdgeMask;
		};
	}
}

#endif // CDPL_CHEM_CANONICALNUMBERINGCALCULATOR_HPP

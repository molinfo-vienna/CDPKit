/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CanonicalNumberingGenerator.hpp 
 *
 * B.D. McKay, Practical graph isomorphism. Proceedings of
 * the 10th Manitoba Conference on Numerical Maths and
 * Computing. Congressus Numerantium, 30 (1981) 45-87.
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
 * \brief Definition of the class CDPL::Chem::CanonicalNumberingGenerator.
 */

#ifndef CDPL_CHEM_CANONICALNUMBERINGGENERATOR_HPP
#define CDPL_CHEM_CANONICALNUMBERINGGENERATOR_HPP

#include <cstddef>
#include <vector>
#include <functional>
#include <utility>

#include <boost/function.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/BondPropertyFlag.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Util/Array.hpp"
#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Util/ObjectStack.hpp"
#include "CDPL/Base/IntegerTypes.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;
		class Fragment;
		class Atom;
		class Bond;

		/**
		 * \addtogroup CDPL_CHEM_CANONICAL_NUMBERING
		 * @{
		 */

		/**
		 * \brief CanonicalNumberingGenerator.
		 * \see [\ref MCKAY]
		 */
		class CDPL_CHEM_API CanonicalNumberingGenerator 
		{

		public:
			/**
			 * \brief Specifies the default set of atomic properties considered by the canonical
			 *        numbering algorithm.
			 */
			static const unsigned int DEF_ATOM_PROPERTY_FLAGS = 
				AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE | AtomPropertyFlag::FORMAL_CHARGE |
				AtomPropertyFlag::AROMATICITY | AtomPropertyFlag::CONFIGURATION | AtomPropertyFlag::H_COUNT;

			/**
			 * \brief Specifies the default set of bond properties considered by the canonical
			 *        numbering algorithm.
			 */
			static const unsigned int DEF_BOND_PROPERTY_FLAGS = 
				BondPropertyFlag::ORDER | BondPropertyFlag::AROMATICITY | BondPropertyFlag::CONFIGURATION;

			typedef boost::function2<std::size_t, const Atom&, const MolecularGraph&> HydrogenCountFunction;

			/**
			 * \brief Constructs the \c %CanonicalNumberingGenerator instance.
			 */
			CanonicalNumberingGenerator();

			/**
			 * \brief Constructs the \c %CanonicalNumberingGenerator instance and performs a canonical numbering
			 *        of the atoms in the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to perform the canonical numbering.
			 * \param numbering An array that contains the generated canonical atom labels. The labels
			 *         are stored in the same order as the atoms appear in the atom list of the molecular graph
			 *         (i.e. the canonical number of an atom is accessible via its index).
			 */
			CanonicalNumberingGenerator(const MolecularGraph& molgraph, Util::STArray& numbering);
		
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
			 * \note The default set of atomic properties is specified by CanonicalNumberingGenerator::DEF_ATOM_PROPERTY_FLAGS.
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
			 * \note The default set of bond properties is specified by CanonicalNumberingGenerator::DEF_BOND_PROPERTY_FLAGS.
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
			 * \param numbering An array that contains the generated canonical atom labels. The labels
			 *         are stored in the same order as the atoms appear in the atom list of the molecular graph
			 *         (i.e. the canonical number of an atom is accessible via its index).
			 */
			void generate(const MolecularGraph& molgraph, Util::STArray& numbering);

		private:
			class AtomNode;
			class Edge;

			typedef CanonicalNumberingGenerator Generator;
			typedef std::vector<Edge*> EdgeList;

			CanonicalNumberingGenerator(const CanonicalNumberingGenerator&);

			CanonicalNumberingGenerator& operator=(const CanonicalNumberingGenerator&);

			typedef std::vector<Base::uint64> ConnectionTable;

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

			AtomNode* allocNode(Generator* generator, const Atom* atom, Base::uint64 label, std::size_t id);

			Edge* allocEdge(const Generator* generator, const Bond* bond, Base::uint64 label,
							AtomNode* nbr_node, std::size_t id);

			class AtomNode
			{

			public:
				typedef EdgeList::const_iterator EdgeIterator;

				AtomNode();

				void init(Generator* generator, const Atom* atom, Base::uint64 label, std::size_t id);

				const Atom* getAtom() const;

				void addEdge(Edge* edge);

				Base::uint64 getLabel() const;

				void setLabel(Base::uint64 label);
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

				bool reachesNodeViaStereocenter(AtomNode* node, bool found_ctr);

				bool involvedInStereocenter();

				bool isEquivalent(const AtomNode* node) const;
				bool isNonEquivalent(const AtomNode* node) const;

				void addToEquivalenceSet(const AtomNode* node);
				void addToNonEquivalenceSet(const AtomNode* node);

				static bool terminalAndOnCommonNonStereoNode(const AtomNode* node1, const AtomNode* node2);

				struct LessCmpFunc : public std::binary_function<const AtomNode*, const AtomNode*, bool>
				{

					bool operator()(const AtomNode*, const AtomNode*) const;
				};

			private:
				bool initConfigurationData();

				Generator*        generator;
				const Atom*       atom;
				Base::uint64      initialLabel;
				Base::uint64      label;
				std::size_t       newLabel;
				std::size_t       id;
				Util::BitSet      equivNodeMask;
				Util::BitSet      nonEquivNodeMask;
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

				void init(const Generator* generator, const Bond* bond, Base::uint64 label, 
						  AtomNode* nbr_node, std::size_t id);

				void appendBondData(ConnectionTable&) const;
				void appendConfigurationData(const AtomNode* node, ConnectionTable& ctab);

				AtomNode* getNeighborNode() const;

				bool representsStereoBond(const AtomNode* node);

				std::size_t getID() const;

				struct LessCmpFunc : public std::binary_function<const Edge*, const Edge*, bool>
				{

					bool operator()(const Edge*, const Edge*) const;
				};

			private:
				bool initConfigurationData(const AtomNode* node);

				const Generator*  generator;
				const Bond*       bond;
				AtomNode*         nbrNode;
				Base::uint64      label;
				std::size_t       id;
				StereoDescriptor  stereoDescr;
				bool              hasConfiguration;
				bool              configDataValid;
			};

			typedef std::pair<const Fragment*, const ConnectionTable*> CanonComponentInfo;

			struct ComponentCmpFunc : public std::binary_function<CanonComponentInfo, CanonComponentInfo, bool>
			{
					
				bool operator()(const CanonComponentInfo&, const CanonComponentInfo&) const;
			};

			typedef std::pair<AtomNode*, Base::uint64> NodeLabelingState;
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

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_CANONICALNUMBERINGGENERATOR_HPP

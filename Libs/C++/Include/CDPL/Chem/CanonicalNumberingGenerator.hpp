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

#include <boost/shared_ptr.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/BondPropertyFlag.hpp"
#include "CDPL/Util/Array.hpp"
#include "CDPL/Util/BitSet.hpp"
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

			/**
			 * \brief Constructs the \c %CanonicalNumberingGenerator instance.
			 */
			CanonicalNumberingGenerator();

			/**
			 * \brief Constructs the \c %CanonicalNumberingGenerator instance and performs a canonical numbering
			 *        of the atoms in the molecular graph \a molgraph.
			 *
			 * The generated canonical atom labels can be retrieved by a call to getResult().
			 *
			 * \param molgraph The molecular graph for which to perform the canonical numbering.
			 */
			CanonicalNumberingGenerator(const MolecularGraph& molgraph);
		
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

			/**
			 * \brief Performs a canonical numbering of the atoms in the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to perform the canonical numbering.
			 * \return An array that contains the generated canonical atom labels. The labels
			 *         are stored in the same order as the atoms appear in the atom list of the molecular graph
			 *         (i.e. the canonical number of an atom is accessible via its index).
			 */
			const Util::STArray& generate(const MolecularGraph& molgraph);

			/**
			 * \brief Returns the result of the last canonical numbering.
			 * \return An array that contains the canonical atom labels. If a canonical
			 *         numbering has not yet been performed, the returned array is empty.
			 * \see generate()
			 */
			const Util::STArray& getResult() const;

		private:
			/** \cond CDPL_PRIVATE_SECTION_DOC */

			CanonicalNumberingGenerator(const CanonicalNumberingGenerator&);

			CanonicalNumberingGenerator& operator=(const CanonicalNumberingGenerator&);

			typedef std::vector<Base::uint64> ConnectionTable;

			void init(const MolecularGraph&);
			void setup(const MolecularGraph&);

			void canonicalize(const MolecularGraph& mol);			
			void canonicalize(std::size_t depth);

			void processNewSolution();

			int testNewSolution();

			void buildConnectionTable(ConnectionTable& ctab) const;
			void appendAtomConfigs(ConnectionTable& ctab);
			void appendBondConfigs(ConnectionTable& ctab);

			void establishCanonNumbering();

			void saveState();
			void restoreState();

			typedef CanonicalNumberingGenerator Generator;

			class Edge;

			class AtomNode
			{

				typedef std::vector<Edge*> EdgeList;

			public:
				typedef boost::shared_ptr<AtomNode> SharedPointer;

				typedef EdgeList::const_iterator EdgeIterator;

				AtomNode(Generator* generator, const Atom* atom, 
						 Base::uint64 label, std::size_t id);

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
				const Atom*       refNbrAtoms[4];
				unsigned int      configuration;
				bool              hasConfiguration;
				bool              configDataValid;
				bool              partOfStereocenter;
				bool              partOfStereocenterValid;
			};
		 
			class Edge
			{

			public:
				typedef boost::shared_ptr<Edge> SharedPointer;

				Edge(const Generator* generator, const Bond* bond, Base::uint64 label, 
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
				const Atom*       configRefAtoms[2];
				unsigned int      configuration;
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
			typedef std::vector<AtomNode::SharedPointer> AllocNodeList;
			typedef std::vector<Edge::SharedPointer> AllocEdgeList;
			typedef std::vector<AtomNode*> NodeList;
			typedef std::vector<ConnectionTable> ConnectionTableList;
			typedef std::vector<CanonComponentInfo> CanonComponentList;

			unsigned int           atomPropertyFlags;
			unsigned int           bondPropertyFlags;
			bool                   foundStereogenicAtoms;
			bool                   foundStereogenicBonds;
			const MolecularGraph*  molGraph;
			AllocNodeList          allocNodes;
			AllocEdgeList          allocEdges;
			NodeList               nodeList;
			NodeList               equivNodeStack;
			NodeLabelingStack      nodeLabelingStack;
			ConnectionTableList    compConnectionTables;
			ConnectionTableList    levelConnectionTables;
			ConnectionTable        testConnectionTable;
			NodeList               minNodeList;
			CanonComponentList     canonComponentList;
			Util::STArray          canonNumbering;
			Util::BitSet           visitedEdgeMask;

			/** \endcond */
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_CANONICALNUMBERINGGENERATOR_HPP

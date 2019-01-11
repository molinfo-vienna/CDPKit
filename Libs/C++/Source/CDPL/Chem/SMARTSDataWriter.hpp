/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SMARTSDataWriter.hpp 
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


#ifndef CDPL_CHEM_SMARTSDATAWRITER_HPP
#define CDPL_CHEM_SMARTSDATAWRITER_HPP

#include <iosfwd>
#include <vector>
#include <string>
#include <cstddef>

#include <boost/shared_ptr.hpp>


namespace CDPL 
{

	namespace Base
	{

		class DataIOBase;
	}

	namespace Chem
	{

		class Reaction;
		class MolecularGraph;
		class Atom;
		class Bond;
		class MatchConstraint;
		class MatchConstraintList;
		class StereoDescriptor;

		class SMARTSDataWriter
		{

		public:
			SMARTSDataWriter(const Base::DataIOBase& io_base);

			bool writeReaction(std::ostream&, const Reaction&);
			bool writeMolGraph(std::ostream&, const MolecularGraph&, bool = false);

		private:
			class DFSTreeNode;
			class DFSTreeEdge;

			void writeComponent(std::ostream&, const MolecularGraph&);

			void init();

			void buildDFSTree(const MolecularGraph&, DFSTreeNode* = 0);

			DFSTreeNode* createRootNode(const MolecularGraph&);

			void distRingClosureNumbers();
			void setBondDirections() const;
			void generateSMARTS(std::ostream&) const;

			std::size_t getRingClosureNumber();
			void putRingClosureNumber(std::size_t);

			DFSTreeNode* allocNode();
			DFSTreeEdge* allocEdge();

			void writeSMARTS(std::ostream&, const MolecularGraph&);

			void destroySMARTSWriter(SMARTSDataWriter*) const;

			class DFSTreeEdge
			{

			public:
				typedef boost::shared_ptr<DFSTreeEdge> SharedPointer;

				DFSTreeEdge(SMARTSDataWriter&);

				void setBond(const Bond*);
				const Bond* getBond() const;

				void setMolGraph(const MolecularGraph*);

				void setNodes(DFSTreeNode*, DFSTreeNode*);

				const DFSTreeNode* getBegin() const;
				const DFSTreeNode* getEnd() const;

				void setRingClosureNumber(std::size_t);
				std::size_t getRingClosureNumber() const;

				std::size_t getBondOrder() const;

				void writeBondExpression(std::ostream&) const;

			private:
				bool isImplicitExpression(const MatchConstraintList&) const;

				void writeBondExpression(const MatchConstraintList&, std::string&, std::size_t) const;

				void writeExpressionList(const MatchConstraint&, std::string&, std::size_t) const;
				void writeOrderExpression(const MatchConstraint&, std::string&, std::size_t) const;
				void writeAromaticityExpression(const MatchConstraint&, std::string&) const;
				void writeRingTopologyExpression(const MatchConstraint&, std::string&) const;
				void writeDirectionExpression(const MatchConstraint&, std::string&) const;

				SMARTSDataWriter&       writer;
				const MolecularGraph*   molGraph;
				const Bond*             bond;
				DFSTreeNode*            nodes[2];
				std::size_t             ringClosureNumber;
			};

			typedef std::vector<DFSTreeEdge*> EdgeList;
			typedef EdgeList::iterator EdgeIterator;

			class DFSTreeNode
			{

			public:
				typedef boost::shared_ptr<DFSTreeNode> SharedPointer;

				DFSTreeNode(SMARTSDataWriter&);

				void clear();
				
				void setAtom(const Atom*);
				const Atom* getAtom() const;

				void setMolGraph(const MolecularGraph*);

				void setLexicalOrder(std::size_t);
				std::size_t getLexicalOrder() const;

				void setParentEdge(DFSTreeEdge*);
				const DFSTreeEdge* getParentEdge() const;

				void addChildEdge(DFSTreeEdge*);
				void addRingClosureInEdge(DFSTreeEdge*);
				void addRingClosureOutEdge(DFSTreeEdge*);

				EdgeIterator getRingClosureInEdgesBegin();
				EdgeIterator getRingClosureInEdgesEnd();

				EdgeIterator getRingClosureOutEdgesBegin();
				EdgeIterator getRingClosureOutEdgesEnd();

				void generateSMARTS(std::ostream&) const;

			private:
				void writeAtomExpression(std::ostream&) const;	
				bool writeSimpleAtomExpression(std::ostream&, const MatchConstraintList&) const;	
				void writeComplexAtomExpression(const MatchConstraintList&, std::string&, std::size_t) const;

				void writeEnvironmentExpression(const MatchConstraint&, std::string&) const;

				void writeAtomTypeExpression(const MatchConstraint*, const MatchConstraint*,
											 std::string&, bool) const;
				bool writeAtomTypeExpression(const MatchConstraintList&, std::string&, bool = false) const;
				void writeExpressionList(const MatchConstraint&, std::string&, std::size_t) const;
				void writeAtomicNumber(unsigned int, bool, std::string&) const;
				void writeImplicitHCountExpression(const MatchConstraint&, std::string&) const;
				void writeTotalHCountExpression(const MatchConstraint&, std::string&) const;
				void writeRingSizeExpression(const MatchConstraint&, std::string&) const;
				void writeRingTopologyExpression(const MatchConstraint&, std::string&) const;
				void writeUnsaturationFlagExpression(const MatchConstraint&, std::string&) const;
				void writeRingMembershipExpression(const MatchConstraint&, std::string&) const;
				void writeValenceExpression(const MatchConstraint&, std::string&) const;
				void writeExplicitDegreeExpression(const MatchConstraint&, std::string&) const;
				void writeConnectivityExpression(const MatchConstraint&, std::string&) const;
				void writeRingConnectivityExpression(const MatchConstraint&, std::string&) const;
				void writeChargeExpression(const MatchConstraint&, std::string&) const;
				void writeChiralityExpression(const MatchConstraint&, std::string&) const;
				void writeIsotopeExpression(const MatchConstraint&, std::string&) const;
				void writeHybridizationStateExpression(const MatchConstraint&, std::string&) const;

				void writeReactionAtomMappingID(std::ostream&, std::size_t) const;

				void writeRingClosures(std::ostream&) const;
				void writeRingClosureNumber(std::ostream&, const DFSTreeEdge*) const;

				void writeChildNodeExpressions(std::ostream&) const;

				int getStereoParity(const StereoDescriptor&) const;

				typedef std::vector<std::size_t> NeighborIndexList;

				SMARTSDataWriter&          writer;
				const MolecularGraph*      molGraph;
				const Atom*                atom;
				DFSTreeEdge*               parentEdge;
				EdgeList                   childEdges;
				EdgeList                   ringClosureInEdges;
				EdgeList                   ringClosureOutEdges;
				mutable NeighborIndexList  nbrAtomIndices;
				std::size_t                lexicalOrder;
			};

			typedef boost::shared_ptr<SMARTSDataWriter> SharedPointer;

			typedef std::vector<DFSTreeNode::SharedPointer> AllocNodeList;
			typedef std::vector<DFSTreeEdge::SharedPointer> AllocEdgeList;
			typedef std::vector<DFSTreeNode*> NodeList;
			typedef std::vector<std::size_t> RingClosureNumberStack;

			const Base::DataIOBase& ioBase;	
			AllocNodeList           allocNodes;
			AllocEdgeList           allocEdges;
			std::size_t             freeNodeIndex;
			std::size_t             freeEdgeIndex;
			NodeList                componentNodes;
			NodeList                atomNodeMapping;
			RingClosureNumberStack  ringClosureNumberStack;
			std::size_t             highestRingClosureNumber;
			SharedPointer           smartsWriter;
			bool                    strictErrorChecking;
		};
	}
}

#endif // CDPL_CHEM_SMARTSDATAWRITER_HPP
 

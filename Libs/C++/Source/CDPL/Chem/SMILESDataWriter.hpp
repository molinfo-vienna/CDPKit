/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SMILESDataWriter.hpp 
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


#ifndef CDPL_CHEM_SMILESDATAWRITER_HPP
#define CDPL_CHEM_SMILESDATAWRITER_HPP

#include <iosfwd>
#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <cstddef>

#include <boost/shared_ptr.hpp>

#include "CDPL/Util/Array.hpp"
#include "CDPL/Util/ObjectStack.hpp"


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
		class Fragment;
		class Atom;
		class Bond;
		class CanonicalNumberingCalculator;
		class BondDirectionCalculator;

		class SMILESDataWriter
		{

		public:
			SMILESDataWriter(const Base::DataIOBase& io_base);

			~SMILESDataWriter();

			bool writeReaction(std::ostream&, const Reaction&);
			bool writeMolGraph(std::ostream&, const MolecularGraph&);

		private:
			class DFSTreeNode;
			class DFSTreeEdge;

			void init(std::ostream&, bool);
			void init();

			void writeNonCanonSMILES(std::ostream&, const Reaction&);
			void writeCanonSMILES(std::ostream&, const Reaction&);

			void writeNonCanonSMILES(std::ostream&, const MolecularGraph&);
			void writeCanonSMILES(std::ostream&, const MolecularGraph&);

			void generateCanonComponentSMILES(const MolecularGraph&);
			void outputCanonComponentSMILES(std::ostream&);
			
			void buildHDepleteMolGraph(const MolecularGraph&);
			void buildCanonMolGraph(const MolecularGraph&);

			void buildNonCanonDFSTree(const MolecularGraph&, DFSTreeNode* = 0);
			void buildCanonDFSTree(const MolecularGraph&, DFSTreeNode* = 0);

			DFSTreeNode* createRootNode(const MolecularGraph&);

			void distRingClosureNumbers();
			void generateSMILES(std::ostream&) const;

			std::size_t getRingClosureNumber();
			void putRingClosureNumber(std::size_t);

			DFSTreeNode* createNode();
			DFSTreeEdge* createEdge();

			DFSTreeNode* allocNode();
			DFSTreeEdge* allocEdge();
			
			void freeNodes();
			void freeEdges();

			struct CtrlParameters
			{

				bool        strictErrorChecking;
				bool        canonicalize;
				bool        writeKekuleForm;
				bool        writeAtomStereo;
				bool        writeBondStereo;
				bool        writeRingBondStereo;
				bool        writeIsotope;
				bool        writeRxnAtomMappingID;
				bool        writeSingleBonds;
				bool        writeAromaticBonds;
				bool        writeHydrogens;
				bool        noOrganicSubset;
				std::size_t minStereoBondRingSize;
				std::string recordFormat;
			};

			class CanonAtomCmpFunc : public std::binary_function<const Atom*, const Atom*, bool>
			{

			public:
				CanonAtomCmpFunc(const SMILESDataWriter& writer, const MolecularGraph& molgraph): 
					writer(writer), molGraph(molgraph) {}

				bool operator()(const Atom*, const Atom*) const;

			private:
				const SMILESDataWriter& writer;
				const MolecularGraph&   molGraph;
			};
	
			typedef std::vector<DFSTreeEdge*> EdgeList;
			typedef EdgeList::iterator EdgeIterator;

			class DFSTreeEdge
			{

			public:
				typedef boost::shared_ptr<DFSTreeEdge> SharedPointer;

				DFSTreeEdge(SMILESDataWriter&);

				void setBond(const Bond*);
				const Bond* getBond() const;

				void setMolGraph(const MolecularGraph*);

				void setNodes(DFSTreeNode*, DFSTreeNode*);

				const DFSTreeNode* getBegin() const;
				const DFSTreeNode* getEnd() const;

				void setRingClosureNumber(std::size_t);
				std::size_t getRingClosureNumber() const;

				void writeBondSymbol(std::ostream&) const;

			private:
				SMILESDataWriter&     writer;
				const MolecularGraph* molGraph;
				const Bond*           bond;
				DFSTreeNode*          nodes[2];
				std::size_t           ringClosureNumber;
			};

			class DFSTreeNode
			{

			public:
				typedef boost::shared_ptr<DFSTreeNode> SharedPointer;

				DFSTreeNode(SMILESDataWriter&);

				void clear();
				
				void setAtom(const Atom*);
				void setMolGraph(const MolecularGraph*);

				const Atom* getAtom() const;

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

				void generateSMILES(std::ostream&) const;

			private:
				void writeAtomString(std::ostream&) const;	
				void writeRingClosures(std::ostream&) const;
				void writeChildNodes(std::ostream&) const;

				void writeIsotope(std::ostream&, std::size_t) const;	
				void writeAtomSymbol(std::ostream&, unsigned int) const;	
				void writeAtomStereo(std::ostream&, int) const;	
				void writeHCount(std::ostream&, std::size_t) const;	
				void writeCharge(std::ostream&, long) const;	
				void writeReactionAtomMappingID(std::ostream&, std::size_t) const;	
				void writeRingClosureNumber(std::ostream&, const DFSTreeEdge*) const;

				int getStereoParity() const;

				SMILESDataWriter&          writer;
				const MolecularGraph*      molGraph;
				const Atom*                atom;
				DFSTreeEdge*               parentEdge;
				EdgeList                   childEdges;
				EdgeList                   ringClosureInEdges;
				EdgeList                   ringClosureOutEdges;
				std::size_t                lexicalOrder;
			};

			typedef std::auto_ptr<BondDirectionCalculator> BondDirCalculatorPtr;
			typedef std::auto_ptr<CanonicalNumberingCalculator> CanonNumberingCalculatorPtr;
			typedef std::auto_ptr<Fragment> FragmentPtr;
			typedef std::vector<const Atom*> AtomList;
			typedef std::vector<DFSTreeNode*> NodeList;
			typedef std::vector<std::size_t> RingClosureNumberStack;
			typedef std::vector<std::string> CanonSMILESList;
			typedef Util::ObjectStack<DFSTreeNode> NodeCache;
			typedef Util::ObjectStack<DFSTreeEdge> EdgeCache;

			const Base::DataIOBase&     ioBase;
			NodeCache                   nodeCache;
			EdgeCache                   edgeCache;
			NodeList                    componentNodes;
			NodeList                    atomNodeMapping;
			AtomList                    canonAtomList;
			FragmentPtr                 hDepleteMolGraph;
			FragmentPtr                 canonMolGraph;
			BondDirCalculatorPtr        bondDirCalculator;
			CanonNumberingCalculatorPtr canonNumberingCalculator;
			CanonSMILESList             canonSMILESStrings;
			Util::STArray               canonNumbering;
			Util::UIArray               bondDirections;
			CtrlParameters              ctrlParameters;
			RingClosureNumberStack      ringClosureNumberStack;
			std::size_t                 highestRingClosureNumber;
		};
	}
}

#endif // CDPL_CHEM_SMILESDATAWRITER_HPP

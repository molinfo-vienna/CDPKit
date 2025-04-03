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
#include <memory>
#include <cstddef>

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
            
            void distBondDirections(const MolecularGraph& molgraph);
            void distBondDirections(DFSTreeEdge* edge);
            
            void collectStereoBondEdges(DFSTreeNode* node, const MolecularGraph& molgraph);
            
            DFSTreeEdge* getBondStereoRefEdge(DFSTreeNode* node, const DFSTreeEdge* excl_edge);

            void generateSMILES(std::ostream&) const;

            std::size_t getRingClosureNumber();
            void        putRingClosureNumber(std::size_t);

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
                bool        outputKekuleForm;
                bool        outputAtomStereo;
                bool        outputBondStereo;
                bool        outputRingBondStereo;
                bool        outputIsotope;
                bool        outputRxnAtomMappingID;
                bool        outputSingleBonds;
                bool        outputAromaticBonds;
                bool        outputHydrogens;
                bool        noOrganicSubset;
                std::size_t minStereoBondRingSize;
                std::string recordFormat;
            };

            class CanonAtomCmpFunc
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
            typedef EdgeList::iterator        EdgeIterator;

            class DFSTreeEdge
            {

              public:
                typedef std::shared_ptr<DFSTreeEdge> SharedPointer;

                DFSTreeEdge(SMILESDataWriter&);

                void clear();
                
                void setBond(const Bond*);
                const Bond* getBond() const;

                void setMolGraph(const MolecularGraph*);

                void setNodes(DFSTreeNode*, DFSTreeNode*);

                DFSTreeNode* getBegin() const;
                DFSTreeNode* getEnd() const;

                DFSTreeNode* getOtherNode(const DFSTreeNode* node) const;
                
                void setRingClosureNumber(std::size_t);
                std::size_t getRingClosureNumber() const;

                void setDirection(const DFSTreeNode* node, int level);
                char getDirection() const;

                int getLevel(const DFSTreeNode* node) const;

                void setConfiguration(unsigned int config);
                unsigned int getConfiguration() const;

                void setConfigRefAtoms(const Atom* ref1, const Atom* ref2);
                const Atom* const* getConfigRefAtoms() const;
                
                void setVisited(bool vis);
                bool wasVisited() const;
                
                void writeBondSymbol(std::ostream&) const;
                
              private:
                SMILESDataWriter&     writer;
                const MolecularGraph* molGraph;
                const Bond*           bond;
                DFSTreeNode*          nodes[2];
                std::size_t           ringClosureNumber;
                char                  direction;
                unsigned int          config;
                const Atom*           configRefAtoms[2];
                bool                  visited;
            };

            class DFSTreeNode
            {

              public:
                typedef std::shared_ptr<DFSTreeNode> SharedPointer;

                DFSTreeNode(SMILESDataWriter&);

                void clear();

                void setAtom(const Atom*);
                void setMolGraph(const MolecularGraph*);

                const Atom* getAtom() const;

                void setLexicalOrder(std::size_t);
                std::size_t getLexicalOrder() const;

                void  setParentEdge(DFSTreeEdge*);
                DFSTreeEdge* getParentEdge() const;

                void addChildEdge(DFSTreeEdge*);
                void addRingClosureInEdge(DFSTreeEdge*);
                void addRingClosureOutEdge(DFSTreeEdge*);

                EdgeIterator getChildEdgesBegin();
                EdgeIterator getChildEdgesEnd();
                
                EdgeIterator getRingClosureInEdgesBegin();
                EdgeIterator getRingClosureInEdgesEnd();

                EdgeIterator getRingClosureOutEdgesBegin();
                EdgeIterator getRingClosureOutEdgesEnd();

                EdgeIterator begin();
                EdgeIterator end();

                void hasDirEdge(bool has);
                bool hasDirEdge() const;
                
                void setStereoBondEdge(DFSTreeEdge* edge);
                DFSTreeEdge* getStereoBondEdge() const;
                
                void generateSMILES(std::ostream&) const;

              private:
                void collectEdges();
                
                void writeAtomString(std::ostream&) const;
                void writeRingClosures(std::ostream&) const;
                void writeChildNodes(std::ostream&) const;

                void writeIsotope(std::ostream&, std::size_t) const;
                void writeAtomSymbol(std::ostream&, unsigned int, bool) const;
                void writeAtomStereo(std::ostream&, int) const;
                void writeHCount(std::ostream&, std::size_t) const;
                void writeCharge(std::ostream&, long) const;
                void writeReactionAtomMappingID(std::ostream&, std::size_t) const;
                void writeRingClosureNumber(std::ostream&, const DFSTreeEdge*) const;

                int getStereoParity() const;

                SMILESDataWriter&     writer;
                const MolecularGraph* molGraph;
                const Atom*           atom;
                DFSTreeEdge*          parentEdge;
                EdgeList              childEdges;
                EdgeList              ringClosureInEdges;
                EdgeList              ringClosureOutEdges;
                EdgeList              edges;
                std::size_t           lexicalOrder;
                bool                  dirEdge;
                DFSTreeEdge*          stereoBondEdge;
            };

            typedef std::unique_ptr<CanonicalNumberingCalculator> CanonNumberingCalculatorPtr;
            typedef std::unique_ptr<Fragment>                     FragmentPtr;
            typedef std::vector<const Atom*>                      AtomList;
            typedef std::vector<DFSTreeNode*>                     NodeList;
            typedef std::vector<std::size_t>                      RingClosureNumberStack;
            typedef std::vector<std::string>                      CanonSMILESList;
            typedef Util::ObjectStack<DFSTreeNode>                NodeCache;
            typedef Util::ObjectStack<DFSTreeEdge>                EdgeCache;

            const Base::DataIOBase&     ioBase;
            NodeCache                   nodeCache;
            EdgeCache                   edgeCache;
            NodeList                    componentNodes;
            NodeList                    atomNodeMapping;
            AtomList                    canonAtomList;
            FragmentPtr                 hDepleteMolGraph;
            FragmentPtr                 canonMolGraph;
            CanonNumberingCalculatorPtr canonNumberingCalculator;
            CanonSMILESList             canonSMILESStrings;
            Util::STArray               canonNumbering;
            EdgeList                    stereoBondEdges;
            CtrlParameters              ctrlParameters;
            RingClosureNumberStack      ringClosureNumberStack;
            std::size_t                 highestRingClosureNumber;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_SMILESDATAWRITER_HPP

/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/*
 * Atom2DCoordinatesGenerator.hpp 
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
 * \brief Definition of the class CDPL::Chem::Atom2DCoordinatesGenerator.
 */

#ifndef CDPL_CHEM_ATOM2DCOORDINATESGENERATOR_HPP
#define CDPL_CHEM_ATOM2DCOORDINATESGENERATOR_HPP

#include <cstddef>
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <utility>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Util/ObjectStack.hpp"


namespace CDPL 
{

	namespace Chem
	{
	 
		class Atom;
		class Bond;
		class MolecularGraph;
		class Fragment;

		/**
		 * \addtogroup CDPL_CHEM_2D_STRUCTURE_LAYOUT
		 * @{
		 */

		/**
		 * \brief Atom2DCoordinatesGenerator.
		 */
		class CDPL_CHEM_API Atom2DCoordinatesGenerator 
		{

		public:
			/**
			 * \brief Constructs the \c %Atom2DCoordinatesGenerator instance.
			 */
			Atom2DCoordinatesGenerator();

			/**
			 * \brief Constructs the \c %Atom2DCoordinatesGenerator instance and generates 2D-coordinates for
			 *        the atoms of the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to generate 2D-coordinates.
			 * \param coords An array containing the generated 2D-coordinates. The coordinates
			 *         are stored in the same order as the atoms appear in the atom list of
			 *         the molecular graph (i.e. the coordinates of an atom are accessible via
			 *         its index).
			 */
			Atom2DCoordinatesGenerator(const MolecularGraph& molgraph, Math::Vector2DArray& coords);

			/**
			 * \brief Generates 2D-coordinates for the atoms of the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to generate 2D-coordinates.
			 * \param coords An array containing the generated 2D-coordinates. The coordinates
			 *         are stored in the same order as the atoms appear in the atom list of
			 *         the molecular graph (i.e. the coordinates of an atom are accessible via
			 *         its index).
			 */
			void generate(const MolecularGraph& molgraph, Math::Vector2DArray& coords);

		private:
			class RingInfo
			{

			public:
				void init(const MolecularGraph*, const Fragment&, std::size_t, std::size_t);

				const Fragment& getFragment() const;

				const Util::BitSet& getAtomMask() const;
				const Util::BitSet& getBondMask() const;

				double getPriority() const;
				void setPriority(double);

				std::size_t getSize() const;

			private:
				const Fragment* fragment;
				Util::BitSet    atomMask;
				Util::BitSet    bondMask;
				double          priority;
			};
		
			class LGNode;

			class LGEdge
			{

			public:
				enum Type
				{

					BOND_EDGE,
					SPIRO_EDGE
				};

				void init(const MolecularGraph*, const Atom*, LGNode*, LGNode*);
				void init(const MolecularGraph*, const Bond*, LGNode*, LGNode*);

				const Atom* getSpiroCenter() const;
				const Bond* getBond() const;

				LGNode* otherNode(const LGNode*) const;

				Type getType() const;

				bool hasConfigConstraint() const;
				bool configConstraintFulfilled(const Math::Vector2DArray&) const;

			private:
				bool initConfigInfo();

				const MolecularGraph* molGraph;
				const Atom*           spiroCenter;
				const Bond*           bond;
				LGNode*               node1;
				LGNode*               node2;
				Type                  type;
				bool                  hasConfig;
				unsigned int          configuration;
				const Atom*           configRefAtoms[2];
			};

			typedef std::vector<std::size_t> AtomIndexList;
			typedef std::vector<const Bond*> BondList;
			typedef std::vector<LGNode*> NodeList;

			class LGNode
			{

			public:
				enum Type
				{

					RING_SYS   = 0x1,
					CHAIN_ATOM = 0x2,
					END_ATOM   = 0x3
				};

				enum Direction
				{

					UP,
					DOWN
				};

				virtual ~LGNode() {}

				void init(const MolecularGraph* molgraph);

				virtual void addEdge(const Atom*, const LGEdge*) = 0;

				virtual void getChildNodes(NodeList&) const = 0;

				virtual void init() = 0;

				virtual void createChildLayouts() = 0;

				virtual double getPriority() const = 0;

				virtual std::size_t getChainID() const = 0;

				virtual void layout() = 0;
				virtual bool layout(double, const Math::Vector2D&, std::size_t&, std::size_t, bool) = 0;

				virtual bool layoutChildNodes(std::size_t&, std::size_t, bool) = 0;

				virtual Type getType() const = 0;

				virtual double getAngularDemand(const Atom*) const;

				virtual bool setParentEdge(const LGEdge*, Direction) = 0;

			protected:
				std::size_t countAtomCollisions(const AtomIndexList&, const AtomIndexList&, const Math::Vector2DArray&);
				std::size_t countAtomCollisionsForAtom(std::size_t, const AtomIndexList&, const Math::Vector2DArray&);

				std::size_t countBondCollisions(const BondList&, const BondList&, const Math::Vector2DArray&);
				std::size_t countBondCollisionsForBond(const Bond*, const BondList&, const Math::Vector2DArray&);

				std::size_t countAtomBondCollisions(const AtomIndexList&, const BondList&, const Math::Vector2DArray&);
				std::size_t countBondCollisionsForAtom(std::size_t, const BondList&, const Math::Vector2DArray&);

				std::size_t countBondAtomCollisions(const BondList&, const AtomIndexList&, const Math::Vector2DArray&);
				std::size_t countAtomCollisionsForBond(const Bond*, const AtomIndexList&, const Math::Vector2DArray&);

				bool testAtomBondCollision(std::size_t, const Bond*, const Math::Vector2DArray&);

				struct NodeLayoutInfo
				{

					NodeLayoutInfo(const LGEdge* edge, double angle): edge(edge), angle(angle) {}

					const LGEdge* edge;
					double        angle;
				};

				typedef std::vector<NodeLayoutInfo> NodeLayoutInfoList;
				typedef std::pair<double, double> AngleRange;

				class EdgePriorityGreaterCmpFunc;

				class LinkedNodePriorityLessCmpFunc;
				class LinkedNodePriorityEqualCmpFunc;

				class NodeLayoutInfoListEqualCmpFunc;

				const MolecularGraph* molGraph;
			};

			typedef std::list<RingInfo*> RingInfoList;
			typedef std::vector<const LGEdge*> EdgeList;

			class RingSysNode : public LGNode
			{

			public:
				void init(const MolecularGraph*, const RingInfo*, Math::Vector2DArray&, 
						  AtomIndexList&, BondList&);

				const Util::BitSet& getAtomMask() const;
				const Util::BitSet& getBondMask() const;

				bool containsAtom(std::size_t) const;

				bool addRing(const RingInfo*);

				void addEdge(const Atom*, const LGEdge*);

				void getChildNodes(NodeList&) const;

				void init();

				double getPriority() const;

				std::size_t getChainID() const;

				void layout();
				bool layout(double, const Math::Vector2D&, std::size_t&, std::size_t, bool);

				bool layoutChildNodes(std::size_t&, std::size_t, bool);

				Type getType() const;

				double getAngularDemand(const Atom*) const;

				bool setParentEdge(const LGEdge*, Direction);

			private:
				bool layoutChildNodes(double, double, bool, double, std::size_t&, std::size_t, bool);
				bool layoutChildNodes(std::size_t, std::size_t&, std::size_t, bool);

				void createChildLayouts();
				void createChildLayouts(const Atom*, EdgeList&);

				bool layout(std::size_t, const Math::Vector2D&, double, bool, double, std::size_t&, std::size_t);

				void transformCoords(std::size_t, const Math::Vector2D&, double, bool, double);

				double transformEdgeAngle(double) const;

				void copyCoords();

				void commitAtomAndBondList() const;

				void calcCoords();

				void calcCoordsForRing(const RingInfo*);
				void calcCoordsForRingSegment(const RingInfo*);

				void refineLayout();

				void initSpringLayoutParams();
				void performSpringLayout();

				Math::Vector2D computePartialDerivatives(std::size_t) const;
				Math::Vector2D computePartialDerivative(std::size_t, std::size_t) const;

				bool layoutFinished(bool, double, double&, double&) const;

				void distributeWeightFactors(std::size_t, double, const Math::ULMatrix&);

				void calcFreeSweeps();

				bool getNextRingSegment(const RingInfo*);

				double calcCongestionFactor(const Math::Vector2D&) const;
				double calcCongestionFactor(const Math::Vector2D&, const Util::BitSet&) const;

				typedef std::vector<const RingInfo*> RingInfoList;
				typedef std::list<const RingInfo*> RingLayoutQueue;
				typedef std::map<const Atom*, EdgeList> EdgeListMap;
				typedef std::map<const Atom*, AngleRange> AngleRangeMap;
				typedef std::deque<std::size_t> RingSegment;
				typedef std::vector<std::vector<NodeLayoutInfoList> > NodeLayoutInfoListTable;
				typedef std::vector<std::size_t> LayoutIndexTable;
				typedef std::vector<const Atom*> AtomTable;
				typedef std::vector<Math::Vector2D> EnergyDerivativeTable;
				typedef std::vector<double> WeightFactorTable;

				Util::BitSet             atomMask;
				Util::BitSet             bondMask;
				Util::BitSet             procAtomMask;
				Util::BitSet             tmpBitMask;
				double                   priority;
				RingInfoList             ringList;
				RingLayoutQueue          ringLayoutQueue;
				RingSegment              ringSegment;	
				EdgeListMap              edgeListMap;
				AngleRangeMap            freeSweepMap;
				AtomIndexList            atomList;		
				BondList                 bondList;
				AtomIndexList*           procAtomList;
				BondList*                procBondList;
				Math::Vector2DArray      localCoords;
				Math::Vector2DArray*     outputCoords;
				const LGEdge*            parentEdge;
				const Atom*              parentEdgeAtom;
				EdgeList                 parentEdgeAtomEdges;
				NodeLayoutInfoListTable  childLayouts;
				LayoutIndexTable         childLayoutIndexTable;
				AtomTable                edgeAtomTable;
				Math::Vector2D           parentPos;
				std::size_t              rsysLayoutIndex;
				double                   parentEdgeAngle;
				double                   rsysRotAngle;
				double                   rsysAxisAngle;
				bool                     flipped;
				WeightFactorTable        layoutWeightFactors;
				EnergyDerivativeTable    layoutEnergyDerivatives;
				Math::DMatrix            layoutAtomDistances;
				Math::DMatrix            layoutSpringStrengths;
			};

			class AtomNode : public LGNode
			{

			public:
				void init(const MolecularGraph*, const Atom*, double, Math::Vector2DArray&, AtomIndexList&, BondList&);

				void addEdge(const Atom*, const LGEdge*);

				const Atom* getAtom() const;
				std::size_t getAtomIndex() const;

				void getChildNodes(NodeList&) const;

				void init();

				double getPriority() const;

				std::size_t getChainID() const;

				void setChainID(std::size_t);

				void layout();
				bool layout(double, const Math::Vector2D&, std::size_t&, std::size_t, bool);

				bool layoutChildNodes(std::size_t&, std::size_t, bool);

				Type getType() const;

				bool setParentEdge(const LGEdge*, Direction);

			private:
				struct LayoutParameters
				{

					LayoutParameters(std::size_t num_colls): numCollisions(num_colls) {}

					std::size_t numCollisions;
					double      bondLength; 
					double      edgeAngle; 
				};

				void layout(double, double, const Math::Vector2D&, std::size_t, std::size_t, LayoutParameters&);

				std::size_t getChildNodeTypePattern() const;

				void createChildLayouts();

				void createChildLayoutsD1();
				void createChildLayoutsD2();
				void createChildLayoutsD3();
				void createChildLayoutsD4();
				void createChildLayoutsDN();

				void removeChildLayoutSymmetryDuplicates();

				void removeParentEdge();

				void sortChildEdges();

				typedef std::vector<NodeLayoutInfoList> NodeLayoutInfoListTable;

				const Atom*             atom;
				std::size_t             atomIndex;
				bool                    isHydrogen;
				Type                    type;
				double                  priority;
				std::size_t             chainID;
				AtomIndexList*          procAtomList;
				BondList*               procBondList;
				Math::Vector2DArray*    outputCoords;
				Direction               chainDirection;
				double                  parentEdgeAngle;
				EdgeList                edges;
				const LGEdge*           parentEdge;
				NodeLayoutInfoListTable childLayouts;
				std::size_t             childLayoutIndex;
				Direction               childChainDirections[4];
			};

			typedef std::pair<Math::Vector2D, Math::Vector2D> BoundingBox;
			
			Atom2DCoordinatesGenerator(const Atom2DCoordinatesGenerator&);

			Atom2DCoordinatesGenerator& operator=(const Atom2DCoordinatesGenerator&);

			void init(const MolecularGraph&, Math::Vector2DArray&);

			void extractRingInformation();

			void calcAtomPriorities();
			void calcRingPriorities();

			void layoutComponents(Math::Vector2DArray&);
			void layoutComponent(const Fragment&, Math::Vector2DArray&);

			void alignComponents(Math::Vector2DArray&);

			void moveComponent(const BoundingBox&, double, double, const Fragment&, Math::Vector2DArray&);
			void addPoint(BoundingBox&, const Math::Vector2D&) const;
			void calcBounds(BoundingBox&, const Fragment&, Math::Vector2DArray&) const;

			void createLayoutTree(const Fragment&, Math::Vector2DArray&);
			void createRingSysNodes(const Fragment&, Math::Vector2DArray&);
			void createAtomNodes(const Fragment&, Math::Vector2DArray&);
			void createBondEdges(const Fragment&);
			void createSpiroEdges(const Fragment&);

			void setAtomNodeChainIDs();

			class AtomNode;

			void findLongestNodePath(AtomNode*, const AtomNode*);

			void createBFSNodeList();
			void initNodes() const;

			void layoutNodes();
			bool layoutChildNodes(std::size_t);

			LGEdge* allocEdge(const Atom*, LGNode*, LGNode*);
			LGEdge* allocEdge(const Bond*, LGNode*, LGNode*);

			RingInfo* allocRingInfo(const Fragment&);
			RingSysNode* allocRingSysNode(const RingInfo*, Math::Vector2DArray&);

			AtomNode* allocAtomNode(const Atom*, Math::Vector2DArray&);

  			void freeAllocEdges();
  			void freeAllocRingInfos();
  			void freeAllocRingSysNodes();
  			void freeAllocAtomNodes();

			typedef std::vector<AtomNode*> AtomNodeList;
			typedef std::vector<std::size_t> AtomPriorityTable;
			typedef Util::ObjectStack<RingInfo> RingInfoCache;
			typedef Util::ObjectStack<RingSysNode> RingSysNodeCache;
			typedef Util::ObjectStack<AtomNode> AtomNodeCache;
			typedef Util::ObjectStack<LGEdge> EdgeCache;
			typedef std::vector<RingSysNode*> RingSysNodeList;

			const MolecularGraph* molGraph;
			RingInfoCache         ringInfoCache;
			RingSysNodeCache      ringSysNodeCache;
			AtomNodeCache         atomNodeCache;
			EdgeCache             edgeCache;
			EdgeList              edgeList;
			RingInfoList          ringList;
			RingSysNodeList       ringSysNodeList;
			AtomNodeList          atomNodeList;
			RingInfoList          tmpRingList;
			NodeList              bfsNodeList;
			AtomNodeList          atomNodeTable;
			AtomNodeList          longestAtomNodePath;
			AtomNodeList          currAtomNodePath;
			AtomIndexList         procAtomList;
			BondList              procBondList;
			Util::BitSet          atomMask;
			Util::BitSet          ringAtomMask;
			Util::BitSet          tmpBitMask;
			AtomPriorityTable     atomPriorityTable;
			std::size_t           numAtoms;
			std::size_t           numBonds;
			bool                  strictLayoutGeometry;
			std::size_t           numLayoutCollisions;
			std::size_t           maxNumLayoutCollisions;
			std::size_t           backtrackingCount;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_ATOM2DCOORDINATESGENERATOR_HPP

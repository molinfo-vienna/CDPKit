/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/*
 * Hydrogen3DCoordinatesGenerator.hpp 
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
 * \brief Definition of the class CDPL::Chem::Hydrogen3DCoordinatesGenerator.
 */

#ifndef CDPL_CHEM_HYDROGEN3DCOORDINATESGENERATOR_HPP
#define CDPL_CHEM_HYDROGEN3DCOORDINATESGENERATOR_HPP

#include <cstddef>
#include <vector>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunctionWrapper.hpp"
#include "CDPL/Chem/AtomPredicateWrapper.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Math/KabschAlgorithm.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

	namespace Chem
	{
	 	
		class MolecularGraph;
		class Atom;

		/**
		 * \addtogroup CDPL_CHEM_3D_COORDINATES_GENERATION
		 * @{
		 */

		/**
		 * \brief Hydrogen3DCoordinatesGenerator.
		 */
		class CDPL_CHEM_API Hydrogen3DCoordinatesGenerator 
		{

		public:
			/**
			 * \brief Constructs the \c %Hydrogen3DCoordinatesGenerator instance.
			 */
			Hydrogen3DCoordinatesGenerator();

			/**
			 * \brief Constructs the \c %Hydrogen3DCoordinatesGenerator instance and generates 3D-coordinates for
			 *        the hydrogen atoms of the molecular graph \a molgraph.
			 *
			 * The generated coordinates can be retrieved by a call to getResult().
			 *
			 * \param molgraph The molecular graph for which to generate 3D-coordinates.
			 * \param coords An array containing the heavy atom and generated hydrogen 3D-coordinates. The coordinates
			 *         are stored in the same order as the atoms appear in the atom list of
			 *         the molecular graph (i.e. the coordinates of an atom are accessible via
			 *         its index).
			 * \param undef_only Specifies whether or not to recalculate already defined hydrogen atom coordinates.
			 */
			Hydrogen3DCoordinatesGenerator(const MolecularGraph& molgraph, Math::Vector3DArray& coords, bool undef_only = true);

			/**
			 * \brief Allows to specify whether already defined hydrogen atom coordinates have to be recalculated or are left unchanged.
			 * \param undef_only \c true if already defined hydrogen atom coordinates have to be left unchanged, and \c false otherwise.
			 * \note The default setting is to calculate coordinates only for hydrogens with not yet defined positions.
			 */
			void undefinedOnly(bool undef_only);
			
			/**
			 * \brief Tells whether already defined hydrogen atom coordinates are recalculated or left unchanged.
			 * \return \c true if already defined hydrogen atom coordinates are left unchanged, and \c false otherwise.
			 */
			bool undefinedOnly() const;

			/**
			 * \brief Specifies a function that tells whether 3D coordinates are available for it's argument atom.
			 * \param func The atom 3D coordinates check function.
			 */
			void setAtom3DCoordinatesCheckFunction(const AtomPredicate& func);

			/**
			 * \brief Returns the function that was registered to determine whether for a given atom 3D coordinates are available.
			 * \return The registered atom 3D coordinates check function.
			 */
			const AtomPredicate& getAtom3DCoordinatesCheckFunction() const;

			/**
			 * \brief Specifies a function for the retrieval of atom 3D-coordinates.
			 * \param func The atom 3D-coordinates function.
			 */
			void setAtom3DCoordinatesFunction(const Atom3DCoordinatesFunction& func);

			/**
			 * \brief Returns the function that was registered for the retrieval of atom 3D-coordinates.
			 * \return The registered atom 3D-coordinates function.
			 */
			const Atom3DCoordinatesFunction& getAtom3DCoordinatesFunction() const;

			void setup(const MolecularGraph& molgraph);

			/**
			 * \brief Generates 3D-coordinates for the hydrogen atoms of the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to generate 3D-coordinates.
			 * \param coords An array containing the heavy atom and generated hydrogen 3D-coordinates. The coordinates
			 *         are stored in the same order as the atoms appear in the atom list of
			 *         the molecular graph (i.e. the coordinates of an atom are accessible via
			 *         its index).
			 * \paran init_coords If \false, defined atom coordinates are already present in \a coords and thus won't get assigned again.
			 */
			void generate(const MolecularGraph& molgraph, Math::Vector3DArray& coords, bool init_coords = true);

			void generate(Math::Vector3DArray& coords, bool init_coords = true);

		private:
			typedef std::vector<std::size_t> AtomIndexList;
		
			void assignCoordinates(Math::Vector3DArray&, bool init_coords);
			void assignDiatomicMolCoords(const Atom&, std::size_t, Math::Vector3DArray&);
			void assignLinearCoords(const Atom&, std::size_t, std::size_t, Math::Vector3DArray&);
			void assignTrigonalPlanarCoords(const Atom&, std::size_t, std::size_t, Math::Vector3DArray&);
			void assignTetrahedralCoords(const Atom&, std::size_t, std::size_t, Math::Vector3DArray&);
			void assignSquarePlanarCoords(const Atom&, std::size_t, std::size_t, Math::Vector3DArray&);
			void assignTrigonalBipyramidalCoords(const Atom&, std::size_t, std::size_t, Math::Vector3DArray&);
			void assignOctahedralCoords(const Atom&, std::size_t, std::size_t, Math::Vector3DArray&);
			void assignPentagonalBipyramidalCoords(const Atom&, std::size_t, std::size_t, Math::Vector3DArray&);
			void assignEvenlyDistributedCoords(const Atom&, std::size_t, std::size_t, Math::Vector3DArray&);

			void assignTemplateCoords(const Atom&, std::size_t, std::size_t, 
									  std::size_t, const Math::Vector3D[], const std::size_t*, 
									  Math::Vector3DArray&);

			std::size_t getConnectedAtoms(const Atom&, AtomIndexList&);
			bool getConnectedAtomWithCoords(std::size_t, const Atom&, std::size_t&) const;

			double getHydrogenBondLength(const Atom&) const;

			unsigned int getHybridizationState(const Atom&, std::size_t) const;

			void buildOrthogonalBasis(const Math::Vector3D&, const Math::Vector3D&, 
									  Math::Matrix3D&, bool) const;
			void getRotationReferenceVector(const Atom&, std::size_t, std::size_t, std::size_t, 
											Math::Vector3D&, Math::Vector3DArray&) const;
			void getPerpendicularVector(const Math::Vector3D&, Math::Vector3D&) const;
			
			typedef std::vector<Math::Vector3D> DynamicPointArray;
			
			const MolecularGraph*          molGraph;
			bool                           undefOnly;
			Atom3DCoordinatesFunction      coordsFunc;
			AtomPredicate                  hasCoordsFunc;
			Util::BitSet                   defCoordsMask;
			Util::BitSet                   savedCoordsMask;
			AtomIndexList                  centerAtoms;
			AtomIndexList                  conctdAtoms;
			Math::DMatrix                  refPoints;
			Math::DMatrix                  tmpltPoints;
			DynamicPointArray              genPoints;
			Math::KabschAlgorithm<double>  kabschAlgo;
			Util::BitSet                   usedPosMask;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_HYDROGEN3DCOORDINATESGENERATOR_HPP

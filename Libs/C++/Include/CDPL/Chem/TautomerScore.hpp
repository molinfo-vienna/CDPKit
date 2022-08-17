/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TautomerScore.hpp 
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
 * \brief Definition of the class CDPL::Chem::TautomerScore.
 */

#ifndef CDPL_CHEM_TAUTOMERSCORE_HPP
#define CDPL_CHEM_TAUTOMERSCORE_HPP

#include "CDPL/Chem/APIPrefix.hpp"


namespace CDPL 
{

    namespace Chem
    {

		class MolecularGraph;
		class Fragment;
		class Atom;
		class Bond;

		/**
		 * \brief TautomerScore.
		 */
		class CDPL_CHEM_API TautomerScore
		{

		  public:
			TautomerScore();

			TautomerScore(const TautomerScore& ts);

			double operator()(const MolecularGraph& molgraph);

			TautomerScore& operator=(const TautomerScore& ts);

		  private:
			double getAtomTypeScoreIncrement(unsigned int type) const;
			double getExocyclicBondIncrement(const Bond& bond) const;

			std::size_t getUnsaturatedNeighborCount(const Atom& atom, const Bond& bond, const MolecularGraph& molgraph) const;

			bool isLactim(const Fragment& ring, const MolecularGraph& molgraph) const;

			bool hasExocyclicOH(const Atom& atom, const MolecularGraph& molgraph) const;
		};
    }
}

#endif // CDPL_CHEM_TAUTOMERSCORE_HPP

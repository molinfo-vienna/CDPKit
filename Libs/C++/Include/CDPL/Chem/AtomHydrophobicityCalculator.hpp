/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomHydrophobicityCalculator.hpp 
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
 * \brief Definition of the class CDPL::Chem::AtomHydrophobicityCalculator.
 */

#ifndef CDPL_CHEM_ATOMHYDROPHOBICITYCALCULATOR_HPP
#define CDPL_CHEM_ATOMHYDROPHOBICITYCALCULATOR_HPP

#include <vector>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/SubstructureSearch.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunctionWrapper.hpp"
#include "CDPL/Util/Array.hpp"


namespace CDPL 
{

    namespace Chem
    {

	/**
	 * \addtogroup CDPL_CHEM_ATOM_HYDROPHOBICITY
	 * @{
	 */

	/**
	 * \brief AtomHydrophobicityCalculator.
	 * \see [\ref CATA] 
	 */
	class CDPL_CHEM_API AtomHydrophobicityCalculator
	{

	  public:
	    /**
	     * \brief Constructs the \c %AtomHydrophobicityCalculator instance.
	     */
	    AtomHydrophobicityCalculator();
		
	    /**
	     * \brief Constructs a copy of the \c %AtomHydrophobicityCalculator instance \a calculator.
	     * \param calculator The \c %AtomHydrophobicityCalculator to copy.
	     */
	    AtomHydrophobicityCalculator(const AtomHydrophobicityCalculator& calculator);
		
	    /**
	     * \brief Perceives the hydrophobicities of the atoms in the molecular graph a\ molgraph.
	     * \param molgraph The molecular graph for which to perceive the atom hydrophobicities.
	     * \param hyd_table The output vector where to store the atom hydrophobicities.
	     */
	    AtomHydrophobicityCalculator(const MolecularGraph& molgraph, Util::DArray& hyd_table);

	    /**
	     * Destructor.
	     */
	    ~AtomHydrophobicityCalculator();

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

	    /**
	     * \brief Perceives the hydrophobicities of the atoms in the molecular graph a\ molgraph.
	     * \param molgraph The molecular graph for which to perceive the atom hydrophobicities.
	     * \param hyd_table The output vector where to store the atom hydrophobicities.
	     */
	    void calculate(const MolecularGraph& molgraph, Util::DArray& hyd_table);

	    /**
	     * \brief Copies the \c %AtomHydrophobicityCalculator instance \a calculator.
	     * \param calculator The \c %AtomHydrophobicityCalculator to copy.
	     * \return A reference to itself.
	     */
	    AtomHydrophobicityCalculator& operator=(const AtomHydrophobicityCalculator& calculator);

	  private:
	    typedef std::vector<double> DoubleArray;
	    typedef std::vector<Math::Vector3D> CoordsArray;
	    typedef std::vector<SubstructureSearch::SharedPointer> HydPatternSubSearchTable;
	
	    void init(const MolecularGraph& molgraph);

	    void calcHydrophobicities(Util::DArray& atom_hyds);
	    double calcAccessibleSurfaceFactor(const Atom& atom);

	    Atom3DCoordinatesFunction   coordsFunc;
	    const MolecularGraph*       molGraph;
	    HydPatternSubSearchTable    hydSubSearchTable;
	    DoubleArray                 nbrAtomVdWRadii;
	    CoordsArray                 nbrAtomPositions;
	};

	/**
	 * @}
	 */
    }
}

#endif // CDPL_CHEM_ATOMHYDROPHOBICITYCALCULATOR_HPP

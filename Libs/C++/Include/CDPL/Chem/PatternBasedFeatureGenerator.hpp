/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PatternBasedFeatureGenerator.hpp 
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
 * \brief Definition of the class CDPL::Chem::PatternBasedFeatureGenerator.
 */

#ifndef CDPL_CHEM_PATTERNBASEDFEATUREGENERATOR_HPP
#define CDPL_CHEM_PATTERNBASEDFEATUREGENERATOR_HPP

#include <cstddef>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"


namespace CDPL 
{

    namespace Chem
    {

	class SubstructureSearch;
	class Pharmacophore;

	/**
	 * \addtogroup CDPL_CHEM_PHARMACOPHORE_PERCEPTION
	 * @{
	 */

	/**
	 * \brief PatternBasedFeatureGenerator.
	 */
	class CDPL_CHEM_API PatternBasedFeatureGenerator 
	{

	  public:
	    /**
	     * \brief Constructs the \c %PatternBasedFeatureGenerator instance.
	     */
	    PatternBasedFeatureGenerator();
		
	    /**
	     * \brief Perceives pharmacophore features according to the specified include/exclude patterns and adds 
	     *        them to the pharmacophore \a pharm.
	     * \param molgraph The molecular graph for which to perceive the features.
	     * \param pharm The output pharmacophore where the generated features get added.
	     * \return The number of generated features.
	     */
	    std::size_t generate(const MolecularGraph& molgraph, Pharmacophore& pharm);

	  private:
	    /** \cond CDPL_PRIVATE_SECTION_DOC */

	    typedef boost::shared_ptr<SubstructureSearch> SubstructureSearchPtr;
	 
	    void init(const MolecularGraph& molgraph);
	
	    const MolecularGraph*  molGraph;
	    SubstructureSearchPtr  substructSearch;
	   
	    /** \endcond */
	};

	/**
	 * @}
	 */
    }
}

#endif // CDPL_CHEM_PATTERNBASEDFEATUREGENERATOR_HPP
 

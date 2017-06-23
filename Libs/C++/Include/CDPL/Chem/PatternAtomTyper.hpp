/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PatternAtomTyper.hpp 
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
 * \brief Definition of the class CDPL::Chem::PatternAtomTyper.
 */

#ifndef CDPL_CHEM_PATTERNATOMTYPER_HPP
#define CDPL_CHEM_PATTERNATOMTYPER_HPP

#include <cstddef>
#include <vector>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/SubstructureSearch.hpp"


namespace CDPL 
{

    namespace Chem
    {

	class MolecularGraph;

	/**
	 * \addtogroup CDPL_CHEM_ATOM_CLASSIFICATION
	 * @{
	 */

	/**
	 * \brief PatternAtomTyper.
	 */
	class CDPL_CHEM_API PatternAtomTyper
	{

	  public:
	    class Pattern
	    {

	    public:
		Pattern(const MolecularGraph::SharedPointer& ptn_molgraph, std::size_t priority = 0, std::size_t atom_label = 0, 
			bool all_matches = true, bool unique_matches = false):
		    ptnMolGraph(ptn_molgraph), priority(priority), atomLabel(atom_label), allMatches(all_matches), uniqueMatches(unique_matches)
		    {}
		    
		const MolecularGraph::SharedPointer& getStructure() const;

		std::size_t getPriority() const;

		std::size_t getAtomLabel() const;

		bool getAllMatches() const;

		bool getOnlyUniqueMatches() const;

	    private:
		MolecularGraph::SharedPointer ptnMolGraph;
		std::size_t                   priority;
		std::size_t                   atomLabel;
		bool                          allMatches;
		bool                          uniqueMatches;
	    };

	    void addPattern(const MolecularGraph::SharedPointer& ptn_molgraph, std::size_t priority = 0, std::size_t atom_label = 0, 
			    bool all_matches = true, bool unique_matches = false);

	    void addPattern(const Pattern& ptn);

	    const Pattern& getPattern() const;

	    void removePattern(std::size_t idx);

	    void clear();

	    std::size_t getNumPatterns() const;

	    std::size_t getAtomLabel(std::size_t idx) const;

	    std::size_t getMatchingPatternID(std::size_t idx) const;

	    void execute(const MolecularGraph& molgraph);

	  private:
	    typedef std::vector<Pattern> PatternList;
	    typedef std::vector<std::size_t> SizeTypeArray;

	    PatternList        patterns;
	    SizeTypeArray      atomLabeling;
	    SizeTypeArray      matchingPatternIDs;
	    SubstructureSearch substructSearch;
	};

	/**
	 * @}
	 */
    }
}

#endif // CDPL_CHEM_PATTERNATOMTYPER_HPP

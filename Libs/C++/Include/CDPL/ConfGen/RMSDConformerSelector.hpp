/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RMSDConformerSelector.hpp 
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
 * \brief Definition of the class CDPL::ConfGen::RMSDConformerSelector.
 */

#ifndef CDPL_CONFGEN_RMSDCONFORMERSELECTOR_HPP
#define CDPL_CONFGEN_RMSDCONFORMERSELECTOR_HPP

#include <cstddef>
#include <vector>

#include <boost/iterator/indirect_iterator.hpp>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/ConformerData.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

    namespace ConfGen 
    {

	/**
	 * \addtogroup CDPL_CONFGEN_HELPERS
	 * @{
	 */

	class CDPL_CONFGEN_API RMSDConformerSelector
	{

	    typedef std::vector<const ConformerData*> ConformerList;

	  public:
	    typedef boost::indirect_iterator<ConformerList::const_iterator, const ConformerData> ConstConformerIterator;

	    RMSDConformerSelector();
	
	    void setMinRMSD(double min_rmsd);

	    double getMinRMSD() const;
	    
	    void setup(const Chem::MolecularGraph& molgraph, const Util::BitSet& atom_mask, 
		       const Util::BitSet& stable_config_atom_mask);

	    bool process(const ConformerData& conf_data);

	    void clearConformers();

	    std::size_t getNumConformers() const;

	    const ConformerData& getConformer(std::size_t idx) const;

	    ConstConformerIterator getConformersBegin() const;

	    ConstConformerIterator getConformersEnd() const;

	  private:
	    RMSDConformerSelector(const RMSDConformerSelector&);

	    RMSDConformerSelector& operator=(const RMSDConformerSelector&);

	    Chem::Fragment  symMappingMolGraph;
	    ConformerList   selectedConfs;
	    double          minRMSD;
	};

	/**
	 * @}
	 */
    }
}

#endif // CDPL_CONFGEN_RMSDCONFORMERSELECTOR_HPP

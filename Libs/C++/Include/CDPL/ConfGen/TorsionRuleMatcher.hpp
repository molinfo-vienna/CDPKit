/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TorsionRuleMatcher.hpp 
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
 * \brief Definition of the class CDPL::ConfGen::TorsionRuleMatcher.
 */

#ifndef CDPL_CONFGEN_TORSIONRULEMATCHER_HPP
#define CDPL_CONFGEN_TORSIONRULEMATCHER_HPP

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/TorsionLibrary.hpp"
#include "CDPL/Chem/SubstructureSearch.hpp"


namespace CDPL 
{

    namespace ConfGen 
    {

		class TorsionRuleMapping;

		/**
		 * \addtogroup CDPL_CONFGEN_HELPERS
		 * @{
		 */

		class CDPL_CONFGEN_API TorsionRuleMatcher
		{

		  public:
			TorsionRuleMatcher();

			TorsionRuleMatcher(const TorsionLibrary::SharedPointer& lib);

			void reportUniqueMappingsOnly(bool unique);

			bool onlyUniqueMappingsReported() const;

			void reportAllRuleMappings(bool all);

			bool allRuleMappingsReported() const;

			void stopAtFirstMatchingRule(bool stop);

			bool stoppedAtFirstMatchingRule() const;

			void setTorsionLibrary(const TorsionLibrary::SharedPointer& lib);

			const TorsionLibrary::SharedPointer& getTorsionLibrary() const;

			bool findMatches(const Chem::Bond& bond, const Chem::MolecularGraph& molgraph, 
							 TorsionRuleMapping& rule_map, bool append = false);

		  private:
			bool findMatchingRules(const TorsionCategory& tor_cat, const Chem::Bond& bond, 
								   const Chem::MolecularGraph& molgraph, TorsionRuleMapping& rule_map);
			bool getRuleMatches(const TorsionRule& rule, const Chem::Bond& bond, const Chem::MolecularGraph& molgraph, 
								TorsionRuleMapping& rule_map);
			bool matchesCategory(const TorsionCategory& tor_cat, const Chem::Bond& bond, 
								 const Chem::MolecularGraph& molgraph);

			void outputRuleMatch(const Chem::AtomBondMapping& ab_mapping, const Chem::Bond& bond, 
								 const TorsionRule& rule, TorsionRuleMapping& rule_map) const;

			std::size_t getCentralBondIndex(const Chem::MolecularGraph& ptn) const;

			TorsionLibrary::SharedPointer torLib;
			Chem::SubstructureSearch      subSearch;
			bool                          uniqueMappingsOnly;
			bool                          stopAtFirstRule;
		};
    
		/**
		 * @}
		 */
    }
}

#endif // CDPL_CONFGEN_TORSIONRULEMATCHER_HPP

/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TautomerGenerator.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::Chem::TautomerGenerator.
 */

#ifndef CDPL_CHEM_TAUTOMERGENERATOR_HPP
#define CDPL_CHEM_TAUTOMERGENERATOR_HPP

#include <vector>
#include <cstddef>
#include <cstdint>
#include <unordered_set>
#include <array>
#include <memory>

#include <boost/function.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/TautomerizationRule.hpp"
#include "CDPL/Chem/HashCodeCalculator.hpp"
#include "CDPL/Util/ObjectPool.hpp"


namespace CDPL 
{

    namespace Chem
    {

		/**
		 * \brief TautomerGenerator.
		 */
		class CDPL_CHEM_API TautomerGenerator 
		{

		  public:
			enum Mode 
			{

			    TOPOLOGICALLY_UNIQUE,
				GEOMETRICALLY_UNIQUE,
				EXHAUSTIVE
			};

			typedef std::shared_ptr<TautomerGenerator> SharedPointer;

			typedef boost::function1<bool, MolecularGraph&> CallbackFunction;
			typedef boost::function1<void, MolecularGraph&> CustomSetupFunction;

			/**
			 * \brief Constructs the \c %TautomerGenerator instance.
			 */
			TautomerGenerator();

			TautomerGenerator(const TautomerGenerator& gen);

			virtual ~TautomerGenerator() {}

			TautomerGenerator& operator=(const TautomerGenerator& gen);

			void addTautomerizationRule(const TautomerizationRule::SharedPointer& rule);

			const TautomerizationRule::SharedPointer& getTautomerizationRule(std::size_t idx) const;

			void removeTautomerizationRule(std::size_t idx);

			std::size_t getNumTautomerizationRules() const;

			void setCallbackFunction(const CallbackFunction& func);

			const CallbackFunction& getCallbackFunction() const;

			void setMode(Mode mode);

			Mode getMode() const;

			void regardStereochemistry(bool regard);

			bool stereochemistryRegarded() const;

			void regardIsotopes(bool regard);

			bool isotopesRegarded() const;

			void setCustomSetupFunction(const CustomSetupFunction& func);

			/**
			 * \brief Generates all unique tautomers of the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to generate the tautomers.
			 */
			void generate(const MolecularGraph& molgraph);

		  private:
			typedef Util::ObjectPool<BasicMolecule> MoleculeCache;
			typedef MoleculeCache::SharedObjectPointer MoleculePtr;

			bool init(const MolecularGraph& molgraph);
			void initHashCalculator();

			MoleculePtr copyInputMolGraph(const MolecularGraph& molgraph);

			void extractStereoCenters(const MolecularGraph& molgraph);
			void extractAtomStereoCenters(const MolecularGraph& molgraph);
			void extractBondStereoCenters(const MolecularGraph& molgraph);

			bool addNewTautomer(const MoleculePtr& mol);

			std::uint64_t calcTautomerHashCode(const BasicMolecule& tautomer);
		
			typedef std::array<std::size_t, 3> BondDescriptor;
			typedef std::vector<MoleculePtr> MoleculeList;
			typedef std::vector<TautomerizationRule::SharedPointer> TautRuleList;
			typedef std::vector<BondDescriptor> BondDescrArray;
			typedef std::vector<std::size_t> SizeTArray;
			typedef std::unordered_set<std::uint64_t> HashCodeSet;
			typedef std::array<std::size_t, 6> StereoCenter;
			typedef std::vector<StereoCenter> StereoCenterList;

			MoleculeCache         molCache;
			CallbackFunction      callbackFunc;
			Mode                  mode;
			bool                  regStereo;
			bool                  regIsotopes;
			CustomSetupFunction   customSetupFunc;
			TautRuleList          tautRules;
			MoleculeList          currGeneration;
			MoleculeList          nextGeneration;
			StereoCenterList      atomStereoCenters;
			StereoCenterList      bondStereoCenters;
			HashCodeSet           tautHashCodes;
			HashCodeCalculator    hashCalculator;
			BondDescrArray        tautomerBonds;
			SizeTArray            shaInput;
		};
    }
}

#endif // CDPL_CHEM_TAUTOMERGENERATOR_HPP

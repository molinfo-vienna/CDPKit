/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TautomerGenerator.hpp 
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
 * \brief Definition of the class CDPL::Chem::TautomerGenerator.
 */

#ifndef CDPL_CHEM_TAUTOMERGENERATOR_HPP
#define CDPL_CHEM_TAUTOMERGENERATOR_HPP

#include <vector>
#include <cstddef>

#include <boost/function.hpp>
#include <boost/unordered_set.hpp>
#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/TautomerizationRule.hpp"
#include "CDPL/Chem/HashCodeCalculator.hpp"
#include "CDPL/Base/IntegerTypes.hpp"


namespace CDPL 
{

    namespace Chem
    {

		/**
		 * \addtogroup CDPL_CHEM_TAUTOMER_GENERATION
		 * @{
		 */

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

			typedef boost::shared_ptr<TautomerGenerator> SharedPointer;

			typedef boost::function1<bool, const MolecularGraph&> CallbackFunction;

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

			/**
			 * \brief Generates all unique tautomers of the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to generate the tautomers.
			 */
			void generate(const MolecularGraph& molgraph);

		  private:
			class SafeMoleculePtr;

			bool init(const MolecularGraph& molgraph);
			void initHashCalculator();

			bool addNewTautomer(Molecule* mol);

			Base::uint64 calcTautomerHashCode(const Molecule& tautomer);

			void freeCurrentGenTautomers();
			void freeNextGenTautomers();

			Molecule* allocMolecule();
			
			void freeMolecule(Molecule* mol);

			typedef boost::array<std::size_t, 3> BondDescriptor;
			typedef std::vector<Molecule*> MoleculeList;
			typedef std::vector<Molecule::SharedPointer> AllocMoleculeList;
			typedef std::vector<TautomerizationRule::SharedPointer> TautRuleList;
			typedef std::vector<BondDescriptor> BondDescrArray;
			typedef std::vector<std::size_t> SizeTArray;
			typedef boost::unordered_set<Base::uint64> HashCodeSet;

			CallbackFunction   callbackFunc;
			Mode               mode;
			bool               regStereo;
			bool               regIsotopes;
			TautRuleList       tautRules;
			MoleculeList       currGeneration;
			MoleculeList       nextGeneration;
			MoleculeList       freeMolecules;
			AllocMoleculeList  allocMolecules;
			HashCodeSet        tautHashCodes;
			HashCodeCalculator hashCalculator;
			BondDescrArray     tautomerBonds;
			SizeTArray         shaInput;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CHEM_TAUTOMERGENERATOR_HPP

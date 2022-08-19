/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomMatchExpressionStringFunction.cpp 
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


#include "StaticInit.hpp"

#include <cassert>
#include <locale>
#include <sstream>

#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>

#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/SMARTSMolecularGraphWriter.hpp"
#include "CDPL/Chem/AtomMatchConstraint.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/HybridizationState.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"


using namespace CDPL; 


namespace
{

	const std::string LEFT_LIST_DELIMITER              = "(";
	const std::string RIGHT_LIST_DELIMITER             = ")";

	const std::string LEFT_ATOM_ENV_STRING_DELIMITER   = "$(";
	const std::string RIGHT_ATOM_ENV_STRING_DELIMITER  = ")";

	const std::string NOT_OPERATOR                     = "!";
	const std::string LESS_OPERATOR                    = "<";
	const std::string LESS_EQUAL_OPERATOR              = "<=";
	const std::string GREATER_OPERATOR                 = ">";
	const std::string GREATER_EQUAL_OPERATOR           = ">=";

	const std::string AND_LIST_SEPARATOR               = ";";
	const std::string OR_LIST_SEPARATOR                = ",";

	const std::string ATOMIC_NUMBER_PREFIX             = "#";
	const std::string UNSATURATION_FLAG_SYMBOL         = "u";
	const std::string AROMATICITY_FLAG_SYMBOL          = "a";
	const std::string HYBRIDIZATION_STATE_SYMBOL       = "^";
	const std::string RING_FLAG_SYMBOL                 = "r";
	const std::string ZERO_CHARGE_SYMBOL               = "+0";
	const std::string RING_BOND_COUNT_SYMBOL           = "x";
	const std::string TOTAL_H_COUNT_SYMBOL             = "H";
	const std::string IMPLICIT_H_COUNT_SYMBOL          = "h";
	const std::string EXPLICIT_H_COUNT_SYMBOL          = "!h";
	const std::string TOTAL_BOND_COUNT_SYMBOL          = "X";
	const std::string EXPLICIT_BOND_COUNT_SYMBOL       = "D";
	const std::string HEAVY_BOND_COUNT_SYMBOL          = "!H";
	const std::string TOTAL_VALENCE_SYMBOL             = "v";
	const std::string EXPLICIT_VALENCE_SYMBOL          = "V";
	const std::string ISOTOPE_SYMBOL                   = "";
	const std::string SSSR_RING_COUNT_SYMBOL           = "R";
	const std::string SSSR_RING_SIZE_SYMBOL            = "r";
	const std::string CONFIGURATION_SYMBOL             = "@";
	const std::string NO_CONFIGURATION_SYMBOL          = "0";
	const std::string ODD_CONFIGURATION_SYMBOL         = "";
	const std::string EVEN_CONFIGURATION_SYMBOL        = "@";
	const std::string EITHER_CONFIGURATION_SYMBOL      = "?";
	const std::string UNKNOWN_ATOM_TYPE_SYMBOL         = "?";
	const std::string HYB_STATE_SP_SYMBOL              = "sp";
	const std::string HYB_STATE_SP2_SYMBOL             = "sp2";
	const std::string HYB_STATE_SP3_SYMBOL             = "sp3";
	const std::string HYB_STATE_DP_SYMBOL              = "dp";
	const std::string HYB_STATE_SD3_SYMBOL             = "sd3";
	const std::string HYB_STATE_SP2D_SYMBOL            = "sp2d";
	const std::string HYB_STATE_SP3D_SYMBOL            = "sp3d";
	const std::string HYB_STATE_SP3D2_SYMBOL           = "sp3d2";
	const std::string HYB_STATE_SP3D3_SYMBOL           = "sp3d3";


	const Chem::MatchConstraint* findMatchConstraint(const Chem::MatchConstraintList& constr_list,
													 unsigned int constr_id, Chem::MatchConstraint::Relation relation)
	{
		using namespace Chem;

		MatchConstraintList::ConstElementIterator constr_end = constr_list.getElementsEnd();
				
		for (MatchConstraintList::ConstElementIterator it = constr_list.getElementsBegin(); it != constr_end; ++it) {
			const MatchConstraint& constraint = *it;

			if (constraint.getID() == constr_id && constraint.getRelation() == relation)
				return &constraint;
		}

		return 0;
	}

	void appendOperatorSymbol(const Chem::MatchConstraint& constraint, std::string& str)
	{
		using namespace Chem;

		switch (constraint.getRelation()) {

			case MatchConstraint::LESS:
				str.append(LESS_OPERATOR);
				return;

			case MatchConstraint::GREATER:
				str.append(GREATER_OPERATOR);
				return;

			case MatchConstraint::LESS_OR_EQUAL:
				str.append(LESS_EQUAL_OPERATOR);
				return;

			case MatchConstraint::GREATER_OR_EQUAL:
				str.append(GREATER_EQUAL_OPERATOR);
				return;

			case MatchConstraint::NOT_EQUAL:
				str.append(NOT_OPERATOR);
				return;

			case MatchConstraint::EQUAL:
			default:
				return;
		}
	}

	template <typename PropFunc>
	void createIntegralPropertyExpressionString(const Chem::Atom& atom, const Chem::MatchConstraint& constraint,
												std::string& expr_str, const std::string& constr_sym,
												const PropFunc& propFunc)
	{
		expr_str.append(constr_sym);

		appendOperatorSymbol(constraint, expr_str);

		std::size_t prop_value;

		if (!constraint.hasValue())
			prop_value = propFunc(atom);
		else
			prop_value = constraint.getValue<std::size_t>();

		expr_str.append(boost::lexical_cast<std::string>(prop_value));
	}

	template <typename PropFunc>
	void createBooleanPropertyExpressionString(const Chem::Atom& atom, const Chem::MatchConstraint& constraint,
											   std::string& expr_str, const std::string& constr_sym,
											   const PropFunc& propFunc)
	{
		using namespace Chem;

		if (constraint.getRelation() != MatchConstraint::EQUAL && 
			constraint.getRelation() != MatchConstraint::NOT_EQUAL)
			return;

		bool not_operator = false;

		if (constraint.getRelation() == MatchConstraint::NOT_EQUAL) 
			not_operator = !not_operator;

		bool flag;

		if (!constraint.hasValue())
			flag = propFunc(atom);
		else
			flag = constraint.getValue<bool>();

		if (!flag) 
			not_operator = !not_operator;

		if (not_operator)
			expr_str.append(NOT_OPERATOR);

		expr_str.append(constr_sym);
	}

	void writeAtomicNumber(unsigned int atomic_no, bool not_prefix, std::string& str)
	{
		if (not_prefix)
			str.append(NOT_OPERATOR);

		str.append(ATOMIC_NUMBER_PREFIX);
		str.append(boost::lexical_cast<std::string>(atomic_no));
	}
	
	void createExpressionString(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph,
								const Chem::MatchConstraintList& constr_list, std::string& expr_list_str, bool root);

	void createConstraintListExpressionString(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, 
											  const Chem::MatchConstraint& constraint, std::string& expr_list_str)
	{
		using namespace Chem;

		if (constraint.getRelation() != MatchConstraint::EQUAL && 
			constraint.getRelation() != MatchConstraint::NOT_EQUAL)
			return;
	
		const MatchConstraintList& constr_list = 
			*constraint.getValue<MatchConstraintList::SharedPointer>();

		createExpressionString(atom, molgraph, constr_list, expr_list_str, false);

		if (!expr_list_str.empty() && constraint.getRelation() == MatchConstraint::NOT_EQUAL)
			expr_list_str.insert(0, NOT_OPERATOR);
	}

	void createAtomTypeExpressionString(const Chem::Atom& atom, const Chem::MatchConstraint* type_constraint,
										const Chem::MatchConstraint* arom_constraint, std::string& expr_str)
	{
		using namespace Chem;

		if (type_constraint && type_constraint->getRelation() != MatchConstraint::EQUAL &&
			type_constraint->getRelation() != MatchConstraint::NOT_EQUAL)
			type_constraint = 0;

		if (arom_constraint && arom_constraint->getRelation() != MatchConstraint::EQUAL &&
			arom_constraint->getRelation() != MatchConstraint::NOT_EQUAL)
			arom_constraint = 0;

		if (!type_constraint && !arom_constraint)
			return;

		unsigned int atom_type = AtomType::UNKNOWN;

		if (type_constraint) {
			if (!type_constraint->hasValue())
				atom_type = getType(atom);
			else
				atom_type = type_constraint->getValue<unsigned int>();

			if (atom_type == AtomType::UNKNOWN || atom_type > AtomType::MAX_TYPE) {
				if (!arom_constraint)
					return;

				type_constraint = 0;

			} else if (!arom_constraint) {
				if (atom_type <= AtomType::MAX_ATOMIC_NO) {
					writeAtomicNumber(atom_type, type_constraint->getRelation() == MatchConstraint::NOT_EQUAL, expr_str);

				} else {
					const std::string& symbol = AtomDictionary::getSymbol(atom_type);

					assert(!symbol.empty());

					if (type_constraint->getRelation() == MatchConstraint::NOT_EQUAL)
						expr_str.append(NOT_OPERATOR);

					expr_str.append(symbol);
				}

				return;
			}
		}

		assert(arom_constraint);

		bool write_arom_sym;

		if (!arom_constraint->hasValue())
			write_arom_sym = getAromaticityFlag(atom);
		else
			write_arom_sym = arom_constraint->getValue<bool>();

		if (arom_constraint->getRelation() == MatchConstraint::NOT_EQUAL)
			write_arom_sym = !write_arom_sym;

		if (!type_constraint) {
			expr_str.append(write_arom_sym ? AROMATICITY_FLAG_SYMBOL : NOT_OPERATOR + AROMATICITY_FLAG_SYMBOL);
			return;
		}

		if (type_constraint->getRelation() == MatchConstraint::NOT_EQUAL) {
			if (atom_type <= AtomType::MAX_ATOMIC_NO) {
				writeAtomicNumber(atom_type, true, expr_str);
				expr_str.append(write_arom_sym ? AROMATICITY_FLAG_SYMBOL : NOT_OPERATOR + AROMATICITY_FLAG_SYMBOL);

			} else {
				const std::string& symbol = AtomDictionary::getSymbol(atom_type);

				assert(!symbol.empty());

				expr_str.append(write_arom_sym ? AROMATICITY_FLAG_SYMBOL : NOT_OPERATOR + AROMATICITY_FLAG_SYMBOL);			
				expr_str.append(NOT_OPERATOR);
				expr_str.append(symbol);
			}

			return;
		}

		const std::string& symbol = AtomDictionary::getSymbol(atom_type);

		assert(!symbol.empty());
	
		if (atom_type <= AtomType::MAX_ATOMIC_NO) {
			if (!write_arom_sym)
				expr_str.append(symbol);
			else 
				for (std::size_t i = 0; i < symbol.size(); i++)
					expr_str.push_back(std::tolower(symbol[i], std::locale::classic()));
		} else {
			expr_str.append(write_arom_sym ? AROMATICITY_FLAG_SYMBOL : NOT_OPERATOR + AROMATICITY_FLAG_SYMBOL);
			expr_str.append(symbol);
		}
	}

	bool createAtomTypeExpressionString(const Chem::Atom& atom, const Chem::MatchConstraintList& constr_list, 
										std::string& expr_str)
	{
		using namespace Chem;

		if (constr_list.getSize() != 2)
			return false;

		const MatchConstraint* arom_constraint = 
			findMatchConstraint(constr_list, AtomMatchConstraint::AROMATICITY, MatchConstraint::EQUAL);

		if (!arom_constraint)
			arom_constraint = findMatchConstraint(constr_list, AtomMatchConstraint::AROMATICITY, MatchConstraint::NOT_EQUAL);

		if (!arom_constraint)
			return false;

		const MatchConstraint* type_constraint = findMatchConstraint(constr_list, AtomMatchConstraint::TYPE, MatchConstraint::EQUAL);

		if (!type_constraint)
			type_constraint = findMatchConstraint(constr_list, AtomMatchConstraint::TYPE, MatchConstraint::NOT_EQUAL);

		if (!type_constraint)
			return false;

		bool aromatic;

		if (!arom_constraint->hasValue())
			aromatic = getAromaticityFlag(atom);
		else
			aromatic = arom_constraint->getValue<bool>();

		if (arom_constraint->getRelation() == MatchConstraint::NOT_EQUAL)
			aromatic = !aromatic;

		bool write_arom_sym = false;
		bool write_not_prefix = false;

		switch (constr_list.getType()) {

			case MatchConstraintList::OR_LIST:
				if (type_constraint->getRelation() != MatchConstraint::NOT_EQUAL)
					return false;

				write_not_prefix = true;
				write_arom_sym = !aromatic;
				break;

			case MatchConstraintList::NOT_OR_LIST:
				if (type_constraint->getRelation() != MatchConstraint::NOT_EQUAL)
					return false;

				write_arom_sym = !aromatic;
				break;

			case MatchConstraintList::AND_LIST:
				if (type_constraint->getRelation() != MatchConstraint::EQUAL)
					return false;

				write_arom_sym = aromatic;
				break;

			case MatchConstraintList::NOT_AND_LIST:
				if (type_constraint->getRelation() != MatchConstraint::EQUAL)
					return false;

				write_not_prefix = true;
				write_arom_sym = aromatic;
				break;

			default:
				return false;
		}

		unsigned int atom_type;

		if (!type_constraint->hasValue())
			atom_type = getType(atom);
		else
			atom_type = type_constraint->getValue<unsigned int>();

		if (atom_type == AtomType::UNKNOWN || atom_type > AtomType::MAX_TYPE)
			return false;

		if (write_not_prefix) {
			if (atom_type > AtomType::MAX_ATOMIC_NO)
				return false;

			expr_str.append(NOT_OPERATOR);
		}
	
		const std::string& symbol = AtomDictionary::getSymbol(atom_type);

		assert(!symbol.empty());
	
		if (atom_type <= AtomType::MAX_ATOMIC_NO) {
			if (!write_arom_sym)
				expr_str.append(symbol);
			else 
				for (std::size_t i = 0; i < symbol.size(); i++)
					expr_str.push_back(std::tolower(symbol[i], std::locale::classic()));
		} else {
			expr_str.append(write_arom_sym ? AROMATICITY_FLAG_SYMBOL : NOT_OPERATOR + AROMATICITY_FLAG_SYMBOL);
			expr_str.append(symbol);
		}

		return true;
	}

	void createConfigurationExpressionString(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph,
											 const Chem::MatchConstraint& constraint, std::string& config_expr_str)
	{
		using namespace Chem;

		if (constraint.getRelation() != MatchConstraint::EQUAL && 
			constraint.getRelation() != MatchConstraint::NOT_EQUAL)
			return;

		unsigned int configuration;

		if (!constraint.hasValue()) {
			const StereoDescriptor& stereo_descr = calcStereoDescriptor(atom, molgraph, 0);

			configuration = stereo_descr.getConfiguration();

			if ((configuration & (AtomConfiguration::R | AtomConfiguration::S)) == 0)
				return;

		} else {
			const StereoDescriptor& stereo_descr = constraint.getValue<StereoDescriptor>();

			configuration = stereo_descr.getConfiguration();
		}

		configuration &= (AtomConfiguration::NONE | AtomConfiguration::R |
						  AtomConfiguration::S | AtomConfiguration::EITHER);

		if (configuration == 0)
			return;

		if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
			config_expr_str.append(NOT_OPERATOR);

		config_expr_str.append(CONFIGURATION_SYMBOL);

		if ((configuration & AtomConfiguration::EITHER) != 0)
			config_expr_str.append(EITHER_CONFIGURATION_SYMBOL);

		if ((configuration & AtomConfiguration::NONE) != 0)
			config_expr_str.append(NO_CONFIGURATION_SYMBOL);

		if ((configuration & AtomConfiguration::S) != 0)
			config_expr_str.append(ODD_CONFIGURATION_SYMBOL);

		if ((configuration & AtomConfiguration::R) != 0)
			config_expr_str.append(EVEN_CONFIGURATION_SYMBOL);
	}
	
	void createHybridizationStateExpressionString(const Chem::Atom& atom, const Chem::MatchConstraint& constraint, std::string& expr_str)
	{
		using namespace Chem;

		if (constraint.getRelation() != MatchConstraint::EQUAL && 
			constraint.getRelation() != MatchConstraint::NOT_EQUAL)
			return;

		unsigned int hyb_state;

		if (!constraint.hasValue()) {
			hyb_state = getHybridizationState(atom);

		} else
			hyb_state = constraint.getValue<unsigned int>();

		const char* sym;

		switch (hyb_state) {

			case HybridizationState::SP:
				sym = HYB_STATE_SP_SYMBOL.c_str();
				break;
		
			case HybridizationState::SP2:
				sym = HYB_STATE_SP2_SYMBOL.c_str();
				break;

			case HybridizationState::SP3:
				sym = HYB_STATE_SP3_SYMBOL.c_str();
				break;

			case HybridizationState::DP:
				sym = HYB_STATE_DP_SYMBOL.c_str();
				break;

			case HybridizationState::SD3:
				sym = HYB_STATE_SD3_SYMBOL.c_str();
				break;

			case HybridizationState::SP2D:
				sym = HYB_STATE_SP2D_SYMBOL.c_str();
				break;

			case HybridizationState::SP3D:
				sym = HYB_STATE_SP3D_SYMBOL.c_str();
				break;

			case HybridizationState::SP3D2:
				sym = HYB_STATE_SP3D2_SYMBOL.c_str();
				break;

			case HybridizationState::SP3D3:
				sym = HYB_STATE_SP3D3_SYMBOL.c_str();
				break;

			default:
				return;
		}

		if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
			expr_str.append(NOT_OPERATOR);

		expr_str.append(sym);
	}

	void createEnvironmentExpressionString(const Chem::MatchConstraint& constraint,
										   std::string& env_expr_str)
	{
		using namespace Chem;

		if (constraint.getRelation() != MatchConstraint::EQUAL && 
			constraint.getRelation() != MatchConstraint::NOT_EQUAL)
			return;

		const Molecule& env_pattern = *constraint.getValue<Molecule::SharedPointer>();

		if (env_pattern.getNumAtoms() == 0)
			return;

		std::ostringstream oss;
		SMARTSMolecularGraphWriter writer(oss);

		writer.write(env_pattern);

		std::string smarts = oss.str();

		if (smarts.empty())
			return;

		if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
			env_expr_str.append(NOT_OPERATOR);

		env_expr_str.append(LEFT_ATOM_ENV_STRING_DELIMITER);
		env_expr_str.append(smarts);
		env_expr_str.append(RIGHT_ATOM_ENV_STRING_DELIMITER);
	}

	void createChargeExpressionString(const Chem::Atom& atom, const Chem::MatchConstraint& constraint,
									  std::string& charge_expr_str)
	{
		using namespace Chem;

		appendOperatorSymbol(constraint, charge_expr_str);

		long charge;

		if (!constraint.hasValue()) 
			charge = getFormalCharge(atom);
		else
			charge = constraint.getValue<long>();

		if (charge == 0) {
			charge_expr_str.append(ZERO_CHARGE_SYMBOL);
			return;
		}

		if (charge > 0) {
			charge_expr_str.push_back('+');

			if (charge > 1)
				charge_expr_str.append(boost::lexical_cast<std::string>(charge));

			return;
		}

		charge_expr_str.push_back('-');

		if (charge < -1)
			charge_expr_str.append(boost::lexical_cast<std::string>(-charge));
	}

	void createSSSRRingSizeExpressionString(const Chem::MatchConstraint& constraint, std::string& expr_str)
	{
		expr_str.append(SSSR_RING_SIZE_SYMBOL);

		appendOperatorSymbol(constraint, expr_str);

		std::size_t rsize = constraint.getValue<std::size_t>();

		expr_str.append(boost::lexical_cast<std::string>(rsize));
	}

	void createExpressionString(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph,
								const Chem::MatchConstraintList& constr_list, std::string& expr_list_str, bool root)
	{
		using namespace Chem;

		if (createAtomTypeExpressionString(atom, constr_list, expr_list_str))
			return;

		std::size_t list_size = 0;
		std::string expr_str;

		bool or_list = (constr_list.getType() == MatchConstraintList::NOT_OR_LIST || 
						constr_list.getType() == MatchConstraintList::OR_LIST);

		MatchConstraintList::ConstElementIterator constr_end = constr_list.getElementsEnd();

		for (MatchConstraintList::ConstElementIterator it = constr_list.getElementsBegin(); it != constr_end; ++it) {
			const MatchConstraint& constraint = *it;

			switch (constraint.getID()) {

				case AtomMatchConstraint::CONSTRAINT_LIST:
					createConstraintListExpressionString(atom, molgraph, constraint, expr_str);
					break;

				case AtomMatchConstraint::ENVIRONMENT:
					createEnvironmentExpressionString(constraint, expr_str);
					break;

				case AtomMatchConstraint::TYPE:
					if (!or_list && (it + 1) != constr_end) {
						const MatchConstraint& next_constraint = *(it + 1);

						if (next_constraint.getID() == AtomMatchConstraint::AROMATICITY) {
							++it;
							createAtomTypeExpressionString(atom, &constraint, &next_constraint, expr_str);
							break;
						}
					} 

					createAtomTypeExpressionString(atom, &constraint, static_cast<const MatchConstraint*>(0),
												   expr_str);
					break;

				case AtomMatchConstraint::AROMATICITY:
					if (!or_list && (it + 1) != constr_end) {
						const MatchConstraint& next_constraint = *(it + 1);

						if (next_constraint.getID() == AtomMatchConstraint::TYPE) {
							++it;
							createAtomTypeExpressionString(atom, &next_constraint, &constraint, expr_str);
							break;
						}
					}

					createAtomTypeExpressionString(atom, static_cast<const MatchConstraint*>(0), &constraint, 
												   expr_str);
					break;

				case AtomMatchConstraint::CHARGE:
					createChargeExpressionString(atom, constraint, expr_str);
					break;

				case AtomMatchConstraint::ISOTOPE:
					createIntegralPropertyExpressionString(atom, constraint, expr_str, ISOTOPE_SYMBOL, 
														   boost::bind(&getIsotope, _1));
					break;

				case AtomMatchConstraint::RING_BOND_COUNT:
					createIntegralPropertyExpressionString(atom, constraint, expr_str, RING_BOND_COUNT_SYMBOL, 
														   boost::bind(&getRingBondCount, _1, boost::ref(molgraph)));
					break;

				case AtomMatchConstraint::H_COUNT:
					createIntegralPropertyExpressionString(atom, constraint, expr_str, TOTAL_H_COUNT_SYMBOL, 
														   boost::bind(&getAtomCount, _1, boost::ref(molgraph), Chem::AtomType::H, true));
					break;

				case AtomMatchConstraint::IMPLICIT_H_COUNT:
					createIntegralPropertyExpressionString(atom, constraint, expr_str, IMPLICIT_H_COUNT_SYMBOL, 
														   boost::bind(static_cast<std::size_t (*)(const Atom&)>(&getImplicitHydrogenCount), _1));
					break;

				case AtomMatchConstraint::EXPLICIT_H_COUNT:
					createIntegralPropertyExpressionString(atom, constraint, expr_str, EXPLICIT_H_COUNT_SYMBOL, 
														   boost::bind(&getExplicitAtomCount, _1, boost::ref(molgraph), Chem::AtomType::H, true));
					break;

				case AtomMatchConstraint::BOND_COUNT:
					createIntegralPropertyExpressionString(atom, constraint, expr_str, TOTAL_BOND_COUNT_SYMBOL, 
														   boost::bind(static_cast<std::size_t (*)(const Atom&, const MolecularGraph&)>(&getBondCount), _1, boost::ref(molgraph)));
					break;

				case AtomMatchConstraint::EXPLICIT_BOND_COUNT:
					createIntegralPropertyExpressionString(atom, constraint, expr_str, EXPLICIT_BOND_COUNT_SYMBOL, 
														   boost::bind(static_cast<std::size_t (*)(const Atom&, const MolecularGraph&)>(&getExplicitBondCount), _1, boost::ref(molgraph)));
					break;

				case AtomMatchConstraint::HEAVY_BOND_COUNT:
					createIntegralPropertyExpressionString(atom, constraint, expr_str, HEAVY_BOND_COUNT_SYMBOL, 
														   boost::bind(&getHeavyBondCount, _1, boost::ref(molgraph)));
					break;

				case AtomMatchConstraint::VALENCE:
					createIntegralPropertyExpressionString(atom, constraint, expr_str, TOTAL_VALENCE_SYMBOL, 
														   boost::bind(&calcValence, _1, boost::ref(molgraph)));
					break;

				case AtomMatchConstraint::EXPLICIT_VALENCE:
					createIntegralPropertyExpressionString(atom, constraint, expr_str, EXPLICIT_VALENCE_SYMBOL, 
														   boost::bind(&calcExplicitValence, _1, boost::ref(molgraph)));
					break;
		
				case AtomMatchConstraint::RING_TOPOLOGY:
					createBooleanPropertyExpressionString(atom, constraint, expr_str, RING_FLAG_SYMBOL, 
														  boost::bind(&getRingFlag, _1));
					break;

				case AtomMatchConstraint::CONFIGURATION:
					createConfigurationExpressionString(atom, molgraph, constraint, expr_str);
					break;

				case AtomMatchConstraint::UNSATURATION:
					createBooleanPropertyExpressionString(atom, constraint, expr_str, UNSATURATION_FLAG_SYMBOL, 
														  boost::bind(&isUnsaturated, _1, boost::ref(molgraph)));
					break;

				case AtomMatchConstraint::SSSR_RING_COUNT:
					createIntegralPropertyExpressionString(atom, constraint, expr_str, SSSR_RING_COUNT_SYMBOL, 
														   boost::bind(&getNumContainingSSSRRings, _1, boost::ref(molgraph)));
					break;

				case AtomMatchConstraint::SSSR_RING_SIZE:
					createSSSRRingSizeExpressionString(constraint, expr_str);
					break;

				case AtomMatchConstraint::HYBRIDIZATION_STATE:
					createHybridizationStateExpressionString(atom, constraint, expr_str);
					break;

				default:
					continue;
			}

			if (expr_str.empty())
				continue;

			if (list_size > 0) 
				expr_list_str.append(or_list ? OR_LIST_SEPARATOR : AND_LIST_SEPARATOR);
		
			expr_list_str.append(expr_str);
			expr_str.clear();

			list_size++;
		}

		if (list_size == 0)
			return;

		bool not_list = (constr_list.getType() == MatchConstraintList::NOT_AND_LIST || 
						 constr_list.getType() == MatchConstraintList::NOT_OR_LIST);

		if (list_size > 1 && (!root || not_list)) {
			expr_list_str.insert(0, LEFT_LIST_DELIMITER);
			expr_list_str.append(RIGHT_LIST_DELIMITER);
		}

		if (not_list)
			expr_list_str.insert(0, NOT_OPERATOR);
	}
}


void Chem::buildMatchExpressionString(const Atom& atom, const MolecularGraph& molgraph, std::string& expr_str)
{
	createExpressionString(atom, molgraph, *getMatchConstraints(atom), expr_str, true);
}

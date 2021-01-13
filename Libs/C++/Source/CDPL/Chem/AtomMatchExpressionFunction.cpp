/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomMatchExpressionFunction.cpp 
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

#include <boost/bind.hpp>

#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/AtomMatchConstraint.hpp"
#include "CDPL/Chem/ANDMatchExpressionList.hpp"
#include "CDPL/Chem/ORMatchExpressionList.hpp"
#include "CDPL/Chem/NOTMatchExpression.hpp"
#include "CDPL/Chem/AtomTypeMatchExpression.hpp"
#include "CDPL/Chem/AtomEnvironmentMatchExpression.hpp"
#include "CDPL/Chem/AtomConfigurationMatchExpression.hpp"
#include "CDPL/Chem/AtomSSSRRingSizeMatchExpression.hpp"
#include "CDPL/Chem/PropertyMatchExpression.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/AtomType.hpp"


using namespace CDPL; 


namespace
{

	template <typename ValueType>
	struct SingleArgPropertyFuncWrapper
	{

		SingleArgPropertyFuncWrapper(ValueType (*func)(const Chem::Atom&)): func(func) {}

		ValueType operator()(const Chem::Atom& atom, const Chem::MolecularGraph&) const {
			return func(atom);
		}

		ValueType (*func)(const Chem::Atom&);
	};

	Chem::MatchExpression<Chem::Atom, Chem::MolecularGraph>::SharedPointer 
	createTypeMatchExpression(const Chem::Atom& atom, const Chem::MatchConstraint& constraint)
	{
		using namespace Chem;

		if (constraint.getRelation() != MatchConstraint::EQUAL && 
			constraint.getRelation() != MatchConstraint::NOT_EQUAL)
			return MatchExpression<Atom, MolecularGraph>::SharedPointer();

		unsigned int atom_type;

		if (!constraint.hasValue()) {
			atom_type = getType(atom);
		} else
			atom_type = constraint.getValue<unsigned int>();

		if (atom_type == AtomType::UNKNOWN || atom_type > AtomType::MAX_TYPE)
			return MatchExpression<Atom, MolecularGraph>::SharedPointer();

		return MatchExpression<Atom, MolecularGraph>::SharedPointer(new AtomTypeMatchExpression(atom_type, constraint.getRelation() == 
																								MatchConstraint::NOT_EQUAL));
	}

	Chem::MatchExpression<Chem::Atom, Chem::MolecularGraph>::SharedPointer 
	createMatchExpression(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph,
						  const Chem::MatchConstraintList& constr_list);

	Chem::MatchExpression<Chem::Atom, Chem::MolecularGraph>::SharedPointer 
	createMatchExpressionList(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph,
							  const Chem::MatchConstraint& constraint)
	{
		using namespace Chem;

		if (constraint.getRelation() != MatchConstraint::EQUAL && 
			constraint.getRelation() != MatchConstraint::NOT_EQUAL)
			return MatchExpression<Atom, MolecularGraph>::SharedPointer();

		const MatchConstraintList& constr_list = 
			*constraint.getValue<MatchConstraintList::SharedPointer>();

		MatchExpression<Atom, MolecularGraph>::SharedPointer expr_ptr = createMatchExpression(atom, molgraph, constr_list);

		if (!expr_ptr)
			return expr_ptr;

		if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
			expr_ptr.reset(new NOTMatchExpression<Atom, MolecularGraph>(expr_ptr));

		return expr_ptr;
	}

	Chem::MatchExpression<Chem::Atom, Chem::MolecularGraph>::SharedPointer 
	createEnvironmentMatchExpression(const Chem::MatchConstraint& constraint)
	{
		using namespace Chem;

		if (constraint.getRelation() != MatchConstraint::EQUAL && 
			constraint.getRelation() != MatchConstraint::NOT_EQUAL)
			return MatchExpression<Atom, MolecularGraph>::SharedPointer();

		const Molecule::SharedPointer& env_pattern = constraint.getValue<Molecule::SharedPointer>();

		if (env_pattern->getNumAtoms() == 0)
			return MatchExpression<Atom, MolecularGraph>::SharedPointer();

		return MatchExpression<Atom, MolecularGraph>::SharedPointer(new AtomEnvironmentMatchExpression(env_pattern, constraint.getRelation() == 
																									   MatchConstraint::NOT_EQUAL));
	}

	Chem::MatchExpression<Chem::Atom, Chem::MolecularGraph>::SharedPointer 
	createConfigurationMatchExpression(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph,
									   const Chem::MatchConstraint& constraint)
	{
		using namespace Chem;

		if (constraint.getRelation() != MatchConstraint::EQUAL && 
			constraint.getRelation() != MatchConstraint::NOT_EQUAL)
			return MatchExpression<Atom, MolecularGraph>::SharedPointer();

		if (!constraint.hasValue()) {
			const StereoDescriptor& stereo_descr = calcStereoDescriptor(atom, molgraph, 0);

			if ((stereo_descr.getConfiguration() & (AtomConfiguration::R | AtomConfiguration::S)) == 0)
				return MatchExpression<Atom, MolecularGraph>::SharedPointer();

			return MatchExpression<Atom, MolecularGraph>::SharedPointer(new AtomConfigurationMatchExpression(stereo_descr, atom, constraint.getRelation() ==
																											 MatchConstraint::NOT_EQUAL, true));
		} else {
			const StereoDescriptor& stereo_descr = constraint.getValue<StereoDescriptor>();

			if ((stereo_descr.getConfiguration() & 
				 (AtomConfiguration::NONE | AtomConfiguration::R | AtomConfiguration::S | AtomConfiguration::EITHER)) == 0)
				return MatchExpression<Atom, MolecularGraph>::SharedPointer();

			return MatchExpression<Atom, MolecularGraph>::SharedPointer(new AtomConfigurationMatchExpression(stereo_descr, atom, constraint.getRelation() ==
																											 MatchConstraint::NOT_EQUAL, true));
		}
	}

	Chem::MatchExpression<Chem::Atom, Chem::MolecularGraph>::SharedPointer 
	createSSSRRingSizeMatchExpression(const Chem::MatchConstraint& constraint)
	{
		using namespace Chem;

		std::size_t rsize = constraint.getValue<std::size_t>();

		switch (constraint.getRelation()) {

			case MatchConstraint::EQUAL:
				return MatchExpression<Atom, MolecularGraph>::SharedPointer(new AtomSSSRRingSizeMatchExpression<std::equal_to<std::size_t> >(rsize));

			case MatchConstraint::NOT_EQUAL: {
				MatchExpression<Atom, MolecularGraph>::SharedPointer 
					expr_ptr(new AtomSSSRRingSizeMatchExpression<std::equal_to<std::size_t> >(rsize));

				return MatchExpression<Atom, MolecularGraph>::SharedPointer(new NOTMatchExpression<Atom, MolecularGraph>(expr_ptr));
			}

			case MatchConstraint::GREATER:
				return MatchExpression<Atom, MolecularGraph>::SharedPointer(new AtomSSSRRingSizeMatchExpression<std::greater<std::size_t> >(rsize));

			case MatchConstraint::LESS:
				return MatchExpression<Atom, MolecularGraph>::SharedPointer(new AtomSSSRRingSizeMatchExpression<std::less<std::size_t> >(rsize));

			case MatchConstraint::GREATER_OR_EQUAL:
				return MatchExpression<Atom, MolecularGraph>::SharedPointer(new AtomSSSRRingSizeMatchExpression<std::greater_equal<std::size_t> >(rsize));
				
			case MatchConstraint::LESS_OR_EQUAL:
				return MatchExpression<Atom, MolecularGraph>::SharedPointer(new AtomSSSRRingSizeMatchExpression<std::less_equal<std::size_t> >(rsize));

			default:
				return MatchExpression<Atom, MolecularGraph>::SharedPointer();
		}
	}

	template <typename ValueType, typename PropertyFunc>
	Chem::MatchExpression<Chem::Atom, Chem::MolecularGraph>::SharedPointer 
	createIntegralPropertyMatchExpression(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, 
										  const Chem::MatchConstraint& constraint, const PropertyFunc& func)
	{
		using namespace Chem;

		MatchExpression<Atom, MolecularGraph>::SharedPointer expr_ptr;

		switch (constraint.getRelation()) {

			case MatchConstraint::EQUAL:
				if (!constraint.hasValue()) 
					expr_ptr.reset(new PropertyMatchExpression<ValueType, std::equal_to<ValueType>,
								   Atom, MolecularGraph>(func(atom, molgraph), func));
				else
					expr_ptr.reset(new PropertyMatchExpression<ValueType, std::equal_to<ValueType>,
								   Atom, MolecularGraph>(constraint.template getValue<ValueType>(), func));
				break;

			case MatchConstraint::NOT_EQUAL:
				if (!constraint.hasValue()) 
					expr_ptr.reset(new PropertyMatchExpression<ValueType, std::not_equal_to<ValueType>,
								   Atom, MolecularGraph>(func(atom, molgraph), func));
				else
					expr_ptr.reset(new PropertyMatchExpression<ValueType, std::not_equal_to<ValueType>,
								   Atom, MolecularGraph>(constraint.template getValue<ValueType>(), func));

				break;

			case MatchConstraint::GREATER:
				if (!constraint.hasValue()) 
					expr_ptr.reset(new PropertyMatchExpression<ValueType, std::greater<ValueType>, 
								   Atom, MolecularGraph>(func(atom, molgraph), func));
				else
					expr_ptr.reset(new PropertyMatchExpression<ValueType, std::greater<ValueType>, 
								   Atom, MolecularGraph>(constraint.template getValue<ValueType>(), func));

				break;

			case MatchConstraint::LESS:
				if (!constraint.hasValue()) 
					expr_ptr.reset(new PropertyMatchExpression<ValueType, std::less<ValueType>, 
								   Atom, MolecularGraph>(func(atom, molgraph), func));
				else
					expr_ptr.reset(new PropertyMatchExpression<ValueType, std::less<ValueType>, 
								   Atom, MolecularGraph>(constraint.template getValue<ValueType>(), func));

				break;

			case MatchConstraint::GREATER_OR_EQUAL:
				if (!constraint.hasValue()) 
					expr_ptr.reset(new PropertyMatchExpression<ValueType, std::greater_equal<ValueType>, 
								   Atom, MolecularGraph>(func(atom, molgraph), func));
				else
					expr_ptr.reset(new PropertyMatchExpression<ValueType, std::greater_equal<ValueType>, 
								   Atom, MolecularGraph>(constraint.template getValue<ValueType>(), func));

				break;
				
			case MatchConstraint::LESS_OR_EQUAL:
				if (!constraint.hasValue()) 
					expr_ptr.reset(new PropertyMatchExpression<ValueType, std::less_equal<ValueType>, 
								   Atom, MolecularGraph>(func(atom, molgraph), func));
				else
					expr_ptr.reset(new PropertyMatchExpression<ValueType, std::less_equal<ValueType>, 
								   Atom, MolecularGraph>(constraint.template getValue<ValueType>(), func));

				break;

			default:
				return MatchExpression<Atom, MolecularGraph>::SharedPointer();
		}

		return expr_ptr;
	}

	template <typename PropertyFunc>
	Chem::MatchExpression<Chem::Atom, Chem::MolecularGraph>::SharedPointer 
	createBooleanPropertyMatchExpression(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, 
										 const Chem::MatchConstraint& constraint, const PropertyFunc& func)
	{
		using namespace Chem;

		MatchExpression<Atom, MolecularGraph>::SharedPointer expr_ptr;

		bool not_match = false;

		switch (constraint.getRelation()) {

			case MatchConstraint::EQUAL: 
				break;
		
			case MatchConstraint::NOT_EQUAL:
				not_match = true;
				break;
	
			default:
				return expr_ptr;
		} 

		if (!constraint.hasValue()) {
			if (not_match)
				expr_ptr.reset(new PropertyMatchExpression<bool, std::not_equal_to<bool>, Atom, MolecularGraph>(func(atom, molgraph), func));
			else
				expr_ptr.reset(new PropertyMatchExpression<bool, std::equal_to<bool>, Atom, MolecularGraph>(func(atom, molgraph), func));

		} else {
			bool value = constraint.getValue().toBool();

			if (not_match)
				expr_ptr.reset(new PropertyMatchExpression<bool, std::not_equal_to<bool>, Atom, MolecularGraph>(value, func));
			else
				expr_ptr.reset(new PropertyMatchExpression<bool, std::equal_to<bool>, Atom, MolecularGraph>(value, func));
		}

		return expr_ptr;
	}

	Chem::MatchExpression<Chem::Atom, Chem::MolecularGraph>::SharedPointer 
	createMatchExpression(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, 
						  const Chem::MatchConstraintList& constr_list)
	{
		using namespace Chem;

		MatchExpressionList<Atom, MolecularGraph>::SharedPointer expr_list_ptr;

		if (constr_list.getType() == MatchConstraintList::AND_LIST || 
			constr_list.getType() == MatchConstraintList::NOT_AND_LIST)
			expr_list_ptr.reset(new ANDMatchExpressionList<Atom, MolecularGraph>());
		else
			expr_list_ptr.reset(new ORMatchExpressionList<Atom, MolecularGraph>());

		MatchConstraintList::ConstElementIterator constr_end = constr_list.getElementsEnd();

		for (MatchConstraintList::ConstElementIterator it = constr_list.getElementsBegin(); it != constr_end; ++it) {
			const MatchConstraint& constraint = *it;

			MatchExpression<Atom, MolecularGraph>::SharedPointer expr_ptr;

			switch (constraint.getID()) {

				case AtomMatchConstraint::CONSTRAINT_LIST:
					expr_ptr = createMatchExpressionList(atom, molgraph, constraint);
					break;

				case AtomMatchConstraint::TYPE:
					expr_ptr = createTypeMatchExpression(atom, constraint);
					break;

				case AtomMatchConstraint::ENVIRONMENT:
					expr_ptr = createEnvironmentMatchExpression(constraint);
					break;

				case AtomMatchConstraint::ISOTOPE:
					expr_ptr = createIntegralPropertyMatchExpression<std::size_t>(atom, molgraph, constraint, SingleArgPropertyFuncWrapper<std::size_t>(&getIsotope));
					break;

				case AtomMatchConstraint::CHARGE:
					expr_ptr = createIntegralPropertyMatchExpression<long>(atom, molgraph, constraint, SingleArgPropertyFuncWrapper<long>(&getFormalCharge));
					break;

				case AtomMatchConstraint::RING_BOND_COUNT:
					expr_ptr = createIntegralPropertyMatchExpression<std::size_t>(atom, molgraph, constraint, &getRingBondCount);
					break;

				case AtomMatchConstraint::H_COUNT:
					expr_ptr = createIntegralPropertyMatchExpression<std::size_t>(atom, molgraph, constraint, boost::bind(&getAtomCount, _1, _2, AtomType::H, true));
					break;

				case AtomMatchConstraint::IMPLICIT_H_COUNT:
					expr_ptr = createIntegralPropertyMatchExpression<std::size_t>(atom, molgraph, constraint, SingleArgPropertyFuncWrapper<std::size_t>(&getImplicitHydrogenCount));
					break;

				case AtomMatchConstraint::EXPLICIT_H_COUNT:
					expr_ptr = createIntegralPropertyMatchExpression<std::size_t>(atom, molgraph, constraint, boost::bind(&getExplicitAtomCount, _1, _2, AtomType::H, true));
					break;

				case AtomMatchConstraint::BOND_COUNT:
					expr_ptr = createIntegralPropertyMatchExpression<std::size_t>(atom, molgraph, constraint, static_cast<std::size_t (*)(const Atom&, const MolecularGraph&)>(&getBondCount));
					break;

				case AtomMatchConstraint::EXPLICIT_BOND_COUNT:
					expr_ptr = createIntegralPropertyMatchExpression<std::size_t>(atom, molgraph, constraint, static_cast<std::size_t (*)(const Atom&, const MolecularGraph&)>(&getExplicitBondCount));
					break;

				case AtomMatchConstraint::HEAVY_BOND_COUNT:
					expr_ptr = createIntegralPropertyMatchExpression<std::size_t>(atom, molgraph, constraint, &getHeavyBondCount);
					break;

				case AtomMatchConstraint::VALENCE:
					expr_ptr = createIntegralPropertyMatchExpression<std::size_t>(atom, molgraph, constraint, &calcValence);
					break;

				case AtomMatchConstraint::EXPLICIT_VALENCE:
					expr_ptr = createIntegralPropertyMatchExpression<std::size_t>(atom, molgraph, constraint, &calcExplicitValence);
					break;

				case AtomMatchConstraint::HYBRIDIZATION_STATE:
					expr_ptr = createIntegralPropertyMatchExpression<unsigned int>(atom, molgraph, constraint, 
																				   SingleArgPropertyFuncWrapper<unsigned int>(&getHybridizationState));
					break;

				case AtomMatchConstraint::AROMATICITY:
					expr_ptr = createBooleanPropertyMatchExpression(atom, molgraph, constraint, SingleArgPropertyFuncWrapper<bool>(&getAromaticityFlag));
					break;

				case AtomMatchConstraint::RING_TOPOLOGY:
					expr_ptr = createBooleanPropertyMatchExpression(atom, molgraph, constraint, SingleArgPropertyFuncWrapper<bool>(&getRingFlag));
					break;

				case AtomMatchConstraint::CONFIGURATION:
					expr_ptr = createConfigurationMatchExpression(atom, molgraph, constraint);
					break;

				case AtomMatchConstraint::UNSATURATION:
					expr_ptr = createBooleanPropertyMatchExpression(atom, molgraph, constraint, &isUnsaturated);
					break;

				case AtomMatchConstraint::SSSR_RING_COUNT:
					expr_ptr = createIntegralPropertyMatchExpression<std::size_t>(atom, molgraph, constraint, &getNumContainingSSSRRings);
					break;

				case AtomMatchConstraint::SSSR_RING_SIZE:
					expr_ptr = createSSSRRingSizeMatchExpression(constraint);
					break;

				default:
					continue;
			}

			if (expr_ptr)
				expr_list_ptr->addElement(expr_ptr);
		}

		MatchExpression<Atom, MolecularGraph>::SharedPointer expr_ptr;
	
		if (expr_list_ptr->getSize() == 0)
			return expr_ptr;

		if (expr_list_ptr->getSize() == 1)
			expr_ptr = expr_list_ptr->getBase().getFirstElement();
		else
			expr_ptr = expr_list_ptr;

		if (constr_list.getType() == MatchConstraintList::NOT_AND_LIST || 
			constr_list.getType() == MatchConstraintList::NOT_OR_LIST) 
			expr_ptr.reset(new NOTMatchExpression<Atom, MolecularGraph>(expr_ptr));
	
		return expr_ptr;
	}
}


Chem::MatchExpression<Chem::Atom, Chem::MolecularGraph>::SharedPointer Chem::buildMatchExpression(const Atom& atom, const MolecularGraph& molgraph)
{
	MatchExpression<Atom, MolecularGraph>::SharedPointer expr_ptr = createMatchExpression(atom, molgraph, *getMatchConstraints(atom));

	if (!expr_ptr)
		expr_ptr.reset(new MatchExpression<Atom, MolecularGraph>());

	return expr_ptr; 
}

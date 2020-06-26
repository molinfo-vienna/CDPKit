/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentGenerator.cpp 
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

#include "CDPL/Chem/FragmentGenerator.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


Chem::FragmentGenerator::FragmentationRule::FragmentationRule(const MolecularGraph::SharedPointer& match_ptn,
															  unsigned int rule_id, unsigned int atom1_type,
															  unsigned int atom2_type):
	matchPtn(match_ptn), ruleID(rule_id), atom1Type(atom1_type), atom2Type(atom2_type)
{}

const Chem::MolecularGraph::SharedPointer& Chem::FragmentGenerator::FragmentationRule::getMatchPattern() const
{
	return matchPtn;
}

void Chem::FragmentGenerator::FragmentationRule::setMatchPattern(const MolecularGraph::SharedPointer& ptn)
{
	matchPtn = ptn;
}

unsigned int Chem::FragmentGenerator::FragmentationRule::getRuleID() const
{
	return ruleID;
}

void Chem::FragmentGenerator::FragmentationRule::setRuleID( unsigned int rule_id)
{
	ruleID = rule_id;
}

unsigned int Chem::FragmentGenerator::FragmentationRule::getAtom1Type() const
{
	return atom1Type;
}

void Chem::FragmentGenerator::FragmentationRule::setAtom1Type(unsigned int atom1_type)
{
	atom1Type = atom1_type;
}

unsigned int Chem::FragmentGenerator::FragmentationRule::getAtom2Type() const
{
	return atom2Type;
}

void Chem::FragmentGenerator::FragmentationRule::setAtom2Type(unsigned int atom2_type)
{
	atom2Type = atom2_type;
}
	
	
Chem::FragmentGenerator::ExcludePattern::ExcludePattern(const MolecularGraph::SharedPointer& match_ptn, unsigned int rule_id):
	matchPtn(match_ptn), ruleID(rule_id), generic(false)
{}

Chem::FragmentGenerator::ExcludePattern::ExcludePattern(const MolecularGraph::SharedPointer& match_ptn):
	matchPtn(match_ptn), ruleID(0), generic(true)
{}

const Chem::MolecularGraph::SharedPointer& Chem::FragmentGenerator::ExcludePattern::getMatchPattern() const
{
	return matchPtn;
}

void Chem::FragmentGenerator::ExcludePattern::setMatchPattern(const MolecularGraph::SharedPointer& ptn)
{
	matchPtn = ptn;
}

unsigned int Chem::FragmentGenerator::ExcludePattern::getRuleID() const
{
	return ruleID;
}

void Chem::FragmentGenerator::ExcludePattern::setRuleID( unsigned int rule_id)
{
	ruleID = rule_id;
}

bool Chem::FragmentGenerator::ExcludePattern::isGeneric() const
{
	return generic;
}

void Chem::FragmentGenerator::ExcludePattern::setGeneric(bool gen)
{
	generic = gen;
}
				
		
Chem::FragmentGenerator::FragmentLink::FragmentLink(std::size_t frag1_idx, std::size_t frag2_idx, const Bond& bond,
													unsigned int rule_id, unsigned int atom1_type, unsigned int atom2_type):
	frag1Idx(frag1_idx), frag2Idx(frag2_idx), bond(&bond), ruleID(rule_id), atom1Type(atom1_type), atom2Type(atom2_type)
{}

std::size_t Chem::FragmentGenerator::FragmentLink::getFragment1Index() const
{
	return frag1Idx;
}

void Chem::FragmentGenerator::FragmentLink::setFragment1Index(std::size_t frag1_idx)
{
	frag1Idx = frag1_idx;
}

std::size_t Chem::FragmentGenerator::FragmentLink::getFragment2Index() const
{
	return frag2Idx;
}

void Chem::FragmentGenerator::FragmentLink::setFragment2Index(std::size_t frag2_idx)
{
	frag2Idx = frag2_idx;
}
				
const Chem::Bond& Chem::FragmentGenerator::FragmentLink::getBond() const
{
	return *bond;
}

void Chem::FragmentGenerator::FragmentLink::setBond(const Bond& bond)
{
	this->bond = &bond;
}
				
unsigned int Chem::FragmentGenerator::FragmentLink::getRuleID() const
{
	return ruleID;
}

void Chem::FragmentGenerator::FragmentLink::setRuleID( unsigned int rule_id)
{
	ruleID = rule_id;
}

unsigned int Chem::FragmentGenerator::FragmentLink::getAtom1Type() const
{
	return atom1Type;
}

void Chem::FragmentGenerator::FragmentLink::setAtom1Type(unsigned int atom1_type)
{
	atom1Type = atom1_type;
}

unsigned int Chem::FragmentGenerator::FragmentLink::getAtom2Type() const
{
	return atom2Type;
}

void Chem::FragmentGenerator::FragmentLink::setAtom2Type(unsigned int atom2_type)
{
	atom2Type = atom2_type;
}
			   
	
Chem::FragmentGenerator::FragmentGenerator(): incSplitBonds(true), genFragLinks(false)
{}

Chem::FragmentGenerator::FragmentGenerator(const FragmentGenerator& gen):
	fragRules(gen.fragRules), exclPatterns(gen.exclPatterns), incSplitBonds(gen.incSplitBonds),
	genFragLinks(gen.genFragLinks), fragLinks(gen.fragLinks)
{}

Chem::FragmentGenerator& Chem::FragmentGenerator::operator=(const FragmentGenerator& gen)
{
	if (this == &gen)
		return *this;
	
	fragRules = gen.fragRules;
	exclPatterns = gen.exclPatterns;
	fragLinks = gen.fragLinks;
	incSplitBonds = gen.incSplitBonds;
	genFragLinks = gen.genFragLinks;

	return *this;
}

void Chem::FragmentGenerator::addFragmentationRule(const MolecularGraph::SharedPointer& match_ptn, unsigned int rule_id,
												   unsigned int atom1_type, unsigned int atom2_type)
{
	fragRules.push_back(FragmentationRule(match_ptn, rule_id, atom1_type, atom2_type));
}

void Chem::FragmentGenerator::addFragmentationRule(const FragmentationRule& rule)
{
	fragRules.push_back(rule);
}

const Chem::FragmentGenerator::FragmentationRule& Chem::FragmentGenerator::getFragmentationRule(std::size_t idx) const
{
	if (idx >= fragRules.size())
		throw Base::IndexError("FragmentGenerator: fragmentation rule index out of bounds");

	return fragRules[idx];
}

Chem::FragmentGenerator::FragmentationRule& Chem::FragmentGenerator::getFragmentationRule(std::size_t idx)
{
	if (idx >= fragRules.size())
		throw Base::IndexError("FragmentGenerator: fragmentation rule index out of bounds");

	return fragRules[idx];
}

void Chem::FragmentGenerator::removeFragmentationRule(std::size_t idx)
{
	if (idx >= fragRules.size())
		throw Base::IndexError("FragmentGenerator: fragmentation rule index out of bounds");

	fragRules.erase(fragRules.begin() + idx);
}

std::size_t Chem::FragmentGenerator::getNumFragmentationRules() const
{
	return fragRules.size();
}

void Chem::FragmentGenerator::clearFragmentationRules()
{
	fragRules.clear();
}

void Chem::FragmentGenerator::addExcludePattern(const MolecularGraph::SharedPointer& match_ptn, unsigned int rule_id)
{
	exclPatterns.push_back(ExcludePattern(match_ptn, rule_id));
}

void Chem::FragmentGenerator::addExcludePattern(const MolecularGraph::SharedPointer& match_ptn)
{
	exclPatterns.push_back(ExcludePattern(match_ptn));
}

void Chem::FragmentGenerator::addExcludePattern(const ExcludePattern& excl_ptn)
{
	exclPatterns.push_back(excl_ptn);
}

const Chem::FragmentGenerator::ExcludePattern& Chem::FragmentGenerator::getExcludePattern(std::size_t idx) const
{
	if (idx >= exclPatterns.size())
		throw Base::IndexError("FragmentGenerator: exclude pattern index out of bounds");

	return exclPatterns[idx];
}

Chem::FragmentGenerator::ExcludePattern& Chem::FragmentGenerator::getExcludePattern(std::size_t idx)
{
	if (idx >= exclPatterns.size())
		throw Base::IndexError("FragmentGenerator: exclude pattern index out of bounds");

	return exclPatterns[idx];
}

void Chem::FragmentGenerator::removeExcludePattern(std::size_t idx)
{
	if (idx >= exclPatterns.size())
		throw Base::IndexError("FragmentGenerator: exclude pattern index out of bounds");

	exclPatterns.erase(exclPatterns.begin() + idx);
}

std::size_t Chem::FragmentGenerator::getNumExcludePatterns() const
{
	return exclPatterns.size();
}

void Chem::FragmentGenerator::clearExcludePatterns()
{
	exclPatterns.clear();
}

void Chem::FragmentGenerator::generate(const MolecularGraph& molgraph, FragmentList& frags, bool append)
{
	init(molgraph);
}

std::size_t Chem::FragmentGenerator::getNumFragmentLinks() const
{
	return fragLinks.size();
}

const Chem::FragmentGenerator::FragmentLink& Chem::FragmentGenerator::getFragmentLink(std::size_t idx) const
{
	if (idx >= fragLinks.size())
		throw Base::IndexError("FragmentGenerator: fragment links index out of bounds");

	return fragLinks[idx];
}

void Chem::FragmentGenerator::init(const MolecularGraph& molgraph)
{
	fragLinks.clear();

	std::size_t num_bonds = molgraph.getNumBonds();

	splitBondMask.resize(num_bonds);
	splitBondMask.reset();
}

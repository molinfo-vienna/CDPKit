/* 
 * TorsionRule.cpp 
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


#include "StaticInit.hpp"

#include "CDPL/ConfGen/TorsionRule.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


const std::string& ConfGen::TorsionRule::getMatchPatternString() const
{
	return matchPatternStr;
}

void ConfGen::TorsionRule::setMatchPatternString(const std::string& ptn_str)
{
	matchPatternStr = ptn_str;
}

const Chem::MolecularGraph::SharedPointer& ConfGen::TorsionRule::getMatchPattern() const
{
	return matchPattern;
}

void ConfGen::TorsionRule::setMatchPattern(const Chem::MolecularGraph::SharedPointer& ptn)
{
	matchPattern = ptn;
}

void ConfGen::TorsionRule::addAngle(const AngleEntry& angle)
{
	angles.push_back(angle);
}

void ConfGen::TorsionRule::addAngle(double angle, double tol1, double tol2, double score)
{
	angles.push_back(AngleEntry(angle, tol1, tol2, score));
}

std::size_t ConfGen::TorsionRule::getNumAngles() const
{
	return angles.size();
}

const ConfGen::TorsionRule::AngleEntry& ConfGen::TorsionRule::getAngle(std::size_t idx) const
{
	checkAngleIndex(idx, false);

	return angles[idx];
}

void ConfGen::TorsionRule::removeAngle(std::size_t idx)
{
	checkAngleIndex(idx, false);

	angles.erase(angles.begin() + idx);
}

void ConfGen::TorsionRule::removeAngle(const AngleEntryIterator& it)
{
	checkAngleIndex(it - angles.begin(), true);

	angles.erase(it);
}

ConfGen::TorsionRule::AngleEntryIterator ConfGen::TorsionRule::getAnglesBegin()
{
	return angles.begin();
}

ConfGen::TorsionRule::AngleEntryIterator ConfGen::TorsionRule::getAnglesEnd()
{
	return angles.end();
}

ConfGen::TorsionRule::ConstAngleEntryIterator ConfGen::TorsionRule::getAnglesBegin() const
{
	return angles.begin();
}

ConfGen::TorsionRule::ConstAngleEntryIterator ConfGen::TorsionRule::getAnglesEnd() const
{
	return angles.end();
}

ConfGen::TorsionRule::AngleEntryIterator ConfGen::TorsionRule::begin()
{
	return angles.begin();
}

ConfGen::TorsionRule::AngleEntryIterator ConfGen::TorsionRule::end()
{
	return angles.end();
}

ConfGen::TorsionRule::ConstAngleEntryIterator ConfGen::TorsionRule::begin() const
{
	return angles.begin();
}

ConfGen::TorsionRule::ConstAngleEntryIterator ConfGen::TorsionRule::end() const
{
	return angles.end();
}

void ConfGen::TorsionRule::swap(TorsionRule& cat)
{
	matchPattern.swap(cat.matchPattern);
	angles.swap(cat.angles);
}

void ConfGen::TorsionRule::clear()
{
	angles.clear();
	matchPattern.reset();
}

void ConfGen::TorsionRule::checkAngleIndex(std::size_t idx, bool it) const
{
	if (idx >= angles.size())
		throw Base::IndexError(it ? "TorsionRule: angle iterator out of bounds" : 
							   "TorsionRule: angle index out of bounds");
}

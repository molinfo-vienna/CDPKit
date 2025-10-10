/* 
 * ECFPCalculator.cpp
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


#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Descr/CircularFingerprintGenerator.hpp"

#include "CmdLine/Lib/CmdLineBase.hpp"

#include "ECFPCalculator.hpp"


using namespace SimScreen;


ECFPCalculator::ECFPCalculator(): DescriptorCalculator("ECFP", BITSET, false)
{}

ECFPCalculator::~ECFPCalculator()
{}

void ECFPCalculator::addOptions(CmdLineLib::CmdLineBase& cl_base)
{
    cl_base.addOption("ecfp-size",
                      "Size of the generated fingerprint (default: " + std::to_string(size) + ").",
                      cl_base.value<std::size_t>(&size));
    cl_base.addOption("ecfp-radius",
                      "Atom environment radius in number of bonds (default: " + std::to_string(radius) + ").",
                      cl_base.value<std::size_t>(&radius));
}

void ECFPCalculator::getOptionSummary(std::string& summary) const
{
    summary.append("ECFP Bit Count;");
    summary.append(std::to_string(size));
    summary.push_back(';');
    summary.append("ECFP Atom Env. Radius;");
    summary.append(std::to_string(radius));
    summary.push_back(';');
}

DescriptorCalculator* ECFPCalculator::clone() const
{
    auto copy = new ECFPCalculator();

    copy->radius = radius;
    copy->size = size;
    
    return copy;
}

void ECFPCalculator::prepare(CDPL::Chem::Molecule& mol)
{
    initSubstructureSearchTarget(mol, false);
}

void ECFPCalculator::calculate(const CDPL::Chem::MolecularGraph& molgraph, CDPL::Util::BitSet& fp)
{
    if (!ecfpGenImpl) {
        ecfpGenImpl.reset(new CDPL::Descr::CircularFingerprintGenerator());

        ecfpGenImpl->includeHydrogens(false);
        ecfpGenImpl->includeChirality(true);
        ecfpGenImpl->setNumIterations(radius);
    }

    fp.resize(size);

    ecfpGenImpl->generate(molgraph);
    ecfpGenImpl->setFeatureBits(fp);
}

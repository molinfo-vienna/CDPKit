/* 
 * DaylightFPCalculator.cpp
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
#include "CDPL/Chem/MoleculeFunctions.hpp"
#include "CDPL/Descr/PathFingerprintGenerator.hpp"

#include "CmdLine/Lib/CmdLineBase.hpp"

#include "DaylightFPCalculator.hpp"


using namespace SimScreen;


DaylightFPCalculator::DaylightFPCalculator(): DescriptorCalculator("DAYLIGHT", BITSET, false)
{}

DaylightFPCalculator::~DaylightFPCalculator()
{}

void DaylightFPCalculator::addOptions(CmdLineLib::CmdLineBase& cl_base)
{
    cl_base.addOption("daylight-size",
                      "Size of the generated fingerprint (default: 8191).",
                      cl_base.value<std::size_t>(&size));
    cl_base.addOption("daylight-min-path-len",
                      "Minimum considered atom path length in number of bonds (default: 0).",
                      cl_base.value<std::size_t>(&minPathLen));
    cl_base.addOption("daylight-max-path-len",
                      "Maximum considered atom path length in number of bonds (default: 5).",
                      cl_base.value<std::size_t>(&maxPathLen));
    cl_base.addOption("daylight-inc-H",
                      "Whether or not to include hydrogen atoms (default: false).",
                      cl_base.value<bool>(&incHydrogens));
}

void DaylightFPCalculator::getOptionSummary(std::string& summary) const
{
    summary.append("Daylight FP Bit Count;");
    summary.append(std::to_string(size));
    summary.push_back(';');
    summary.append("Daylight FP min. Path Length;");
    summary.append(std::to_string(minPathLen));
    summary.push_back(';');
    summary.append("Daylight FP max. Path Length;");
    summary.append(std::to_string(maxPathLen));
    summary.push_back(';');
    summary.append("Daylight FP include Hydrogens;");
    summary.append(incHydrogens ? "Yes" : "No");
}

DescriptorCalculator* DaylightFPCalculator::clone() const
{
    auto copy = new DaylightFPCalculator();

    copy->minPathLen = minPathLen;
    copy->maxPathLen = maxPathLen;
    copy->incHydrogens = incHydrogens;
    copy->size = size;
    
    return copy;
}

void DaylightFPCalculator::prepare(CDPL::Chem::Molecule& mol) const
{
    calcBasicProperties(mol, false);

    if (incHydrogens)        
        makeHydrogenComplete(mol);
}

void DaylightFPCalculator::calculate(const CDPL::Chem::MolecularGraph& molgraph, CDPL::Util::BitSet& fp)
{
    if (!fpGenImpl) {
        fpGenImpl.reset(new CDPL::Descr::PathFingerprintGenerator());

        fpGenImpl->setMinPathLength(maxPathLen);
        fpGenImpl->setMaxPathLength(maxPathLen);
        fpGenImpl->includeHydrogens(incHydrogens);
    }

    fp.resize(size);

    fpGenImpl->generate(molgraph, fp);
}

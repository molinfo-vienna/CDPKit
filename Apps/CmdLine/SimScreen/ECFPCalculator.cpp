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
#include "CDPL/Chem/MoleculeFunctions.hpp"
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
                      "Size of the generated fingerprint (default: 8191).",
                      cl_base.value<std::size_t>(&size));
    cl_base.addOption("ecfp-radius",
                      "Atom environment radius in number of bonds (default: 2 -> ECFP4).",
                      cl_base.value<std::size_t>(&radius));
    cl_base.addOption("ecfp-inc-H",
                      "Whether or not to include hydrogen atoms (default: false).",
                      cl_base.value<bool>(&incHydrogens));
    cl_base.addOption("ecfp-inc-chirality",
                      "Whether or not to regard the chriality of stereo atoms(default: false).",
                      cl_base.value<bool>(&incChirality));
}

void ECFPCalculator::getOptionSummary(std::string& summary) const
{
    summary.append("ECFP Bit Count;");
    summary.append(std::to_string(size));
    summary.push_back(';');
    summary.append("ECFP Atom Env. Radius;");
    summary.append(std::to_string(radius));
    summary.push_back(';');
    summary.append("ECFP include Hydrogens;");
    summary.append(incHydrogens ? "Yes" : "No");
    summary.push_back(';');
    summary.append("ECFP include Chirality Info;");
    summary.append(incChirality ? "Yes" : "No");
    summary.push_back(';');
}

DescriptorCalculator* ECFPCalculator::clone() const
{
    auto copy = new ECFPCalculator();

    copy->radius = radius;
    copy->size = size;
    copy->incHydrogens = incHydrogens;
    copy->incChirality = incChirality;
    
    return copy;
}

void ECFPCalculator::prepare(CDPL::Chem::Molecule& mol) const
{
    calcBasicProperties(mol, false);

    if (incChirality) {
        calcCIPPriorities(mol, false);
        perceiveAtomStereoCenters(mol, false, true);
        calcAtomStereoDescriptors(mol, false);
    }
    
    if (incHydrogens)        
        makeHydrogenComplete(mol);
}

void ECFPCalculator::calculate(const CDPL::Chem::MolecularGraph& molgraph, CDPL::Util::BitSet& fp)
{
    if (!fpGenImpl) {
        fpGenImpl.reset(new CDPL::Descr::CircularFingerprintGenerator());

        fpGenImpl->includeHydrogens(incHydrogens);
        fpGenImpl->includeChirality(incChirality);
        fpGenImpl->setNumIterations(radius);
    }

    fp.resize(size);

    fpGenImpl->generate(molgraph);
    fpGenImpl->setFeatureBits(fp);
}

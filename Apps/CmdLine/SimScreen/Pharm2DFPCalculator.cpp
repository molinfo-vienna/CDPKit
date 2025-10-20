/* 
 * Pharm2DFPCalculator.cpp
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


#include <boost/format.hpp>

#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Pharm/MoleculeFunctions.hpp"
#include "CDPL/Descr/NPoint2DPharmacophoreFingerprintGenerator.hpp"

#include "CmdLine/Lib/CmdLineBase.hpp"

#include "Pharm2DFPCalculator.hpp"


using namespace SimScreen;


Pharm2DFPCalculator::Pharm2DFPCalculator(): DescriptorCalculator("PHARM_2D", BITSET, false)
{}

Pharm2DFPCalculator::~Pharm2DFPCalculator()
{}

void Pharm2DFPCalculator::addOptions(CmdLineLib::CmdLineBase& cl_base)
{
    cl_base.addOption("pharm-2d-size",
                      "Size of the generated fingerprint (default: 8191).",
                      cl_base.value<std::size_t>(&size));
    cl_base.addOption("pharm-2d-min-tuple-size",
                      "Minimum feature tuple size (default: 1).",
                      cl_base.value<std::size_t>(&minTupleSize));
    cl_base.addOption("pharm-2d-max-tuple-size",
                      "Maximum feature tuple size (default: 3).",
                      cl_base.value<std::size_t>(&maxTupleSize));
    cl_base.addOption("pharm-2d-bin-size",
                      "Feature distance bin size (default: 2.0, must be > 0).",
                      cl_base.value<double>()->notifier(
                          [&](double bin_size) {
                              if (bin_size <= 0.0)
                                  cl_base.throwValidationError("pharm-2d-bin-size");
                              
                              this->binSize = bin_size;
                          }));
}

void Pharm2DFPCalculator::getOptionSummary(std::string& summary) const
{
    summary.append("Pharm. 2D FP Bit Count;");
    summary.append(std::to_string(size));
    summary.push_back(';');
    summary.append("Pharm. 2D FP Min. Ftr. Tuple Size;");
    summary.append(std::to_string(minTupleSize));
    summary.push_back(';');
    summary.append("Pharm. 2D FP Max. Ftr. Tuple Size;");
    summary.append(std::to_string(maxTupleSize));
    summary.push_back(';');
    summary.append("Pharm. 2D FP Bin Size;");
    summary.append((boost::format("%.3f") % binSize).str());
    summary.push_back(';');
}

DescriptorCalculator* Pharm2DFPCalculator::clone() const
{
    auto copy = new Pharm2DFPCalculator();

    copy->minTupleSize = minTupleSize;
    copy->maxTupleSize = maxTupleSize;
    copy->binSize = binSize;
    copy->size = size;
    
    return copy;
}

void Pharm2DFPCalculator::prepare(CDPL::Chem::Molecule& mol) const
{
    CDPL::Pharm::prepareForPharmacophoreGeneration(mol);
}

void Pharm2DFPCalculator::calculate(const CDPL::Chem::MolecularGraph& molgraph, CDPL::Util::BitSet& fp)
{
    if (!fpGenImpl) {
        fpGenImpl.reset(new CDPL::Descr::NPoint2DPharmacophoreFingerprintGenerator());

        fpGenImpl->setMinFeatureTupleSize(minTupleSize);
        fpGenImpl->setMaxFeatureTupleSize(maxTupleSize);
        fpGenImpl->setBinSize(binSize);
    }

    fp.resize(size);

    fpGenImpl->generate(molgraph, fp);
}

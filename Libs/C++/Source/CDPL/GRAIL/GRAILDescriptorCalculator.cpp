/* 
 * GRAILDescriptorCalculator.cpp 
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

#include <mutex>

#include "CDPL/GRAIL/GRAILDescriptorCalculator.hpp"
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/HBondingInteractionScore.hpp"
#include "CDPL/Pharm/XBondingInteractionScore.hpp"
#include "CDPL/Pharm/CationPiInteractionScore.hpp"
#include "CDPL/Pharm/HydrophobicInteractionScore.hpp"
#include "CDPL/Pharm/FeatureInteractionScoreCombiner.hpp"
#include "CDPL/Pharm/ParallelPiPiInteractionScore.hpp"
#include "CDPL/Pharm/OrthogonalPiPiInteractionScore.hpp"

#include "GRAILDescriptorCalculatorImpl.hpp"


using namespace CDPL;


namespace
{

    GRAIL::GRAILDescriptorCalculatorImpl::FeatureInteractionFuncList ftrInteractionFuncList;
    std::once_flag initFtrInteractionFuncListFlag;
    
    void initFtrInteractionFuncList()
    {
        using namespace Pharm;

        typedef FeatureInteractionScore::SharedPointer FISPtr;
        
        ftrInteractionFuncList.push_back({ FeatureType::POSITIVE_IONIZABLE, FeatureType::AROMATIC, FISPtr(new CationPiInteractionScore(false)) });
        ftrInteractionFuncList.push_back({ FeatureType::AROMATIC, FeatureType::POSITIVE_IONIZABLE, FISPtr(new CationPiInteractionScore(true)) });
        ftrInteractionFuncList.push_back({ FeatureType::HYDROPHOBIC, FeatureType::HYDROPHOBIC, FISPtr(new HydrophobicInteractionScore()) });
        ftrInteractionFuncList.push_back({ FeatureType::AROMATIC, FeatureType::AROMATIC,
                  FISPtr(new FeatureInteractionScoreCombiner(FISPtr(new OrthogonalPiPiInteractionScore()), FISPtr(new ParallelPiPiInteractionScore()))) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR, FeatureType::H_BOND_ACCEPTOR, FISPtr(new HBondingInteractionScore(true)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR, FeatureType::H_BOND_DONOR, FISPtr(new HBondingInteractionScore(false)) });
        ftrInteractionFuncList.push_back({ FeatureType::HALOGEN_BOND_DONOR, FeatureType::HALOGEN_BOND_ACCEPTOR, FISPtr(new XBondingInteractionScore(true)) });
    }

    GRAIL::GRAILDescriptorCalculatorImpl::FeatureTypeInfoList ligandDescrFtrTypes({
        { Pharm::FeatureType::POSITIVE_IONIZABLE,    false },
        { Pharm::FeatureType::NEGATIVE_IONIZABLE,    false },
        { Pharm::FeatureType::AROMATIC,              false },
        { Pharm::FeatureType::HYDROPHOBIC,           false },
        { Pharm::FeatureType::H_BOND_DONOR,          true  },
        { Pharm::FeatureType::H_BOND_ACCEPTOR,       false },
        { Pharm::FeatureType::HALOGEN_BOND_DONOR,    false },
        { Pharm::FeatureType::HALOGEN_BOND_ACCEPTOR, false }
    });

    GRAIL::GRAILDescriptorCalculatorImpl::FeatureTypeInfoList tgtEnvOccupHBAHBDTypes({
        { Pharm::FeatureType::H_BOND_ACCEPTOR, false },
        { Pharm::FeatureType::H_BOND_DONOR,    true  }
    });

    unsigned int getFeatureType(const Pharm::Feature& ftr, bool)
    {
        return getType(ftr);
    }
}


constexpr std::size_t GRAIL::GRAILDescriptorCalculator::TOTAL_DESCRIPTOR_SIZE;
constexpr std::size_t GRAIL::GRAILDescriptorCalculator::LIGAND_DESCRIPTOR_SIZE;


GRAIL::GRAILDescriptorCalculator::GRAILDescriptorCalculator(): impl() {}

GRAIL::GRAILDescriptorCalculator::GRAILDescriptorCalculator(const GRAILDescriptorCalculator& calc):
    impl(calc.impl ? new GRAILDescriptorCalculatorImpl(*calc.impl) : nullptr) {}

GRAIL::GRAILDescriptorCalculator::~GRAILDescriptorCalculator() {}

GRAIL::GRAILDescriptorCalculator& GRAIL::GRAILDescriptorCalculator::operator=(const GRAILDescriptorCalculator& calc)
{
    if (this == &calc)
        return *this;

    if (calc.impl) {
        if (impl)
            *impl = *calc.impl;
        else
            impl.reset(new GRAILDescriptorCalculatorImpl(*calc.impl));

    } else if (impl)
        impl.reset();
    
    return *this;
}

void GRAIL::GRAILDescriptorCalculator::initTargetData(const Chem::MolecularGraph& tgt_env, const Chem::Atom3DCoordinatesFunction& coords_func, bool tgt_env_changed)
{
    initCalculatorImpl();

    impl->initTargetData(tgt_env, coords_func, tgt_env_changed);
}

void GRAIL::GRAILDescriptorCalculator::initLigandData(const Chem::MolecularGraph& ligand)
{
   initCalculatorImpl();

   impl->initLigandData(ligand);
}

void GRAIL::GRAILDescriptorCalculator::calculate(const Math::Vector3DArray& atom_coords, Math::DVector& descr, bool update_lig_part)
{
    if (!impl)
        return;
    
    if (descr.getSize() < TOTAL_DESCRIPTOR_SIZE)
        descr.resize(TOTAL_DESCRIPTOR_SIZE);

    impl->calculate(atom_coords, descr, update_lig_part);
}

void GRAIL::GRAILDescriptorCalculator::initCalculatorImpl()
{
    if (impl)
        return;
    
    std::call_once(initFtrInteractionFuncListFlag, &initFtrInteractionFuncList);

    impl.reset(new GRAILDescriptorCalculatorImpl(ftrInteractionFuncList, ligandDescrFtrTypes, tgtEnvOccupHBAHBDTypes, &getFeatureType));
}

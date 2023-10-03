/* 
 * GRAILXDescriptorCalculator.cpp 
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

#include "CDPL/GRAIL/GRAILXDescriptorCalculator.hpp"
#include "CDPL/GRAIL/FeatureType.hpp"
#include "CDPL/GRAIL/FeatureFunctions.hpp"
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
        using namespace GRAIL;

        typedef Pharm::FeatureInteractionScore::SharedPointer FISPtr;
        
        ftrInteractionFuncList.push_back({ FeatureType::POSITIVE_IONIZABLE, FeatureType::AROMATIC, FISPtr(new Pharm::CationPiInteractionScore(false)) });
        ftrInteractionFuncList.push_back({ FeatureType::AROMATIC, FeatureType::POSITIVE_IONIZABLE, FISPtr(new Pharm::CationPiInteractionScore(true)) });
        ftrInteractionFuncList.push_back({ FeatureType::HYDROPHOBIC, FeatureType::HYDROPHOBIC, FISPtr(new Pharm::HydrophobicInteractionScore()) });
        ftrInteractionFuncList.push_back({ FeatureType::AROMATIC, FeatureType::AROMATIC,
                  FISPtr(new Pharm::FeatureInteractionScoreCombiner(FISPtr(new Pharm::OrthogonalPiPiInteractionScore()), FISPtr(new Pharm::ParallelPiPiInteractionScore()))) });

        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR, FeatureType::H_BOND_ACCEPTOR_N, FISPtr(new Pharm::HBondingInteractionScore(true)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR, FeatureType::H_BOND_ACCEPTOR_O, FISPtr(new Pharm::HBondingInteractionScore(true)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR, FeatureType::H_BOND_ACCEPTOR_S, FISPtr(new Pharm::HBondingInteractionScore(true)) });

        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR_N3, FeatureType::H_BOND_ACCEPTOR_N, FISPtr(new Pharm::HBondingInteractionScore(true)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR_N3, FeatureType::H_BOND_ACCEPTOR_O, FISPtr(new Pharm::HBondingInteractionScore(true)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR_N3, FeatureType::H_BOND_ACCEPTOR_S, FISPtr(new Pharm::HBondingInteractionScore(true)) });

        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR_N2, FeatureType::H_BOND_ACCEPTOR_N, FISPtr(new Pharm::HBondingInteractionScore(true)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR_N2, FeatureType::H_BOND_ACCEPTOR_O, FISPtr(new Pharm::HBondingInteractionScore(true)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR_N2, FeatureType::H_BOND_ACCEPTOR_S, FISPtr(new Pharm::HBondingInteractionScore(true)) });
                      
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR_Nar, FeatureType::H_BOND_ACCEPTOR_N, FISPtr(new Pharm::HBondingInteractionScore(true)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR_Nar, FeatureType::H_BOND_ACCEPTOR_O, FISPtr(new Pharm::HBondingInteractionScore(true)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR_Nar, FeatureType::H_BOND_ACCEPTOR_S, FISPtr(new Pharm::HBondingInteractionScore(true)) });

        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR_Nam, FeatureType::H_BOND_ACCEPTOR_N, FISPtr(new Pharm::HBondingInteractionScore(true)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR_Nam, FeatureType::H_BOND_ACCEPTOR_O, FISPtr(new Pharm::HBondingInteractionScore(true)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR_Nam, FeatureType::H_BOND_ACCEPTOR_S, FISPtr(new Pharm::HBondingInteractionScore(true)) });

        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR_Npl3, FeatureType::H_BOND_ACCEPTOR_N, FISPtr(new Pharm::HBondingInteractionScore(true)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR_Npl3, FeatureType::H_BOND_ACCEPTOR_O, FISPtr(new Pharm::HBondingInteractionScore(true)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR_Npl3, FeatureType::H_BOND_ACCEPTOR_S, FISPtr(new Pharm::HBondingInteractionScore(true)) });

        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR_N4, FeatureType::H_BOND_ACCEPTOR_N, FISPtr(new Pharm::HBondingInteractionScore(true)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR_N4, FeatureType::H_BOND_ACCEPTOR_O, FISPtr(new Pharm::HBondingInteractionScore(true)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR_N4, FeatureType::H_BOND_ACCEPTOR_S, FISPtr(new Pharm::HBondingInteractionScore(true)) });
                
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR_O3, FeatureType::H_BOND_ACCEPTOR_N, FISPtr(new Pharm::HBondingInteractionScore(true)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR_O3, FeatureType::H_BOND_ACCEPTOR_O, FISPtr(new Pharm::HBondingInteractionScore(true)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR_O3, FeatureType::H_BOND_ACCEPTOR_S, FISPtr(new Pharm::HBondingInteractionScore(true)) });

        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR_S3, FeatureType::H_BOND_ACCEPTOR_N, FISPtr(new Pharm::HBondingInteractionScore(true)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR_S3, FeatureType::H_BOND_ACCEPTOR_O, FISPtr(new Pharm::HBondingInteractionScore(true)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_DONOR_S3, FeatureType::H_BOND_ACCEPTOR_S, FISPtr(new Pharm::HBondingInteractionScore(true)) });

        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR, FeatureType::H_BOND_DONOR_N, FISPtr(new Pharm::HBondingInteractionScore(false)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR, FeatureType::H_BOND_DONOR_O, FISPtr(new Pharm::HBondingInteractionScore(false)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR, FeatureType::H_BOND_DONOR_S, FISPtr(new Pharm::HBondingInteractionScore(false)) });
                      
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_N3, FeatureType::H_BOND_DONOR_N, FISPtr(new Pharm::HBondingInteractionScore(false)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_N3, FeatureType::H_BOND_DONOR_O, FISPtr(new Pharm::HBondingInteractionScore(false)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_N3, FeatureType::H_BOND_DONOR_S, FISPtr(new Pharm::HBondingInteractionScore(false)) });
                       
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_N2, FeatureType::H_BOND_DONOR_N, FISPtr(new Pharm::HBondingInteractionScore(false)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_N2, FeatureType::H_BOND_DONOR_O, FISPtr(new Pharm::HBondingInteractionScore(false)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_N2, FeatureType::H_BOND_DONOR_S, FISPtr(new Pharm::HBondingInteractionScore(false)) });
                        
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_N1, FeatureType::H_BOND_DONOR_N, FISPtr(new Pharm::HBondingInteractionScore(false)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_N1, FeatureType::H_BOND_DONOR_O, FISPtr(new Pharm::HBondingInteractionScore(false)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_N1, FeatureType::H_BOND_DONOR_S, FISPtr(new Pharm::HBondingInteractionScore(false)) });
                      
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_Nar, FeatureType::H_BOND_DONOR_N, FISPtr(new Pharm::HBondingInteractionScore(false)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_Nar, FeatureType::H_BOND_DONOR_O, FISPtr(new Pharm::HBondingInteractionScore(false)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_Nar, FeatureType::H_BOND_DONOR_S, FISPtr(new Pharm::HBondingInteractionScore(false)) });
                        
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_Npl3, FeatureType::H_BOND_DONOR_N, FISPtr(new Pharm::HBondingInteractionScore(false)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_Npl3, FeatureType::H_BOND_DONOR_O, FISPtr(new Pharm::HBondingInteractionScore(false)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_Npl3, FeatureType::H_BOND_DONOR_S, FISPtr(new Pharm::HBondingInteractionScore(false)) });
                      
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_O3, FeatureType::H_BOND_DONOR_N, FISPtr(new Pharm::HBondingInteractionScore(false)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_O3, FeatureType::H_BOND_DONOR_O, FISPtr(new Pharm::HBondingInteractionScore(false)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_O3, FeatureType::H_BOND_DONOR_S, FISPtr(new Pharm::HBondingInteractionScore(false)) });
                     
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_O2, FeatureType::H_BOND_DONOR_N, FISPtr(new Pharm::HBondingInteractionScore(false)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_O2, FeatureType::H_BOND_DONOR_O, FISPtr(new Pharm::HBondingInteractionScore(false)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_O2, FeatureType::H_BOND_DONOR_S, FISPtr(new Pharm::HBondingInteractionScore(false)) });
                    
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_Oco2, FeatureType::H_BOND_DONOR_N, FISPtr(new Pharm::HBondingInteractionScore(false)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_Oco2, FeatureType::H_BOND_DONOR_O, FISPtr(new Pharm::HBondingInteractionScore(false)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_Oco2, FeatureType::H_BOND_DONOR_S, FISPtr(new Pharm::HBondingInteractionScore(false)) });
                    
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_S3, FeatureType::H_BOND_DONOR_N, FISPtr(new Pharm::HBondingInteractionScore(false)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_S3, FeatureType::H_BOND_DONOR_O, FISPtr(new Pharm::HBondingInteractionScore(false)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_S3, FeatureType::H_BOND_DONOR_S, FISPtr(new Pharm::HBondingInteractionScore(false)) });
                       
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_S2, FeatureType::H_BOND_DONOR_N, FISPtr(new Pharm::HBondingInteractionScore(false)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_S2, FeatureType::H_BOND_DONOR_O, FISPtr(new Pharm::HBondingInteractionScore(false)) });
        ftrInteractionFuncList.push_back({ FeatureType::H_BOND_ACCEPTOR_S2, FeatureType::H_BOND_DONOR_S, FISPtr(new Pharm::HBondingInteractionScore(false)) });
                     
        ftrInteractionFuncList.push_back({ FeatureType::HALOGEN_BOND_DONOR, FeatureType::HALOGEN_BOND_ACCEPTOR, FISPtr(new Pharm::XBondingInteractionScore(true)) });
    }

    GRAIL::GRAILDescriptorCalculatorImpl::FeatureTypeInfoList ligandDescrFtrTypes({
        { GRAIL::FeatureType::POSITIVE_IONIZABLE,    false },
        { GRAIL::FeatureType::NEGATIVE_IONIZABLE,    false },
        { GRAIL::FeatureType::AROMATIC,              false },
        { GRAIL::FeatureType::HYDROPHOBIC,           false },
        { GRAIL::FeatureType::H_BOND_DONOR,          true  },
        { GRAIL::FeatureType::H_BOND_ACCEPTOR,       false },
        { GRAIL::FeatureType::HALOGEN_BOND_DONOR,    false },
        { GRAIL::FeatureType::HALOGEN_BOND_ACCEPTOR, false },
        { GRAIL::FeatureType::H_BOND_DONOR_N3,       true  },
        { GRAIL::FeatureType::H_BOND_DONOR_N2,       true  },
        { GRAIL::FeatureType::H_BOND_DONOR_Nar,      true  },
        { GRAIL::FeatureType::H_BOND_DONOR_Nam,      true  },
        { GRAIL::FeatureType::H_BOND_DONOR_Npl3,     true  },
        { GRAIL::FeatureType::H_BOND_DONOR_N4,       true  },
        { GRAIL::FeatureType::H_BOND_DONOR_O3,       true  },
        { GRAIL::FeatureType::H_BOND_DONOR_S3,       true  },
        { GRAIL::FeatureType::H_BOND_ACCEPTOR_N3,    false },
        { GRAIL::FeatureType::H_BOND_ACCEPTOR_N2,    false },
        { GRAIL::FeatureType::H_BOND_ACCEPTOR_N1,    false },
        { GRAIL::FeatureType::H_BOND_ACCEPTOR_Nar,   false },
        { GRAIL::FeatureType::H_BOND_ACCEPTOR_Npl3,  false },
        { GRAIL::FeatureType::H_BOND_ACCEPTOR_O3,    false },
        { GRAIL::FeatureType::H_BOND_ACCEPTOR_O2,    false },
        { GRAIL::FeatureType::H_BOND_ACCEPTOR_Oco2,  false },
        { GRAIL::FeatureType::H_BOND_ACCEPTOR_S3,    false },
        { GRAIL::FeatureType::H_BOND_ACCEPTOR_S2,    false }
    });

    GRAIL::GRAILDescriptorCalculatorImpl::FeatureTypeInfoList tgtEnvOccupHBAHBDTypes({
        { GRAIL::FeatureType::H_BOND_ACCEPTOR_N, false },
        { GRAIL::FeatureType::H_BOND_ACCEPTOR_O, false },
        { GRAIL::FeatureType::H_BOND_ACCEPTOR_S, false },
        { GRAIL::FeatureType::H_BOND_DONOR_N,    true  },
        { GRAIL::FeatureType::H_BOND_DONOR_O,    true  },
        { GRAIL::FeatureType::H_BOND_DONOR_S,    true  }
    });
}


constexpr std::size_t GRAIL::GRAILXDescriptorCalculator::TOTAL_DESCRIPTOR_SIZE;
constexpr std::size_t GRAIL::GRAILXDescriptorCalculator::LIGAND_DESCRIPTOR_SIZE;


GRAIL::GRAILXDescriptorCalculator::GRAILXDescriptorCalculator(): impl() {}

GRAIL::GRAILXDescriptorCalculator::GRAILXDescriptorCalculator(const GRAILXDescriptorCalculator& calc):
    impl(calc.impl ? new GRAILDescriptorCalculatorImpl(*calc.impl) : nullptr) {}

GRAIL::GRAILXDescriptorCalculator::~GRAILXDescriptorCalculator() {}

GRAIL::GRAILXDescriptorCalculator& GRAIL::GRAILXDescriptorCalculator::operator=(const GRAILXDescriptorCalculator& calc)
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

void GRAIL::GRAILXDescriptorCalculator::initTargetData(const Chem::MolecularGraph& tgt_env, const Chem::Atom3DCoordinatesFunction& coords_func, bool tgt_env_changed)
{
    initCalculatorImpl();

    impl->initTargetData(tgt_env, coords_func, tgt_env_changed);
}

void GRAIL::GRAILXDescriptorCalculator::initLigandData(const Chem::MolecularGraph& ligand)
{
   initCalculatorImpl();

   impl->initLigandData(ligand);
}

void GRAIL::GRAILXDescriptorCalculator::calculate(const Math::Vector3DArray& atom_coords, Math::DVector& descr, bool update_lig_part)
{
    if (!impl)
        return;
    
    if (descr.getSize() < TOTAL_DESCRIPTOR_SIZE)
        descr.resize(TOTAL_DESCRIPTOR_SIZE);

    impl->calculate(atom_coords, descr, update_lig_part);
}

void GRAIL::GRAILXDescriptorCalculator::initCalculatorImpl()
{
    if (impl)
        return;
    
    std::call_once(initFtrInteractionFuncListFlag, &initFtrInteractionFuncList);

    impl.reset(new GRAILDescriptorCalculatorImpl(ftrInteractionFuncList, ligandDescrFtrTypes, tgtEnvOccupHBAHBDTypes, &perceiveExtendedType));
}

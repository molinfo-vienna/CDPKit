/* 
 * GRAILXDescriptorCalculator.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::GRAIL::GRAILXDescriptorCalculator.
 */

#ifndef CDPL_GRAIL_GRAILXDESCRIPTORCALCULATOR_HPP
#define CDPL_GRAIL_GRAILXDESCRIPTORCALCULATOR_HPP

#include <cstddef>
#include <memory>

#include "CDPL/GRAIL/APIPrefix.hpp"
#include "CDPL/Chem/Atom3DCoordinatesFunction.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Math/Vector.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
    }
    
    namespace GRAIL
    {

        class GRAILDescriptorCalculatorImpl;
        
        /**
         * \brief GRAILXDescriptorCalculator.
         * \see [\ref GRAIL]
         */
        class CDPL_GRAIL_API GRAILXDescriptorCalculator
        {

          public:
            static constexpr std::size_t TOTAL_DESCRIPTOR_SIZE  = 177;
            static constexpr std::size_t LIGAND_DESCRIPTOR_SIZE = 31;

            typedef std::shared_ptr<GRAILXDescriptorCalculator> SharedPointer;

            enum ElementIndex
            {

                PI_COUNT,
                NI_COUNT,
                AR_COUNT,
                H_COUNT,
                HBD_COUNT,
                HBA_COUNT,
                XBD_COUNT,
                XBA_COUNT,
                HBD_N3_COUNT,
                HBD_N2_COUNT,
                HBD_Nar_COUNT,
                HBD_Nam_COUNT,
                HBD_Npl3_COUNT,
                HBD_N4_COUNT,
                HBD_O3_COUNT,
                HBD_S3_COUNT,
                HBA_N3_COUNT,
                HBA_N2_COUNT,
                HBA_N1_COUNT,
                HBA_Nar_COUNT,
                HBA_Npl3_COUNT,
                HBA_O3_COUNT,
                HBA_O2_COUNT,
                HBA_Oco2_COUNT,
                HBA_S3_COUNT,
                HBA_S2_COUNT,
                HVY_ATOM_COUNT,
                ROT_BOND_COUNT,
                TOTAL_HYD,
                LOGP,
                TPSA,
                ENV_HBA_N_OCC_SUM,
                ENV_HBA_N_OCC_MAX,
                ENV_HBA_O_OCC_SUM,
                ENV_HBA_O_OCC_MAX,
                ENV_HBA_S_OCC_SUM,
                ENV_HBA_S_OCC_MAX,
                ENV_HBD_N_OCC_SUM,
                ENV_HBD_N_OCC_MAX,
                ENV_HBD_O_OCC_SUM,
                ENV_HBD_O_OCC_MAX,
                ENV_HBD_S_OCC_SUM,
                ENV_HBD_S_OCC_MAX,
                PI_AR_SCORE_SUM,
                PI_AR_SCORE_MAX,
                AR_PI_SCORE_SUM,
                AR_PI_SCORE_MAX,
                H_H_SCORE_SUM,
                H_H_SCORE_MAX,
                AR_AR_SCORE_SUM,
                AR_AR_SCORE_MAX,
                HBD_HBA_N_SCORE_SUM,
                HBD_HBA_N_SCORE_MAX,
                HBD_HBA_O_SCORE_SUM,
                HBD_HBA_O_SCORE_MAX,
                HBD_HBA_S_SCORE_SUM,
                HBD_HBA_S_SCORE_MAX,
                HBD_N3_HBA_N_SCORE_SUM,
                HBD_N3_HBA_N_SCORE_MAX,
                HBD_N3_HBA_O_SCORE_SUM,
                HBD_N3_HBA_O_SCORE_MAX,
                HBD_N3_HBA_S_SCORE_SUM,
                HBD_N3_HBA_S_SCORE_MAX,
                HBD_N2_HBA_N_SCORE_SUM,
                HBD_N2_HBA_N_SCORE_MAX,
                HBD_N2_HBA_O_SCORE_SUM,
                HBD_N2_HBA_O_SCORE_MAX,
                HBD_N2_HBA_S_SCORE_SUM,
                HBD_N2_HBA_S_SCORE_MAX,
                HBD_Nar_HBA_N_SCORE_SUM,
                HBD_Nar_HBA_N_SCORE_MAX,
                HBD_Nar_HBA_O_SCORE_SUM,
                HBD_Nar_HBA_O_SCORE_MAX,
                HBD_Nar_HBA_S_SCORE_SUM,
                HBD_Nar_HBA_S_SCORE_MAX,
                HBD_Nam_HBA_N_SCORE_SUM,
                HBD_Nam_HBA_N_SCORE_MAX,
                HBD_Nam_HBA_O_SCORE_SUM,
                HBD_Nam_HBA_O_SCORE_MAX,
                HBD_Nam_HBA_S_SCORE_SUM,
                HBD_Nam_HBA_S_SCORE_MAX,
                HBD_Npl3_HBA_N_SCORE_SUM,
                HBD_Npl3_HBA_N_SCORE_MAX,
                HBD_Npl3_HBA_O_SCORE_SUM,
                HBD_Npl3_HBA_O_SCORE_MAX,
                HBD_Npl3_HBA_S_SCORE_SUM,
                HBD_Npl3_HBA_S_SCORE_MAX,
                HBD_N4_HBA_N_SCORE_SUM,
                HBD_N4_HBA_N_SCORE_MAX,
                HBD_N4_HBA_O_SCORE_SUM,
                HBD_N4_HBA_O_SCORE_MAX,
                HBD_N4_HBA_S_SCORE_SUM,
                HBD_N4_HBA_S_SCORE_MAX,
                HBD_O3_HBA_N_SCORE_SUM,
                HBD_O3_HBA_N_SCORE_MAX,
                HBD_O3_HBA_O_SCORE_SUM,
                HBD_O3_HBA_O_SCORE_MAX,
                HBD_O3_HBA_S_SCORE_SUM,
                HBD_O3_HBA_S_SCORE_MAX,
                HBD_S3_HBA_N_SCORE_SUM,
                HBD_S3_HBA_N_SCORE_MAX,
                HBD_S3_HBA_O_SCORE_SUM,
                HBD_S3_HBA_O_SCORE_MAX,
                HBD_S3_HBA_S_SCORE_SUM,
                HBD_S3_HBA_S_SCORE_MAX,
                HBA_HBD_N_SCORE_SUM,
                HBA_HBD_N_SCORE_MAX,
                HBA_HBD_O_SCORE_SUM,
                HBA_HBD_O_SCORE_MAX,
                HBA_HBD_S_SCORE_SUM,
                HBA_HBD_S_SCORE_MAX,
                HBA_N3_HBD_N_SCORE_SUM,
                HBA_N3_HBD_N_SCORE_MAX,
                HBA_N3_HBD_O_SCORE_SUM,
                HBA_N3_HBD_O_SCORE_MAX,
                HBA_N3_HBD_S_SCORE_SUM,
                HBA_N3_HBD_S_SCORE_MAX,
                HBA_N2_HBD_N_SCORE_SUM,
                HBA_N2_HBD_N_SCORE_MAX,
                HBA_N2_HBD_O_SCORE_SUM,
                HBA_N2_HBD_O_SCORE_MAX,
                HBA_N2_HBD_S_SCORE_SUM,
                HBA_N2_HBD_S_SCORE_MAX,
                HBA_N1_HBD_N_SCORE_SUM,
                HBA_N1_HBD_N_SCORE_MAX,
                HBA_N1_HBD_O_SCORE_SUM,
                HBA_N1_HBD_O_SCORE_MAX,
                HBA_N1_HBD_S_SCORE_SUM,
                HBA_N1_HBD_S_SCORE_MAX,
                HBA_Nar_HBD_N_SCORE_SUM,
                HBA_Nar_HBD_N_SCORE_MAX,
                HBA_Nar_HBD_O_SCORE_SUM,
                HBA_Nar_HBD_O_SCORE_MAX,
                HBA_Nar_HBD_S_SCORE_SUM,
                HBA_Nar_HBD_S_SCORE_MAX,
                HBA_Npl3_HBD_N_SCORE_SUM,
                HBA_Npl3_HBD_N_SCORE_MAX,
                HBA_Npl3_HBD_O_SCORE_SUM,
                HBA_Npl3_HBD_O_SCORE_MAX,
                HBA_Npl3_HBD_S_SCORE_SUM,
                HBA_Npl3_HBD_S_SCORE_MAX,
                HBA_O3_HBD_N_SCORE_SUM,
                HBA_O3_HBD_N_SCORE_MAX,
                HBA_O3_HBD_O_SCORE_SUM,
                HBA_O3_HBD_O_SCORE_MAX,
                HBA_O3_HBD_S_SCORE_SUM,
                HBA_O3_HBD_S_SCORE_MAX,
                HBA_O2_HBD_N_SCORE_SUM,
                HBA_O2_HBD_N_SCORE_MAX,
                HBA_O2_HBD_O_SCORE_SUM,
                HBA_O2_HBD_O_SCORE_MAX,
                HBA_O2_HBD_S_SCORE_SUM,
                HBA_O2_HBD_S_SCORE_MAX,
                HBA_Oco2_HBD_N_SCORE_SUM,
                HBA_Oco2_HBD_N_SCORE_MAX,
                HBA_Oco2_HBD_O_SCORE_SUM,
                HBA_Oco2_HBD_O_SCORE_MAX,
                HBA_Oco2_HBD_S_SCORE_SUM,
                HBA_Oco2_HBD_S_SCORE_MAX,
                HBA_S3_HBD_N_SCORE_SUM,
                HBA_S3_HBD_N_SCORE_MAX,
                HBA_S3_HBD_O_SCORE_SUM,
                HBA_S3_HBD_O_SCORE_MAX,
                HBA_S3_HBD_S_SCORE_SUM,
                HBA_S3_HBD_S_SCORE_MAX,
                HBA_S2_HBD_N_SCORE_SUM,
                HBA_S2_HBD_N_SCORE_MAX,
                HBA_S2_HBD_O_SCORE_SUM,
                HBA_S2_HBD_O_SCORE_MAX,
                HBA_S2_HBD_S_SCORE_SUM,
                HBA_S2_HBD_S_SCORE_MAX,
                XBD_XBA_SCORE_SUM,
                XBD_XBA_SCORE_MAX,
                ES_ENERGY,
                ES_ENERGY_SQRD_DIST,
                VDW_ENERGY_ATT,
                VDW_ENERGY_REP
            };

            GRAILXDescriptorCalculator();

            GRAILXDescriptorCalculator(const GRAILXDescriptorCalculator& calc);

            ~GRAILXDescriptorCalculator();
            
            GRAILXDescriptorCalculator& operator=(const GRAILXDescriptorCalculator& calc);

            void initTargetData(const Chem::MolecularGraph& tgt_env, const Chem::Atom3DCoordinatesFunction& coords_func,
                                bool tgt_env_changed = true);

            void initLigandData(const Chem::MolecularGraph& ligand);

            void calculate(const Math::Vector3DArray& atom_coords, Math::DVector& descr, bool update_lig_part = true);

          private:
            void initCalculatorImpl();

            typedef std::unique_ptr<GRAILDescriptorCalculatorImpl> ImplementationPointer;

            ImplementationPointer impl;
        };
    } // namespace GRAIL
} // namespace CDPL

#endif // CDPL_GRAIL_GRAILXDESCRIPTORCALCULATOR_HPP

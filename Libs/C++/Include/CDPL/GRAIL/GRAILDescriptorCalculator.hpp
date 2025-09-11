/* 
 * GRAILDescriptorCalculator.hpp 
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
 * \brief Definition of class CDPL::GRAIL::GRAILDescriptorCalculator.
 */

#ifndef CDPL_GRAIL_GRAILDESCRIPTORCALCULATOR_HPP
#define CDPL_GRAIL_GRAILDESCRIPTORCALCULATOR_HPP

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
         * \brief GRAILDescriptorCalculator.
         * \see [\ref GRAIL]
         */
        class CDPL_GRAIL_API GRAILDescriptorCalculator
        {

          public:
            static constexpr std::size_t TOTAL_DESCRIPTOR_SIZE  = 35;
            static constexpr std::size_t LIGAND_DESCRIPTOR_SIZE = 13;

            typedef std::shared_ptr<GRAILDescriptorCalculator> SharedPointer;
            
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
                HVY_ATOM_COUNT,
                ROT_BOND_COUNT,
                TOTAL_HYD,
                LOGP,
                TPSA,
                ENV_HBA_OCC_SUM,
                ENV_HBA_OCC_MAX,
                ENV_HBD_OCC_SUM,
                ENV_HBD_OCC_MAX,
                PI_AR_SCORE_SUM,
                PI_AR_SCORE_MAX,
                AR_PI_SCORE_SUM,
                AR_PI_SCORE_MAX,
                H_H_SCORE_SUM,
                H_H_SCORE_MAX,
                AR_AR_SCORE_SUM,
                AR_AR_SCORE_MAX,
                HBD_HBA_SCORE_SUM,
                HBD_HBA_SCORE_MAX,
                HBA_HBD_SCORE_SUM,
                HBA_HBD_SCORE_MAX,
                XBD_XBA_SCORE_SUM,
                XBD_XBA_SCORE_MAX,
                ES_ENERGY,
                ES_ENERGY_SQRD_DIST,
                VDW_ENERGY_ATT,
                VDW_ENERGY_REP
            };

            GRAILDescriptorCalculator();

            GRAILDescriptorCalculator(const GRAILDescriptorCalculator& calc);

            ~GRAILDescriptorCalculator();
            
            GRAILDescriptorCalculator& operator=(const GRAILDescriptorCalculator& calc);

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

#endif // CDPL_GRAIL_GRAILDESCRIPTORCALCULATOR_HPP

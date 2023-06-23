/* 
 * HBondDonorFeatureGenerator.hpp 
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
 * \brief Definition of the class CDPL::Pharm::HBondDonorFeatureGenerator.
 */

#ifndef CDPL_PHARM_HBONDDONORFEATUREGENERATOR_HPP
#define CDPL_PHARM_HBONDDONORFEATUREGENERATOR_HPP

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/PatternBasedFeatureGenerator.hpp"


namespace CDPL 
{

    namespace Pharm
    {

        /**
         * \brief HBondDonorFeatureGenerator.
         */
        class CDPL_PHARM_API HBondDonorFeatureGenerator : public PatternBasedFeatureGenerator
        {

          public:
            /**
             * \brief Constructs the \c %HBondDonorFeatureGenerator instance.
             * \param static_h_bonds \c true if hydrogens on donor atoms connected via rotatable bonds should be 
             *                       considered static and emitted features modeled as defined vectors, and \c false otherwise.
             */
            HBondDonorFeatureGenerator(bool static_h_bonds);
                
            /**
             * \brief Perceives the hydrogen bond donor features of the molecular graph a\ molgraph and adds 
             *        them to the pharmacophore \a pharm.
             * \param molgraph The molecular graph for which to perceive the features.
             * \param pharm The output pharmacophore where to add the generated features.
             * \param static_h_bonds \c true if hydrogens on donor atoms connected via rotatable bonds should be 
             *                       considered static and emitted features modeled as defined vectors, and \c false otherwise.
             */
            HBondDonorFeatureGenerator(const Chem::MolecularGraph& molgraph, Pharmacophore& pharm, bool static_h_bonds);
        
          private:
            void init(bool static_h_bonds);
        };
    }
}

#endif // CDPL_PHARM_HBONDDONORFEATUREGENERATOR_HPP

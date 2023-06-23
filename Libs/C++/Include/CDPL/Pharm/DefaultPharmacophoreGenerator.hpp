/* 
 * DefaultPharmacophoreGenerator.hpp 
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
 * \brief Definition of the class CDPL::Pharm::DefaultPharmacophoreGenerator.
 */

#ifndef CDPL_PHARM_DEFAULTPHARMACOPHOREGENERATOR_HPP
#define CDPL_PHARM_DEFAULTPHARMACOPHOREGENERATOR_HPP

#include <vector>

#include "CDPL/Pharm/APIPrefix.hpp"
#include "CDPL/Pharm/PharmacophoreGenerator.hpp"


namespace CDPL 
{

    namespace Pharm
    {

        /**
         * \brief DefaultPharmacophoreGenerator.
         */
        class CDPL_PHARM_API DefaultPharmacophoreGenerator : public PharmacophoreGenerator
        {

          public:
            /**
             * \brief Flags controlling feature generation.
             */
            enum Configuration
            {
            
              /**
               * \brief If set, ionic features are only generated for explicitely charged atoms/groups.
               */
              PI_NI_ON_CHARGED_GROUPS_ONLY = 0x1,

              /**
               * \brief If set, the HBD feature representation will always be a defined vector
               *        from the hydrogen donor heavy atom to the hydrogen atom.
               */
              STATIC_H_DONORS = 0x2,

              /**
               * \brief Default configuration.
               */
              DEFAULT_CONFIG = 0
            };

            /**
             * \brief Constructs the \c %DefaultPharmacophoreGenerator instance.
             */
            DefaultPharmacophoreGenerator(int config = DEFAULT_CONFIG);

            /**
             * \brief Perceives all pharmacophore features of the molecular graph a\ molgraph
             *        and adds them to the pharmacophore \a pharm.
             * \param molgraph The molecular graph for which to perceive the features.
             * \param pharm The output pharmacophore where to add the generated features.
             * \param config Feature generation configuration.
             */
            DefaultPharmacophoreGenerator(const Chem::MolecularGraph& molgraph, Pharmacophore& pharm, int config = DEFAULT_CONFIG);

            void applyConfiguration(int config);
            
          private:
            void init(int config);
        };
    }
}

#endif // CDPL_PHARM_DEFAULTPHARMACOPHOREGENERATOR_HPP

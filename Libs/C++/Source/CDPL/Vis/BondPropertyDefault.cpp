/* 
 * BondPropertyDefault.cpp 
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

#include "CDPL/Vis/BondPropertyDefault.hpp"


namespace CDPL
{

    namespace Vis
    {

        namespace BondPropertyDefault
        {

            const Color             COLOR                        = Color(0, 0, 0);
            const SizeSpecification LINE_WIDTH                   = SizeSpecification(1.0, false, false, true);
            const SizeSpecification LINE_SPACING                 = SizeSpecification(0.15, true, true, true);
            const SizeSpecification STEREO_BOND_WEDGE_WIDTH      = SizeSpecification(0.15, true, true, true);
            const SizeSpecification STEREO_BOND_HASH_SPACING     = SizeSpecification(0.1, true, true, true);
            const SizeSpecification REACTION_CENTER_LINE_LENGTH  = SizeSpecification(0.4, true, true, true);
            const SizeSpecification REACTION_CENTER_LINE_SPACING = SizeSpecification(0.1, true, true, true);
            const SizeSpecification DOUBLE_BOND_TRIM_LENGTH      = SizeSpecification(0.1, true, true, true);
            const SizeSpecification TRIPLE_BOND_TRIM_LENGTH      = SizeSpecification(0.1, true, true, true);
            const Font              LABEL_FONT                   = Font();
            const SizeSpecification LABEL_SIZE                   = SizeSpecification(8.0, false, false, true);
            const SizeSpecification LABEL_MARGIN                 = SizeSpecification(2.0, false, false, true);
            const Font              CONFIGURATION_LABEL_FONT            = Font();
            const SizeSpecification CONFIGURATION_LABEL_SIZE            = SizeSpecification(8.0, false, false, true);
        }

        void initBondPropertyDefaults() {}
    }
}

/* 
 * PMLFormatData.hpp
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


#ifndef CDPL_PHARM_PMLFORMATDATA_HPP
#define CDPL_PHARM_PMLFORMATDATA_HPP

#include <string>


namespace CDPL
{

    namespace Pharm
    {

        namespace PML
        {
            
            
            const std::string DOC_PROLOG = "<ElementContainer activeResult=\"-1\">\n <ContainerPharmacophores>";
            const std::string DOC_EPILOG = " </ContainerPharmacophores>\n</ElementContainer>";

            const std::string DEFAULT_FLAG_CODE       = "111000000";
            const std::string PHARM_TYPE_LIGAND_SCOUT = "LIGAND_SCOUT";
            const std::string VOLUME_TYPE_EXCLUSION   = "exclusion";
            
            namespace Element
            {

                const std::string ALIGNMENT_ELEM = "alignmentElement";
                const std::string PHARMACOPHORE  = "pharmacophore";
                const std::string POINT_FEATURE  = "point";
                const std::string PLANE_FEATURE  = "plane";
                const std::string VECTOR_FEATURE = "vector";
                const std::string VOLUME_FEATURE = "volume";

                const std::string FEATURE_POSITION = "position";
                const std::string FEATURE_NORMAL   = "normal";
                const std::string FEATURE_ORIGIN   = "origin";
                const std::string FEATURE_TARGET   = "target";
            } // namespace Element

            namespace Attribute
            {

                const std::string NAME                    = "name";
                const std::string FLAG_CODE               = "flagCode";
                const std::string ID                      = "id";
                const std::string FEATURE_ID              = "featureId";
                const std::string OPTIONAL                = "optional";
                const std::string DISABLED                = "disabled";
                const std::string WEIGHT                  = "weight";
                const std::string POINTS_TO_LIGAND        = "pointsToLigand";
                const std::string HAS_SYN_PROJECTED_POINT = "hasSyntheticProjectedPoint";
                const std::string TYPE                    = "type";
                const std::string TOLERANCE               = "tolerance";
                const std::string COORDS_X                = "x3";
                const std::string COORDS_Y                = "y3";
                const std::string COORDS_Z                = "z3";
                const std::string PHARM_TYPE              = "pharmacophoreType";
            } // namespace Attribute

            namespace FeatureName
            {

                const std::string HYDROPHOBIC     = "H";
                const std::string AROMATIC        = "AR";
                const std::string NEG_IONIZABLE   = "NI";
                const std::string POS_IONIZABLE   = "PI";
                const std::string H_BOND_DONOR    = "HBD";
                const std::string H_BOND_ACCEPTOR = "HBA";
                const std::string X_BOND_DONOR    = "XBD";
                const std::string X_BOND_ACCEPTOR = "XBA";
            } // namespace FeatureName
        } // namespace PML
    } // namespace Pharm
} // namespace CDPL

#endif // CDPL_PHARM_PMLFORMATDATA_HPP

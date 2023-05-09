/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

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

			const std::string ELEM_CONTAINER_HEADER  = "<ElementContainer activeResult=\"-1\"><ContainerPharmacophores>";
			const std::string ELEM_CONTAINER_FOOTER  = "</ContainerPharmacophores></ElementContainer>";

			const std::string ALIGNMENT_ELEM_TAG = "alignmentElement";
			const std::string PHARMACOPHORE_TAG  = "pharmacophore";
			const std::string POINT_FEATURE_TAG  = "point";
			const std::string PLANE_FEATURE_TAG  = "plane";
			const std::string VECTOR_FEATURE_TAG = "vector";
			const std::string VOLUME_FEATURE_TAG = "volume";

			const std::string FEATURE_POSITION_TAG = "position";
			const std::string FEATURE_NORMAL_TAG   = "normal";
			const std::string FEATURE_ORIGIN_TAG   = "origin";
			const std::string FEATURE_TARGET_TAG   = "target";

			const std::string NAME_ATTRIBUTE             = "name";
			const std::string FLAG_CODE_ATTRIBUTE        = "flagCode";
			const std::string ID_ATTRIBUTE               = "id";
			const std::string FEATURE_ID_ATTRIBUTE       = "featureId";
			const std::string OPTIONAL_ATTRIBUTE         = "optional";
			const std::string DISABLED_ATTRIBUTE         = "disabled";
			const std::string WEIGHT_ATTRIBUTE           = "weight";
			const std::string POINTS_TO_LIGAND_ATTRIBUTE = "pointsToLigand";
			const std::string PROJECTED_POINT_ATTRIBUTE  = "hasSyntheticProjectedPoint";
			const std::string TYPE_ATTRIBUTE             = "type";
			const std::string TOLERANCE_ATTRIBUTE        = "tolerance";
			const std::string COORDS_X_ATTRIBUTE         = "x3";
			const std::string COORDS_Y_ATTRIBUTE         = "y3";
			const std::string COORDS_Z_ATTRIBUTE         = "z3";
			const std::string PHARM_TYPE_ATTRIBUTE       = "pharmacophoreType";

			const std::string DEFAULT_FLAG_CODE          = "111000000";
			const std::string PHARM_TYPE_LIGAND_SCOUT    = "LIGAND_SCOUT";
			const std::string VOLUME_TYPE_EXCLUSION      = "exclusion";

			const std::string HYDROPHOBIC_FEATURE_NAME     = "H";
			const std::string AROMATIC_FEATURE_NAME        = "AR";
			const std::string NEG_IONIZABLE_FEATURE_NAME   = "NI";
			const std::string POS_IONIZABLE_FEATURE_NAME   = "PI";
			const std::string H_BOND_DONOR_FEATURE_NAME    = "HBD";
			const std::string H_BOND_ACCEPTOR_FEATURE_NAME = "HBA";
			const std::string X_BOND_DONOR_FEATURE_NAME    = "XBD";
			const std::string X_BOND_ACCEPTOR_FEATURE_NAME = "XBA";
		}
    }
}

#endif // CDPL_PHARM_PMLFORMATDATA_HPP

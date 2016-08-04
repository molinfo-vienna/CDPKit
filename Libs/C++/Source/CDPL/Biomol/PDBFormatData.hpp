/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PDBFormatData.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#ifndef CDPL_BIOMOL_PDBFORMATDATA_HPP
#define CDPL_BIOMOL_PDBFORMATDATA_HPP

#include <cstddef>
#include <string>


namespace CDPL
{

	namespace Biomol
	{
		
		namespace PDB
		{
		
			const std::size_t MAX_LINE_LENGTH      = 80;
			const std::size_t RECORD_NAME_LENGTH   = 6;
			const char        END_OF_LINE          = '\n';

			// Title Section
			const std::string  HEADER_PREFIX       = "HEADER";
			const std::string  OBSLTE_PREFIX       = "OBSLTE";
			const std::string  TITLE_PREFIX        = "TITLE";
			const std::string  SPLIT_PREFIX        = "SPLIT";
			const std::string  CAVEAT_PREFIX       = "CAVEAT";
			const std::string  COMPND_PREFIX       = "COMPND";
			const std::string  SOURCE_PREFIX       = "SOURCE";
			const std::string  KEYWDS_PREFIX       = "KEYWDS";
			const std::string  EXPDTA_PREFIX       = "EXPDTA";
			const std::string  NUMMDL_PREFIX       = "NUMMDL";
			const std::string  MDLTYP_PREFIX       = "MDLTYP";
			const std::string  AUTHOR_PREFIX       = "AUTHOR";
			const std::string  REVDAT_PREFIX       = "REVDAT";
			const std::string  SPRSDE_PREFIX       = "SPRSDE";
			const std::string  JRNL_PREFIX         = "JRNL";

			// Remark Annotations
			const std::string  REMARK_PREFIX       = "REMARK";

			// Primary Structure
			const std::string  DBREF_PREFIX        = "DBREF";
			const std::string  DBREF1_PREFIX       = "DBREF1";
			const std::string  DBREF2_PREFIX       = "DBREF2";
			const std::string  SEQADV_PREFIX       = "SEQADV";
			const std::string  SEQRES_PREFIX       = "SEQRES";
			const std::string  MODRES_PREFIX       = "MODRES";

			// Heterogen Section
			const std::string  HET_PREFIX          = "HET";
			const std::string  FORMUL_PREFIX       = "FORMUL";
			const std::string  HETNAM_PREFIX       = "HETNAM";
			const std::string  HETSYN_PREFIX       = "HETSYN";

			// Secondary Structure
			const std::string  HELIX_PREFIX        = "HELIX";
			const std::string  SHEET_PREFIX        = "SHEET";
			const std::string  TURN_PREFIX         = "TURN";    // deprecated

			// Connectivity Annotations
			const std::string  SSBOND_PREFIX       = "SSBOND";
			const std::string  LINK_PREFIX         = "LINK";
			const std::string  CISPEP_PREFIX       = "CISPEP";

			// Miscellaneous Features
			const std::string  SITE_PREFIX         = "SITE";

			// Crystallographic Information
			const std::string  CRYST1_PREFIX       = "CRYST1";

			// Coordinate Transformations
			const std::string  MTRIX1_PREFIX       = "MTRIX1";
			const std::string  MTRIX2_PREFIX       = "MTRIX2";
			const std::string  MTRIX3_PREFIX       = "MTRIX3";
			const std::string  ORIGX1_PREFIX       = "ORIGX1";
			const std::string  ORIGX2_PREFIX       = "ORIGX2";
			const std::string  ORIGX3_PREFIX       = "ORIGX3";
			const std::string  SCALE1_PREFIX       = "SCALE1";
			const std::string  SCALE2_PREFIX       = "SCALE2";
			const std::string  SCALE3_PREFIX       = "SCALE3";

			// Coordinates Section
			const std::string  MODEL_PREFIX        = "MODEL";
			const std::string  ATOM_PREFIX         = "ATOM";
			const std::string  ANISOU_PREFIX       = "ANISOU";
			const std::string  TER_PREFIX          = "TER";
			const std::string  HETATM_PREFIX       = "HETATM";
			const std::string  ENDMDL_PREFIX       = "ENDMDL";
			
			// Connectivity Information
			const std::string  CONECT_PREFIX       = "CONECT";

			// Bookkeeping
			const std::string  MASTER_PREFIX       = "MASTER";
			const std::string  END_PREFIX          = "END";

			// Deprectated
			const std::string  HYDBND_PREFIX       = "HYDBND";
			const std::string  SLTBRG_PREFIX       = "SLTBRG";

			// Special marker for non-water HETATM records
			const std::string  HETGRP_PREFIX       = "HETGRP";

			const std::size_t  HEADER_DATA_LENGTH  = 60;
			const std::size_t  OBSLTE_DATA_LENGTH  = 69;
			const std::size_t  TITLE_DATA_LENGTH   = 74;
			const std::size_t  SPLIT_DATA_LENGTH   = 74;
			const std::size_t  CAVEAT_DATA_LENGTH  = 73;
			const std::size_t  COMPND_DATA_LENGTH  = 74;
			const std::size_t  SOURCE_DATA_LENGTH  = 73;
			const std::size_t  KEYWDS_DATA_LENGTH  = 73;
			const std::size_t  EXPDTA_DATA_LENGTH  = 73;
			const std::size_t  NUMMDL_DATA_LENGTH  = 8;
			const std::size_t  MDLTYP_DATA_LENGTH  = 74;
			const std::size_t  AUTHOR_DATA_LENGTH  = 73;
			const std::size_t  REVDAT_DATA_LENGTH  = 60;
			const std::size_t  SPRSDE_DATA_LENGTH  = 69;
			const std::size_t  JRNL_DATA_LENGTH    = 73;
			const std::size_t  REMARK_DATA_LENGTH  = 74;
			const std::size_t  DBREF_DATA_LENGTH   = 62;
			const std::size_t  DBREF1_DATA_LENGTH  = 61;
			const std::size_t  DBREF2_DATA_LENGTH  = 61;
			const std::size_t  SEQADV_DATA_LENGTH  = 64;
			const std::size_t  SEQRES_DATA_LENGTH  = 64;
			const std::size_t  MODRES_DATA_LENGTH  = 64;
			const std::size_t  HET_DATA_LENGTH     = 64;
			const std::size_t  FORMUL_DATA_LENGTH  = 64;
			const std::size_t  HETNAM_DATA_LENGTH  = 64;
			const std::size_t  HETSYN_DATA_LENGTH  = 64;
			const std::size_t  HELIX_DATA_LENGTH   = 70;
			const std::size_t  SHEET_DATA_LENGTH   = 64;
			const std::size_t  TURN_DATA_LENGTH    = 64;
			const std::size_t  SSBOND_DATA_LENGTH  = 72;
			const std::size_t  LINK_DATA_LENGTH    = 72;
			const std::size_t  CISPEP_DATA_LENGTH  = 53;
			const std::size_t  SITE_DATA_LENGTH    = 55;
			const std::size_t  CRYST1_DATA_LENGTH  = 64;
			const std::size_t  MTRIX1_DATA_LENGTH  = 54;
			const std::size_t  MTRIX2_DATA_LENGTH  = 54;
			const std::size_t  MTRIX3_DATA_LENGTH  = 54;
			const std::size_t  ORIGX1_DATA_LENGTH  = 49;
			const std::size_t  ORIGX2_DATA_LENGTH  = 49;
			const std::size_t  ORIGX3_DATA_LENGTH  = 49;
			const std::size_t  SCALE1_DATA_LENGTH  = 49;
			const std::size_t  SCALE2_DATA_LENGTH  = 49;
			const std::size_t  SCALE3_DATA_LENGTH  = 49;
			const std::size_t  MODEL_DATA_LENGTH   = 8;
			const std::size_t  ATOM_DATA_LENGTH    = 74;
			const std::size_t  ANISOU_DATA_LENGTH  = 74;
			const std::size_t  TER_DATA_LENGTH     = 21;
			const std::size_t  HETATM_DATA_LENGTH  = 74;
			const std::size_t  ENDMDL_DATA_LENGTH  = 0;
			const std::size_t  CONECT_DATA_LENGTH  = 25;
			const std::size_t  MASTER_DATA_LENGTH  = 64;
			const std::size_t  END_DATA_LENGTH     = 0;
			const std::size_t  HYDBND_DATA_LENGTH  = 66;
			const std::size_t  SLTBRG_DATA_LENGTH  = 66;

			const std::string  RECORD_ORDER[] = {
				HEADER_PREFIX,
				OBSLTE_PREFIX,
				TITLE_PREFIX,
				SPLIT_PREFIX,
				CAVEAT_PREFIX,
				COMPND_PREFIX,
				SOURCE_PREFIX,
				KEYWDS_PREFIX,
				EXPDTA_PREFIX,
				NUMMDL_PREFIX,
				MDLTYP_PREFIX,
				AUTHOR_PREFIX,
				REVDAT_PREFIX,
				SPRSDE_PREFIX,
				JRNL_PREFIX,
				REMARK_PREFIX,
				DBREF_PREFIX,
				DBREF1_PREFIX,
				DBREF2_PREFIX,
				SEQADV_PREFIX,
				SEQRES_PREFIX,
				MODRES_PREFIX,
				HET_PREFIX,
				HETNAM_PREFIX,
				HETSYN_PREFIX,
				FORMUL_PREFIX,
				HELIX_PREFIX,
				SHEET_PREFIX,
				TURN_PREFIX,
				SSBOND_PREFIX,
				LINK_PREFIX,
				CISPEP_PREFIX,
				SITE_PREFIX,
				CRYST1_PREFIX,
				ORIGX1_PREFIX,
				ORIGX2_PREFIX,
				ORIGX3_PREFIX,
				SCALE1_PREFIX,
				SCALE2_PREFIX,
				SCALE3_PREFIX,
				MTRIX1_PREFIX,
				MTRIX2_PREFIX,
				MTRIX3_PREFIX,
				MODEL_PREFIX,    // ---
				ATOM_PREFIX,
				ANISOU_PREFIX,
				TER_PREFIX,
				HETATM_PREFIX,
				ENDMDL_PREFIX,   // ---
				MODEL_PREFIX,    // ---
				ATOM_PREFIX,
				ANISOU_PREFIX,
				TER_PREFIX,
				HETATM_PREFIX,
				ENDMDL_PREFIX,   // ---
				CONECT_PREFIX,
				MASTER_PREFIX,
				END_PREFIX
			};

			const std::string  MANDATORY_RECORDS[][2] = {
			    { HEADER_PREFIX, "" },
				{ TITLE_PREFIX,  "" },
				{ COMPND_PREFIX, "" },
				{ SOURCE_PREFIX, "" },
				{ KEYWDS_PREFIX, "" },
				{ EXPDTA_PREFIX, "" },
				{ AUTHOR_PREFIX, "" },
				{ REVDAT_PREFIX, "" },
				{ REMARK_PREFIX, "" },
				{ SEQRES_PREFIX, ATOM_PREFIX },
				{ HET_PREFIX,    HETGRP_PREFIX },
				{ HETNAM_PREFIX, HETGRP_PREFIX },
				{ FORMUL_PREFIX, HETATM_PREFIX },
				{ CRYST1_PREFIX, "" },
				{ ORIGX1_PREFIX, "" },
				{ ORIGX2_PREFIX, "" },
				{ ORIGX3_PREFIX, "" },
				{ SCALE1_PREFIX, "" },
				{ SCALE2_PREFIX, "" },
				{ SCALE3_PREFIX, "" },
				{ TER_PREFIX,    ATOM_PREFIX },
				{ ENDMDL_PREFIX, MODEL_PREFIX },
				{ MASTER_PREFIX, "" },
				{ END_PREFIX,    "" }
			};

			const std::string  MULTILINE_RECORDS[] = {
			    HEADER_PREFIX,
			    AUTHOR_PREFIX,
				CAVEAT_PREFIX,
				COMPND_PREFIX,
				EXPDTA_PREFIX,
				MDLTYP_PREFIX,
				KEYWDS_PREFIX,
				OBSLTE_PREFIX,
				SOURCE_PREFIX,
				SPLIT_PREFIX,
				SPRSDE_PREFIX,
				TITLE_PREFIX,
				JRNL_PREFIX,
				REMARK_PREFIX,
				REVDAT_PREFIX,
				FORMUL_PREFIX,
				HETNAM_PREFIX,
				HETSYN_PREFIX,
				SEQRES_PREFIX,
				SITE_PREFIX,         
				ATOM_PREFIX,
				CISPEP_PREFIX,
				CONECT_PREFIX,
				DBREF_PREFIX,
				HELIX_PREFIX,
				TURN_PREFIX,
				HET_PREFIX,
				HETATM_PREFIX,
				LINK_PREFIX,
				MODRES_PREFIX,
				SEQADV_PREFIX,
				SHEET_PREFIX,
				SSBOND_PREFIX
			};

			const std::string  ONE_TIME_RECORDS[] = {
			    CRYST1_PREFIX,
				END_PREFIX,
				HEADER_PREFIX,
				NUMMDL_PREFIX,
				MASTER_PREFIX,
				ORIGX1_PREFIX,
				ORIGX2_PREFIX,
				ORIGX3_PREFIX,
				SCALE1_PREFIX,
				SCALE2_PREFIX,
				SCALE3_PREFIX,
				AUTHOR_PREFIX,
				CAVEAT_PREFIX,
				COMPND_PREFIX,
				EXPDTA_PREFIX,
				MDLTYP_PREFIX,
				KEYWDS_PREFIX,
				OBSLTE_PREFIX,
				SOURCE_PREFIX,
				SPLIT_PREFIX,
				SPRSDE_PREFIX,
				TITLE_PREFIX,
			};
		}
	}
}

#endif // CDPL_BIOMOL_PDBFORMATDATA_HPP

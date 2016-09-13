/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SQLScreeningDBMetaData.hpp
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


#ifndef CDPL_PHARM_SQLSCREENINGDBMETADATA_HPP
#define CDPL_PHARM_SQLSCREENINGDBMETADATA_HPP


namespace CDPL
{

    namespace Pharm
    {

		namespace SQLScreeningDB
		{

			const char* MOL_TABLE_NAME               = "molecules";
			const char* PHARM_TABLE_NAME             = "pharmacophores";
			const char* FTR_COUNT_TABLE_NAME         = "ftr_counts";
			const char* TWO_POINT_PHARM_TABLE_NAME   = "two_pt_pharms";
			const char* THREE_POINT_PHARM_TABLE_NAME = "three_pt_pharms";
	
			const char* MOL_ID_COLUMN_NAME           = "mol_id";
			const char* MOL_HASH_COLUMN_NAME         = "mol_hash";
			const char* MOL_DATA_COLUMN_NAME         = "mol_data";
			const char* MOL_CONF_IDX_COLUMN_NAME     = "mol_conf_idx";

			const char* PHARM_DATA_COLUMN_NAME       = "pharm_data";

			const char* FTR_TYPE_COLUMN_NAME         = "ftr_type";
			const char* FTR_COUNT_COLUMN_NAME        = "ftr_count";

			const char* FTR1_TYPE_COLUMN_NAME        = "ftr1_type";
			const char* FTR2_TYPE_COLUMN_NAME        = "ftr2_type";
			const char* FTR3_TYPE_COLUMN_NAME        = "ftr3_type";
	    
			const char* FTR12_DIST_COLUMN_NAME       = "ftr12_dist";
			const char* FTR23_DIST_COLUMN_NAME       = "ftr23_dist";
			const char* FTR31_DIST_COLUMN_NAME       = "ftr31_dist";
		}
    }
}

#endif // CDPL_PHARM_SQLSCREENINGDBMETADATA_HPP

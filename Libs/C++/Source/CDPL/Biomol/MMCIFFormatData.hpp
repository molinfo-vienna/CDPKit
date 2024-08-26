/* 
 * MMCIFFormatData.hpp 
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


#ifndef CDPL_BIOMOL_MMCIFFORMATDATA_HPP
#define CDPL_BIOMOL_MMCIFFORMATDATA_HPP

#include <string>


namespace CDPL
{

    namespace Biomol
    {

        namespace MMCIF
        {

            constexpr char END_OF_LINE                = '\n';
            constexpr char COMMENT_PREFIX             = '#';
            constexpr char QUOTED_STRING_DELIMITER_1  = '\'';
            constexpr char QUOTED_STRING_DELIMITER_2  = '"';
            constexpr char TEXT_FIELD_DELIMITER       = ';';
            constexpr char CATEGORY_NAME_SEPARATOR    = '.';
            constexpr char DATA_NAME_PREFIX           = '_';

            const std::string DATA_BLOCK_ID_PREFIX = "data_";
            const std::string SAVE_FRAME_PREFIX    = "save_";
            const std::string LOOP_KEYWORD         = "loop_";
            const std::string STOP_KEYWORD         = "stop_";
            const std::string GLOBAL_KEYWORD       = "global_";

            const std::string UNDEFINED_DATA_VALUE = ".";
            const std::string MISSING_DATA_VALUE   = "?";

            namespace Category
            {

                namespace AtomSite
                {

                    const std::string NAME = "atom_site";

                    namespace Item
                    {

                        const std::string group_PDB          = "group_PDB";
                        const std::string id                 = "id";
                        const std::string type_symbol        = "type_symbol";
                        const std::string label_atom_id      = "label_atom_id";
                        const std::string label_alt_id       = "label_alt_id";
                        const std::string label_comp_id      = "label_comp_id";
                        const std::string label_asym_id      = "label_asym_id";
                        const std::string label_entity_id    = "label_entity_id";
                        const std::string label_seq_id       = "label_seq_id";
                        const std::string pdbx_PDB_ins_code  = "pdbx_PDB_ins_code";
                        const std::string Cartn_x            = "Cartn_x";
                        const std::string Cartn_y            = "Cartn_y";
                        const std::string Cartn_z            = "Cartn_z";
                        const std::string occupancy          = "occupancy";
                        const std::string B_iso_or_equiv     = "B_iso_or_equiv";
                        const std::string pdbx_formal_charge = "pdbx_formal_charge";
                        const std::string auth_seq_id        = "auth_seq_id";
                        const std::string auth_comp_id       = "auth_comp_id";
                        const std::string auth_asym_id       = "auth_asym_id";
                        const std::string auth_atom_id       = "auth_atom_id";
                        const std::string pdbx_PDB_model_num = "pdbx_PDB_model_num";
                    }
                }

                namespace ChemComp
                {

                    const std::string NAME = "chem_comp";

                    namespace Item
                    {

                        const std::string ID             = "id";
                        const std::string TYPE           = "type";
                        const std::string MON_NSTD_FLAG  = "mon_nstd_flag";
                        const std::string NAME           = "name";
                        const std::string PDBX_SYNONYMS  = "pdbx_synonyms";
                        const std::string FORMULA        = "formula";
                        const std::string FORMULA_WEIGHT = "formula_weight";
                    }
                }

                namespace ChemCompAtom
                {

                    const std::string NAME = "chem_comp_atom";

                    namespace Item
                    {

                        const std::string COMP_ID       = "comp_id";
                        const std::string ATOM_ID       = "atom_id";
                        const std::string TYPE_SYMBOL   = "type_symbol";
                        const std::string AROM_FLAG     = "pdbx_aromatic_flag";
                        const std::string STEREO_CONFIG = "pdbx_stereo_config";
                        const std::string ORDINAL       = "pdbx_ordinal";
                    }
                }

                namespace ChemCompBond
                {

                    const std::string NAME = "chem_comp_bond";

                    namespace Item
                    {

                        const std::string COMP_ID       = "comp_id";
                        const std::string ATOM_ID_1     = "atom_id_1";
                        const std::string ATOM_ID_2     = "atom_id_2";
                        const std::string ORDER         = "value_order";
                        const std::string AROM_FLAG     = "pdbx_aromatic_flag";
                        const std::string STEREO_CONFIG = "pdbx_stereo_config";
                        const std::string ORDINAL       = "pdbx_ordinal";
                    }
                }
            } // namespace Category

            inline bool isSpace(char c)
            {

                switch (c) {

                    case ' ':
                    case '\t':
                    case '\r':
                    case END_OF_LINE:
                        return true;

                    default:
                        return false;
                }
            }
            
        } // namespace MMCIF
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_MMCIFFORMATDATA_HPP

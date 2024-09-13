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
            const std::string TRUE_FLAG            = "Y";
            const std::string FALSE_FLAG           = "N";

            namespace Entry
            {

                const std::string NAME = "entry";

                namespace Item
                {

                    const std::string ID = "id";
                }
            } // namespace Entry

            namespace AtomSite
            {

                const std::string NAME = "atom_site";

                namespace Item
                {

                    const std::string GROUP_PDB          = "group_PDB";
                    const std::string ID                 = "id";
                    const std::string TYPE_SYMBOL        = "type_symbol";     // mandatory
                    const std::string LABEL_ATOM_ID      = "label_atom_id";   // mandatory
                    const std::string LABEL_ALT_ID       = "label_alt_id";    // mandatory
                    const std::string LABEL_COMP_ID      = "label_comp_id";   // mandatory
                    const std::string LABEL_ASYM_ID      = "label_asym_id";   // mandatory
                    const std::string LABEL_ENTITY_ID    = "label_entity_id"; // mandatory
                    const std::string LABEL_SEQ_ID       = "label_seq_id";    // mandatory
                    const std::string COORDS_X           = "Cartn_x";
                    const std::string COORDS_Y           = "Cartn_y";
                    const std::string COORDS_Z           = "Cartn_z";
                    const std::string OCCUPANCY          = "occupancy";
                    const std::string B_ISO_OR_EQUIV     = "B_iso_or_equiv";
                    const std::string AUTH_SEQ_ID        = "auth_seq_id";
                    const std::string AUTH_COMP_ID       = "auth_comp_id";
                    const std::string AUTH_ASYM_ID       = "auth_asym_id";    // mandatory
                    const std::string AUTH_ATOM_ID       = "auth_atom_id";
                    const std::string PDBX_PDB_INS_CODE  = "pdbx_PDB_ins_code";
                    const std::string PDBX_FORMAL_CHARGE = "pdbx_formal_charge";
                    const std::string PDBX_PDB_MODEL_NUM = "pdbx_PDB_model_num";
                } // namespace Item

                namespace PDBGroup
                {

                    const std::string ATOM     = "ATOM";
                    const std::string HET_ATOM = "HETATM";
                } // namespace StereoConfig
            } // namespace AtomSite

            namespace StructConn
            {

                const std::string NAME = "struct_conn";

                namespace Item
                {

                    const std::string ID                      = "id";
                    const std::string CONN_TYPE_ID            = "conn_type_id";
                    const std::string DETAILS                 = "details";
                    const std::string PTNR1_AUTH_ASYM_ID      = "ptnr1_auth_asym_id";
                    const std::string PTNR1_AUTH_ATOM_ID      = "ptnr1_auth_atom_id";
                    const std::string PTNR1_AUTH_COMP_ID      = "ptnr1_auth_comp_id";
                    const std::string PTNR1_AUTH_SEQ_ID       = "ptnr1_auth_seq_id";
                    const std::string PTNR1_LABEL_ALT_ID      = "ptnr1_label_alt_id";
                    const std::string PTNR1_LABEL_ASYM_ID     = "ptnr1_label_asym_id";
                    const std::string PTNR1_LABEL_ATOM_ID     = "ptnr1_label_atom_id";
                    const std::string PTNR1_LABEL_COMP_ID     = "ptnr1_label_comp_id";
                    const std::string PTNR1_LABEL_SEQ_ID      = "ptnr1_label_seq_id";
                    const std::string PDBX_PTNR1_PDB_INS_CODE = "pdbx_ptnr1_PDB_ins_code";
                    const std::string PTNR1_ROLE              = "ptnr1_role";
                    const std::string PTNR1_SYMMETRY          = "ptnr1_symmetry";
                    const std::string PTNR2_AUTH_ASYM_ID      = "ptnr2_auth_asym_id";
                    const std::string PTNR2_AUTH_ATOM_ID      = "ptnr2_auth_atom_id";
                    const std::string PTNR2_AUTH_COMP_ID      = "ptnr2_auth_comp_id";
                    const std::string PTNR2_AUTH_SEQ_ID       = "ptnr2_auth_seq_id";
                    const std::string PTNR2_LABEL_ALT_ID      = "ptnr2_label_alt_id";
                    const std::string PTNR2_LABEL_ASYM_ID     = "ptnr2_label_asym_id";
                    const std::string PTNR2_LABEL_ATOM_ID     = "ptnr2_label_atom_id";
                    const std::string PTNR2_LABEL_COMP_ID     = "ptnr2_label_comp_id";
                    const std::string PTNR2_LABEL_SEQ_ID      = "ptnr2_label_seq_id";
                    const std::string PDBX_PTNR2_PDB_INS_CODE = "pdbx_ptnr2_PDB_ins_code";
                    const std::string PTNR2_ROLE              = "ptnr2_role";
                    const std::string PTNR2_SYMMETRY          = "ptnr2_symmetry";
                } // namespace Item

                namespace Type
                {

                    const std::string COVALE           = "covale";           // covalent bond
                    const std::string COVALE_BASE      = "covale_base";      // covalent modification of a nucleotide base
                    const std::string COVALE_PHOSPHATE = "covale_phosphate"; // covalent modification of a nucleotide phosphate
                    const std::string COVALE_SUGAR     = "covale_sugar";     // covalent modification of a nucleotide sugar
                    const std::string DISULF           = "disulf";           // disulfide bridge
                    const std::string HYDROG           = "hydrog";           // hydrogen bond
                    const std::string METALC           = "metalc";           // metal coordination
                    const std::string MISMAT           = "mismat";           // mismatched base pairs
                    const std::string MODRES           = "modres";           // covalent residue modification
                    const std::string SALTBR           = "saltbr";           // ionic interaction
                } // namespace ConnType
            } // namespace StructConn

            namespace ChemComp
            {

                const std::string NAME = "chem_comp";

                namespace Item
                {

                    const std::string ID                             = "id";
                    const std::string TYPE                           = "type";
                    const std::string MON_NSTD_FLAG                  = "mon_nstd_flag";
                    const std::string NAME                           = "name";
                    const std::string FORMULA                        = "formula";
                    const std::string FORMULA_WEIGHT                 = "formula_weight";
                    const std::string ONE_LETTER_CODE                = "one_letter_code";
                    const std::string THREE_LETTER_CODE              = "three_letter_code";
                    const std::string MON_NSTD_PARENT_COMP_ID        = "mon_nstd_parent_comp_id";
                    const std::string PDBX_SYNONYMS                  = "pdbx_synonyms";
                    const std::string PDBX_TYPE                      = "pdbx_type";
                    const std::string PDBX_FORMAL_CHARGE             = "pdbx_formal_charge";
                    const std::string PDBX_INITIAL_DATE              = "pdbx_initial_date";
                    const std::string PDBX_MODIFIED_DATE             = "pdbx_modified_date";
                    const std::string PDBX_AMBIGUOUS_FLAG            = "pdbx_ambiguous_flag";
                    const std::string PDBX_RELEASE_STATUS            = "pdbx_release_status";
                    const std::string PDBX_REPLACED_BY               = "pdbx_replaced_by";
                    const std::string PDBX_REPLACES                  = "pdbx_replaces";
                    const std::string PDBX_COORDS_DETAILS            = "pdbx_model_coordinates_details";
                    const std::string PDBX_COORDS_MISSING_FLAG       = "pdbx_model_coordinates_missing_flag";
                    const std::string PDBX_IDEAL_COORDS_DETAILS      = "pdbx_ideal_coordinates_details";
                    const std::string PDBX_IDEAL_COORDS_MISSING_FLAG = "pdbx_ideal_coordinates_missing_flag";
                    const std::string PDBX_MODEL_COORDS_DB_CODE      = "pdbx_model_coordinates_db_code";
                    const std::string PDBX_SUBCOMP_LIST              = "pdbx_subcomponent_list";
                    const std::string PDBX_PROC_SITE                 = "pdbx_processing_site";
                } // namespace Item
            } // namespace ChemComp

            namespace ChemCompAtom
            {

                const std::string NAME = "chem_comp_atom";

                namespace Item
                {

                    const std::string COMP_ID                = "comp_id";
                    const std::string ATOM_ID                = "atom_id";
                    const std::string ALT_ATOM_ID            = "alt_atom_id";
                    const std::string TYPE_SYMBOL            = "type_symbol";
                    const std::string CHARGE                 = "charge";
                    const std::string COORDS_X               = "model_Cartn_x";
                    const std::string COORDS_Y               = "model_Cartn_y";
                    const std::string COORDS_Z               = "model_Cartn_z";
                    const std::string PDBX_IDEAL_COORDS_X    = "pdbx_model_Cartn_x_ideal";
                    const std::string PDBX_IDEAL_COORDS_Y    = "pdbx_model_Cartn_y_ideal";
                    const std::string PDBX_IDEAL_COORDS_Z    = "pdbx_model_Cartn_z_ideal";
                    const std::string PDBX_LEAVING_ATOM_FLAG = "pdbx_leaving_atom_flag";
                    const std::string PDBX_AROM_FLAG         = "pdbx_aromatic_flag";
                    const std::string PDBX_STEREO_CONFIG     = "pdbx_stereo_config";
                    const std::string PDBX_ORDINAL           = "pdbx_ordinal";
                    const std::string PDBX_ATOM_ID           = "pdbx_component_atom_id";
                    const std::string PDBX_COMP_ID           = "pdbx_component_comp_id";
                } // namespace Item

                namespace StereoConfig
                {

                    const std::string NONE = "N";
                    const std::string R    = "R";
                    const std::string S    = "S";
                } // namespace StereoConfig
            } // namespace ChemCompAtom

            namespace ChemCompBond
            {

                const std::string NAME = "chem_comp_bond";

                namespace Item
                {

                    const std::string COMP_ID            = "comp_id";
                    const std::string ATOM_ID_1          = "atom_id_1";
                    const std::string ATOM_ID_2          = "atom_id_2";
                    const std::string ORDER              = "value_order";
                    const std::string PDBX_AROM_FLAG     = "pdbx_aromatic_flag";
                    const std::string PDBX_STEREO_CONFIG = "pdbx_stereo_config";
                    const std::string PDBX_ORDINAL       = "pdbx_ordinal";
                } // namespace Item

                namespace StereoConfig
                {

                    const std::string NONE = "N";
                    const std::string E    = "E";
                    const std::string Z    = "Z";
                } // namespace StereoConfig

                namespace Order
                {

                    const std::string AROMATIC    = "arom";
                    const std::string DELOCALIZED = "delo";
                    const std::string PI          = "pi";
                    const std::string POLYMERIC   = "poly";
                    const std::string SINGLE      = "sing";
                    const std::string DOUBLE      = "doub";
                    const std::string TRIPLE      = "trip";
                    const std::string QUADRUPLE   = "quad";
                } // namespace Order
            } // namespace ChemCompBond

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

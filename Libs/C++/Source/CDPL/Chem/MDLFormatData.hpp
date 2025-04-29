/* 
 * MDLFormatData.hpp 
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


#ifndef CDPL_CHEM_MDLFORMATDATA_HPP
#define CDPL_CHEM_MDLFORMATDATA_HPP

#include <cstddef>
#include <string>


namespace CDPL
{

    namespace Chem
    {

        namespace MDL
        {

            constexpr std::size_t MAX_LINE_LENGTH      = 80;
            constexpr std::size_t MAX_DATA_LINE_LENGTH = 200;
            constexpr char        END_OF_LINE          = '\n';

            namespace V3000
            {

                const std::string LINE_PREFIX            = "M  V30 ";
                constexpr char    LINE_CONTINUATION_MARK = '-';

                const std::string BLOCK_BEGIN_TAG = "BEGIN";
                const std::string BLOCK_END_TAG   = "END";

                const std::string DATA_END_TAG     = "M  END";
                const std::string DATA_END_TAG_ALT = "M END";

                constexpr char KEYWORD_VALUE_SEPARATOR = '=';
                constexpr char STRING_QUOTE_CHAR       = '"';
                constexpr char VALUE_LIST_START_DELIM  = '(';
                constexpr char VALUE_LIST_END_DELIM    = ')';
            } // namespace V3000

            namespace MOLFile
            {

                const std::string END_TAG     = "M  END";
                const std::string END_TAG_ALT = "M END";

                namespace Header
                {

                    const std::string DIM_CODE_2D = "2D";
                    const std::string DIM_CODE_3D = "3D";
                } // namespace Header

                namespace CountsLine
                {

                    constexpr unsigned int CHIRAL_FLAG_OFF = 0;
                    constexpr unsigned int CHIRAL_FLAG_ON  = 1;

                    const std::string V2000_TAG = "V2000";
                    const std::string V3000_TAG = "V3000";
                } // namespace CountsLine

                namespace CTab
                {

                    namespace V2000
                    {

                        namespace AtomBlock
                        {

                            constexpr int MAX_MASS_DIFF = 4;
                            constexpr int MIN_MASS_DIFF = -3;

                            constexpr unsigned int CHARGE_0        = 0;
                            constexpr unsigned int CHARGE_P1       = 3;
                            constexpr unsigned int CHARGE_P2       = 2;
                            constexpr unsigned int CHARGE_P3       = 1;
                            constexpr unsigned int CHARGE_M1       = 5;
                            constexpr unsigned int CHARGE_M2       = 6;
                            constexpr unsigned int CHARGE_M3       = 7;
                            constexpr unsigned int DOUBLET_RADICAL = 4;

                            constexpr unsigned int STEREO_PARITY_NONE   = 0;
                            constexpr unsigned int STEREO_PARITY_ODD    = 1;
                            constexpr unsigned int STEREO_PARITY_EVEN   = 2;
                            constexpr unsigned int STEREO_PARITY_EITHER = 3;

                            constexpr unsigned int HYDROGEN_COUNT_UNDEF = 0;
                            constexpr unsigned int HYDROGEN_COUNT_E0    = 1;
                            constexpr unsigned int HYDROGEN_COUNT_GE1   = 2;
                            constexpr unsigned int HYDROGEN_COUNT_GE2   = 3;
                            constexpr unsigned int HYDROGEN_COUNT_GE3   = 4;
                            constexpr unsigned int HYDROGEN_COUNT_GE4   = 5;

                            constexpr unsigned int DB_STEREO_IGNORE = 0;
                            constexpr unsigned int DB_STEREO_MATCH  = 1;

                            constexpr unsigned int VALENCE_UNDEF = 0;
                            constexpr unsigned int VALENCE_MAX   = 14;
                            constexpr unsigned int VALENCE_ZERO  = 15;

                            constexpr std::size_t RXN_MAPPING_NO_UNDEF = 0;

                            constexpr unsigned int RXN_INV_RET_UNDEF     = 0;
                            constexpr unsigned int RXN_INV_RET_INVERSION = 1;
                            constexpr unsigned int RXN_INV_RET_RETENTION = 2;

                            constexpr unsigned int RXN_CHANGE_UNDEF = 0;
                            constexpr unsigned int RXN_CHANGE_EXACT = 1;
                        } // namespace AtomBlock

                        namespace BondBlock
                        {

                            constexpr unsigned int TYPE_SINGLE          = 1;
                            constexpr unsigned int TYPE_DOUBLE          = 2;
                            constexpr unsigned int TYPE_TRIPLE          = 3;
                            constexpr unsigned int TYPE_AROMATIC        = 4;
                            constexpr unsigned int TYPE_SINGLE_DOUBLE   = 5;
                            constexpr unsigned int TYPE_SINGLE_AROMATIC = 6;
                            constexpr unsigned int TYPE_DOUBLE_AROMATIC = 7;
                            constexpr unsigned int TYPE_ANY             = 8;

                            constexpr unsigned int STEREO_NONE      = 0;
                            constexpr unsigned int STEREO_UP        = 1;
                            constexpr unsigned int STEREO_DOWN      = 6;
                            constexpr unsigned int STEREO_EITHER    = 4;
                            constexpr unsigned int STEREO_EITHER_DB = 3;

                            constexpr unsigned int TOPOLOGY_EITHER = 0;
                            constexpr unsigned int TOPOLOGY_RING   = 1;
                            constexpr unsigned int TOPOLOGY_CHAIN  = 2;

                            constexpr int RXN_STATUS_UNMARKED     = 0;
                            constexpr int RXN_STATUS_NO_CENTER    = -1;
                            constexpr int RXN_STATUS_IS_CENTER    = 1;
                            constexpr int RXN_STATUS_NO_CHANGE    = 2;
                            constexpr int RXN_STATUS_MADE_BROKEN  = 4;
                            constexpr int RXN_STATUS_ORDER_CHANGE = 8;
                        } // namespace BondBlock

                        namespace AListBlock
                        {

                            constexpr std::size_t MAX_ENTRIES = 5;

                            const std::string NORMAL_LIST_FLAG = "F";
                            const std::string NOT_LIST_FLAG    = "T";
                        } // namespace AListBlock

                        namespace PropertyBlock
                        {

                            const std::string ATOM_ALIAS_PREFIX         = "A  ";
                            const std::string ATOM_VALUE_PREFIX         = "V  ";
                            const std::string GROUP_ABBREV_PREFIX       = "G  ";
                            const std::string LINE_SKIP_PREFIX          = "S  SKP";
                            const std::string CHARGE_PREFIX             = "M  CHG";
                            const std::string RADICAL_PREFIX            = "M  RAD";
                            const std::string ISOTOPE_PREFIX            = "M  ISO";
                            const std::string RING_BOND_COUNT_PREFIX    = "M  RBC";
                            const std::string SUBSTITUTION_COUNT_PREFIX = "M  SUB";
                            const std::string UNSATURATION_PREFIX       = "M  UNS";
                            const std::string ATOM_LIST_PREFIX          = "M  ALS";
                            const std::string REGISTRY_NO_PREFIX        = "M  REG";
                            const std::string LINE_PREFIX               = "M  ";

                            constexpr std::size_t MAX_CHARGE_ENTRIES             = 8;
                            constexpr std::size_t MAX_RADICAL_ENTRIES            = 8;
                            constexpr std::size_t MAX_ISOTOPE_ENTRIES            = 8;
                            constexpr std::size_t MAX_RING_BOND_COUNT_ENTRIES    = 8;
                            constexpr std::size_t MAX_SUBSTITUTION_COUNT_ENTRIES = 8;
                            constexpr std::size_t MAX_UNSATURATION_ENTRIES       = 8;
                            constexpr std::size_t MAX_ATOM_LIST_ENTRIES          = 16;

                            constexpr int MIN_CHARGE = -15;
                            constexpr int MAX_CHARGE = 15;

                            constexpr unsigned int NO_RADICAL      = 0;
                            constexpr unsigned int SINGLET_RADICAL = 1;
                            constexpr unsigned int DOUBLET_RADICAL = 2;
                            constexpr unsigned int TRIPLET_RADICAL = 3;

                            constexpr int RING_BOND_COUNT_UNDEF = 0;
                            constexpr int RING_BOND_COUNT_E0    = -1;
                            constexpr int RING_BOND_COUNT_DRAWN = -2;
                            constexpr int RING_BOND_COUNT_E2    = 2;
                            constexpr int RING_BOND_COUNT_E3    = 3;
                            constexpr int RING_BOND_COUNT_GE4   = 4;

                            constexpr int SUBSTITUTION_COUNT_UNDEF = 0;
                            constexpr int SUBSTITUTION_COUNT_E0    = -1;
                            constexpr int SUBSTITUTION_COUNT_DRAWN = -2;
                            constexpr int SUBSTITUTION_COUNT_E1    = 1;
                            constexpr int SUBSTITUTION_COUNT_E2    = 2;
                            constexpr int SUBSTITUTION_COUNT_E3    = 3;
                            constexpr int SUBSTITUTION_COUNT_E4    = 4;
                            constexpr int SUBSTITUTION_COUNT_E5    = 5;
                            constexpr int SUBSTITUTION_COUNT_GE6   = 6;

                            constexpr unsigned int UNSATURATION_UNDEF = 0;
                            constexpr unsigned int UNSATURATION_ON    = 1;

                            const std::string NORMAL_ATOM_LIST_FLAG = "F";
                            const std::string NOT_ATOM_LIST_FLAG    = "T";
                        } // namespace PropertyBlock
                    } // namespace V2000

                    namespace V3000
                    {

                        const std::string BLOCK_TYPE_KEY = "CTAB";

                        namespace CountsLine
                        {

                            const std::string COUNTS_TAG = "COUNTS";

                            const std::string REGISTRY_NO_KEYWORD = "REGNO";

                            constexpr unsigned int CHIRAL_FLAG_OFF = 0;
                            constexpr unsigned int CHIRAL_FLAG_ON  = 1;
                        } // namespace CountsLine

                        namespace AtomBlock
                        {

                            const std::string BLOCK_TYPE_KEY = "ATOM";

                            const std::string CHARGE_KEYWORD             = "CHG";
                            const std::string RADICAL_KEYWORD            = "RAD";
                            const std::string CONFIG_KEYWORD             = "CFG";
                            const std::string MASS_KEYWORD               = "MASS";
                            const std::string VALENCE_KEYWORD            = "VAL";
                            const std::string HYDROGEN_COUNT_KEYWORD     = "HCOUNT";
                            const std::string STEREO_BOX_KEYWORD         = "STBOX";
                            const std::string RXN_INV_RET_KEYWORD        = "INVRET";
                            const std::string RXN_CHANGE_KEYWORD         = "EXACHG";
                            const std::string SUBSTITUTION_COUNT_KEYWORD = "SUBST";
                            const std::string UNSATURATION_KEYWORD       = "UNSAT";
                            const std::string RING_BOND_COUNT_KEYWORD    = "RBCNT";
                            const std::string ATTACHMENT_POINT_KEYWORD   = "ATTCHPT";
                            const std::string ATTACHMENT_ORDER_KEYWORD   = "ATTCHORD";
                            const std::string RGROUPS_KEYWORD            = "RGROUPS";

                            const std::string NOT_ATOM_LIST_TAG = "NOT";

                            constexpr char ATOM_LIST_START_DELIMITER = '[';
                            constexpr char ATOM_LIST_END_DELIMITER   = ']';
                            constexpr char ATOM_LIST_SEPARATOR       = ',';

                            constexpr int MIN_CHARGE = -15;
                            constexpr int MAX_CHARGE = 15;

                            constexpr unsigned int NO_RADICAL      = 0;
                            constexpr unsigned int SINGLET_RADICAL = 1;
                            constexpr unsigned int DOUBLET_RADICAL = 2;
                            constexpr unsigned int TRIPLET_RADICAL = 3;

                            constexpr unsigned int STEREO_PARITY_NONE   = 0;
                            constexpr unsigned int STEREO_PARITY_ODD    = 1;
                            constexpr unsigned int STEREO_PARITY_EVEN   = 2;
                            constexpr unsigned int STEREO_PARITY_EITHER = 3;

                            constexpr int VALENCE_UNDEF = 0;
                            constexpr int VALENCE_ZERO  = -1;

                            constexpr int HYDROGEN_COUNT_UNDEF = 0;
                            constexpr int HYDROGEN_COUNT_E0    = -1;
                            constexpr int HYDROGEN_COUNT_GE1   = 1;
                            constexpr int HYDROGEN_COUNT_GE2   = 2;
                            constexpr int HYDROGEN_COUNT_GE3   = 3;
                            constexpr int HYDROGEN_COUNT_GE4   = 4;

                            constexpr unsigned int DB_STEREO_IGNORE = 0;
                            constexpr unsigned int DB_STEREO_MATCH  = 1;

                            constexpr unsigned int RXN_INV_RET_UNDEF     = 0;
                            constexpr unsigned int RXN_INV_RET_INVERSION = 1;
                            constexpr unsigned int RXN_INV_RET_RETENTION = 2;

                            constexpr unsigned int RXN_CHANGE_UNDEF = 0;
                            constexpr unsigned int RXN_CHANGE_EXACT = 1;

                            constexpr int SUBSTITUTION_COUNT_UNDEF = 0;
                            constexpr int SUBSTITUTION_COUNT_E0    = -1;
                            constexpr int SUBSTITUTION_COUNT_E1    = 1;
                            constexpr int SUBSTITUTION_COUNT_E2    = 2;
                            constexpr int SUBSTITUTION_COUNT_E3    = 3;
                            constexpr int SUBSTITUTION_COUNT_E4    = 4;
                            constexpr int SUBSTITUTION_COUNT_E5    = 5;
                            constexpr int SUBSTITUTION_COUNT_GE6   = 6;

                            constexpr unsigned int UNSATURATION_UNDEF = 0;
                            constexpr unsigned int UNSATURATION_ON    = 1;

                            constexpr int RING_BOND_COUNT_UNDEF = 0;
                            constexpr int RING_BOND_COUNT_E0    = -1;
                            constexpr int RING_BOND_COUNT_E2    = 2;
                            constexpr int RING_BOND_COUNT_E3    = 3;
                            constexpr int RING_BOND_COUNT_GE4   = 4;
                        } // namespace AtomBlock

                        namespace BondBlock
                        {

                            const std::string BLOCK_TYPE_KEY = "BOND";

                            const std::string CONFIG_KEYWORD            = "CFG";
                            const std::string TOPOLOGY_KEYWORD          = "TOPO";
                            const std::string STEREO_BOX_KEYWORD        = "STBOX";
                            const std::string RXN_CENTER_STATUS_KEYWORD = "RXCTR";

                            constexpr unsigned int TYPE_SINGLE          = 1;
                            constexpr unsigned int TYPE_DOUBLE          = 2;
                            constexpr unsigned int TYPE_TRIPLE          = 3;
                            constexpr unsigned int TYPE_AROMATIC        = 4;
                            constexpr unsigned int TYPE_SINGLE_DOUBLE   = 5;
                            constexpr unsigned int TYPE_SINGLE_AROMATIC = 6;
                            constexpr unsigned int TYPE_DOUBLE_AROMATIC = 7;
                            constexpr unsigned int TYPE_ANY             = 8;

                            constexpr unsigned int STEREO_NONE   = 0;
                            constexpr unsigned int STEREO_UP     = 1;
                            constexpr unsigned int STEREO_EITHER = 2;
                            constexpr unsigned int STEREO_DOWN   = 3;

                            constexpr unsigned int TOPOLOGY_EITHER = 0;
                            constexpr unsigned int TOPOLOGY_RING   = 1;
                            constexpr unsigned int TOPOLOGY_CHAIN  = 2;

                            constexpr unsigned int DB_STEREO_IGNORE = 0;
                            constexpr unsigned int DB_STEREO_MATCH  = 1;

                            constexpr int RXN_STATUS_UNMARKED     = 0;
                            constexpr int RXN_STATUS_NO_CENTER    = -1;
                            constexpr int RXN_STATUS_IS_CENTER    = 1;
                            constexpr int RXN_STATUS_NO_CHANGE    = 2;
                            constexpr int RXN_STATUS_MADE_BROKEN  = 4;
                            constexpr int RXN_STATUS_ORDER_CHANGE = 8;
                        } // namespace BondBlock
                    } // namespace V3000
                } // namespace CTab
            } // namespace MOLFile

            namespace SDFile
            {

                const std::string DATA_HEADER_PREFIX = "> ";

                const std::string RECORD_DELIMITER = "$$$$";
            } // namespace SDFile

            namespace RXNFile
            {

                const std::string RXN_FILE_IDENTIFIER = "$RXN";
                const std::string V3000_VERSION_TAG   = "V3000";

                const std::string MOL_FILE_DELIMITER = "$MOL";

                namespace V3000
                {
                    const std::string COUNTS_TAG = "COUNTS";

                    const std::string REACTANT_BLOCK_KEY = "REACTANT";
                    const std::string PRODUCT_BLOCK_KEY  = "PRODUCT";
                } // namespace V3000
            } // namespace RXNFile

            namespace RDFile
            {

                constexpr char RD_FILE_KEYWORD_PREFIX = '$';

                const std::string RD_FILE_IDENTIFIER    = "$RDFILE";
                const std::string RD_FILE_VERSION_STAMP = "1";
                const std::string DATE_TIME_KEYWORD     = "$DATM";

                const std::string DATE_PART_SEPARATOR   = "/";
                const std::string HOUR_MINUTE_SEPARATOR = ":";

                const std::string RXN_RECORD_IDENTIFIER = "$RFMT";
                const std::string MOL_RECORD_IDENTIFIER = "$MFMT";

                const std::string MOL_INT_REGISTRY_NO_KEYWORD = "$MIREG";
                const std::string MOL_EXT_REGISTRY_NO_KEYWORD = "$MEREG";

                const std::string RXN_INT_REGISTRY_NO_KEYWORD = "$RIREG";
                const std::string RXN_EXT_REGISTRY_NO_KEYWORD = "$REREG";

                const std::string DATA_FIELD_IDENTIFIER = "$DTYPE";
                const std::string DATA_FIELD_PREFIX     = "$DATUM";
            } // namespace RDFile
        } // namespace MDL
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_MDLFORMATDATA_HPP

/* 
 * ControlParameterDefault.cpp 
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


#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Brush.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/Alignment.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"
#include "CDPL/Vis/DefaultAtomColorTable.hpp"

#include "ControlParameterDefault.hpp"


namespace ChOX
{

    namespace ControlParameterDefault
    {

        const CDPL::Vis::Color                     VIEW_BACKGROUND_COLOR                   = CDPL::Vis::Color(1.0, 1.0, 1.0);
        const CDPL::Vis::Color                     VIEW_SELECTION_COLOR                    = CDPL::Vis::Color(0.8, 0.8, 1.0);
        const CDPL::Vis::SizeSpecification         VIEWPORT_MARGIN                         = CDPL::Vis::SizeSpecification(10.0);
        const std::size_t                          GRID_ROW_COUNT                          = 1;
        const std::size_t                          GRID_COLUMN_COUNT                       = 1;
        const bool                                 SHOW_GRID                               = true;
        const bool                                 SHOW_RECORD_NUMBERS                     = true;
        const bool                                 SHOW_RECORD_NAMES                       = true;
        const bool                                 SHOW_RECORD_PROPERTIES                  = false;
        const CDPL::Vis::Pen::LineStyle            GRID_LINE_STYLE                         = CDPL::Vis::Pen::DOT_LINE;
        const CDPL::Vis::Color                     GRID_LINE_COLOR                         = CDPL::Vis::Color(0.7, 0.7, 0.7);
        const CDPL::Vis::SizeSpecification         GRID_LINE_WIDTH                         = CDPL::Vis::SizeSpecification(1.0);
        const CDPL::Vis::Font                      RECORD_NUMBER_LABEL_FONT                = CDPL::Vis::Font();
        const CDPL::Vis::SizeSpecification         RECORD_NUMBER_LABEL_SIZE                = CDPL::Vis::SizeSpecification(10.0);
        const unsigned int                         RECORD_NUMBER_LABEL_ALIGNMENT           = CDPL::Vis::Alignment::BOTTOM | 
                                                                                             CDPL::Vis::Alignment::LEFT;
        const CDPL::Vis::Color                     RECORD_NUMBER_LABEL_COLOR               = CDPL::Vis::Color(0.0, 0.0, 0.0);
        const CDPL::Vis::Font                      RECORD_NAME_LABEL_FONT                  = CDPL::Vis::Font();
        const CDPL::Vis::SizeSpecification         RECORD_NAME_LABEL_SIZE                  = CDPL::Vis::SizeSpecification(10.0);
        const unsigned int                         RECORD_NAME_LABEL_ALIGNMENT             = CDPL::Vis::Alignment::TOP | 
                                                                                             CDPL::Vis::Alignment::H_CENTER;
        const CDPL::Vis::Color                     RECORD_NAME_LABEL_COLOR                 = CDPL::Vis::Color(0.0, 0.0, 0.0);

        const bool                                 PRINT_FRAME                             = true;
        const bool                                 PRINT_DATE                              = true;
        const bool                                 PRINT_PAGE_NUMBER                       = true;
        const bool                                 PRINT_FILE_NAME                         = true;
        const CDPL::Vis::Pen::LineStyle            FRAME_LINE_STYLE                        = CDPL::Vis::Pen::SOLID_LINE;
        const CDPL::Vis::Color                     FRAME_LINE_COLOR                        = CDPL::Vis::Color(0.0, 0.0, 0.0);
        const CDPL::Vis::SizeSpecification         FRAME_LINE_WIDTH                        = CDPL::Vis::SizeSpecification(0.5);
        const CDPL::Vis::Font                      PRINTING_TEXT_LABEL_FONT                = CDPL::Vis::Font();
        const CDPL::Vis::SizeSpecification         PRINTING_TEXT_LABEL_SIZE                = CDPL::Vis::SizeSpecification(10.0);
        const CDPL::Vis::SizeSpecification         PRINTING_TEXT_LABEL_SPACING             = CDPL::Vis::SizeSpecification(10.0);
        const CDPL::Vis::Color                     PRINTING_TEXT_LABEL_COLOR               = CDPL::Vis::Color(0.0, 0.0, 0.0);
        const unsigned int                         PAGE_NUMBER_LABEL_ALIGNMENT             = CDPL::Vis::Alignment::BOTTOM |
                                                                                             CDPL::Vis::Alignment::H_CENTER;
        const unsigned int                         DATE_LABEL_ALIGNMENT                    = CDPL::Vis::Alignment::TOP | 
                                                                                             CDPL::Vis::Alignment::RIGHT;
        const unsigned int                         FILE_NAME_LABEL_ALIGNMENT               = CDPL::Vis::Alignment::TOP | 
                                                                                             CDPL::Vis::Alignment::LEFT;

        const bool                                 USE_ATOM_COLOR_TABLE                    = true;
        const CDPL::Vis::ColorTable::SharedPointer ATOM_COLOR_TABLE                        = CDPL::Vis::ColorTable::SharedPointer(new CDPL::Vis::DefaultAtomColorTable());

        const std::string                          DEFAULT_MOL_OUTPUT_FORMAT               = "SDF";
        const std::string                          DEFAULT_RXN_OUTPUT_FORMAT               = "RDF";

        const bool                                 OUTPUT_SINGLE_RECORD_FILES              = true;

        const std::string                          RECORD_SEPARATOR                        = "";

        const bool                                 MOL2_INPUT_STRICT_ERROR_CHECKING        = false;
        const bool                                 MOL2_INPUT_MULTI_CONF_IMPORT            = true;

        const bool                                 MOL2_OUTPUT_STRICT_ERROR_CHECKING       = false;
        const bool                                 MOL2_OUTPUT_SINGLE_RECORD_FILES         = false;
        const bool                                 MOL2_OUTPUT_MULTI_CONF_EXPORT           = true;

        const bool                                 XYZ_INPUT_MULTI_CONF_IMPORT             = true;

        const bool                                 XYZ_OUTPUT_SINGLE_RECORD_FILES          = false;
        const bool                                 XYZ_OUTPUT_MULTI_CONF_EXPORT            = true;

        const bool                                 CML_INPUT_STRICT_ERROR_CHECKING         = false;

        const bool                                 CML_OUTPUT_SINGLE_RECORD_FILES          = false;

        const bool                                 MOL_INPUT_STRICT_ERROR_CHECKING         = false;
        const bool                                 MOL_INPUT_IGNORE_PARITY                 = true;
        const bool                                 MOL_INPUT_TRIM_STRINGS                  = true;
        const bool                                 MOL_INPUT_TRIM_LINES                    = false;
        const bool                                 MOL_INPUT_CHECK_LINE_LENGTH             = false;
        const bool                                 MOL_INPUT_MULTI_CONF_IMPORT             = false;

        const bool                                 MOL_OUTPUT_STRICT_ERROR_CHECKING        = false;
        const unsigned int                         MOL_OUTPUT_CTAB_VERSION                 = 0;
        const bool                                 MOL_OUTPUT_UPDATE_TIMESTAMP             = true;
        const bool                                 MOL_OUTPUT_TRIM_STRINGS                 = true;
        const bool                                 MOL_OUTPUT_TRIM_LINES                   = false;
        const bool                                 MOL_OUTPUT_TRUNCATE_STRINGS             = true;
        const bool                                 MOL_OUTPUT_TRUNCATE_LINES               = false;
        const bool                                 MOL_OUTPUT_CHECK_LINE_LENGTH            = false;
        const bool                                 MOL_OUTPUT_IGNORE_PARITY                = true;
        const bool                                 MOL_OUTPUT_SINGLE_RECORD_FILES          = true;
        const bool                                 MOL_OUTPUT_MULTI_CONF_EXPORT            = false;

        const bool                                 SDF_INPUT_STRICT_ERROR_CHECKING         = false;
        const bool                                 SDF_INPUT_IGNORE_PARITY                 = true;
        const bool                                 SDF_INPUT_TRIM_STRINGS                  = true;
        const bool                                 SDF_INPUT_TRIM_LINES                    = false;
        const bool                                 SDF_INPUT_CHECK_LINE_LENGTH             = false;
        const bool                                 SDF_INPUT_MULTI_CONF_IMPORT             = true;

        const bool                                 SDF_OUTPUT_STRICT_ERROR_CHECKING        = false;
        const unsigned int                         SDF_OUTPUT_CTAB_VERSION                 = 0;
        const bool                                 SDF_OUTPUT_UPDATE_TIMESTAMP             = true;
        const bool                                 SDF_OUTPUT_TRIM_STRINGS                 = true;
        const bool                                 SDF_OUTPUT_TRIM_LINES                   = false;
        const bool                                 SDF_OUTPUT_TRUNCATE_STRINGS             = true;
        const bool                                 SDF_OUTPUT_TRUNCATE_LINES               = false;
        const bool                                 SDF_OUTPUT_CHECK_LINE_LENGTH            = false;
        const bool                                 SDF_OUTPUT_IGNORE_PARITY                = true;
        const bool                                 SDF_OUTPUT_SINGLE_RECORD_FILES          = false;
        const bool                                 SDF_OUTPUT_MULTI_CONF_EXPORT            = true;

        const bool                                 RXN_INPUT_STRICT_ERROR_CHECKING         = false;
        const bool                                 RXN_INPUT_IGNORE_PARITY                 = true;
        const bool                                 RXN_INPUT_TRIM_STRINGS                  = true;
        const bool                                 RXN_INPUT_TRIM_LINES                    = false;
        const bool                                 RXN_INPUT_CHECK_LINE_LENGTH             = false;

        const bool                                 RXN_OUTPUT_STRICT_ERROR_CHECKING        = false;
        const unsigned int                         RXN_OUTPUT_CTAB_VERSION                 = 0;
        const unsigned int                         RXN_OUTPUT_RXN_FILE_VERSION             = 0;
        const bool                                 RXN_OUTPUT_UPDATE_TIMESTAMP             = true;
        const bool                                 RXN_OUTPUT_TRIM_STRINGS                 = true;
        const bool                                 RXN_OUTPUT_TRIM_LINES                   = false;
        const bool                                 RXN_OUTPUT_TRUNCATE_STRINGS             = true;
        const bool                                 RXN_OUTPUT_TRUNCATE_LINES               = false;
        const bool                                 RXN_OUTPUT_CHECK_LINE_LENGTH            = false;
        const bool                                 RXN_OUTPUT_IGNORE_PARITY                = true;
        const bool                                 RXN_OUTPUT_SINGLE_RECORD_FILES          = true;

        const bool                                 RDF_INPUT_STRICT_ERROR_CHECKING         = false;
        const bool                                 RDF_INPUT_IGNORE_PARITY                 = true;
        const bool                                 RDF_INPUT_TRIM_STRINGS                  = true;
        const bool                                 RDF_INPUT_TRIM_LINES                    = false;
        const bool                                 RDF_INPUT_CHECK_LINE_LENGTH             = false;

        const bool                                 RDF_OUTPUT_STRICT_ERROR_CHECKING        = false;
        const unsigned int                         RDF_OUTPUT_CTAB_VERSION                 = 0;
        const unsigned int                         RDF_OUTPUT_RXN_FILE_VERSION             = 0;
        const bool                                 RDF_OUTPUT_UPDATE_TIMESTAMP             = true;
        const bool                                 RDF_OUTPUT_TRIM_STRINGS                 = true;
        const bool                                 RDF_OUTPUT_TRIM_LINES                   = false;
        const bool                                 RDF_OUTPUT_TRUNCATE_STRINGS             = true;
        const bool                                 RDF_OUTPUT_TRUNCATE_LINES               = false;
        const bool                                 RDF_OUTPUT_CHECK_LINE_LENGTH            = false;
        const bool                                 RDF_OUTPUT_IGNORE_PARITY                = true;
        const bool                                 RDF_OUTPUT_SINGLE_RECORD_FILES          = false;

        const bool                                 JME_INPUT_STRICT_ERROR_CHECKING         = false;

        const bool                                 JME_OUTPUT_STRICT_ERROR_CHECKING        = false;
        const bool                                 JME_OUTPUT_SEPARATE_COMPONENTS          = true;
        const bool                                 JME_OUTPUT_SINGLE_RECORD_FILES          = true;
        const std::string                          JME_OUTPUT_RECORD_SEPARATOR             = "\n";

        const bool                                 SMILES_INPUT_STRICT_ERROR_CHECKING      = false;
        const std::string                          SMILES_INPUT_RECORD_FORMAT              = "SN";

        const bool                                 SMILES_OUTPUT_STRICT_ERROR_CHECKING     = false;
        const bool                                 SMILES_OUTPUT_ORDINARY_H_DEPLETE        = true;
        const bool                                 SMILES_OUTPUT_CANONICAL_FORM            = false;
        const bool                                 SMILES_OUTPUT_KEKULE_FORM               = false;
        const bool                                 SMILES_OUTPUT_ATOM_STEREO               = true;
        const bool                                 SMILES_OUTPUT_BOND_STEREO               = true;
        const bool                                 SMILES_OUTPUT_RING_BOND_STEREO          = false;
        const bool                                 SMILES_OUTPUT_ATOM_MAPPING_ID           = true;
        const bool                                 SMILES_OUTPUT_SINGLE_BONDS              = false;
        const bool                                 SMILES_OUTPUT_AROMATIC_BONDS            = false;
        const bool                                 SMILES_OUTPUT_ISOTOPE                   = true;
        const bool                                 SMILES_OUTPUT_NO_ORGANIC_SUBSET         = false;
        const std::size_t                          SMILES_OUTPUT_MIN_STEREO_BOND_RING_SIZE = 8;
        const bool                                 SMILES_OUTPUT_SINGLE_RECORD_FILES       = false;
        const std::string                          SMILES_OUTPUT_RECORD_FORMAT             = "SN";

        const bool                                 SMARTS_INPUT_STRICT_ERROR_CHECKING      = false;

        const bool                                 SMARTS_OUTPUT_STRICT_ERROR_CHECKING     = false;
        const bool                                 SMARTS_OUTPUT_SINGLE_RECORD_FILES       = false;
        const std::string                          SMARTS_OUTPUT_RECORD_SEPARATOR          = "\n";

        const bool                                 INCHI_INPUT_STRICT_ERROR_CHECKING       = false;
        const std::string                          INCHI_INPUT_OPTIONS                     = "";

        const bool                                 INCHI_OUTPUT_STRICT_ERROR_CHECKING      = false;
        const std::string                          INCHI_OUTPUT_OPTIONS                    = "-WarnOnEmptyStructure -AuxNone -NEWPSOFF";
        const std::string                          INCHI_OUTPUT_RECORD_SEPARATOR           = "\n";
        const bool                                 INCHI_OUTPUT_SINGLE_RECORD_FILES        = true;

        const bool                                 PDB_INPUT_STRICT_ERROR_CHECKING         = false;
        const bool                                 PDB_INPUT_CHECK_LINE_LENGTH             = false;

        const bool                                 MMCIF_INPUT_STRICT_ERROR_CHECKING       = false;

        const bool                                 MMCIF_OUTPUT_STRICT_ERROR_CHECKING      = false;
        const bool                                 MMCIF_OUTPUT_SINGLE_RECORD_FILES        = false;

        const bool                                 MMTF_INPUT_STRICT_ERROR_CHECKING        = true;

        const bool                                 CDF_OUTPUT_SINGLE_RECORD_FILES          = false;
        const bool                                 CDF_OUTPUT_SINGLE_PRECISION_FLOATS      = true;

        const bool                                 CFL_INPUT_STRICT_ERROR_CHECKING         = true;

        const bool                                  PSD_OUTPUT_SINGLE_RECORD_FILES         = false;
        const bool                                  PSD_OUTPUT_SINGLE_PRECISION_FLOATS     = true;
        const bool                                  PSD_OUTPUT_ALLOW_DUPLICATES            = true;
        const CDPL::Pharm::ScreeningDBCreator::Mode PSD_CREATION_MODE                      = CDPL::Pharm::ScreeningDBCreator::CREATE;

        const QStringList                           SUBSTRUCT_HIGHLIGHTING_PATTERNS        = QStringList();
        const bool                                  SUBSTRUCT_HIGHLIGHTING_ENABLED         = true;

        const QStringList                           SUBSTRUCT_SEARCH_QUERY                 = QStringList();
        
        const CDPL::Vis::Brush                      ATOM_HIGHLIGHT_AREA_BRUSH              = CDPL::Vis::Brush(CDPL::Vis::Color(1.0, 0.666, 1.0));
        const CDPL::Vis::Brush                      BOND_HIGHLIGHT_AREA_BRUSH              = CDPL::Vis::Brush(CDPL::Vis::Color(1.0, 0.666, 1.0));
    }
}

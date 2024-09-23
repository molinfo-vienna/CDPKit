/* 
 * ControlParameterDefault.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#ifndef CHOX_CONTROLPARAMETERDEFAULT_HPP
#define CHOX_CONTROLPARAMETERDEFAULT_HPP

#include <cstddef>
#include <string>

#include <QStringList>

#include "CDPL/Vis/ColorTable.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Pharm/ScreeningDBCreator.hpp"


namespace CDPL
{

    namespace Vis
    {

        class Color;
        class Brush;
        class Font;
        class SizeSpecification;
    } // namespace Vis
} // namespace CDPL


namespace ChOX
{

    namespace ControlParameterDefault
    {

        extern const CDPL::Vis::Color             VIEW_BACKGROUND_COLOR;
        extern const CDPL::Vis::Color             VIEW_SELECTION_COLOR;
        extern const CDPL::Vis::SizeSpecification VIEWPORT_MARGIN;
        extern const std::size_t                  GRID_ROW_COUNT;
        extern const std::size_t                  GRID_COLUMN_COUNT;
        extern const bool                         SHOW_GRID;
        extern const bool                         SHOW_RECORD_NUMBERS;
        extern const bool                         SHOW_RECORD_NAMES;
        extern const CDPL::Vis::Pen::LineStyle    GRID_LINE_STYLE;
        extern const CDPL::Vis::Color             GRID_LINE_COLOR;
        extern const CDPL::Vis::SizeSpecification GRID_LINE_WIDTH;
        extern const CDPL::Vis::Font              RECORD_NUMBER_LABEL_FONT;
        extern const CDPL::Vis::SizeSpecification RECORD_NUMBER_LABEL_SIZE;
        extern const unsigned int                 RECORD_NUMBER_LABEL_ALIGNMENT;

        extern const CDPL::Vis::Color             RECORD_NUMBER_LABEL_COLOR;
        extern const CDPL::Vis::Font              RECORD_NAME_LABEL_FONT;
        extern const CDPL::Vis::SizeSpecification RECORD_NAME_LABEL_SIZE;
        extern const unsigned int                 RECORD_NAME_LABEL_ALIGNMENT;

        extern const CDPL::Vis::Color RECORD_NAME_LABEL_COLOR;

        extern const bool                         PRINT_FRAME;
        extern const bool                         PRINT_DATE;
        extern const bool                         PRINT_PAGE_NUMBER;
        extern const bool                         PRINT_FILE_NAME;
        extern const CDPL::Vis::Pen::LineStyle    FRAME_LINE_STYLE;
        extern const CDPL::Vis::Color             FRAME_LINE_COLOR;
        extern const CDPL::Vis::SizeSpecification FRAME_LINE_WIDTH;
        extern const CDPL::Vis::Font              PRINTING_TEXT_LABEL_FONT;
        extern const CDPL::Vis::SizeSpecification PRINTING_TEXT_LABEL_SIZE;
        extern const CDPL::Vis::SizeSpecification PRINTING_TEXT_LABEL_SPACING;
        extern const CDPL::Vis::Color             PRINTING_TEXT_LABEL_COLOR;
        extern const unsigned int                 PAGE_NUMBER_LABEL_ALIGNMENT;

        extern const unsigned int DATE_LABEL_ALIGNMENT;
        extern const unsigned int FILE_NAME_LABEL_ALIGNMENT;

        extern const bool                                 USE_ATOM_COLOR_TABLE;
        extern const CDPL::Vis::ColorTable::SharedPointer ATOM_COLOR_TABLE;

        extern const std::string DEFAULT_MOL_OUTPUT_FORMAT;
        extern const std::string DEFAULT_RXN_OUTPUT_FORMAT;

        extern const bool WRITE_SINGLE_RECORD_FILES;

        extern const std::string RECORD_SEPARATOR;

        extern const bool MOL2_INPUT_STRICT_ERROR_CHECKING;
        extern const bool MOL2_INPUT_MULTI_CONF_IMPORT;

        extern const bool MOL2_OUTPUT_STRICT_ERROR_CHECKING;
        extern const bool MOL2_OUTPUT_WRITE_SINGLE_RECORD_FILES;
        extern const bool MOL2_OUTPUT_MULTI_CONF_EXPORT;

        extern const bool XYZ_INPUT_MULTI_CONF_IMPORT;

        extern const bool XYZ_OUTPUT_WRITE_SINGLE_RECORD_FILES;
        extern const bool XYZ_OUTPUT_MULTI_CONF_EXPORT;

        extern const bool MOL_INPUT_STRICT_ERROR_CHECKING;
        extern const bool MOL_INPUT_IGNORE_PARITY;
        extern const bool MOL_INPUT_TRIM_STRINGS;
        extern const bool MOL_INPUT_TRIM_LINES;
        extern const bool MOL_INPUT_CHECK_LINE_LENGTH;
        extern const bool MOL_INPUT_MULTI_CONF_IMPORT;

        extern const bool         MOL_OUTPUT_STRICT_ERROR_CHECKING;
        extern const unsigned int MOL_OUTPUT_CTAB_VERSION;
        extern const bool         MOL_OUTPUT_UPDATE_TIMESTAMP;
        extern const bool         MOL_OUTPUT_TRIM_STRINGS;
        extern const bool         MOL_OUTPUT_TRIM_LINES;
        extern const bool         MOL_OUTPUT_TRUNCATE_STRINGS;
        extern const bool         MOL_OUTPUT_TRUNCATE_LINES;
        extern const bool         MOL_OUTPUT_CHECK_LINE_LENGTH;
        extern const bool         MOL_OUTPUT_IGNORE_PARITY;
        extern const bool         MOL_OUTPUT_WRITE_SINGLE_RECORD_FILES;
        extern const bool         MOL_OUTPUT_MULTI_CONF_EXPORT;

        extern const bool SDF_INPUT_STRICT_ERROR_CHECKING;
        extern const bool SDF_INPUT_IGNORE_PARITY;
        extern const bool SDF_INPUT_TRIM_STRINGS;
        extern const bool SDF_INPUT_TRIM_LINES;
        extern const bool SDF_INPUT_CHECK_LINE_LENGTH;
        extern const bool SDF_INPUT_MULTI_CONF_IMPORT;

        extern const bool         SDF_OUTPUT_STRICT_ERROR_CHECKING;
        extern const unsigned int SDF_OUTPUT_CTAB_VERSION;
        extern const bool         SDF_OUTPUT_UPDATE_TIMESTAMP;
        extern const bool         SDF_OUTPUT_TRIM_STRINGS;
        extern const bool         SDF_OUTPUT_TRIM_LINES;
        extern const bool         SDF_OUTPUT_TRUNCATE_STRINGS;
        extern const bool         SDF_OUTPUT_TRUNCATE_LINES;
        extern const bool         SDF_OUTPUT_CHECK_LINE_LENGTH;
        extern const bool         SDF_OUTPUT_IGNORE_PARITY;
        extern const bool         SDF_OUTPUT_WRITE_SINGLE_RECORD_FILES;
        extern const bool         SDF_OUTPUT_MULTI_CONF_EXPORT;

        extern const bool RXN_INPUT_STRICT_ERROR_CHECKING;
        extern const bool RXN_INPUT_IGNORE_PARITY;
        extern const bool RXN_INPUT_TRIM_STRINGS;
        extern const bool RXN_INPUT_TRIM_LINES;
        extern const bool RXN_INPUT_CHECK_LINE_LENGTH;

        extern const bool         RXN_OUTPUT_STRICT_ERROR_CHECKING;
        extern const unsigned int RXN_OUTPUT_CTAB_VERSION;
        extern const unsigned int RXN_OUTPUT_RXN_FILE_VERSION;
        extern const bool         RXN_OUTPUT_UPDATE_TIMESTAMP;
        extern const bool         RXN_OUTPUT_TRIM_STRINGS;
        extern const bool         RXN_OUTPUT_TRIM_LINES;
        extern const bool         RXN_OUTPUT_TRUNCATE_STRINGS;
        extern const bool         RXN_OUTPUT_TRUNCATE_LINES;
        extern const bool         RXN_OUTPUT_CHECK_LINE_LENGTH;
        extern const bool         RXN_OUTPUT_IGNORE_PARITY;
        extern const bool         RXN_OUTPUT_WRITE_SINGLE_RECORD_FILES;

        extern const bool RDF_INPUT_STRICT_ERROR_CHECKING;
        extern const bool RDF_INPUT_IGNORE_PARITY;
        extern const bool RDF_INPUT_TRIM_STRINGS;
        extern const bool RDF_INPUT_TRIM_LINES;
        extern const bool RDF_INPUT_CHECK_LINE_LENGTH;

        extern const bool         RDF_OUTPUT_STRICT_ERROR_CHECKING;
        extern const unsigned int RDF_OUTPUT_CTAB_VERSION;
        extern const unsigned int RDF_OUTPUT_RXN_FILE_VERSION;
        extern const bool         RDF_OUTPUT_UPDATE_TIMESTAMP;
        extern const bool         RDF_OUTPUT_TRIM_STRINGS;
        extern const bool         RDF_OUTPUT_TRIM_LINES;
        extern const bool         RDF_OUTPUT_TRUNCATE_STRINGS;
        extern const bool         RDF_OUTPUT_TRUNCATE_LINES;
        extern const bool         RDF_OUTPUT_CHECK_LINE_LENGTH;
        extern const bool         RDF_OUTPUT_IGNORE_PARITY;
        extern const bool         RDF_OUTPUT_WRITE_SINGLE_RECORD_FILES;

        extern const bool JME_INPUT_STRICT_ERROR_CHECKING;

        extern const bool        JME_OUTPUT_STRICT_ERROR_CHECKING;
        extern const bool        JME_OUTPUT_SEPARATE_COMPONENTS;
        extern const bool        JME_OUTPUT_WRITE_SINGLE_RECORD_FILES;
        extern const std::string JME_OUTPUT_RECORD_SEPARATOR;

        extern const bool        SMILES_INPUT_STRICT_ERROR_CHECKING;
        extern const std::string SMILES_INPUT_RECORD_FORMAT;

        extern const bool        SMILES_OUTPUT_STRICT_ERROR_CHECKING;
        extern const bool        SMILES_OUTPUT_ORDINARY_H_DEPLETE;
        extern const bool        SMILES_OUTPUT_WRITE_CANONICAL_FORM;
        extern const bool        SMILES_OUTPUT_WRITE_KEKULE_FORM;
        extern const bool        SMILES_OUTPUT_WRITE_ATOM_STEREO;
        extern const bool        SMILES_OUTPUT_WRITE_BOND_STEREO;
        extern const bool        SMILES_OUTPUT_WRITE_RING_BOND_STEREO;
        extern const bool        SMILES_OUTPUT_WRITE_ATOM_MAPPING_ID;
        extern const bool        SMILES_OUTPUT_WRITE_SINGLE_BONDS;
        extern const bool        SMILES_OUTPUT_WRITE_AROMATIC_BONDS;
        extern const bool        SMILES_OUTPUT_WRITE_ISOTOPE;
        extern const bool        SMILES_OUTPUT_NO_ORGANIC_SUBSET;
        extern const std::size_t SMILES_OUTPUT_MIN_STEREO_BOND_RING_SIZE;
        extern const bool        SMILES_OUTPUT_WRITE_SINGLE_RECORD_FILES;
        extern const std::string SMILES_OUTPUT_RECORD_FORMAT;

        extern const bool SMARTS_INPUT_STRICT_ERROR_CHECKING;

        extern const bool        SMARTS_OUTPUT_STRICT_ERROR_CHECKING;
        extern const bool        SMARTS_OUTPUT_WRITE_SINGLE_RECORD_FILES;
        extern const std::string SMARTS_OUTPUT_RECORD_SEPARATOR;

        extern const bool        INCHI_INPUT_STRICT_ERROR_CHECKING;
        extern const std::string INCHI_INPUT_OPTIONS;

        extern const bool        INCHI_OUTPUT_STRICT_ERROR_CHECKING;
        extern const std::string INCHI_OUTPUT_OPTIONS;
        extern const std::string INCHI_OUTPUT_RECORD_SEPARATOR;
        extern const bool        INCHI_OUTPUT_WRITE_SINGLE_RECORD_FILES;

        extern const bool PDB_INPUT_STRICT_ERROR_CHECKING;
        extern const bool PDB_INPUT_CHECK_LINE_LENGTH;

        extern const bool MMCIF_INPUT_STRICT_ERROR_CHECKING;

        extern const bool MMCIF_OUTPUT_STRICT_ERROR_CHECKING;
        extern const bool MMCIF_OUTPUT_WRITE_SINGLE_RECORD_FILES;
        
        extern const bool MMTF_INPUT_STRICT_ERROR_CHECKING;

        extern const bool CDF_OUTPUT_WRITE_SINGLE_RECORD_FILES;
        extern const bool CDF_OUTPUT_WRITE_SINGLE_PRECISION_FLOATS;

        extern const bool CFL_INPUT_STRICT_ERROR_CHECKING;

        extern const bool                                  PSD_OUTPUT_WRITE_SINGLE_RECORD_FILES;
        extern const bool                                  PSD_OUTPUT_WRITE_SINGLE_PRECISION_FLOATS;
        extern const bool                                  PSD_OUTPUT_ALLOW_DUPLICATES;
        extern const CDPL::Pharm::ScreeningDBCreator::Mode PSD_CREATION_MODE;

        extern const QStringList SUBSTRUCT_HIGHLIGHTING_PATTERNS;
        extern const bool        SUBSTRUCT_HIGHLIGHTING_ENABLED;

        extern const QStringList SUBSTRUCT_SEARCH_QUERY;
        
        extern const CDPL::Vis::Brush ATOM_HIGHLIGHT_AREA_BRUSH;
        extern const CDPL::Vis::Brush BOND_HIGHLIGHT_AREA_BRUSH;
        
    } // namespace ControlParameterDefault
} // namespace ChOX

#endif // CHOX_CONTROLPARAMETERDEFAULT_HPP

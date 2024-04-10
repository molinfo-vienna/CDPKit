/* 
 * Settings.cpp 
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
 * along with this program; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <cstddef>
#include <functional>

#include <boost/lexical_cast.hpp>

#include <QSettings>
#include <QStringList>
#include <QString>

#include "CDPL/Base/DataFormat.hpp"
#include "CDPL/Chem/ControlParameter.hpp"
#include "CDPL/Chem/DataFormat.hpp"
#include "CDPL/Pharm/ControlParameter.hpp"
#include "CDPL/Pharm/DataFormat.hpp"
#include "CDPL/Biomol/ControlParameter.hpp"
#include "CDPL/Biomol/DataFormat.hpp"
#include "CDPL/ConfGen/ControlParameter.hpp"
#include "CDPL/ConfGen/DataFormat.hpp"
#include "CDPL/Vis/ControlParameter.hpp"
#include "CDPL/Vis/ControlParameterDefault.hpp"
#include "CDPL/Vis/ControlParameterFunctions.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Brush.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"
#include "CDPL/Vis/DataFormat.hpp"

#include "Settings.hpp"
#include "ControlParameter.hpp"
#include "ControlParameterDefault.hpp"
#include "ControlParameterFunctions.hpp"


using namespace ChOX;


Settings::Settings(QObject* parent): QObject(parent) 
{
    using namespace CDPL;
    using namespace std::placeholders;
    
    registerParameterChangedCallback(std::bind(&Settings::parameterChanged, this, _1, _2));

    readerControlParams[Chem::DataFormat::CDF_GZ.getName()].setParent(&readerControlParams[Chem::DataFormat::CDF.getName()]);
    readerControlParams[Chem::DataFormat::CDF_BZ2.getName()].setParent(&readerControlParams[Chem::DataFormat::CDF.getName()]);
    readerControlParams[Chem::DataFormat::SMILES_GZ.getName()].setParent(&readerControlParams[Chem::DataFormat::SMILES.getName()]);
    readerControlParams[Chem::DataFormat::SMILES_BZ2.getName()].setParent(&readerControlParams[Chem::DataFormat::SMILES.getName()]);
    readerControlParams[Chem::DataFormat::SDF_GZ.getName()].setParent(&readerControlParams[Chem::DataFormat::SDF.getName()]);
    readerControlParams[Chem::DataFormat::SDF_BZ2.getName()].setParent(&readerControlParams[Chem::DataFormat::SDF.getName()]);
    readerControlParams[Chem::DataFormat::RDF_GZ.getName()].setParent(&readerControlParams[Chem::DataFormat::RDF.getName()]);
    readerControlParams[Chem::DataFormat::RDF_BZ2.getName()].setParent(&readerControlParams[Chem::DataFormat::RDF.getName()]);
    readerControlParams[Chem::DataFormat::MOL2_GZ.getName()].setParent(&readerControlParams[Chem::DataFormat::MOL2.getName()]);
    readerControlParams[Chem::DataFormat::MOL2_BZ2.getName()].setParent(&readerControlParams[Chem::DataFormat::MOL2.getName()]);
    readerControlParams[Chem::DataFormat::XYZ_GZ.getName()].setParent(&readerControlParams[Chem::DataFormat::XYZ.getName()]);
    readerControlParams[Chem::DataFormat::XYZ_BZ2.getName()].setParent(&readerControlParams[Chem::DataFormat::XYZ.getName()]);
    readerControlParams[Biomol::DataFormat::PDB_GZ.getName()].setParent(&readerControlParams[Biomol::DataFormat::PDB.getName()]);
    readerControlParams[Biomol::DataFormat::PDB_BZ2.getName()].setParent(&readerControlParams[Biomol::DataFormat::PDB.getName()]);

    writerControlParams[Chem::DataFormat::CDF_GZ.getName()].setParent(&writerControlParams[Chem::DataFormat::CDF.getName()]);
    writerControlParams[Chem::DataFormat::CDF_BZ2.getName()].setParent(&writerControlParams[Chem::DataFormat::CDF.getName()]);
    writerControlParams[Chem::DataFormat::SMILES_GZ.getName()].setParent(&writerControlParams[Chem::DataFormat::SMILES.getName()]);
    writerControlParams[Chem::DataFormat::SMILES_BZ2.getName()].setParent(&writerControlParams[Chem::DataFormat::SMILES.getName()]);
    writerControlParams[Chem::DataFormat::SDF_GZ.getName()].setParent(&writerControlParams[Chem::DataFormat::SDF.getName()]);
    writerControlParams[Chem::DataFormat::SDF_BZ2.getName()].setParent(&writerControlParams[Chem::DataFormat::SDF.getName()]);
    writerControlParams[Chem::DataFormat::RDF_GZ.getName()].setParent(&writerControlParams[Chem::DataFormat::RDF.getName()]);
    writerControlParams[Chem::DataFormat::RDF_BZ2.getName()].setParent(&writerControlParams[Chem::DataFormat::RDF.getName()]);
    writerControlParams[Chem::DataFormat::MOL2_GZ.getName()].setParent(&writerControlParams[Chem::DataFormat::MOL2.getName()]);
    writerControlParams[Chem::DataFormat::MOL2_BZ2.getName()].setParent(&writerControlParams[Chem::DataFormat::MOL2.getName()]);
    writerControlParams[Chem::DataFormat::XYZ_GZ.getName()].setParent(&writerControlParams[Chem::DataFormat::XYZ.getName()]);
    writerControlParams[Chem::DataFormat::XYZ_BZ2.getName()].setParent(&writerControlParams[Chem::DataFormat::XYZ.getName()]);
    writerControlParams[Biomol::DataFormat::PDB_GZ.getName()].setParent(&writerControlParams[Biomol::DataFormat::PDB.getName()]);
    writerControlParams[Biomol::DataFormat::PDB_BZ2.getName()].setParent(&writerControlParams[Biomol::DataFormat::PDB.getName()]);

    SettingsContainer& img_params = writerControlParams["img"];

    writerControlParams[Vis::DataFormat::PNG.getName()].setParent(&img_params);
    writerControlParams[Vis::DataFormat::PDF.getName()].setParent(&img_params);
    writerControlParams[Vis::DataFormat::SVG.getName()].setParent(&img_params);
    writerControlParams[Vis::DataFormat::PS.getName()].setParent(&img_params);
}

const SettingsContainer& Settings::getReaderControlParameters(const std::string& format) const
{
    IOControlParamMap::const_iterator it = readerControlParams.find(format);

    return (it == readerControlParams.end() ? *this : it->second);
}

const SettingsContainer& Settings::getWriterControlParameters(const std::string& format) const
{
    IOControlParamMap::const_iterator it = writerControlParams.find(format);

    return (it == writerControlParams.end() ? *this : it->second);
}

SettingsContainer& Settings::getReaderControlParameters(const std::string& format)
{
    IOControlParamMap::iterator it = readerControlParams.find(format);

    return (it == readerControlParams.end() ? *this : it->second);
}

SettingsContainer& Settings::getWriterControlParameters(const std::string& format)
{
    IOControlParamMap::iterator it = writerControlParams.find(format);

    return (it == writerControlParams.end() ? *this : it->second);
}

void Settings::load()
{
    QSettings settings;

    using namespace CDPL;

    for (IOControlParamMap::iterator it = readerControlParams.begin(), end = readerControlParams.end(); it != end; ++it)
        it->second.clearParameters();

    for (IOControlParamMap::iterator it = writerControlParams.begin(), end = writerControlParams.end(); it != end; ++it)
        it->second.clearParameters();

    settings.beginGroup("View");

    readColorParameter(*this, settings, ControlParameter::VIEW_BACKGROUND_COLOR, ControlParameterDefault::VIEW_BACKGROUND_COLOR);
    readColorParameter(*this, settings, ControlParameter::VIEW_SELECTION_COLOR, ControlParameterDefault::VIEW_SELECTION_COLOR);
    readParameter<bool>(*this, settings, ControlParameter::SHOW_GRID, ControlParameterDefault::SHOW_GRID);
    readParameter<bool>(*this, settings, ControlParameter::SHOW_RECORD_NUMBERS, ControlParameterDefault::SHOW_RECORD_NUMBERS);
    readParameter<bool>(*this, settings, ControlParameter::SHOW_RECORD_NAMES, ControlParameterDefault::SHOW_RECORD_NAMES);
    readLineStyleParameter(*this, settings, ControlParameter::GRID_LINE_STYLE, ControlParameterDefault::GRID_LINE_STYLE);
    readParameter<std::size_t>(*this, settings, ControlParameter::GRID_ROW_COUNT, ControlParameterDefault::GRID_ROW_COUNT);
    readParameter<std::size_t>(*this, settings, ControlParameter::GRID_COLUMN_COUNT, ControlParameterDefault::GRID_COLUMN_COUNT);
    readColorParameter(*this, settings, ControlParameter::GRID_LINE_COLOR, ControlParameterDefault::GRID_LINE_COLOR);
    readSizeSpecParameter(*this, settings, ControlParameter::GRID_LINE_WIDTH, ControlParameterDefault::GRID_LINE_WIDTH);

    readFontParameter(*this, settings, ControlParameter::RECORD_NUMBER_LABEL_FONT, ControlParameterDefault::RECORD_NUMBER_LABEL_FONT);
    readSizeSpecParameter(*this, settings, ControlParameter::RECORD_NUMBER_LABEL_SIZE, ControlParameterDefault::RECORD_NUMBER_LABEL_SIZE);
    readParameter<unsigned int>(*this, settings, ControlParameter::RECORD_NUMBER_LABEL_ALIGNMENT, ControlParameterDefault::RECORD_NUMBER_LABEL_ALIGNMENT);
    readColorParameter(*this, settings, ControlParameter::RECORD_NUMBER_LABEL_COLOR, ControlParameterDefault::RECORD_NUMBER_LABEL_COLOR);

    readFontParameter(*this, settings, ControlParameter::RECORD_NAME_LABEL_FONT, ControlParameterDefault::RECORD_NAME_LABEL_FONT);
    readSizeSpecParameter(*this, settings, ControlParameter::RECORD_NAME_LABEL_SIZE, ControlParameterDefault::RECORD_NAME_LABEL_SIZE);
    readParameter<unsigned int>(*this, settings, ControlParameter::RECORD_NAME_LABEL_ALIGNMENT, ControlParameterDefault::RECORD_NAME_LABEL_ALIGNMENT);
    readColorParameter(*this, settings, ControlParameter::RECORD_NAME_LABEL_COLOR, ControlParameterDefault::RECORD_NAME_LABEL_COLOR);

    readParameter<unsigned int>(*this, settings, Vis::ControlParameter::SIZE_ADJUSTMENT, Vis::ControlParameterDefault::SIZE_ADJUSTMENT);
    readParameter<unsigned int>(*this, settings, Vis::ControlParameter::ALIGNMENT, Vis::ControlParameterDefault::ALIGNMENT);

    settings.endGroup();

    settings.beginGroup("Reactions");

    readParameter<unsigned int>(*this, settings, Vis::ControlParameter::REACTION_ARROW_STYLE, Vis::ControlParameterDefault::REACTION_ARROW_STYLE);
    readColorParameter(*this, settings, Vis::ControlParameter::REACTION_ARROW_COLOR, Vis::ControlParameterDefault::REACTION_ARROW_COLOR);
    readSizeSpecParameter(*this, settings, Vis::ControlParameter::REACTION_ARROW_LENGTH, Vis::ControlParameterDefault::REACTION_ARROW_LENGTH);
    readSizeSpecParameter(*this, settings, Vis::ControlParameter::REACTION_ARROW_HEAD_LENGTH, Vis::ControlParameterDefault::REACTION_ARROW_HEAD_LENGTH);
    readSizeSpecParameter(*this, settings, Vis::ControlParameter::REACTION_ARROW_HEAD_WIDTH, Vis::ControlParameterDefault::REACTION_ARROW_HEAD_WIDTH);
    readSizeSpecParameter(*this, settings, Vis::ControlParameter::REACTION_ARROW_SHAFT_WIDTH, Vis::ControlParameterDefault::REACTION_ARROW_SHAFT_WIDTH);
    readSizeSpecParameter(*this, settings, Vis::ControlParameter::REACTION_ARROW_LINE_WIDTH, Vis::ControlParameterDefault::REACTION_ARROW_LINE_WIDTH);
    readParameter<unsigned int>(*this, settings, Vis::ControlParameter::REACTION_COMPONENT_LAYOUT, Vis::ControlParameterDefault::REACTION_COMPONENT_LAYOUT);
    readParameter<unsigned int>(*this, settings, Vis::ControlParameter::REACTION_COMPONENT_LAYOUT_DIRECTION, 
                                Vis::ControlParameterDefault::REACTION_COMPONENT_LAYOUT_DIRECTION);
    readSizeSpecParameter(*this, settings, Vis::ControlParameter::REACTION_COMPONENT_MARGIN, Vis::ControlParameterDefault::REACTION_COMPONENT_MARGIN);
    readParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_REACTION_REACTANTS, Vis::ControlParameterDefault::SHOW_REACTION_REACTANTS);
    readParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_REACTION_AGENTS, Vis::ControlParameterDefault::SHOW_REACTION_AGENTS);
    readParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_REACTION_PRODUCTS, Vis::ControlParameterDefault::SHOW_REACTION_PRODUCTS);
    readParameter<unsigned int>(*this, settings, Vis::ControlParameter::REACTION_AGENT_ALIGNMENT, Vis::ControlParameterDefault::REACTION_AGENT_ALIGNMENT);
    readParameter<unsigned int>(*this, settings, Vis::ControlParameter::REACTION_AGENT_LAYOUT, Vis::ControlParameterDefault::REACTION_AGENT_LAYOUT);
    readParameter<unsigned int>(*this, settings, Vis::ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION, 
                                Vis::ControlParameterDefault::REACTION_AGENT_LAYOUT_DIRECTION);
    readColorParameter(*this, settings, Vis::ControlParameter::REACTION_PLUS_SIGN_COLOR, Vis::ControlParameterDefault::REACTION_PLUS_SIGN_COLOR);
    readSizeSpecParameter(*this, settings, Vis::ControlParameter::REACTION_PLUS_SIGN_SIZE, Vis::ControlParameterDefault::REACTION_PLUS_SIGN_SIZE);
    readSizeSpecParameter(*this, settings, Vis::ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH, 
                          Vis::ControlParameterDefault::REACTION_PLUS_SIGN_LINE_WIDTH);
    readParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_REACTION_PLUS_SIGNS, Vis::ControlParameterDefault::SHOW_REACTION_PLUS_SIGNS);

    settings.endGroup();

    settings.beginGroup("Atoms");

    readColorParameter(*this, settings, Vis::ControlParameter::ATOM_COLOR, Vis::ControlParameterDefault::ATOM_COLOR);
    readAtomColorTableParam(settings);

    readParameter<bool>(*this, settings, ControlParameter::USE_ATOM_COLOR_TABLE, ControlParameterDefault::USE_ATOM_COLOR_TABLE);
    readParameter<bool>(*this, settings, Vis::ControlParameter::USE_CALCULATED_ATOM_COORDINATES, 
                        Vis::ControlParameterDefault::USE_CALCULATED_ATOM_COORDINATES);
    readFontParameter(*this, settings, Vis::ControlParameter::ATOM_LABEL_FONT, Vis::ControlParameterDefault::ATOM_LABEL_FONT);
    readSizeSpecParameter(*this, settings, Vis::ControlParameter::ATOM_LABEL_SIZE, Vis::ControlParameterDefault::ATOM_LABEL_SIZE);
    readFontParameter(*this, settings, Vis::ControlParameter::SECONDARY_ATOM_LABEL_FONT, Vis::ControlParameterDefault::SECONDARY_ATOM_LABEL_FONT);
    readSizeSpecParameter(*this, settings, Vis::ControlParameter::SECONDARY_ATOM_LABEL_SIZE, Vis::ControlParameterDefault::SECONDARY_ATOM_LABEL_SIZE);
    readSizeSpecParameter(*this, settings, Vis::ControlParameter::ATOM_LABEL_MARGIN, Vis::ControlParameterDefault::ATOM_LABEL_MARGIN);
    readSizeSpecParameter(*this, settings, Vis::ControlParameter::RADICAL_ELECTRON_DOT_SIZE, Vis::ControlParameterDefault::RADICAL_ELECTRON_DOT_SIZE);
    readParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_CARBONS, Vis::ControlParameterDefault::SHOW_CARBONS);
    readParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_CHARGES, Vis::ControlParameterDefault::SHOW_CHARGES);
    readParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_ISOTOPES, Vis::ControlParameterDefault::SHOW_ISOTOPES);
    readParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_EXPLICIT_HYDROGENS, Vis::ControlParameterDefault::SHOW_EXPLICIT_HYDROGENS);
    readParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_HYDROGEN_COUNTS, Vis::ControlParameterDefault::SHOW_HYDROGEN_COUNTS);
    readParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_NON_CARBON_HYDROGEN_COUNTS, 
                        Vis::ControlParameterDefault::SHOW_NON_CARBON_HYDROGEN_COUNTS);
    readParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_ATOM_QUERY_INFOS, Vis::ControlParameterDefault::SHOW_ATOM_QUERY_INFOS);
    readParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_ATOM_REACTION_INFOS, Vis::ControlParameterDefault::SHOW_ATOM_REACTION_INFOS);
    readParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_RADICAL_ELECTRONS, Vis::ControlParameterDefault::SHOW_RADICAL_ELECTRONS);
    readParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_ATOM_CONFIGURATION_LABELS, Vis::ControlParameterDefault::SHOW_ATOM_CONFIGURATION_LABELS);
    readSizeSpecParameter(*this, settings, Vis::ControlParameter::ATOM_CONFIGURATION_LABEL_SIZE, Vis::ControlParameterDefault::ATOM_CONFIGURATION_LABEL_SIZE);
    readFontParameter(*this, settings, Vis::ControlParameter::ATOM_CONFIGURATION_LABEL_FONT, Vis::ControlParameterDefault::ATOM_CONFIGURATION_LABEL_FONT);
    readColorParameter(*this, settings, Vis::ControlParameter::ATOM_CONFIGURATION_LABEL_COLOR, Vis::ControlParameterDefault::ATOM_CONFIGURATION_LABEL_COLOR);

    settings.endGroup();

    settings.beginGroup("Bonds");
            
    readColorParameter(*this, settings, Vis::ControlParameter::BOND_COLOR, Vis::ControlParameterDefault::BOND_COLOR);
    readSizeSpecParameter(*this, settings, Vis::ControlParameter::BOND_LENGTH, Vis::ControlParameterDefault::BOND_LENGTH);
    readSizeSpecParameter(*this, settings, Vis::ControlParameter::BOND_LINE_WIDTH, Vis::ControlParameterDefault::BOND_LINE_WIDTH);
    readSizeSpecParameter(*this, settings, Vis::ControlParameter::BOND_LINE_SPACING, Vis::ControlParameterDefault::BOND_LINE_SPACING);
    readSizeSpecParameter(*this, settings, Vis::ControlParameter::STEREO_BOND_WEDGE_WIDTH, Vis::ControlParameterDefault::STEREO_BOND_WEDGE_WIDTH);
    readSizeSpecParameter(*this, settings, Vis::ControlParameter::STEREO_BOND_HASH_SPACING, Vis::ControlParameterDefault::STEREO_BOND_HASH_SPACING);
    readSizeSpecParameter(*this, settings, Vis::ControlParameter::REACTION_CENTER_LINE_LENGTH, Vis::ControlParameterDefault::REACTION_CENTER_LINE_LENGTH);
    readSizeSpecParameter(*this, settings, Vis::ControlParameter::REACTION_CENTER_LINE_SPACING, Vis::ControlParameterDefault::REACTION_CENTER_LINE_SPACING);
    readSizeSpecParameter(*this, settings, Vis::ControlParameter::DOUBLE_BOND_TRIM_LENGTH, Vis::ControlParameterDefault::DOUBLE_BOND_TRIM_LENGTH);
    readSizeSpecParameter(*this, settings, Vis::ControlParameter::TRIPLE_BOND_TRIM_LENGTH, Vis::ControlParameterDefault::TRIPLE_BOND_TRIM_LENGTH);
    readFontParameter(*this, settings, Vis::ControlParameter::BOND_LABEL_FONT, Vis::ControlParameterDefault::BOND_LABEL_FONT);
    readSizeSpecParameter(*this, settings, Vis::ControlParameter::BOND_LABEL_SIZE, Vis::ControlParameterDefault::BOND_LABEL_SIZE);
    readSizeSpecParameter(*this, settings, Vis::ControlParameter::BOND_LABEL_MARGIN, Vis::ControlParameterDefault::BOND_LABEL_MARGIN);
    readParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_BOND_REACTION_INFOS, Vis::ControlParameterDefault::SHOW_BOND_REACTION_INFOS);
    readParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_BOND_QUERY_INFOS, Vis::ControlParameterDefault::SHOW_BOND_QUERY_INFOS);
    readParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_STEREO_BONDS, Vis::ControlParameterDefault::SHOW_STEREO_BONDS);
    readParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_BOND_CONFIGURATION_LABELS, Vis::ControlParameterDefault::SHOW_BOND_CONFIGURATION_LABELS);
    readSizeSpecParameter(*this, settings, Vis::ControlParameter::BOND_CONFIGURATION_LABEL_SIZE, Vis::ControlParameterDefault::BOND_CONFIGURATION_LABEL_SIZE);
    readFontParameter(*this, settings, Vis::ControlParameter::BOND_CONFIGURATION_LABEL_FONT, Vis::ControlParameterDefault::BOND_CONFIGURATION_LABEL_FONT);
    readColorParameter(*this, settings, Vis::ControlParameter::BOND_CONFIGURATION_LABEL_COLOR, Vis::ControlParameterDefault::BOND_CONFIGURATION_LABEL_COLOR);

    settings.endGroup();

    settings.beginGroup("Printing");

    readParameter<bool>(*this, settings, ControlParameter::PRINT_FRAME, ControlParameterDefault::PRINT_FRAME);
    readParameter<bool>(*this, settings, ControlParameter::PRINT_DATE, ControlParameterDefault::PRINT_DATE);
    readParameter<bool>(*this, settings, ControlParameter::PRINT_PAGE_NUMBER, ControlParameterDefault::PRINT_PAGE_NUMBER);
    readParameter<bool>(*this, settings, ControlParameter::PRINT_FILE_NAME, ControlParameterDefault::PRINT_FILE_NAME);
    readLineStyleParameter(*this, settings, ControlParameter::FRAME_LINE_STYLE, ControlParameterDefault::FRAME_LINE_STYLE);
    readColorParameter(*this, settings, ControlParameter::FRAME_LINE_COLOR, ControlParameterDefault::FRAME_LINE_COLOR);
    readSizeSpecParameter(*this, settings, ControlParameter::FRAME_LINE_WIDTH, ControlParameterDefault::FRAME_LINE_WIDTH);
    readFontParameter(*this, settings, ControlParameter::PRINTING_TEXT_LABEL_FONT, ControlParameterDefault::PRINTING_TEXT_LABEL_FONT);
    readSizeSpecParameter(*this, settings, ControlParameter::PRINTING_TEXT_LABEL_SIZE, ControlParameterDefault::PRINTING_TEXT_LABEL_SIZE);
    readSizeSpecParameter(*this, settings, ControlParameter::PRINTING_TEXT_LABEL_SPACING, ControlParameterDefault::PRINTING_TEXT_LABEL_SPACING);
    readColorParameter(*this, settings, ControlParameter::PRINTING_TEXT_LABEL_COLOR, ControlParameterDefault::PRINTING_TEXT_LABEL_COLOR);
    readParameter<unsigned int>(*this, settings, ControlParameter::PAGE_NUMBER_LABEL_ALIGNMENT, ControlParameterDefault::PAGE_NUMBER_LABEL_ALIGNMENT);
    readParameter<unsigned int>(*this, settings, ControlParameter::DATE_LABEL_ALIGNMENT, ControlParameterDefault::DATE_LABEL_ALIGNMENT);
    readParameter<unsigned int>(*this, settings, ControlParameter::FILE_NAME_LABEL_ALIGNMENT, ControlParameterDefault::FILE_NAME_LABEL_ALIGNMENT);

    settings.endGroup();

    settings.beginGroup("FileIO");

    readParameter<std::string>(*this, settings, ControlParameter::DEFAULT_MOL_OUTPUT_FORMAT, ControlParameterDefault::DEFAULT_MOL_OUTPUT_FORMAT);
    readParameter<std::string>(*this, settings, ControlParameter::DEFAULT_RXN_OUTPUT_FORMAT, ControlParameterDefault::DEFAULT_RXN_OUTPUT_FORMAT);

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + Chem::DataFormat::JME.getName()));

    SettingsContainer& jme_rparams = readerControlParams[Chem::DataFormat::JME.getName()];

    jme_rparams.setParent(this);

    readParameter<bool>(jme_rparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING, ControlParameterDefault::JME_INPUT_STRICT_ERROR_CHECKING);

    settings.endGroup();

    // +++

    settings.beginGroup(QString::fromStdString("Output/" + Chem::DataFormat::JME.getName()));

    SettingsContainer& jme_wparams = writerControlParams[Chem::DataFormat::JME.getName()];

    jme_wparams.setParent(this);

    readParameter<bool>(jme_wparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING, ControlParameterDefault::JME_OUTPUT_STRICT_ERROR_CHECKING);
    readParameter<bool>(jme_wparams, settings, Chem::ControlParameter::JME_SEPARATE_COMPONENTS, ControlParameterDefault::JME_OUTPUT_SEPARATE_COMPONENTS);
    readParameter<bool>(jme_wparams, settings, ControlParameter::WRITE_SINGLE_RECORD_FILES, ControlParameterDefault::JME_OUTPUT_WRITE_SINGLE_RECORD_FILES);
    readParameter<std::string>(jme_wparams, settings, Chem::ControlParameter::RECORD_SEPARATOR, ControlParameterDefault::JME_OUTPUT_RECORD_SEPARATOR);

    settings.endGroup();

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + Chem::DataFormat::SMILES.getName()));

    SettingsContainer& smiles_rparams = readerControlParams[Chem::DataFormat::SMILES.getName()];

    smiles_rparams.setParent(this);

    readParameter<bool>(smiles_rparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING, ControlParameterDefault::SMILES_INPUT_STRICT_ERROR_CHECKING);
    readParameter<std::string>(smiles_rparams, settings, Chem::ControlParameter::SMILES_RECORD_FORMAT, ControlParameterDefault::SMILES_INPUT_RECORD_FORMAT);

    settings.endGroup();

    // +++

    settings.beginGroup(QString::fromStdString("Output/" + Chem::DataFormat::SMILES.getName()));

    SettingsContainer& smiles_wparams = writerControlParams[Chem::DataFormat::SMILES.getName()];

    smiles_wparams.setParent(this);

    readParameter<bool>(smiles_wparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING, ControlParameterDefault::SMILES_OUTPUT_STRICT_ERROR_CHECKING);
    readParameter<bool>(smiles_wparams, settings, Chem::ControlParameter::ORDINARY_HYDROGEN_DEPLETE, ControlParameterDefault::SMILES_OUTPUT_ORDINARY_H_DEPLETE);
    readParameter<bool>(smiles_wparams, settings, Chem::ControlParameter::SMILES_WRITE_CANONICAL_FORM, ControlParameterDefault::SMILES_OUTPUT_WRITE_CANONICAL_FORM);
    readParameter<bool>(smiles_wparams, settings, Chem::ControlParameter::SMILES_WRITE_KEKULE_FORM, ControlParameterDefault::SMILES_OUTPUT_WRITE_KEKULE_FORM);
    readParameter<bool>(smiles_wparams, settings, Chem::ControlParameter::SMILES_WRITE_ATOM_STEREO, ControlParameterDefault::SMILES_OUTPUT_WRITE_ATOM_STEREO);
    readParameter<bool>(smiles_wparams, settings, Chem::ControlParameter::SMILES_WRITE_ISOTOPE, ControlParameterDefault::SMILES_OUTPUT_WRITE_ISOTOPE);
    readParameter<bool>(smiles_wparams, settings, Chem::ControlParameter::SMILES_WRITE_BOND_STEREO, ControlParameterDefault::SMILES_OUTPUT_WRITE_BOND_STEREO);
    readParameter<bool>(smiles_wparams, settings, Chem::ControlParameter::SMILES_WRITE_RING_BOND_STEREO, ControlParameterDefault::SMILES_OUTPUT_WRITE_RING_BOND_STEREO);
    readParameter<bool>(smiles_wparams, settings, Chem::ControlParameter::SMILES_RXN_WRITE_ATOM_MAPPING_ID, ControlParameterDefault::SMILES_OUTPUT_WRITE_ATOM_MAPPING_ID);
    readParameter<bool>(smiles_wparams, settings, Chem::ControlParameter::SMILES_MOL_WRITE_ATOM_MAPPING_ID, ControlParameterDefault::SMILES_OUTPUT_WRITE_ATOM_MAPPING_ID);
    readParameter<bool>(smiles_wparams, settings, Chem::ControlParameter::SMILES_WRITE_SINGLE_BONDS, ControlParameterDefault::SMILES_OUTPUT_WRITE_SINGLE_BONDS);
    readParameter<bool>(smiles_wparams, settings, Chem::ControlParameter::SMILES_WRITE_AROMATIC_BONDS, ControlParameterDefault::SMILES_OUTPUT_WRITE_AROMATIC_BONDS);
    readParameter<bool>(smiles_wparams, settings, Chem::ControlParameter::SMILES_NO_ORGANIC_SUBSET, ControlParameterDefault::SMILES_OUTPUT_NO_ORGANIC_SUBSET);
    readParameter<std::size_t>(smiles_wparams, settings, Chem::ControlParameter::SMILES_MIN_STEREO_BOND_RING_SIZE, ControlParameterDefault::SMILES_OUTPUT_MIN_STEREO_BOND_RING_SIZE);
    readParameter<bool>(smiles_wparams, settings, ControlParameter::WRITE_SINGLE_RECORD_FILES, ControlParameterDefault::SMILES_OUTPUT_WRITE_SINGLE_RECORD_FILES);
    readParameter<std::string>(smiles_wparams, settings, Chem::ControlParameter::SMILES_RECORD_FORMAT, ControlParameterDefault::SMILES_OUTPUT_RECORD_FORMAT);

    settings.endGroup();

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + Chem::DataFormat::SMARTS.getName()));

    SettingsContainer& smarts_rparams = readerControlParams[Chem::DataFormat::SMARTS.getName()];

    smarts_rparams.setParent(this);

    readParameter<bool>(smarts_rparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING, ControlParameterDefault::SMARTS_INPUT_STRICT_ERROR_CHECKING);

    settings.endGroup();

    // +++

    settings.beginGroup(QString::fromStdString("Output/" + Chem::DataFormat::SMARTS.getName()));

    SettingsContainer& smarts_wparams = writerControlParams[Chem::DataFormat::SMARTS.getName()];

    smarts_wparams.setParent(this);

    readParameter<bool>(smarts_wparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING, ControlParameterDefault::SMARTS_OUTPUT_STRICT_ERROR_CHECKING);
    readParameter<bool>(smarts_wparams, settings, ControlParameter::WRITE_SINGLE_RECORD_FILES, ControlParameterDefault::SMARTS_OUTPUT_WRITE_SINGLE_RECORD_FILES);
    readParameter<std::string>(smarts_wparams, settings, Chem::ControlParameter::RECORD_SEPARATOR, ControlParameterDefault::SMARTS_OUTPUT_RECORD_SEPARATOR);

    settings.endGroup();

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + Chem::DataFormat::INCHI.getName()));

    SettingsContainer& inchi_rparams = readerControlParams[Chem::DataFormat::INCHI.getName()];

    inchi_rparams.setParent(this);

    readParameter<bool>(inchi_rparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING, ControlParameterDefault::INCHI_INPUT_STRICT_ERROR_CHECKING);
    readParameter<std::string>(inchi_rparams, settings, Chem::ControlParameter::INCHI_INPUT_OPTIONS, ControlParameterDefault::INCHI_INPUT_OPTIONS);

    settings.endGroup();

    // +++

    settings.beginGroup(QString::fromStdString("Output/" + Chem::DataFormat::INCHI.getName()));

    SettingsContainer& inchi_wparams = writerControlParams[Chem::DataFormat::INCHI.getName()];

    inchi_wparams.setParent(this);

    readParameter<bool>(inchi_wparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING, ControlParameterDefault::INCHI_OUTPUT_STRICT_ERROR_CHECKING);
    readParameter<std::string>(inchi_wparams, settings, Chem::ControlParameter::RECORD_SEPARATOR, ControlParameterDefault::INCHI_OUTPUT_RECORD_SEPARATOR);
    readParameter<bool>(inchi_wparams, settings, ControlParameter::WRITE_SINGLE_RECORD_FILES, ControlParameterDefault::INCHI_OUTPUT_WRITE_SINGLE_RECORD_FILES);
    readParameter<std::string>(inchi_wparams, settings, Chem::ControlParameter::INCHI_OUTPUT_OPTIONS, ControlParameterDefault::INCHI_OUTPUT_OPTIONS);

    settings.endGroup();

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + Chem::DataFormat::MOL2.getName()));

    SettingsContainer& mol2_rparams = readerControlParams[Chem::DataFormat::MOL2.getName()];

    mol2_rparams.setParent(this);

    readParameter<bool>(mol2_rparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING, ControlParameterDefault::MOL2_INPUT_STRICT_ERROR_CHECKING);
    readParameter<bool>(mol2_rparams, settings, Chem::ControlParameter::MULTI_CONF_IMPORT, ControlParameterDefault::MOL2_INPUT_MULTI_CONF_IMPORT);

    settings.endGroup();

    // +++

    settings.beginGroup(QString::fromStdString("Output/" + Chem::DataFormat::MOL2.getName()));

    SettingsContainer& mol2_wparams = writerControlParams[Chem::DataFormat::MOL2.getName()];

    mol2_wparams.setParent(this);

    readParameter<bool>(mol2_wparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING, ControlParameterDefault::MOL2_OUTPUT_STRICT_ERROR_CHECKING);
    readParameter<bool>(mol2_wparams, settings, ControlParameter::WRITE_SINGLE_RECORD_FILES, ControlParameterDefault::MOL2_OUTPUT_WRITE_SINGLE_RECORD_FILES);
    readParameter<bool>(mol2_wparams, settings, Chem::ControlParameter::MULTI_CONF_EXPORT, ControlParameterDefault::MOL2_OUTPUT_MULTI_CONF_EXPORT);

    settings.endGroup();

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + Chem::DataFormat::XYZ.getName()));

    SettingsContainer& xyz_rparams = readerControlParams[Chem::DataFormat::XYZ.getName()];

    xyz_rparams.setParent(this);

    readParameter<bool>(xyz_rparams, settings, Chem::ControlParameter::MULTI_CONF_IMPORT, ControlParameterDefault::XYZ_INPUT_MULTI_CONF_IMPORT);

    settings.endGroup();

    // +++

    settings.beginGroup(QString::fromStdString("Output/" + Chem::DataFormat::XYZ.getName()));

    SettingsContainer& xyz_wparams = writerControlParams[Chem::DataFormat::XYZ.getName()];

    xyz_wparams.setParent(this);

    readParameter<bool>(xyz_wparams, settings, ControlParameter::WRITE_SINGLE_RECORD_FILES, ControlParameterDefault::XYZ_OUTPUT_WRITE_SINGLE_RECORD_FILES);
    readParameter<bool>(xyz_wparams, settings, Chem::ControlParameter::MULTI_CONF_EXPORT, ControlParameterDefault::XYZ_OUTPUT_MULTI_CONF_EXPORT);

    settings.endGroup();

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + Chem::DataFormat::MOL.getName()));

    SettingsContainer& mol_rparams = readerControlParams[Chem::DataFormat::MOL.getName()];

    mol_rparams.setParent(this);

    readParameter<bool>(mol_rparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING, ControlParameterDefault::MOL_INPUT_STRICT_ERROR_CHECKING);
    readParameter<bool>(mol_rparams, settings, Chem::ControlParameter::MDL_IGNORE_PARITY, ControlParameterDefault::MOL_INPUT_IGNORE_PARITY);
    readParameter<bool>(mol_rparams, settings, Chem::ControlParameter::MDL_TRIM_STRINGS, ControlParameterDefault::MOL_INPUT_TRIM_STRINGS);
    readParameter<bool>(mol_rparams, settings, Chem::ControlParameter::MDL_TRIM_LINES, ControlParameterDefault::MOL_INPUT_TRIM_LINES);
    readParameter<bool>(mol_rparams, settings, Chem::ControlParameter::CHECK_LINE_LENGTH, ControlParameterDefault::MOL_INPUT_CHECK_LINE_LENGTH);
    readParameter<bool>(mol_rparams, settings, Chem::ControlParameter::MULTI_CONF_IMPORT, ControlParameterDefault::MOL_INPUT_MULTI_CONF_IMPORT);

    settings.endGroup();

    // +++

    settings.beginGroup(QString::fromStdString("Output/" + Chem::DataFormat::MOL.getName()));

    SettingsContainer& mol_wparams = writerControlParams[Chem::DataFormat::MOL.getName()];

    mol_wparams.setParent(this);

    readParameter<bool>(mol_wparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING, ControlParameterDefault::MOL_OUTPUT_STRICT_ERROR_CHECKING);
    readParameter<unsigned int>(mol_wparams, settings, Chem::ControlParameter::MDL_CTAB_VERSION, ControlParameterDefault::MOL_OUTPUT_CTAB_VERSION);
    readParameter<bool>(mol_wparams, settings, Chem::ControlParameter::MDL_UPDATE_TIMESTAMP, ControlParameterDefault::MOL_OUTPUT_UPDATE_TIMESTAMP);
    readParameter<bool>(mol_wparams, settings, Chem::ControlParameter::MDL_TRIM_STRINGS, ControlParameterDefault::MOL_OUTPUT_TRIM_STRINGS);
    readParameter<bool>(mol_wparams, settings, Chem::ControlParameter::MDL_TRIM_LINES, ControlParameterDefault::MOL_OUTPUT_TRIM_LINES);
    readParameter<bool>(mol_wparams, settings, Chem::ControlParameter::MDL_TRUNCATE_STRINGS, ControlParameterDefault::MOL_OUTPUT_TRUNCATE_STRINGS);
    readParameter<bool>(mol_wparams, settings, Chem::ControlParameter::MDL_TRUNCATE_LINES, ControlParameterDefault::MOL_OUTPUT_TRUNCATE_LINES);
    readParameter<bool>(mol_wparams, settings, Chem::ControlParameter::CHECK_LINE_LENGTH, ControlParameterDefault::MOL_OUTPUT_CHECK_LINE_LENGTH);
    readParameter<bool>(mol_wparams, settings, Chem::ControlParameter::MDL_IGNORE_PARITY, ControlParameterDefault::MOL_OUTPUT_IGNORE_PARITY);
    readParameter<bool>(mol_wparams, settings, ControlParameter::WRITE_SINGLE_RECORD_FILES, ControlParameterDefault::MOL_OUTPUT_WRITE_SINGLE_RECORD_FILES);
    readParameter<bool>(mol_wparams, settings, Chem::ControlParameter::MULTI_CONF_EXPORT, ControlParameterDefault::MOL_OUTPUT_MULTI_CONF_EXPORT);

    settings.endGroup();

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + Chem::DataFormat::SDF.getName()));

    SettingsContainer& sdf_rparams = readerControlParams[Chem::DataFormat::SDF.getName()];

    sdf_rparams.setParent(this);

    readParameter<bool>(sdf_rparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING, ControlParameterDefault::SDF_INPUT_STRICT_ERROR_CHECKING);
    readParameter<bool>(sdf_rparams, settings, Chem::ControlParameter::MDL_IGNORE_PARITY, ControlParameterDefault::SDF_INPUT_IGNORE_PARITY);
    readParameter<bool>(sdf_rparams, settings, Chem::ControlParameter::MDL_TRIM_STRINGS, ControlParameterDefault::SDF_INPUT_TRIM_STRINGS);
    readParameter<bool>(sdf_rparams, settings, Chem::ControlParameter::MDL_TRIM_LINES, ControlParameterDefault::SDF_INPUT_TRIM_LINES);
    readParameter<bool>(sdf_rparams, settings, Chem::ControlParameter::CHECK_LINE_LENGTH, ControlParameterDefault::SDF_INPUT_CHECK_LINE_LENGTH);
    readParameter<bool>(sdf_rparams, settings, Chem::ControlParameter::MULTI_CONF_IMPORT, ControlParameterDefault::SDF_INPUT_MULTI_CONF_IMPORT);

    settings.endGroup();

    // +++

    settings.beginGroup(QString::fromStdString("Output/" + Chem::DataFormat::SDF.getName()));

    SettingsContainer& sdf_wparams = writerControlParams[Chem::DataFormat::SDF.getName()];

    sdf_wparams.setParent(this);

    readParameter<bool>(sdf_wparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING, ControlParameterDefault::SDF_OUTPUT_STRICT_ERROR_CHECKING);
    readParameter<unsigned int>(sdf_wparams, settings, Chem::ControlParameter::MDL_CTAB_VERSION, ControlParameterDefault::SDF_OUTPUT_CTAB_VERSION);
    readParameter<bool>(sdf_wparams, settings, Chem::ControlParameter::MDL_UPDATE_TIMESTAMP, ControlParameterDefault::SDF_OUTPUT_UPDATE_TIMESTAMP);
    readParameter<bool>(sdf_wparams, settings, Chem::ControlParameter::MDL_TRIM_STRINGS, ControlParameterDefault::SDF_OUTPUT_TRIM_STRINGS);
    readParameter<bool>(sdf_wparams, settings, Chem::ControlParameter::MDL_TRIM_LINES, ControlParameterDefault::SDF_OUTPUT_TRIM_LINES);
    readParameter<bool>(sdf_wparams, settings, Chem::ControlParameter::MDL_TRUNCATE_STRINGS, ControlParameterDefault::SDF_OUTPUT_TRUNCATE_STRINGS);
    readParameter<bool>(sdf_wparams, settings, Chem::ControlParameter::MDL_TRUNCATE_LINES, ControlParameterDefault::SDF_OUTPUT_TRUNCATE_LINES);
    readParameter<bool>(sdf_wparams, settings, Chem::ControlParameter::CHECK_LINE_LENGTH, ControlParameterDefault::SDF_OUTPUT_CHECK_LINE_LENGTH);
    readParameter<bool>(sdf_wparams, settings, Chem::ControlParameter::MDL_IGNORE_PARITY, ControlParameterDefault::SDF_OUTPUT_IGNORE_PARITY);
    readParameter<bool>(sdf_wparams, settings, ControlParameter::WRITE_SINGLE_RECORD_FILES, ControlParameterDefault::SDF_OUTPUT_WRITE_SINGLE_RECORD_FILES);
    readParameter<bool>(sdf_wparams, settings, Chem::ControlParameter::MULTI_CONF_EXPORT, ControlParameterDefault::SDF_OUTPUT_MULTI_CONF_EXPORT);

    settings.endGroup();

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + Chem::DataFormat::RXN.getName()));

    SettingsContainer& rxn_rparams = readerControlParams[Chem::DataFormat::RXN.getName()];

    rxn_rparams.setParent(this);

    readParameter<bool>(rxn_rparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING, ControlParameterDefault::RXN_INPUT_STRICT_ERROR_CHECKING);
    readParameter<bool>(rxn_rparams, settings, Chem::ControlParameter::MDL_IGNORE_PARITY, ControlParameterDefault::RXN_INPUT_IGNORE_PARITY);
    readParameter<bool>(rxn_rparams, settings, Chem::ControlParameter::MDL_TRIM_STRINGS, ControlParameterDefault::RXN_INPUT_TRIM_STRINGS);
    readParameter<bool>(rxn_rparams, settings, Chem::ControlParameter::MDL_TRIM_LINES, ControlParameterDefault::RXN_INPUT_TRIM_LINES);
    readParameter<bool>(rxn_rparams, settings, Chem::ControlParameter::CHECK_LINE_LENGTH, ControlParameterDefault::RXN_INPUT_CHECK_LINE_LENGTH);

    settings.endGroup();

    // +++

    settings.beginGroup(QString::fromStdString("Output/" + Chem::DataFormat::RXN.getName()));

    SettingsContainer& rxn_wparams = writerControlParams[Chem::DataFormat::RXN.getName()];

    rxn_wparams.setParent(this);

    readParameter<bool>(rxn_wparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING, ControlParameterDefault::RXN_OUTPUT_STRICT_ERROR_CHECKING);
    readParameter<unsigned int>(rxn_wparams, settings, Chem::ControlParameter::MDL_CTAB_VERSION, ControlParameterDefault::RXN_OUTPUT_CTAB_VERSION);
    readParameter<unsigned int>(rxn_wparams, settings, Chem::ControlParameter::MDL_RXN_FILE_VERSION, ControlParameterDefault::RXN_OUTPUT_RXN_FILE_VERSION);
    readParameter<bool>(rxn_wparams, settings, Chem::ControlParameter::MDL_UPDATE_TIMESTAMP, ControlParameterDefault::RXN_OUTPUT_UPDATE_TIMESTAMP);
    readParameter<bool>(rxn_wparams, settings, Chem::ControlParameter::MDL_TRIM_STRINGS, ControlParameterDefault::RXN_OUTPUT_TRIM_STRINGS);
    readParameter<bool>(rxn_wparams, settings, Chem::ControlParameter::MDL_TRIM_LINES, ControlParameterDefault::RXN_OUTPUT_TRIM_LINES);
    readParameter<bool>(rxn_wparams, settings, Chem::ControlParameter::MDL_TRUNCATE_STRINGS, ControlParameterDefault::RXN_OUTPUT_TRUNCATE_STRINGS);
    readParameter<bool>(rxn_wparams, settings, Chem::ControlParameter::MDL_TRUNCATE_LINES, ControlParameterDefault::RXN_OUTPUT_TRUNCATE_LINES);
    readParameter<bool>(rxn_wparams, settings, Chem::ControlParameter::CHECK_LINE_LENGTH, ControlParameterDefault::RXN_OUTPUT_CHECK_LINE_LENGTH);
    readParameter<bool>(rxn_wparams, settings, Chem::ControlParameter::MDL_IGNORE_PARITY, ControlParameterDefault::RXN_OUTPUT_IGNORE_PARITY);
    readParameter<bool>(rxn_wparams, settings, ControlParameter::WRITE_SINGLE_RECORD_FILES, ControlParameterDefault::RXN_OUTPUT_WRITE_SINGLE_RECORD_FILES);

    settings.endGroup();

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + Chem::DataFormat::RDF.getName()));

    SettingsContainer& rdf_rparams = readerControlParams[Chem::DataFormat::RDF.getName()];

    rdf_rparams.setParent(this);

    readParameter<bool>(rdf_rparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING, ControlParameterDefault::RDF_INPUT_STRICT_ERROR_CHECKING);
    readParameter<bool>(rdf_rparams, settings, Chem::ControlParameter::MDL_IGNORE_PARITY, ControlParameterDefault::RDF_INPUT_IGNORE_PARITY);
    readParameter<bool>(rdf_rparams, settings, Chem::ControlParameter::MDL_TRIM_STRINGS, ControlParameterDefault::RDF_INPUT_TRIM_STRINGS);
    readParameter<bool>(rdf_rparams, settings, Chem::ControlParameter::MDL_TRIM_LINES, ControlParameterDefault::RDF_INPUT_TRIM_LINES);
    readParameter<bool>(rdf_rparams, settings, Chem::ControlParameter::CHECK_LINE_LENGTH, ControlParameterDefault::RDF_INPUT_CHECK_LINE_LENGTH);

    settings.endGroup();

    // +++

    settings.beginGroup(QString::fromStdString("Output/" + Chem::DataFormat::RDF.getName()));

    SettingsContainer& rdf_wparams = writerControlParams[Chem::DataFormat::RDF.getName()];

    rdf_wparams.setParent(this);

    readParameter<bool>(rdf_wparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING, ControlParameterDefault::RDF_OUTPUT_STRICT_ERROR_CHECKING);
    readParameter<unsigned int>(rdf_wparams, settings, Chem::ControlParameter::MDL_CTAB_VERSION, ControlParameterDefault::RDF_OUTPUT_CTAB_VERSION);
    readParameter<unsigned int>(rdf_wparams, settings, Chem::ControlParameter::MDL_RXN_FILE_VERSION, ControlParameterDefault::RDF_OUTPUT_RXN_FILE_VERSION);
    readParameter<bool>(rdf_wparams, settings, Chem::ControlParameter::MDL_UPDATE_TIMESTAMP, ControlParameterDefault::RDF_OUTPUT_UPDATE_TIMESTAMP);
    readParameter<bool>(rdf_wparams, settings, Chem::ControlParameter::MDL_TRIM_STRINGS, ControlParameterDefault::RDF_OUTPUT_TRIM_STRINGS);
    readParameter<bool>(rdf_wparams, settings, Chem::ControlParameter::MDL_TRIM_LINES, ControlParameterDefault::RDF_OUTPUT_TRIM_LINES);
    readParameter<bool>(rdf_wparams, settings, Chem::ControlParameter::MDL_TRUNCATE_STRINGS, ControlParameterDefault::RDF_OUTPUT_TRUNCATE_STRINGS);
    readParameter<bool>(rdf_wparams, settings, Chem::ControlParameter::MDL_TRUNCATE_LINES, ControlParameterDefault::RDF_OUTPUT_TRUNCATE_LINES);
    readParameter<bool>(rdf_wparams, settings, Chem::ControlParameter::CHECK_LINE_LENGTH, ControlParameterDefault::RDF_OUTPUT_CHECK_LINE_LENGTH);
    readParameter<bool>(rdf_wparams, settings, Chem::ControlParameter::MDL_IGNORE_PARITY, ControlParameterDefault::RDF_OUTPUT_IGNORE_PARITY);
    readParameter<bool>(rdf_wparams, settings, ControlParameter::WRITE_SINGLE_RECORD_FILES, ControlParameterDefault::RDF_OUTPUT_WRITE_SINGLE_RECORD_FILES);

    settings.endGroup();

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + Pharm::DataFormat::PSD.getName()));

    SettingsContainer& psd_rparams = readerControlParams[Pharm::DataFormat::PSD.getName()];

    psd_rparams.setParent(this);

    settings.endGroup();

    // +++

    settings.beginGroup(QString::fromStdString("Output/" + Pharm::DataFormat::PSD.getName()));

    SettingsContainer& psd_wparams = writerControlParams[Pharm::DataFormat::PSD.getName()];

    psd_wparams.setParent(this);

    readParameter<bool>(psd_wparams, settings, ControlParameter::WRITE_SINGLE_RECORD_FILES, ControlParameterDefault::PSD_OUTPUT_WRITE_SINGLE_RECORD_FILES);
    readParameter<bool>(psd_wparams, settings, Chem::ControlParameter::CDF_WRITE_SINGLE_PRECISION_FLOATS, ControlParameterDefault::PSD_OUTPUT_WRITE_SINGLE_PRECISION_FLOATS);
    readParameter<bool>(psd_wparams, settings, Pharm::ControlParameter::CDF_WRITE_SINGLE_PRECISION_FLOATS, ControlParameterDefault::PSD_OUTPUT_WRITE_SINGLE_PRECISION_FLOATS);
    readParameter<bool>(psd_wparams, settings, Pharm::ControlParameter::PSD_ALLOW_DUPLICATES, ControlParameterDefault::PSD_OUTPUT_ALLOW_DUPLICATES);
    readDBCreationModeParameter(psd_wparams, settings, Pharm::ControlParameter::PSD_CREATION_MODE, ControlParameterDefault::PSD_CREATION_MODE);

    settings.endGroup();

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + Biomol::DataFormat::PDB.getName()));

    SettingsContainer& pdb_rparams = readerControlParams[Biomol::DataFormat::PDB.getName()];

    pdb_rparams.setParent(this);

    readParameter<bool>(pdb_rparams, settings, Biomol::ControlParameter::STRICT_ERROR_CHECKING, ControlParameterDefault::PDB_INPUT_STRICT_ERROR_CHECKING);
    readParameter<bool>(pdb_rparams, settings, Biomol::ControlParameter::CHECK_LINE_LENGTH, ControlParameterDefault::PDB_INPUT_CHECK_LINE_LENGTH);

    settings.endGroup();
    
    // ------

    settings.beginGroup(QString::fromStdString("Input/" + Biomol::DataFormat::MMTF.getName()));

    SettingsContainer& mmtf_rparams = readerControlParams[Biomol::DataFormat::MMTF.getName()];

    mmtf_rparams.setParent(this);

    readParameter<bool>(mmtf_rparams, settings, Biomol::ControlParameter::STRICT_ERROR_CHECKING, ControlParameterDefault::MMTF_INPUT_STRICT_ERROR_CHECKING);

    settings.endGroup();

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + Chem::DataFormat::CDF.getName()));

    SettingsContainer& cdf_rparams = readerControlParams[Chem::DataFormat::CDF.getName()];

    cdf_rparams.setParent(this);

    settings.endGroup();

    // +++

    settings.beginGroup(QString::fromStdString("Output/" + Chem::DataFormat::CDF.getName()));

    SettingsContainer& cdf_wparams = writerControlParams[Chem::DataFormat::CDF.getName()];

    cdf_wparams.setParent(this);

    readParameter<bool>(cdf_wparams, settings, ControlParameter::WRITE_SINGLE_RECORD_FILES, ControlParameterDefault::CDF_OUTPUT_WRITE_SINGLE_RECORD_FILES);
    readParameter<bool>(psd_wparams, settings, Chem::ControlParameter::CDF_WRITE_SINGLE_PRECISION_FLOATS, ControlParameterDefault::CDF_OUTPUT_WRITE_SINGLE_PRECISION_FLOATS);

    settings.endGroup();

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + ConfGen::DataFormat::CFL.getName()));

    SettingsContainer& cfl_rparams = readerControlParams[ConfGen::DataFormat::CFL.getName()];

    cfl_rparams.setParent(this);

    readParameter<bool>(cfl_rparams, settings, ConfGen::ControlParameter::STRICT_ERROR_CHECKING, ControlParameterDefault::CFL_INPUT_STRICT_ERROR_CHECKING);
    
    settings.endGroup();

    // +++

    // ------

    settings.beginGroup("Output/IMG");

    SettingsContainer& img_params = writerControlParams["img"];

    img_params.setParent(this);

    readParameter<double>(img_params, settings, Vis::ControlParameter::OUTPUT_SCALING_FACTOR, Vis::ControlParameterDefault::OUTPUT_SCALING_FACTOR);
    readBrushParameter(img_params, settings, Vis::ControlParameter::BACKGROUND_BRUSH, Vis::ControlParameterDefault::BACKGROUND_BRUSH);

    settings.endGroup();

    // ------

    if (getUseAtomColorTableParameter(*this))
        Vis::setAtomColorTableParameter(*this, ChOX::getAtomColorTableParameter(*this));
    else
        Vis::clearAtomColorTableParameter(*this);

    // ------
}

void Settings::save() const
{
    QSettings settings;

    using namespace CDPL;

    settings.beginGroup("View");

    writeColorParameter(*this, settings, ControlParameter::VIEW_BACKGROUND_COLOR);
    writeColorParameter(*this, settings, ControlParameter::VIEW_SELECTION_COLOR);
    writeParameter<bool>(*this, settings, ControlParameter::SHOW_GRID);
    writeParameter<bool>(*this, settings, ControlParameter::SHOW_RECORD_NUMBERS);
    writeParameter<bool>(*this, settings, ControlParameter::SHOW_RECORD_NAMES);
    writeParameter<std::size_t>(*this, settings, ControlParameter::GRID_ROW_COUNT);
    writeParameter<std::size_t>(*this, settings, ControlParameter::GRID_COLUMN_COUNT);
    writeLineStyleParameter(*this, settings, ControlParameter::GRID_LINE_STYLE);
    writeColorParameter(*this, settings, ControlParameter::GRID_LINE_COLOR);
    writeSizeSpecParameter(*this, settings, ControlParameter::GRID_LINE_WIDTH);

    writeFontParameter(*this, settings, ControlParameter::RECORD_NUMBER_LABEL_FONT);
    writeSizeSpecParameter(*this, settings, ControlParameter::RECORD_NUMBER_LABEL_SIZE);
    writeParameter<unsigned int>(*this, settings, ControlParameter::RECORD_NUMBER_LABEL_ALIGNMENT);
    writeColorParameter(*this, settings, ControlParameter::RECORD_NUMBER_LABEL_COLOR);

    writeFontParameter(*this, settings, ControlParameter::RECORD_NAME_LABEL_FONT);
    writeSizeSpecParameter(*this, settings, ControlParameter::RECORD_NAME_LABEL_SIZE);
    writeParameter<unsigned int>(*this, settings, ControlParameter::RECORD_NAME_LABEL_ALIGNMENT);
    writeColorParameter(*this, settings, ControlParameter::RECORD_NAME_LABEL_COLOR);

    writeParameter<unsigned int>(*this, settings, Vis::ControlParameter::SIZE_ADJUSTMENT);
    writeParameter<unsigned int>(*this, settings, Vis::ControlParameter::ALIGNMENT);

    settings.endGroup();

    settings.beginGroup("Reactions");

    writeParameter<unsigned int>(*this, settings, Vis::ControlParameter::REACTION_ARROW_STYLE);
    writeColorParameter(*this, settings, Vis::ControlParameter::REACTION_ARROW_COLOR);
    writeSizeSpecParameter(*this, settings, Vis::ControlParameter::REACTION_ARROW_LENGTH);
    writeSizeSpecParameter(*this, settings, Vis::ControlParameter::REACTION_ARROW_HEAD_LENGTH);
    writeSizeSpecParameter(*this, settings, Vis::ControlParameter::REACTION_ARROW_HEAD_WIDTH);
    writeSizeSpecParameter(*this, settings, Vis::ControlParameter::REACTION_ARROW_SHAFT_WIDTH);
    writeSizeSpecParameter(*this, settings, Vis::ControlParameter::REACTION_ARROW_LINE_WIDTH);
    writeParameter<unsigned int>(*this, settings, Vis::ControlParameter::REACTION_COMPONENT_LAYOUT);
    writeParameter<unsigned int>(*this, settings, Vis::ControlParameter::REACTION_COMPONENT_LAYOUT_DIRECTION);
    writeSizeSpecParameter(*this, settings, Vis::ControlParameter::REACTION_COMPONENT_MARGIN);
    writeParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_REACTION_REACTANTS);
    writeParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_REACTION_AGENTS);
    writeParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_REACTION_PRODUCTS);
    writeParameter<unsigned int>(*this, settings, Vis::ControlParameter::REACTION_AGENT_ALIGNMENT);
    writeParameter<unsigned int>(*this, settings, Vis::ControlParameter::REACTION_AGENT_LAYOUT);
    writeParameter<unsigned int>(*this, settings, Vis::ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION);
    writeColorParameter(*this, settings, Vis::ControlParameter::REACTION_PLUS_SIGN_COLOR);
    writeSizeSpecParameter(*this, settings, Vis::ControlParameter::REACTION_PLUS_SIGN_SIZE);
    writeSizeSpecParameter(*this, settings, Vis::ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH);
    writeParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_REACTION_PLUS_SIGNS);

    settings.endGroup();

    settings.beginGroup("Atoms");

    writeColorParameter(*this, settings, Vis::ControlParameter::ATOM_COLOR);
    writeAtomColorTableParam(settings);

    writeParameter<bool>(*this, settings, ControlParameter::USE_ATOM_COLOR_TABLE);
    writeParameter<bool>(*this, settings, Vis::ControlParameter::USE_CALCULATED_ATOM_COORDINATES);
    writeFontParameter(*this, settings, Vis::ControlParameter::ATOM_LABEL_FONT);
    writeSizeSpecParameter(*this, settings, Vis::ControlParameter::ATOM_LABEL_SIZE);
    writeFontParameter(*this, settings, Vis::ControlParameter::SECONDARY_ATOM_LABEL_FONT);
    writeSizeSpecParameter(*this, settings, Vis::ControlParameter::SECONDARY_ATOM_LABEL_SIZE);
    writeSizeSpecParameter(*this, settings, Vis::ControlParameter::ATOM_LABEL_MARGIN);
    writeSizeSpecParameter(*this, settings, Vis::ControlParameter::RADICAL_ELECTRON_DOT_SIZE);
    writeParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_CARBONS);
    writeParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_CHARGES);
    writeParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_ISOTOPES);
    writeParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_EXPLICIT_HYDROGENS);
    writeParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_HYDROGEN_COUNTS);
    writeParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_NON_CARBON_HYDROGEN_COUNTS);
    writeParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_ATOM_QUERY_INFOS);
    writeParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_ATOM_REACTION_INFOS);
    writeParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_RADICAL_ELECTRONS);
    writeParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_ATOM_CONFIGURATION_LABELS);
    writeSizeSpecParameter(*this, settings, Vis::ControlParameter::ATOM_CONFIGURATION_LABEL_SIZE);
    writeFontParameter(*this, settings, Vis::ControlParameter::ATOM_CONFIGURATION_LABEL_FONT);
    writeColorParameter(*this, settings, Vis::ControlParameter::ATOM_CONFIGURATION_LABEL_COLOR);
    
    settings.endGroup();

    settings.beginGroup("Bonds");
        
    writeColorParameter(*this, settings, Vis::ControlParameter::BOND_COLOR);
    writeSizeSpecParameter(*this, settings, Vis::ControlParameter::BOND_LENGTH);
    writeSizeSpecParameter(*this, settings, Vis::ControlParameter::BOND_LINE_WIDTH);
    writeSizeSpecParameter(*this, settings, Vis::ControlParameter::BOND_LINE_SPACING);
    writeSizeSpecParameter(*this, settings, Vis::ControlParameter::STEREO_BOND_WEDGE_WIDTH);
    writeSizeSpecParameter(*this, settings, Vis::ControlParameter::STEREO_BOND_HASH_SPACING);
    writeSizeSpecParameter(*this, settings, Vis::ControlParameter::REACTION_CENTER_LINE_LENGTH);
    writeSizeSpecParameter(*this, settings, Vis::ControlParameter::REACTION_CENTER_LINE_SPACING);
    writeSizeSpecParameter(*this, settings, Vis::ControlParameter::DOUBLE_BOND_TRIM_LENGTH);
    writeSizeSpecParameter(*this, settings, Vis::ControlParameter::TRIPLE_BOND_TRIM_LENGTH);
    writeFontParameter(*this, settings, Vis::ControlParameter::BOND_LABEL_FONT);
    writeSizeSpecParameter(*this, settings, Vis::ControlParameter::BOND_LABEL_SIZE);
    writeSizeSpecParameter(*this, settings, Vis::ControlParameter::BOND_LABEL_MARGIN);
    writeParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_BOND_REACTION_INFOS);
    writeParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_BOND_QUERY_INFOS);
    writeParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_STEREO_BONDS);
    writeParameter<bool>(*this, settings, Vis::ControlParameter::SHOW_BOND_CONFIGURATION_LABELS);
    writeSizeSpecParameter(*this, settings, Vis::ControlParameter::BOND_CONFIGURATION_LABEL_SIZE);
    writeFontParameter(*this, settings, Vis::ControlParameter::BOND_CONFIGURATION_LABEL_FONT);
    writeColorParameter(*this, settings, Vis::ControlParameter::BOND_CONFIGURATION_LABEL_COLOR);
 
    settings.endGroup();

    settings.beginGroup("Printing");

    writeParameter<bool>(*this, settings, ControlParameter::PRINT_FRAME);
    writeParameter<bool>(*this, settings, ControlParameter::PRINT_DATE);
    writeParameter<bool>(*this, settings, ControlParameter::PRINT_PAGE_NUMBER);
    writeParameter<bool>(*this, settings, ControlParameter::PRINT_FILE_NAME);
    writeLineStyleParameter(*this, settings, ControlParameter::FRAME_LINE_STYLE);
    writeColorParameter(*this, settings, ControlParameter::FRAME_LINE_COLOR);
    writeSizeSpecParameter(*this, settings, ControlParameter::FRAME_LINE_WIDTH);
    writeFontParameter(*this, settings, ControlParameter::PRINTING_TEXT_LABEL_FONT);
    writeSizeSpecParameter(*this, settings, ControlParameter::PRINTING_TEXT_LABEL_SIZE);
    writeSizeSpecParameter(*this, settings, ControlParameter::PRINTING_TEXT_LABEL_SPACING);
    writeColorParameter(*this, settings, ControlParameter::PRINTING_TEXT_LABEL_COLOR);
    writeParameter<unsigned int>(*this, settings, ControlParameter::PAGE_NUMBER_LABEL_ALIGNMENT);
    writeParameter<unsigned int>(*this, settings, ControlParameter::DATE_LABEL_ALIGNMENT);
    writeParameter<unsigned int>(*this, settings, ControlParameter::FILE_NAME_LABEL_ALIGNMENT);

    settings.endGroup();

    settings.beginGroup("FileIO");

    writeStrParameter(*this, settings, ControlParameter::DEFAULT_MOL_OUTPUT_FORMAT);
    writeStrParameter(*this, settings, ControlParameter::DEFAULT_RXN_OUTPUT_FORMAT);

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + Chem::DataFormat::JME.getName()));

    const SettingsContainer& jme_rparams = getReaderControlParameters(Chem::DataFormat::JME.getName());

    writeParameter<bool>(jme_rparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING);

    settings.endGroup();

    // +++

    settings.beginGroup(QString::fromStdString("Output/" + Chem::DataFormat::JME.getName()));

    const SettingsContainer& jme_wparams = getWriterControlParameters(Chem::DataFormat::JME.getName());

    writeParameter<bool>(jme_wparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING);
    writeParameter<bool>(jme_wparams, settings, Chem::ControlParameter::JME_SEPARATE_COMPONENTS);
    writeParameter<bool>(jme_wparams, settings, ControlParameter::WRITE_SINGLE_RECORD_FILES);
    writeStrParameter(jme_wparams, settings, Chem::ControlParameter::RECORD_SEPARATOR);

    settings.endGroup();

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + Chem::DataFormat::SMILES.getName()));

    const SettingsContainer& smiles_rparams = getReaderControlParameters(Chem::DataFormat::SMILES.getName());

    writeParameter<bool>(smiles_rparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING);
    writeStrParameter(smiles_rparams, settings, Chem::ControlParameter::SMILES_RECORD_FORMAT);

    settings.endGroup();

    // +++

    settings.beginGroup(QString::fromStdString("Output/" + Chem::DataFormat::SMILES.getName()));

    const SettingsContainer& smiles_wparams = getWriterControlParameters(Chem::DataFormat::SMILES.getName());

    writeParameter<bool>(smiles_wparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING);
    writeParameter<bool>(smiles_wparams, settings, Chem::ControlParameter::ORDINARY_HYDROGEN_DEPLETE);
    writeParameter<bool>(smiles_wparams, settings, Chem::ControlParameter::SMILES_WRITE_CANONICAL_FORM);
    writeParameter<bool>(smiles_wparams, settings, Chem::ControlParameter::SMILES_WRITE_KEKULE_FORM);
    writeParameter<bool>(smiles_wparams, settings, Chem::ControlParameter::SMILES_WRITE_ATOM_STEREO);
    writeParameter<bool>(smiles_wparams, settings, Chem::ControlParameter::SMILES_WRITE_BOND_STEREO);
    writeParameter<bool>(smiles_wparams, settings, Chem::ControlParameter::SMILES_WRITE_RING_BOND_STEREO);
    writeParameter<bool>(smiles_wparams, settings, Chem::ControlParameter::SMILES_MOL_WRITE_ATOM_MAPPING_ID);
    writeParameter<bool>(smiles_wparams, settings, Chem::ControlParameter::SMILES_RXN_WRITE_ATOM_MAPPING_ID);
    writeParameter<bool>(smiles_wparams, settings, Chem::ControlParameter::SMILES_WRITE_SINGLE_BONDS);
    writeParameter<bool>(smiles_wparams, settings, Chem::ControlParameter::SMILES_WRITE_AROMATIC_BONDS);
    writeParameter<bool>(smiles_wparams, settings, Chem::ControlParameter::SMILES_WRITE_ISOTOPE);
    writeParameter<bool>(smiles_wparams, settings, Chem::ControlParameter::SMILES_NO_ORGANIC_SUBSET);
    writeParameter<std::size_t>(smiles_wparams, settings, Chem::ControlParameter::SMILES_MIN_STEREO_BOND_RING_SIZE);
    writeParameter<bool>(smiles_wparams, settings, ControlParameter::WRITE_SINGLE_RECORD_FILES);
    writeStrParameter(smiles_wparams, settings, Chem::ControlParameter::SMILES_RECORD_FORMAT);

    settings.endGroup();

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + Chem::DataFormat::SMARTS.getName()));

    const SettingsContainer& smarts_rparams = getReaderControlParameters(Chem::DataFormat::SMARTS.getName());

    writeParameter<bool>(smarts_rparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING);

    settings.endGroup();

    // +++

    settings.beginGroup(QString::fromStdString("Output/" + Chem::DataFormat::SMARTS.getName()));

    const SettingsContainer& smarts_wparams = getWriterControlParameters(Chem::DataFormat::SMARTS.getName());

    writeParameter<bool>(smarts_wparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING);
    writeParameter<bool>(smarts_wparams, settings, ControlParameter::WRITE_SINGLE_RECORD_FILES);
    writeStrParameter(smarts_wparams, settings, Chem::ControlParameter::RECORD_SEPARATOR);

    settings.endGroup();

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + Chem::DataFormat::INCHI.getName()));

    const SettingsContainer& inchi_rparams = getReaderControlParameters(Chem::DataFormat::INCHI.getName());

    writeParameter<bool>(inchi_rparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING);
    writeStrParameter(inchi_rparams, settings, Chem::ControlParameter::INCHI_INPUT_OPTIONS);

    settings.endGroup();

    // +++

    settings.beginGroup(QString::fromStdString("Output/" + Chem::DataFormat::INCHI.getName()));

    const SettingsContainer& inchi_wparams = getWriterControlParameters(Chem::DataFormat::INCHI.getName());

    writeParameter<bool>(inchi_wparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING);
    writeStrParameter(inchi_wparams, settings, Chem::ControlParameter::RECORD_SEPARATOR);
    writeParameter<bool>(inchi_wparams, settings, ControlParameter::WRITE_SINGLE_RECORD_FILES);
    writeStrParameter(inchi_wparams, settings, Chem::ControlParameter::INCHI_OUTPUT_OPTIONS);

    settings.endGroup();

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + Chem::DataFormat::MOL2.getName()));

    const SettingsContainer& mol2_rparams = getReaderControlParameters(Chem::DataFormat::MOL2.getName());

    writeParameter<bool>(mol2_rparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING);
    writeParameter<bool>(mol2_rparams, settings, Chem::ControlParameter::MULTI_CONF_IMPORT);

    settings.endGroup();

    // +++

    settings.beginGroup(QString::fromStdString("Output/" + Chem::DataFormat::MOL2.getName()));

    const SettingsContainer& mol2_wparams = getWriterControlParameters(Chem::DataFormat::MOL2.getName());

    writeParameter<bool>(mol2_wparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING);
    writeParameter<bool>(mol2_wparams, settings, ControlParameter::WRITE_SINGLE_RECORD_FILES);
    writeParameter<bool>(mol2_wparams, settings, Chem::ControlParameter::MULTI_CONF_EXPORT);

    settings.endGroup();

    // ------
    
    settings.beginGroup(QString::fromStdString("Input/" + Chem::DataFormat::XYZ.getName()));

    const SettingsContainer& xyz_rparams = getReaderControlParameters(Chem::DataFormat::XYZ.getName());

    writeParameter<bool>(xyz_rparams, settings, Chem::ControlParameter::MULTI_CONF_IMPORT);

    settings.endGroup();

    // +++

    settings.beginGroup(QString::fromStdString("Output/" + Chem::DataFormat::XYZ.getName()));

    const SettingsContainer& xyz_wparams = getWriterControlParameters(Chem::DataFormat::XYZ.getName());

    writeParameter<bool>(xyz_wparams, settings, ControlParameter::WRITE_SINGLE_RECORD_FILES);
    writeParameter<bool>(xyz_wparams, settings, Chem::ControlParameter::MULTI_CONF_EXPORT);

    settings.endGroup();

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + Chem::DataFormat::MOL.getName()));

    const SettingsContainer& mol_rparams = getReaderControlParameters(Chem::DataFormat::MOL.getName());

    writeParameter<bool>(mol_rparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING);
    writeParameter<bool>(mol_rparams, settings, Chem::ControlParameter::MDL_IGNORE_PARITY);
    writeParameter<bool>(mol_rparams, settings, Chem::ControlParameter::MDL_TRIM_STRINGS);
    writeParameter<bool>(mol_rparams, settings, Chem::ControlParameter::MDL_TRIM_LINES);
    writeParameter<bool>(mol_rparams, settings, Chem::ControlParameter::CHECK_LINE_LENGTH);
    writeParameter<bool>(mol_rparams, settings, Chem::ControlParameter::MULTI_CONF_IMPORT);

    settings.endGroup();

    // +++

    settings.beginGroup(QString::fromStdString("Output/" + Chem::DataFormat::MOL.getName()));

    const SettingsContainer& mol_wparams = getWriterControlParameters(Chem::DataFormat::MOL.getName());

    writeParameter<bool>(mol_wparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING);
    writeParameter<unsigned int>(mol_wparams, settings, Chem::ControlParameter::MDL_CTAB_VERSION);
    writeParameter<bool>(mol_wparams, settings, Chem::ControlParameter::MDL_UPDATE_TIMESTAMP);
    writeParameter<bool>(mol_wparams, settings, Chem::ControlParameter::MDL_TRIM_STRINGS);
    writeParameter<bool>(mol_wparams, settings, Chem::ControlParameter::MDL_TRIM_LINES);
    writeParameter<bool>(mol_wparams, settings, Chem::ControlParameter::MDL_TRUNCATE_STRINGS);
    writeParameter<bool>(mol_wparams, settings, Chem::ControlParameter::MDL_TRUNCATE_LINES);
    writeParameter<bool>(mol_wparams, settings, Chem::ControlParameter::CHECK_LINE_LENGTH);
    writeParameter<bool>(mol_wparams, settings, Chem::ControlParameter::MDL_IGNORE_PARITY);
    writeParameter<bool>(mol_wparams, settings, ControlParameter::WRITE_SINGLE_RECORD_FILES);
    writeParameter<bool>(mol_wparams, settings, Chem::ControlParameter::MULTI_CONF_EXPORT);

    settings.endGroup();

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + Chem::DataFormat::SDF.getName()));

    const SettingsContainer& sdf_rparams = getReaderControlParameters(Chem::DataFormat::SDF.getName());

    writeParameter<bool>(sdf_rparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING);
    writeParameter<bool>(sdf_rparams, settings, Chem::ControlParameter::MDL_IGNORE_PARITY);
    writeParameter<bool>(sdf_rparams, settings, Chem::ControlParameter::MDL_TRIM_STRINGS);
    writeParameter<bool>(sdf_rparams, settings, Chem::ControlParameter::MDL_TRIM_LINES);
    writeParameter<bool>(sdf_rparams, settings, Chem::ControlParameter::CHECK_LINE_LENGTH);
    writeParameter<bool>(sdf_rparams, settings, Chem::ControlParameter::MULTI_CONF_IMPORT);

    settings.endGroup();

    // +++

    settings.beginGroup(QString::fromStdString("Output/" + Chem::DataFormat::SDF.getName()));

    const SettingsContainer& sdf_wparams = getWriterControlParameters(Chem::DataFormat::SDF.getName());

    writeParameter<bool>(sdf_wparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING);
    writeParameter<unsigned int>(sdf_wparams, settings, Chem::ControlParameter::MDL_CTAB_VERSION);
    writeParameter<bool>(sdf_wparams, settings, Chem::ControlParameter::MDL_UPDATE_TIMESTAMP);
    writeParameter<bool>(sdf_wparams, settings, Chem::ControlParameter::MDL_TRIM_STRINGS);
    writeParameter<bool>(sdf_wparams, settings, Chem::ControlParameter::MDL_TRIM_LINES);
    writeParameter<bool>(sdf_wparams, settings, Chem::ControlParameter::MDL_TRUNCATE_STRINGS);
    writeParameter<bool>(sdf_wparams, settings, Chem::ControlParameter::MDL_TRUNCATE_LINES);
    writeParameter<bool>(sdf_wparams, settings, Chem::ControlParameter::CHECK_LINE_LENGTH);
    writeParameter<bool>(sdf_wparams, settings, Chem::ControlParameter::MDL_IGNORE_PARITY);
    writeParameter<bool>(sdf_wparams, settings, ControlParameter::WRITE_SINGLE_RECORD_FILES);
    writeParameter<bool>(sdf_wparams, settings, Chem::ControlParameter::MULTI_CONF_EXPORT);

    settings.endGroup();

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + Chem::DataFormat::RXN.getName()));

    const SettingsContainer& rxn_rparams = getReaderControlParameters(Chem::DataFormat::RXN.getName());

    writeParameter<bool>(rxn_rparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING);
    writeParameter<bool>(rxn_rparams, settings, Chem::ControlParameter::MDL_IGNORE_PARITY);
    writeParameter<bool>(rxn_rparams, settings, Chem::ControlParameter::MDL_TRIM_STRINGS);
    writeParameter<bool>(rxn_rparams, settings, Chem::ControlParameter::MDL_TRIM_LINES);
    writeParameter<bool>(rxn_rparams, settings, Chem::ControlParameter::CHECK_LINE_LENGTH);

    settings.endGroup();

    // +++

    settings.beginGroup(QString::fromStdString("Output/" + Chem::DataFormat::RXN.getName()));

    const SettingsContainer& rxn_wparams = getWriterControlParameters(Chem::DataFormat::RXN.getName());

    writeParameter<bool>(rxn_wparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING);
    writeParameter<unsigned int>(rxn_wparams, settings, Chem::ControlParameter::MDL_CTAB_VERSION);
    writeParameter<unsigned int>(rxn_wparams, settings, Chem::ControlParameter::MDL_RXN_FILE_VERSION);
    writeParameter<bool>(rxn_wparams, settings, Chem::ControlParameter::MDL_UPDATE_TIMESTAMP);
    writeParameter<bool>(rxn_wparams, settings, Chem::ControlParameter::MDL_TRIM_STRINGS);
    writeParameter<bool>(rxn_wparams, settings, Chem::ControlParameter::MDL_TRIM_LINES);
    writeParameter<bool>(rxn_wparams, settings, Chem::ControlParameter::MDL_TRUNCATE_STRINGS);
    writeParameter<bool>(rxn_wparams, settings, Chem::ControlParameter::MDL_TRUNCATE_LINES);
    writeParameter<bool>(rxn_wparams, settings, Chem::ControlParameter::CHECK_LINE_LENGTH);
    writeParameter<bool>(rxn_wparams, settings, Chem::ControlParameter::MDL_IGNORE_PARITY);
    writeParameter<bool>(rxn_wparams, settings, ControlParameter::WRITE_SINGLE_RECORD_FILES);

    settings.endGroup();

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + Chem::DataFormat::RDF.getName()));

    const SettingsContainer& rdf_rparams = getReaderControlParameters(Chem::DataFormat::RDF.getName());

    writeParameter<bool>(rdf_rparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING);
    writeParameter<bool>(rdf_rparams, settings, Chem::ControlParameter::MDL_IGNORE_PARITY);
    writeParameter<bool>(rdf_rparams, settings, Chem::ControlParameter::MDL_TRIM_STRINGS);
    writeParameter<bool>(rdf_rparams, settings, Chem::ControlParameter::MDL_TRIM_LINES);
    writeParameter<bool>(rdf_rparams, settings, Chem::ControlParameter::CHECK_LINE_LENGTH);

    settings.endGroup();

    // +++

    settings.beginGroup(QString::fromStdString("Output/" + Chem::DataFormat::RDF.getName()));

    const SettingsContainer& rdf_wparams = getWriterControlParameters(Chem::DataFormat::RDF.getName());

    writeParameter<bool>(rdf_wparams, settings, Chem::ControlParameter::STRICT_ERROR_CHECKING);
    writeParameter<unsigned int>(rdf_wparams, settings, Chem::ControlParameter::MDL_CTAB_VERSION);
    writeParameter<unsigned int>(rdf_wparams, settings, Chem::ControlParameter::MDL_RXN_FILE_VERSION);
    writeParameter<bool>(rdf_wparams, settings, Chem::ControlParameter::MDL_UPDATE_TIMESTAMP);
    writeParameter<bool>(rdf_wparams, settings, Chem::ControlParameter::MDL_TRIM_STRINGS);
    writeParameter<bool>(rdf_wparams, settings, Chem::ControlParameter::MDL_TRIM_LINES);
    writeParameter<bool>(rdf_wparams, settings, Chem::ControlParameter::MDL_TRUNCATE_STRINGS);
    writeParameter<bool>(rdf_wparams, settings, Chem::ControlParameter::MDL_TRUNCATE_LINES);
    writeParameter<bool>(rdf_wparams, settings, Chem::ControlParameter::CHECK_LINE_LENGTH);
    writeParameter<bool>(rdf_wparams, settings, Chem::ControlParameter::MDL_IGNORE_PARITY);
    writeParameter<bool>(rdf_wparams, settings, ControlParameter::WRITE_SINGLE_RECORD_FILES);

    settings.endGroup();

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + Biomol::DataFormat::PDB.getName()));

    const SettingsContainer& pdb_rparams = getReaderControlParameters(Biomol::DataFormat::PDB.getName());

    writeParameter<bool>(pdb_rparams, settings, Biomol::ControlParameter::STRICT_ERROR_CHECKING);
    writeParameter<bool>(pdb_rparams, settings, Biomol::ControlParameter::CHECK_LINE_LENGTH);

    settings.endGroup();

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + Biomol::DataFormat::MMTF.getName()));

    const SettingsContainer& mmtf_rparams = getReaderControlParameters(Biomol::DataFormat::MMTF.getName());

    writeParameter<bool>(mmtf_rparams, settings, Biomol::ControlParameter::STRICT_ERROR_CHECKING);

    settings.endGroup();

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + Pharm::DataFormat::PSD.getName()));

    //const SettingsContainer& psd_rparams = getReaderControlParameters(Pharm::DataFormat::PSD.getName());

    settings.endGroup();

    // +++

    settings.beginGroup(QString::fromStdString("Output/" + Pharm::DataFormat::PSD.getName()));

    const SettingsContainer& psd_wparams = getWriterControlParameters(Pharm::DataFormat::PSD.getName());

    writeParameter<bool>(psd_wparams, settings, ControlParameter::WRITE_SINGLE_RECORD_FILES);
    writeParameter<bool>(psd_wparams, settings, Chem::ControlParameter::CDF_WRITE_SINGLE_PRECISION_FLOATS);
    writeParameter<bool>(psd_wparams, settings, Pharm::ControlParameter::PSD_ALLOW_DUPLICATES);
    writeDBCreationModeParameter(psd_wparams, settings, Pharm::ControlParameter::PSD_CREATION_MODE);

    settings.endGroup();

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + Chem::DataFormat::CDF.getName()));

    //const SettingsContainer& cdf_rparams = getReaderControlParameters(Chem::DataFormat::CDF.getName());

    settings.endGroup();

    // +++

    settings.beginGroup(QString::fromStdString("Output/" + Chem::DataFormat::CDF.getName()));

    const SettingsContainer& cdf_wparams = getWriterControlParameters(Chem::DataFormat::CDF.getName());

    writeParameter<bool>(cdf_wparams, settings, ControlParameter::WRITE_SINGLE_RECORD_FILES);
    writeParameter<bool>(cdf_wparams, settings, Chem::ControlParameter::CDF_WRITE_SINGLE_PRECISION_FLOATS);

    settings.endGroup();

    // ------

    settings.beginGroup(QString::fromStdString("Input/" + ConfGen::DataFormat::CFL.getName()));

    const SettingsContainer& cfl_rparams = getReaderControlParameters(ConfGen::DataFormat::CFL.getName());

    writeParameter<bool>(cfl_rparams, settings, ConfGen::ControlParameter::STRICT_ERROR_CHECKING);

    settings.endGroup();

    // +++

    // ------

    settings.beginGroup("Output/IMG");

    const SettingsContainer& img_params = getWriterControlParameters("img");

    writeParameter<double>(img_params, settings, Vis::ControlParameter::OUTPUT_SCALING_FACTOR);
    writeBrushParameter(img_params, settings, Vis::ControlParameter::BACKGROUND_BRUSH);

    settings.endGroup();
}

void Settings::parameterChanged(const CDPL::Base::LookupKey& key, const CDPL::Base::Any& val)
{
    emit controlParamChanged(key, val);
}

void Settings::writeFontParameter(const SettingsContainer& params, QSettings& settings, 
                                  const CDPL::Base::LookupKey& key) const
{
    using namespace CDPL;

    Base::Any val = params.getParameter(key);

    QString name = QString::fromStdString(key.getName());

    if (val.isEmpty()) {
        settings.remove(name + "/family");
        settings.remove(name + "/bold");
        settings.remove(name + "/italic");
        settings.remove(name + "/underlined");
        settings.remove(name + "/overlined");
        settings.remove(name + "/striked_out");
        settings.remove(name + "/fixed_pitch");

        return;
    }

    const Vis::Font& font = val.getData<Vis::Font>();

    settings.setValue(name + "/family", QString::fromStdString(font.getFamily()));
    settings.setValue(name + "/bold", font.isBold());
    settings.setValue(name + "/italic", font.isItalic());
    settings.setValue(name + "/underlined", font.isUnderlined());
    settings.setValue(name + "/overlined", font.isOverlined());
    settings.setValue(name + "/striked_out", font.isStrikedOut());
    settings.setValue(name + "/fixed_pitch", font.hasFixedPitch());
}

void Settings::writeColorParameter(const SettingsContainer& params, QSettings& settings, 
                                   const CDPL::Base::LookupKey& key) const
{
    using namespace CDPL;

    Base::Any val = params.getParameter(key);

    QString name = QString::fromStdString(key.getName());

    if (val.isEmpty()) {
        settings.remove(name + "/red");
        settings.remove(name + "/green");
        settings.remove(name + "/blue");
        settings.remove(name + "/alpha");

        return;
    }

    const Vis::Color& color = val.getData<Vis::Color>();

    settings.setValue(name + "/red", color.getRed());
    settings.setValue(name + "/green", color.getGreen());
    settings.setValue(name + "/blue", color.getBlue());
    settings.setValue(name + "/alpha", color.getAlpha());
}

void Settings::writeBrushParameter(const SettingsContainer& params, QSettings& settings, 
                                   const CDPL::Base::LookupKey& key) const
{
    using namespace CDPL;
    using namespace Vis;
    
    Base::Any val = params.getParameter(key);

    QString name = QString::fromStdString(key.getName());

    if (val.isEmpty()) {
        settings.remove(name + "/red");
        settings.remove(name + "/green");
        settings.remove(name + "/blue");
        settings.remove(name + "/alpha");
        settings.remove(name + "/style");
        return;
    }

    const Brush& brush = val.getData<Brush>();

    settings.setValue(name + "/red", brush.getColor().getRed());
    settings.setValue(name + "/green", brush.getColor().getGreen());
    settings.setValue(name + "/blue", brush.getColor().getBlue());
    settings.setValue(name + "/alpha", brush.getColor().getAlpha());

    int style = 0;
    
    switch (brush.getStyle()) {

        case Brush::NO_PATTERN:
            style = 1;
            break;

        case Brush::SOLID_PATTERN:
            style = 2;
            break;

        case Brush::DENSE1_PATTERN:
            style = 3;
            break;

        case Brush::DENSE2_PATTERN:
            style = 4;
            break;

        case Brush::DENSE3_PATTERN:
            style = 5;
            break;

        case Brush::DENSE4_PATTERN:
            style = 6;
            break;

        case Brush::DENSE5_PATTERN:
            style = 7;
            break;

        case Brush::DENSE6_PATTERN:
            style = 8;
            break;

        case Brush::DENSE7_PATTERN:
            style = 9;
            break;

        case Brush::H_PATTERN:
            style = 10;
            break;

        case Brush::V_PATTERN:
            style = 11;
            break;

        case Brush::CROSS_PATTERN:
            style = 12;
            break;

        case Brush::LEFT_DIAG_PATTERN:
            style = 13;
            break;

        case Brush::RIGHT_DIAG_PATTERN:
            style = 14;
            break;

        case Brush::DIAG_CROSS_PATTERN:
            style = 15;

        default:
            break;
    }

    settings.setValue(name + "/style", style);
}

void Settings::writeSizeSpecParameter(const SettingsContainer& params, QSettings& settings, 
                                      const CDPL::Base::LookupKey& key) const
{
    using namespace CDPL;

    Base::Any val = params.getParameter(key);

    QString name = QString::fromStdString(key.getName());

    if (val.isEmpty()) {
        settings.remove(name + "/value");
        settings.remove(name + "/relative");
        settings.remove(name + "/input_scaling");
        settings.remove(name + "/output_scaling");

        return;
    }

    const Vis::SizeSpecification& size_spec = val.getData<Vis::SizeSpecification>();

    settings.setValue(name + "/value", size_spec.getValue());
    settings.setValue(name + "/relative", size_spec.isRelative());
    settings.setValue(name + "/input_scaling", size_spec.followsInputScaling());
    settings.setValue(name + "/output_scaling", size_spec.followsOutputScaling());
}

void Settings::writeLineStyleParameter(const SettingsContainer& params, QSettings& settings, 
                                       const CDPL::Base::LookupKey& key) const
{
    using namespace CDPL;
    using namespace Vis;

    Base::Any val = params.getParameter(key);

    QString name = QString::fromStdString(key.getName());

    if (val.isEmpty()) {
        settings.remove(name);
        return;
    }

    switch (val.getData<Pen::LineStyle>()) {

    case Pen::NO_LINE:
        settings.setValue(name, 1);
        return;

    case Pen::SOLID_LINE:
        settings.setValue(name, 2);
        return;

    case Pen::DASH_LINE:
        settings.setValue(name, 3);
        return;

    case Pen::DOT_LINE:
        settings.setValue(name, 4);
        return;

    case Pen::DASH_DOT_LINE:
        settings.setValue(name, 5);
        return;

    case Pen::DASH_DOT_DOT_LINE:
        settings.setValue(name, 6);
        return;

    default:
        settings.remove(name);
    }
}

void Settings::writeAtomColorTableParam(QSettings& settings) const
{
    using namespace CDPL;
    using namespace Vis;

    Base::Any val = getParameter(ChOX::ControlParameter::ATOM_COLOR_TABLE);

    if (val.isEmpty()) {
        settings.remove("ATOM_COLOR_TABLE/entries");
        return;
    }

    const Vis::ColorTable& color_tab = *val.getData<Vis::ColorTable::SharedPointer>();

    QStringList atom_type_list;

    Vis::ColorTable::ConstEntryIterator color_tab_end = color_tab.getEntriesEnd();

    for (Vis::ColorTable::ConstEntryIterator it = color_tab.getEntriesBegin(); it != color_tab_end; ++it) {
        QString atom_type_str = QString().setNum(it->first);
        QString item_key_pfx = "ATOM_COLOR_TABLE/" + atom_type_str;

        const Color& color = it->second;

        settings.setValue(item_key_pfx + "/red", color.getRed());
        settings.setValue(item_key_pfx + "/green", color.getGreen());
        settings.setValue(item_key_pfx + "/blue", color.getBlue());
        settings.setValue(item_key_pfx + "/alpha", color.getAlpha());

        atom_type_list.push_back(atom_type_str);
    }

    settings.setValue("ATOM_COLOR_TABLE/entries", atom_type_list);
}

void Settings::writeDBCreationModeParameter(const SettingsContainer&, QSettings& settings, const CDPL::Base::LookupKey& key) const
{
}

template <typename T>
void Settings::writeParameter(const SettingsContainer& params, QSettings& settings, 
                              const CDPL::Base::LookupKey& key) const
{
    using namespace CDPL;

    Base::Any val = params.getParameter(key);

    QString name = QString::fromStdString(key.getName());

    if (val.isEmpty()) {
        settings.remove(name);
        return;
    }

    settings.setValue(name, QString::fromStdString(std::to_string(val.template getData<T>())));
}

void Settings::writeStrParameter(const SettingsContainer& params, QSettings& settings, 
                                 const CDPL::Base::LookupKey& key) const
{
    using namespace CDPL;

    Base::Any val = params.getParameter(key);

    QString name = QString::fromStdString(key.getName());

    if (val.isEmpty()) {
        settings.remove(name);
        return;
    }

    settings.setValue(name, QString::fromStdString(val.template getData<std::string>()));
}

void Settings::readFontParameter(SettingsContainer& params, QSettings& settings, 
                                 const CDPL::Base::LookupKey& key, const CDPL::Vis::Font& def_font)
{
    using namespace CDPL;

    QString name = QString::fromStdString(key.getName());

    Vis::Font font; 

    font.setFamily(settings.value(name + "/family", QString::fromStdString(def_font.getFamily())).toString().toStdString());
    font.setBold(settings.value(name + "/bold", def_font.isBold()).toBool());
    font.setItalic(settings.value(name + "/italic", def_font.isItalic()).toBool());
    font.setUnderlined(settings.value(name + "/underlined", def_font.isUnderlined()).toBool());
    font.setOverlined(settings.value(name + "/overlined", def_font.isOverlined()).toBool());
    font.setStrikedOut(settings.value(name + "/striked_out", def_font.isStrikedOut()).toBool());
    font.setFixedPitch(settings.value(name + "/fixed_pitch", def_font.hasFixedPitch()).toBool());

    params.setParameter(key, font);
}

void Settings::readColorParameter(SettingsContainer& params, QSettings& settings, 
                                  const CDPL::Base::LookupKey& key, const CDPL::Vis::Color& def_color)
{
    using namespace CDPL;

    QString name = QString::fromStdString(key.getName());

    Vis::Color color; 

    color.setRed(settings.value(name + "/red", def_color.getRed()).toDouble());
    color.setGreen(settings.value(name + "/green", def_color.getGreen()).toDouble());
    color.setBlue(settings.value(name + "/blue", def_color.getBlue()).toDouble());
    color.setAlpha(settings.value(name + "/alpha", def_color.getAlpha()).toDouble());

    params.setParameter(key, color);
}

void Settings::readBrushParameter(SettingsContainer& params, QSettings& settings, 
                                  const CDPL::Base::LookupKey& key, const CDPL::Vis::Brush& def_brush)
{
    using namespace CDPL;
    using namespace Vis;

    QString name = QString::fromStdString(key.getName());

    Color color; 

    color.setRed(settings.value(name + "/red", def_brush.getColor().getRed()).toDouble());
    color.setGreen(settings.value(name + "/green", def_brush.getColor().getGreen()).toDouble());
    color.setBlue(settings.value(name + "/blue", def_brush.getColor().getBlue()).toDouble());
    color.setAlpha(settings.value(name + "/alpha", def_brush.getColor().getAlpha()).toDouble());

    auto style = def_brush.getStyle();

    switch (settings.value(name + "/style", 0).toInt()) {

        case 1:
            style = Brush::NO_PATTERN;
            break;

        case 2:
            style = Brush::SOLID_PATTERN;
            break;

        case 3:
            style = Brush::DENSE1_PATTERN;
            break;

        case 4:
            style = Brush::DENSE2_PATTERN;
            break;

        case 5:
            style = Brush::DENSE3_PATTERN;
            break;

        case 6:
            style = Brush::DENSE4_PATTERN;
            break;

        case 7:
            style = Brush::DENSE5_PATTERN;
            break;

        case 8:
            style = Brush::DENSE6_PATTERN;
            break;

        case 9:
            style = Brush::DENSE7_PATTERN;
            break;

        case 10:
            style = Brush::H_PATTERN;
            break;

        case 11:
            style = Brush::V_PATTERN;
            break;

        case 12:
            style = Brush::CROSS_PATTERN;
            break;

        case 13:
            style = Brush::LEFT_DIAG_PATTERN;
            break;

        case 14:
            style = Brush::RIGHT_DIAG_PATTERN;
            break;

        case 15:
            style = Brush::DIAG_CROSS_PATTERN;

        default:
            break;
    }

    params.setParameter(key, Brush(color, style));
}
                    
void Settings::readSizeSpecParameter(SettingsContainer& params, QSettings& settings, 
                                     const CDPL::Base::LookupKey& key, const CDPL::Vis::SizeSpecification& def_size_spec)
{
    using namespace CDPL;

    QString name = QString::fromStdString(key.getName());

    Vis::SizeSpecification size_spec; 

    size_spec.setValue(settings.value(name + "/value", def_size_spec.getValue()).toDouble());
    size_spec.setRelative(settings.value(name + "/relative", def_size_spec.isRelative()).toBool());
    size_spec.followInputScaling(settings.value(name + "/input_scaling", def_size_spec.followsInputScaling()).toBool());
    size_spec.followOutputScaling(settings.value(name + "/output_scaling", def_size_spec.followsOutputScaling()).toBool());

    params.setParameter(key, size_spec);
}

void Settings::readLineStyleParameter(SettingsContainer& params, QSettings& settings, 
                                      const CDPL::Base::LookupKey& key, const CDPL::Vis::Pen::LineStyle& def_style)
{
    using namespace CDPL;
    using namespace Vis;

    QString name = QString::fromStdString(key.getName());

    int item = settings.value(name, 0).toInt();

    if (item == 0) {
        params.setParameter(key, def_style);
        return;
    }

    switch (item) {

    case 1:
        params.setParameter(key, Pen::NO_LINE);
        return;

    case 2:
        params.setParameter(key, Pen::SOLID_LINE);
        return;

    case 3:
        params.setParameter(key, Pen::DASH_LINE);
        return;

    case 4:
        params.setParameter(key, Pen::DOT_LINE);
        return;

    case 5:
        params.setParameter(key, Pen::DASH_DOT_LINE);
        return;

    case 6:        
        params.setParameter(key, Pen::DASH_DOT_DOT_LINE);
        return;

    default:
        params.setParameter(key, def_style);
    }
}

void Settings::readAtomColorTableParam(QSettings& settings)
{
    using namespace CDPL;
    using namespace Vis;

    QVariant entries_var = settings.value("ATOM_COLOR_TABLE/entries");

    Vis::ColorTable::SharedPointer color_tab_ptr;

    if (entries_var.isNull()) {
        color_tab_ptr.reset(new Vis::ColorTable(*ControlParameterDefault::ATOM_COLOR_TABLE));

    } else {
        color_tab_ptr.reset(new Vis::ColorTable());

        const Color& def_color = getAtomColorParameter(*this);

        QStringList entries = entries_var.toStringList();

        for (QStringList::ConstIterator it = entries.begin(), end = entries.end(); it != end; ++it) {
            const QString& atom_id = *it;

            Color color;

            color.setRed(settings.value("ATOM_COLOR_TABLE/" + atom_id + "/red", def_color.getRed()).toDouble());
            color.setGreen(settings.value("ATOM_COLOR_TABLE/" + atom_id + "/green", def_color.getGreen()).toDouble());
            color.setBlue(settings.value("ATOM_COLOR_TABLE/" + atom_id + "/blue", def_color.getBlue()).toDouble());
            color.setAlpha(settings.value("ATOM_COLOR_TABLE/" + atom_id + "/alpha", def_color.getAlpha()).toDouble());

            try {
                std::size_t atom_id_val = std::stoul(atom_id.toStdString());

                color_tab_ptr->setEntry(atom_id_val, color);

            } catch (const std::logic_error&) {}
        }
    }

    ChOX::setAtomColorTableParameter(*this, color_tab_ptr);
}

void Settings::readDBCreationModeParameter(SettingsContainer& params, QSettings& settings, 
                                           const CDPL::Base::LookupKey& key, 
                                           CDPL::Pharm::ScreeningDBCreator::Mode def_value) const
{
}

template <typename T>
void Settings::readParameter(SettingsContainer& params, QSettings& settings, 
                             const CDPL::Base::LookupKey& key, const T& def_value)
{
    using namespace CDPL;

    QString name = QString::fromStdString(key.getName());

    QString item = settings.value(name).toString();

    if (item.isEmpty()) {
        params.setParameter(key, def_value);

        return;
    }

    try {
        T value = boost::lexical_cast<T>(item.toStdString());

        params.setParameter(key, value);

    } catch (const boost::bad_lexical_cast&) {
        params.setParameter(key, def_value);
    }
}

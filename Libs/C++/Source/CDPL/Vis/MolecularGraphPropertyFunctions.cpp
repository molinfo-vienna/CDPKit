/* 
 * MolecularGraphPropertyFunctions.cpp 
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


#include "StaticInit.hpp"

#include "CDPL/Vis/MolecularGraphFunctions.hpp"
#include "CDPL/Vis/MolecularGraphProperty.hpp"
#include "CDPL/Vis/MolecularGraphPropertyDefault.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"


using namespace CDPL;


#define MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(PROP_NAME, TYPE, FUNC_SUFFIX)                        \
    TYPE Vis::get##FUNC_SUFFIX(const Chem::MolecularGraph& molgraph)                          \
    {                                                                                         \
        return molgraph.getPropertyOrDefault<TYPE>(MolecularGraphProperty::PROP_NAME,         \
                                                   MolecularGraphPropertyDefault::PROP_NAME); \
    }                                                                                         \
                                                                                              \
    void Vis::set##FUNC_SUFFIX(Chem::MolecularGraph& molgraph, TYPE arg)                      \
    {                                                                                         \
        molgraph.setProperty(MolecularGraphProperty::PROP_NAME, arg);                         \
    }                                                                                         \
                                                                                              \
    bool Vis::has##FUNC_SUFFIX(const Chem::MolecularGraph& molgraph)                          \
    {                                                                                         \
        return molgraph.isPropertySet(MolecularGraphProperty::PROP_NAME);                     \
    }                                                                                         \
                                                                                              \
    void Vis::clear##FUNC_SUFFIX(Chem::MolecularGraph& molgraph)                              \
    {                                                                                         \
        molgraph.removeProperty(MolecularGraphProperty::PROP_NAME);                           \
    }


MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(ATOM_COLOR_TABLE, const Vis::ColorTable::SharedPointer&, AtomColorTable)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(ATOM_COLOR, const Vis::Color&, AtomColor)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(ATOM_LABEL_FONT, const Vis::Font&, AtomLabelFont)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(ATOM_LABEL_SIZE, const Vis::SizeSpecification&, AtomLabelSize)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(SECONDARY_ATOM_LABEL_FONT, const Vis::Font&, SecondaryAtomLabelFont)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(SECONDARY_ATOM_LABEL_SIZE, const Vis::SizeSpecification&, SecondaryAtomLabelSize)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(ATOM_LABEL_MARGIN, const Vis::SizeSpecification&, AtomLabelMargin)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(RADICAL_ELECTRON_DOT_SIZE, const Vis::SizeSpecification&, RadicalElectronDotSize)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(ATOM_CONFIGURATION_LABEL_FONT, const Vis::Font&, AtomConfigurationLabelFont)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(ATOM_CONFIGURATION_LABEL_COLOR, const Vis::Color&, AtomConfigurationLabelColor)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(ATOM_CONFIGURATION_LABEL_SIZE, const Vis::SizeSpecification&, AtomConfigurationLabelSize)

MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(BOND_COLOR, const Vis::Color&, BondColor)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(BOND_LINE_WIDTH, const Vis::SizeSpecification&, BondLineWidth)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(BOND_LINE_SPACING, const Vis::SizeSpecification&, BondLineSpacing)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(STEREO_BOND_WEDGE_WIDTH, const Vis::SizeSpecification&, StereoBondWedgeWidth)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(STEREO_BOND_HASH_SPACING, const Vis::SizeSpecification&, StereoBondHashSpacing)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(REACTION_CENTER_LINE_LENGTH, const Vis::SizeSpecification&, ReactionCenterLineLength)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(REACTION_CENTER_LINE_SPACING, const Vis::SizeSpecification&, ReactionCenterLineSpacing)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(DOUBLE_BOND_TRIM_LENGTH, const Vis::SizeSpecification&, DoubleBondTrimLength)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(TRIPLE_BOND_TRIM_LENGTH, const Vis::SizeSpecification&, TripleBondTrimLength)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(BOND_LABEL_FONT, const Vis::Font&, BondLabelFont)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(BOND_LABEL_SIZE, const Vis::SizeSpecification&, BondLabelSize)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(BOND_LABEL_MARGIN, const Vis::SizeSpecification&, BondLabelMargin)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(BOND_CONFIGURATION_LABEL_FONT, const Vis::Font&, BondConfigurationLabelFont)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(BOND_CONFIGURATION_LABEL_COLOR, const Vis::Color&, BondConfigurationLabelColor)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(BOND_CONFIGURATION_LABEL_SIZE, const Vis::SizeSpecification&, BondConfigurationLabelSize)

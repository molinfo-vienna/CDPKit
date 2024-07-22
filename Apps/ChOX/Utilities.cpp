/* 
 * Utilities.cpp 
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


#include <algorithm>
#include <functional>
#include <sstream>
#include <exception>

#include <QPointF>
#include <QPainter>
#include <QFileDialog>
#include <QFileInfo>

#include "CDPL/Base/DataFormat.hpp"
#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/ReactionFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/CIPDescriptor.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/DataFormat.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/SMARTSMoleculeReader.hpp"
#include "CDPL/Pharm/MoleculeFunctions.hpp"
#include "CDPL/Pharm/DataFormat.hpp"
#include "CDPL/Vis/Alignment.hpp"
#include "CDPL/Util/BitSet.hpp"

#include "Utilities.hpp"


void ChOX::drawText(QPainter& painter, const QString& text, unsigned int alignment, 
                    double width, double height, double margin)
{
    using namespace CDPL;
    using namespace Vis;

    QRect brect = painter.fontMetrics().boundingRect(text);

    double text_y_pos = 0.0;

    switch (alignment & Alignment::V_ALIGNMENT_MASK) {

        case Alignment::TOP:
            text_y_pos = margin - brect.top();
            break;

        default:
            text_y_pos = height - brect.bottom() - margin;
    }

    double text_x_pos = 0.0;

    switch (alignment & Alignment::H_ALIGNMENT_MASK) {

        case Alignment::RIGHT:
            text_x_pos = width - brect.right() - margin;
            break;

        case Alignment::LEFT:
            text_x_pos = -brect.left() + margin;
            break;

        default:
            text_x_pos = width * 0.5 - brect.center().x();

    }

    painter.drawText(QPointF(text_x_pos, text_y_pos), text);
}

void ChOX::initData(CDPL::Chem::Reaction& rxn)
{
    using namespace CDPL;
    using namespace Chem;

    std::for_each(rxn.getComponentsBegin(), rxn.getComponentsEnd(),
                  std::bind(static_cast<void (*)(Molecule&)>(&initData), std::placeholders::_1));

    perceiveComponentGroups(rxn, false);
}

void ChOX::initData(CDPL::Chem::Molecule& mol)
{
    using namespace CDPL;
    using namespace Chem;

    perceiveComponents(mol, false);
    perceiveComponentGroups(mol, false);
    perceiveSSSR(mol, false);
    setRingFlags(mol, false);
    calcTopologicalDistanceMatrix(mol, false);

    calcImplicitHydrogenCounts(mol, false);
    perceiveHybridizationStates(mol, false);
    setAromaticityFlags(mol, false);

    perceiveAtomStereoCenters(mol, false, false);
    perceiveBondStereoCenters(mol, false, false);

    Util::BitSet def_atom_sto_ctrs(mol.getNumAtoms());
    
    for (auto& atom : mol.getAtoms())
        if (hasStereoDescriptor(atom))
            def_atom_sto_ctrs.set(atom.getIndex());

    calcAtomStereoDescriptors(mol, false);
    calcBondStereoDescriptors(mol, false);
    calcAtomCIPConfigurations(mol, false);
    calcBondCIPConfigurations(mol, false);

    for (auto& atom : mol.getAtoms()) {
        if (def_atom_sto_ctrs.test(atom.getIndex()))
            continue;

        switch (getCIPConfiguration(atom)) {

            case CIPDescriptor::UNDEF:
            case CIPDescriptor::NONE:
            case CIPDescriptor::NS: {
                auto& descr = getStereoDescriptor(atom);

                if (descr.getConfiguration() == AtomConfiguration::R ||
                    descr.getConfiguration() == AtomConfiguration::S)
                    clearStereoDescriptor(atom);
            }
        }
    }

    setAtomSymbolsFromTypes(mol, false);

    generateMatchExpressionStrings(mol, false);
}

void ChOX::prepareOutputData(CDPL::Chem::Molecule& mol, const CDPL::Base::DataFormat& opt_fmt, 
                             const CDPL::Base::ControlParameterContainer& params)
{
    using namespace CDPL;
    using namespace Chem;

    if (opt_fmt == DataFormat::JME || ((opt_fmt == DataFormat::SDF || opt_fmt == DataFormat::MOL ||
                                        opt_fmt == DataFormat::RDF || opt_fmt == DataFormat::RXN) &&
                                       (getCoordinatesDimensionParameter(params) == 2 || getMDLDimensionality(mol) == 2))) {

        if (!hasCoordinates(mol, 2)) {
            calc2DCoordinates(mol, true);
            calcBond2DStereoFlags(mol, true);
        }
        
    } else if (opt_fmt == Pharm::DataFormat::PSD)
        Pharm::prepareForPharmacophoreGeneration(mol, true, false);
}

void ChOX::prepareOutputData(CDPL::Chem::Reaction& rxn, const CDPL::Base::DataFormat& opt_fmt, 
                             const CDPL::Base::ControlParameterContainer& params)
{
    using namespace CDPL;
    using namespace Chem;

    std::for_each(rxn.getComponentsBegin(), rxn.getComponentsEnd(),
                  std::bind(static_cast<void (*)(Molecule&, const Base::DataFormat&,
                                                 const Base::ControlParameterContainer&)>
                            (&prepareOutputData), std::placeholders::_1, std::ref(opt_fmt), std::ref(params)));
}

QString ChOX::validateSMARTS(const QString& smarts)
{
    if (smarts.isEmpty())
        return QString();

    try {
        using namespace CDPL::Chem;

        BasicMolecule mol;
        std::istringstream iss(smarts.toStdString());
        SMARTSMoleculeReader reader(iss);

        setStrictErrorCheckingParameter(reader, true);
        
        if (!reader.read(mol))
            return "Unspecified error";

        return QString();
        
    } catch (const std::exception& e) {
        return QString(e.what()).replace("SMARTSMoleculeReader: while reading record 0: SMARTSDataReader", "Error");
    }
}

CDPL::Chem::Molecule::SharedPointer ChOX::parseSMARTS(const QString& smarts)
{
    using namespace CDPL::Chem;

    try {
        Molecule::SharedPointer mol_ptr(new BasicMolecule());
        std::istringstream iss(smarts.toStdString());
        SMARTSMoleculeReader reader(iss);

        setStrictErrorCheckingParameter(reader, true);

        if (!reader.read(*mol_ptr))
            return Molecule::SharedPointer();

        initSubstructureSearchQuery(*mol_ptr, false);

        return mol_ptr;


    } catch (const std::exception& e) {
        return Molecule::SharedPointer();
    }
}

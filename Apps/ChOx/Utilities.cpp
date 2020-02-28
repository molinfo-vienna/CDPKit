/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Utilities.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include <boost/bind.hpp>

#include <QPointF>
#include <QString>
#include <QPainter>

#include "CDPL/Base/DataFormat.hpp"
#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/ReactionFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/DataFormat.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Vis/Alignment.hpp"

#include "Utilities.hpp"


void ChOx::drawText(QPainter& painter, const QString& text, unsigned int alignment, 
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

void ChOx::initData(CDPL::Chem::Reaction& rxn)
{
	using namespace CDPL;
	using namespace Chem;

	std::for_each(rxn.getComponentsBegin(), rxn.getComponentsEnd(),
				  boost::bind(static_cast<void (*)(Molecule&)>(&initData), _1));

	perceiveComponentGroups(rxn, false);
}

void ChOx::initData(CDPL::Chem::Molecule& mol)
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
	calcCIPPriorities(mol, false);

	perceiveAtomStereoCenters(mol, false, true, false);
	perceiveBondStereoCenters(mol, false);

	for (Molecule::AtomIterator it = mol.getAtomsBegin(), end = mol.getAtomsEnd(); it != end; ++it) {
		Atom& atom = *it;

		if (getStereoCenterFlag(atom) && (!hasStereoDescriptor(atom) || getStereoDescriptor(atom).getConfiguration() == AtomConfiguration::UNDEF)) 
			setStereoDescriptor(atom, calcStereoDescriptor(atom, mol, 1));
	}

	for (Molecule::BondIterator it = mol.getBondsBegin(), end = mol.getBondsEnd(); it != end; ++it) {
		Bond& bond = *it;

		if (getStereoCenterFlag(bond) && (!hasStereoDescriptor(bond) || getStereoDescriptor(bond).getConfiguration() == AtomConfiguration::UNDEF))
			setStereoDescriptor(bond, calcStereoDescriptor(bond, mol, 1));
	}

	setAtomSymbolsFromTypes(mol, false);

	buildMatchExpressionStrings(mol, false);
}

void ChOx::prepareOutputData(CDPL::Chem::Molecule& mol, const CDPL::Base::DataFormat& opt_fmt, 
							 const CDPL::Base::ControlParameterContainer& params)
{
	using namespace CDPL;
	using namespace Chem;

	if (opt_fmt == DataFormat::JME || ((opt_fmt == DataFormat::SDF || opt_fmt == DataFormat::MOL ||
										opt_fmt == DataFormat::RDF || opt_fmt == DataFormat::RXN) &&
									   (getCoordinatesDimensionParameter(params) == 2 || getMDLDimensionality(mol) == 2))) {

		if (!hasCoordinates(mol, 2)) {
			generate2DCoordinates(mol, true);
			generateBond2DStereoFlags(mol, true);
		}
	}
}

void ChOx::prepareOutputData(CDPL::Chem::Reaction& rxn, const CDPL::Base::DataFormat& opt_fmt, 
							 const CDPL::Base::ControlParameterContainer& params)
{
	using namespace CDPL;
	using namespace Chem;

	std::for_each(rxn.getComponentsBegin(), rxn.getComponentsEnd(),
				  boost::bind(static_cast<void (*)(Molecule&, const Base::DataFormat&,
												   const Base::ControlParameterContainer&)>
							  (&prepareOutputData), _1, boost::ref(opt_fmt), boost::ref(params)));
}

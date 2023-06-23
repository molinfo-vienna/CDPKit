/* 
 * AtomContainerDipoleMomentFunctions.cpp 
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

#include "CDPL/MolProp/AtomContainerFunctions.hpp"
#include "CDPL/MolProp/AtomFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Chem/Atom.hpp"


using namespace CDPL; 


bool MolProp::calcDipoleMoment(const Chem::AtomContainer& cntnr, const Chem::Atom3DCoordinatesFunction& coords_func, Math::Vector3D& moment)
{
	using namespace Chem;
	
	const double UNIT_CONV_FACTOR = 4.8032066;
	Math::Vector3D mass_ctr;

	if (!calcCenterOfMass(cntnr, coords_func, mass_ctr))
		return false;

	moment.clear();

	for (AtomContainer::ConstAtomIterator it = cntnr.getAtomsBegin(), end = cntnr.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;
		
		moment.plusAssign((coords_func(atom) - mass_ctr) * calcTotalPartialCharge(atom));
	}
	
	moment *= UNIT_CONV_FACTOR;
	
	return true;
}

bool MolProp::calcDipoleMoment(const Chem::AtomContainer& cntnr, Math::Vector3D& moment)
{
	return calcDipoleMoment(cntnr, static_cast<const Math::Vector3D& (*)(const Chem::Entity3D&)>(&Chem::get3DCoordinates), moment);
}


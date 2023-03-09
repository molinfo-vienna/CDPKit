#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas A. Seidel <thomas.seidel@univie.ac.at>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; see the file COPYING. If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
#

##
# \brief 
# \param cntnr 
# \return 
#
def buildExplicitMolecularFormula(cntnr: CDPL.Chem.AtomContainer) -> str: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getNetFormalCharge(cntnr: CDPL.Chem.AtomContainer) -> int: pass

##
# \brief 
# \param cntnr 
# \return 
#
def buildExplicitMassCompositionString(cntnr: CDPL.Chem.AtomContainer) -> str: pass

##
# \brief 
# \param cntnr 
# \param hist 
# \param append 
#
def buildExplicitElementHistogram(cntnr: CDPL.Chem.AtomContainer, hist: ElementHistogram, append: bool = False) -> None: pass

##
# \brief 
# \param cntnr 
# \param mass_comp 
#
def calcExplicitMassComposition(cntnr: CDPL.Chem.AtomContainer, mass_comp: MassComposition) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def calcExplicitMass(cntnr: CDPL.Chem.AtomContainer) -> float: pass

##
# \brief 
# \param cntnr 
# \param moment 
# \return 
#
def calcDipoleMoment(cntnr: CDPL.Chem.AtomContainer, moment: CDPL.Math.Vector3D) -> bool: pass

##
# \brief 
# \param cntnr 
# \param coords_func 
# \param moment 
# \return 
#
def calcDipoleMoment(cntnr: CDPL.Chem.AtomContainer, coords_func: CDPL.Chem.Atom3DCoordinatesFunction, moment: CDPL.Math.Vector3D) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getAromaticAtomCount(cntnr: CDPL.Chem.AtomContainer) -> int: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getRingAtomCount(cntnr: CDPL.Chem.AtomContainer) -> int: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getExplicitChainAtomCount(cntnr: CDPL.Chem.AtomContainer) -> int: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getExplicitAtomCount(cntnr: CDPL.Chem.AtomContainer) -> int: pass

##
# \brief 
# \param cntnr 
# \param type 
# \param strict 
# \return 
#
def getExplicitAtomCount(cntnr: CDPL.Chem.AtomContainer, type: int, strict: bool = True) -> int: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getHeavyAtomCount(cntnr: CDPL.Chem.AtomContainer) -> int: pass

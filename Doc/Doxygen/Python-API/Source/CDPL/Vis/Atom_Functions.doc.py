#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas Seidel <thomas.seidel@univie.ac.at>
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
# \param atom 
#
def clearLabelSize(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasLabelSize(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getLabelSize(atom: Chem.Atom) -> SizeSpecification: pass

##
# \brief 
# \param atom 
# \param size 
#
def setLabelSize(atom: Chem.Atom, size: SizeSpecification) -> None: pass

##
# \brief 
# \param atom 
#
def clearSecondaryLabelSize(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasSecondaryLabelSize(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getSecondaryLabelSize(atom: Chem.Atom) -> SizeSpecification: pass

##
# \brief 
# \param atom 
# \param size 
#
def setSecondaryLabelSize(atom: Chem.Atom, size: SizeSpecification) -> None: pass

##
# \brief 
# \param atom 
#
def clearRadicalElectronDotSize(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasRadicalElectronDotSize(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getRadicalElectronDotSize(atom: Chem.Atom) -> SizeSpecification: pass

##
# \brief 
# \param atom 
# \param size 
#
def setRadicalElectronDotSize(atom: Chem.Atom, size: SizeSpecification) -> None: pass

##
# \brief 
# \param atom 
#
def clearLabelMargin(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasLabelMargin(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getLabelMargin(atom: Chem.Atom) -> SizeSpecification: pass

##
# \brief 
# \param atom 
# \param margin 
#
def setLabelMargin(atom: Chem.Atom, margin: SizeSpecification) -> None: pass

##
# \brief 
# \param atom 
#
def clearColor(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasColor(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getColor(atom: Chem.Atom) -> Color: pass

##
# \brief 
# \param atom 
# \param color 
#
def setColor(atom: Chem.Atom, color: Color) -> None: pass

##
# \brief 
# \param atom 
#
def clearLabelFont(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasLabelFont(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getLabelFont(atom: Chem.Atom) -> Font: pass

##
# \brief 
# \param atom 
# \param font 
#
def setLabelFont(atom: Chem.Atom, font: Font) -> None: pass

##
# \brief 
# \param atom 
#
def clearSecondaryLabelFont(atom: Chem.Atom) -> None: pass

##
# \brief 
# \param atom 
# \return 
#
def hasSecondaryLabelFont(atom: Chem.Atom) -> bool: pass

##
# \brief 
# \param atom 
# \return 
#
def getSecondaryLabelFont(atom: Chem.Atom) -> Font: pass

##
# \brief 
# \param atom 
# \param font 
#
def setSecondaryLabelFont(atom: Chem.Atom, font: Font) -> None: pass

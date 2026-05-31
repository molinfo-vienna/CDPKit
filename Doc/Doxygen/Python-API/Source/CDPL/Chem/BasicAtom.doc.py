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
# \brief Concrete Chem.Atom implementation used as the atom type of Chem.BasicMolecule.
# 
# Stores its own incident-bond list and provides constant-time access to neighbor atoms and bonds via the inherited Chem.Atom interface. <tt>BasicAtom</tt> instances are owned by a Chem.BasicMolecule and are not constructed directly by client code; use Chem.BasicMolecule.addAtom() instead.
# 
class BasicAtom(Atom):

    ##
    # \brief Assignment operator that replaces the current set of properties with the properties of <em>atom</em>;.
    # 
    # \param atom The atom whose properties get copied.
    # 
    # \return \a self
    # 
    def assign(atom: Atom) -> Atom: pass

    ##
    # \brief Assignment operator that replaces the current set of properties with the properties of <em>atom</em>;.
    # 
    # \param atom The atom whose properties get copied.
    # 
    # \return \a self
    # 
    def assign(atom: BasicAtom) -> BasicAtom: pass

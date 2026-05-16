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
# \brief Provides keys for built-in biomolecular Chem.Atom properties.
# 
class AtomProperty(Boost.Python.instance):

    ##
    # \brief Specifies the residue-local name of the atom (e.g. <em>CA</em>, <em>CB</em>).
    # 
    # <b>Value Type:</b> std::string
    # 
    RESIDUE_ATOM_NAME = CDPL.Base.LookupKey('RESIDUE_ATOM_NAME')

    ##
    # \brief Specifies the alternative residue-local name of the atom.
    # 
    # <b>Value Type:</b> std::string
    # 
    RESIDUE_ALT_ATOM_NAME = CDPL.Base.LookupKey('RESIDUE_ALT_ATOM_NAME')

    ##
    # \brief Specifies whether the atom is a leaving atom in the parent residue.
    # 
    # <b>Value Type:</b> bool
    # 
    RESIDUE_LEAVING_ATOM_FLAG = CDPL.Base.LookupKey('RESIDUE_LEAVING_ATOM_FLAG')

    ##
    # \brief Specifies whether the atom is a linking atom between residues.
    # 
    # <b>Value Type:</b> bool
    # 
    RESIDUE_LINKING_ATOM_FLAG = CDPL.Base.LookupKey('RESIDUE_LINKING_ATOM_FLAG')

    ##
    # \brief Specifies the residue code (three-letter code) of the residue the atom belongs to.
    # 
    # <b>Value Type:</b> std::string
    # 
    RESIDUE_CODE = CDPL.Base.LookupKey('RESIDUE_CODE')

    ##
    # \brief Specifies the sequence number of the residue the atom belongs to.
    # 
    # <b>Value Type:</b> long
    # 
    RESIDUE_SEQUENCE_NUMBER = CDPL.Base.LookupKey('RESIDUE_SEQUENCE_NUMBER')

    ##
    # \brief Specifies the insertion code of the residue the atom belongs to.
    # 
    # <b>Value Type:</b> char
    # 
    RESIDUE_INSERTION_CODE = CDPL.Base.LookupKey('RESIDUE_INSERTION_CODE')

    ##
    # \brief Specifies whether the atom is a hetero atom (HETATM record in PDB).
    # 
    # <b>Value Type:</b> bool
    # 
    HETERO_ATOM_FLAG = CDPL.Base.LookupKey('HETERO_ATOM_FLAG')

    ##
    # \brief Specifies the chain identifier of the chain the atom belongs to.
    # 
    # <b>Value Type:</b> std::string
    # 
    CHAIN_ID = CDPL.Base.LookupKey('CHAIN_ID')

    ##
    # \brief Specifies the alternate-location identifier of the atom.
    # 
    # <b>Value Type:</b> char
    # 
    ALT_LOCATION_ID = CDPL.Base.LookupKey('ALT_LOCATION_ID')

    ##
    # \brief Specifies the identifier of the entity the atom belongs to (e.g. an mmCIF entity ID).
    # 
    # <b>Value Type:</b> std::string \since 1.2
    # 
    ENTITY_ID = CDPL.Base.LookupKey('ENTITY_ID')

    ##
    # \brief Specifies the model number of the model the atom belongs to.
    # 
    # <b>Value Type:</b> std::size_t
    # 
    MODEL_NUMBER = CDPL.Base.LookupKey('MODEL_NUMBER')

    ##
    # \brief Specifies the serial number of the atom as read from or written to the input file.
    # 
    # <b>Value Type:</b> long
    # 
    SERIAL_NUMBER = CDPL.Base.LookupKey('SERIAL_NUMBER')

    ##
    # \brief Specifies the occupancy of the atom as read from or written to the input file.
    # 
    # <b>Value Type:</b> double
    # 
    OCCUPANCY = CDPL.Base.LookupKey('OCCUPANCY')

    ##
    # \brief Specifies the isotropic temperature (B-) factor of the atom.
    # 
    # <b>Value Type:</b> double
    # 
    B_FACTOR = CDPL.Base.LookupKey('B_FACTOR')

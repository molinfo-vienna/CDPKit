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
#
class MolecularGraphProperty(Boost.Python.instance):

    ##
    # \brief 
    #
    ATOM_COLOR = CDPL.Base.LookupKey(id=164, name='ATOM_COLOR')

    ##
    # \brief 
    #
    ATOM_COLOR_TABLE = CDPL.Base.LookupKey(id=163, name='ATOM_COLOR_TABLE')

    ##
    # \brief 
    #
    RADICAL_ELECTRON_DOT_SIZE = CDPL.Base.LookupKey(id=170, name='RADICAL_ELECTRON_DOT_SIZE')

    ##
    # \brief 
    #
    ATOM_LABEL_FONT = CDPL.Base.LookupKey(id=165, name='ATOM_LABEL_FONT')

    ##
    # \brief 
    #
    ATOM_LABEL_MARGIN = CDPL.Base.LookupKey(id=169, name='ATOM_LABEL_MARGIN')

    ##
    # \brief 
    #
    ATOM_LABEL_SIZE = CDPL.Base.LookupKey(id=166, name='ATOM_LABEL_SIZE')

    ##
    # \brief 
    #
    SECONDARY_ATOM_LABEL_FONT = CDPL.Base.LookupKey(id=167, name='SECONDARY_ATOM_LABEL_FONT')

    ##
    # \brief 
    #
    SECONDARY_ATOM_LABEL_SIZE = CDPL.Base.LookupKey(id=168, name='SECONDARY_ATOM_LABEL_SIZE')

    ##
    # \brief 
    #
    BOND_COLOR = CDPL.Base.LookupKey(id=171, name='BOND_COLOR')

    ##
    # \brief 
    #
    BOND_LABEL_FONT = CDPL.Base.LookupKey(id=180, name='BOND_LABEL_FONT')

    ##
    # \brief 
    #
    BOND_LABEL_MARGIN = CDPL.Base.LookupKey(id=182, name='BOND_LABEL_MARGIN')

    ##
    # \brief 
    #
    BOND_LABEL_SIZE = CDPL.Base.LookupKey(id=181, name='BOND_LABEL_SIZE')

    ##
    # \brief 
    #
    BOND_LINE_SPACING = CDPL.Base.LookupKey(id=173, name='BOND_LINE_SPACING')

    ##
    # \brief 
    #
    BOND_LINE_WIDTH = CDPL.Base.LookupKey(id=172, name='BOND_LINE_WIDTH')

    ##
    # \brief 
    #
    REACTION_CENTER_LINE_LENGTH = CDPL.Base.LookupKey(id=176, name='REACTION_CENTER_LINE_LENGTH')

    ##
    # \brief 
    #
    REACTION_CENTER_LINE_SPACING = CDPL.Base.LookupKey(id=177, name='REACTION_CENTER_LINE_SPACING')

    ##
    # \brief 
    #
    STEREO_BOND_HASH_SPACING = CDPL.Base.LookupKey(id=175, name='STEREO_BOND_HASH_SPACING')

    ##
    # \brief 
    #
    STEREO_BOND_WEDGE_WIDTH = CDPL.Base.LookupKey(id=174, name='STEREO_BOND_WEDGE_WIDTH')

    ##
    # \brief 
    #
    DOUBLE_BOND_TRIM_LENGTH = CDPL.Base.LookupKey(id=178, name='DOUBLE_BOND_TRIM_LENGTH')

    ##
    # \brief 
    #
    TRIPLE_BOND_TRIM_LENGTH = CDPL.Base.LookupKey(id=179, name='TRIPLE_BOND_TRIM_LENGTH')

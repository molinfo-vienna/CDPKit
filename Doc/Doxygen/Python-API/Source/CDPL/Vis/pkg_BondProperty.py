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
class BondProperty(Boost.Python.instance):

    ##
    # \brief 
    #
    COLOR = CDPL.Base.LookupKey(id=151, name='COLOR')

    ##
    # \brief 
    #
    DOUBLE_BOND_TRIM_LENGTH = CDPL.Base.LookupKey(id=158, name='DOUBLE_BOND_TRIM_LENGTH')

    ##
    # \brief 
    #
    LABEL_FONT = CDPL.Base.LookupKey(id=160, name='LABEL_FONT')

    ##
    # \brief 
    #
    LABEL_MARGIN = CDPL.Base.LookupKey(id=162, name='LABEL_MARGIN')

    ##
    # \brief 
    #
    LABEL_SIZE = CDPL.Base.LookupKey(id=161, name='LABEL_SIZE')

    ##
    # \brief 
    #
    LINE_SPACING = CDPL.Base.LookupKey(id=153, name='LINE_SPACING')

    ##
    # \brief 
    #
    LINE_WIDTH = CDPL.Base.LookupKey(id=152, name='LINE_WIDTH')

    ##
    # \brief 
    #
    REACTION_CENTER_LINE_LENGTH = CDPL.Base.LookupKey(id=156, name='REACTION_CENTER_LINE_LENGTH')

    ##
    # \brief 
    #
    REACTION_CENTER_LINE_SPACING = CDPL.Base.LookupKey(id=157, name='REACTION_CENTER_LINE_SPACING')

    ##
    # \brief 
    #
    TRIPLE_BOND_TRIM_LENGTH = CDPL.Base.LookupKey(id=159, name='TRIPLE_BOND_TRIM_LENGTH')

    ##
    # \brief 
    #
    STEREO_BOND_HASH_SPACING = CDPL.Base.LookupKey(id=155, name='STEREO_BOND_HASH_SPACING')

    ##
    # \brief 
    #
    STEREO_BOND_WEDGE_WIDTH = CDPL.Base.LookupKey(id=154, name='STEREO_BOND_WEDGE_WIDTH')

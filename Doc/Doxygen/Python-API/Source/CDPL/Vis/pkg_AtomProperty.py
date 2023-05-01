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
class AtomProperty(Boost.Python.instance):

    ##
    # \brief 
    #
    COLOR = CDPL.Base.LookupKey(id=147, name='COLOR')

    ##
    # \brief 
    #
    RADICAL_ELECTRON_DOT_SIZE = CDPL.Base.LookupKey(id=153, name='RADICAL_ELECTRON_DOT_SIZE')

    ##
    # \brief 
    #
    LABEL_FONT = CDPL.Base.LookupKey(id=148, name='LABEL_FONT')

    ##
    # \brief 
    #
    LABEL_MARGIN = CDPL.Base.LookupKey(id=152, name='LABEL_MARGIN')

    ##
    # \brief 
    #
    LABEL_SIZE = CDPL.Base.LookupKey(id=149, name='LABEL_SIZE')

    ##
    # \brief 
    #
    SECONDARY_LABEL_FONT = CDPL.Base.LookupKey(id=150, name='SECONDARY_LABEL_FONT')

    ##
    # \brief 
    #
    SECONDARY_LABEL_SIZE = CDPL.Base.LookupKey(id=151, name='SECONDARY_LABEL_SIZE')

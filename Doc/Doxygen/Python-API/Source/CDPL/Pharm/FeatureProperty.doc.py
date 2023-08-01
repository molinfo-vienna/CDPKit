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
# \brief Provides keys for built-in Pharm.Feature properties.
# 
class FeatureProperty(Boost.Python.instance):

    ##
    # \brief 
    #
    TYPE = CDPL.Base.LookupKey(id=308, name='TYPE')

    ##
    # \brief 
    #
    GEOMETRY = CDPL.Base.LookupKey(id=309, name='GEOMETRY')

    ##
    # \brief 
    #
    LENGTH = CDPL.Base.LookupKey(id=310, name='LENGTH')

    ##
    # \brief 
    #
    ORIENTATION = CDPL.Base.LookupKey(id=311, name='ORIENTATION')

    ##
    # \brief 
    #
    TOLERANCE = CDPL.Base.LookupKey(id=312, name='TOLERANCE')

    ##
    # \brief 
    #
    WEIGHT = CDPL.Base.LookupKey(id=313, name='WEIGHT')

    ##
    # \brief 
    #
    SUBSTRUCTURE = CDPL.Base.LookupKey(id=314, name='SUBSTRUCTURE')

    ##
    # \brief 
    #
    DISABLED_FLAG = CDPL.Base.LookupKey(id=315, name='DISABLED_FLAG')

    ##
    # \brief 
    #
    OPTIONAL_FLAG = CDPL.Base.LookupKey(id=316, name='OPTIONAL_FLAG')

    ##
    # \brief 
    #
    HYDROPHOBICITY = CDPL.Base.LookupKey(id=317, name='HYDROPHOBICITY')

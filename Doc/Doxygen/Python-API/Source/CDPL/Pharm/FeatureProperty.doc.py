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
    # \brief Specifies the type of the pharmacophore feature (see namespace Pharm.FeatureType).
    # 
    # <b>Value Type:</b> unsigned int
    # 
    TYPE = CDPL.Base.LookupKey('TYPE')

    ##
    # \brief Specifies the geometric shape of the feature (see namespace Pharm.FeatureGeometry).
    # 
    # <b>Value Type:</b> unsigned int
    # 
    GEOMETRY = CDPL.Base.LookupKey('GEOMETRY')

    ##
    # \brief Specifies the length of the feature (for directional features).
    # 
    # <b>Value Type:</b> double
    # 
    LENGTH = CDPL.Base.LookupKey('LENGTH')

    ##
    # \brief Specifies the orientation of the feature in 3D space.
    # 
    # <b>Value Type:</b> Math.Vector3D
    # 
    ORIENTATION = CDPL.Base.LookupKey('ORIENTATION')

    ##
    # \brief Specifies the positional tolerance of the feature.
    # 
    # <b>Value Type:</b> double
    # 
    TOLERANCE = CDPL.Base.LookupKey('TOLERANCE')

    ##
    # \brief Specifies the weight (relative importance) of the feature.
    # 
    # <b>Value Type:</b> double
    # 
    WEIGHT = CDPL.Base.LookupKey('WEIGHT')

    ##
    # \brief Specifies the chemical substructure the feature was derived from.
    # 
    # <b>Value Type:</b> Chem.Fragment.SharedPointer
    # 
    SUBSTRUCTURE = CDPL.Base.LookupKey('SUBSTRUCTURE')

    ##
    # \brief Specifies whether the feature is currently disabled (and thus not considered in pharmacophore matching).
    # 
    # <b>Value Type:</b> bool
    # 
    DISABLED_FLAG = CDPL.Base.LookupKey('DISABLED_FLAG')

    ##
    # \brief Specifies whether the feature is optional in pharmacophore matching.
    # 
    # <b>Value Type:</b> bool
    # 
    OPTIONAL_FLAG = CDPL.Base.LookupKey('OPTIONAL_FLAG')

    ##
    # \brief Specifies the calculated hydrophobicity contribution of the feature.
    # 
    # <b>Value Type:</b> double
    # 
    HYDROPHOBICITY = CDPL.Base.LookupKey('HYDROPHOBICITY')

    ##
    # \brief Specifies the environment substructure (e.g. interacting pocket residues) associated with the feature.
    # 
    # <b>Value Type:</b> Chem.Fragment.SharedPointer \since 1.4
    # 
    ENVIRONMENT_SUBSTRUCTURE = CDPL.Base.LookupKey('ENVIRONMENT_SUBSTRUCTURE')

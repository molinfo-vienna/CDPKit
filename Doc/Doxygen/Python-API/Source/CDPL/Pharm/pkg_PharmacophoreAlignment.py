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
# \brief PharmacophoreAlignment.
# 
class PharmacophoreAlignment(SpatialFeatureAlignment):

    ##
    # \brief Constructs the <tt>PharmacophoreAlignment</tt> instance.
    # 
    # \param query_mode If <tt>True</tt>, the features of the first set are interpreted as a query pharmacophore and the features of the second have to match this query after alignment. If <tt>False</tt>, there is no distinction between the features of the first and second set in various performed intermediate checks.
    # 
    def __init__(query_mode: bool) -> None: pass

    ##
    # \brief Initializes the \e %PharmacophoreAlignment instance.
    # \param alignment 
    # 
    def __init__(alignment: PharmacophoreAlignment) -> None: pass

    ##
    # \brief Adds the features of the feature container <em>cntnr</em> to the specified alignment feature set.
    # 
    # \param cntnr The feature container containing features to add.
    # \param first_set If <tt>True</tt>, the features are added to the first feature set, if <tt>False</tt> to the second one.
    # 
    def addFeatures(cntnr: FeatureContainer, first_set: bool) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %PharmacophoreAlignment instance \a alignment.
    # \param alignment The \e %PharmacophoreAlignment instance to copy.
    # \return \a self
    # 
    def assign(alignment: PharmacophoreAlignment) -> PharmacophoreAlignment: pass

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
# \brief Feature.
# 
class Feature(Chem.Entity3D):

    ##
    # \brief Initializes the \e %Feature instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns a reference to the parent pharmacophore.
    # 
    # \return A reference to the parent pharmacophore.
    # 
    def getPharmacophore() -> Pharmacophore: pass

    ##
    # \brief Returns the index of the feature in its parent pharmacophore.
    # 
    # \return The zero-based index of the feature.
    # 
    def getIndex() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Feature instance \a ftr.
    # \param ftr The \e %Feature instance to copy.
    # \return \a self
    # 
    def assign(ftr: Feature) -> Feature: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def __getitem__(key: Base.LookupKey) -> Base.Any: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(key: Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param key 
    # \param value 
    #
    def __setitem__(key: Base.LookupKey, value: Base.Any) -> None: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def __delitem__(key: Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    pharmacophore = property(getPharmacophore)

    index = property(getIndex)

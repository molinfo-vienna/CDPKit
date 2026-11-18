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
# \brief Data type for the storage of feature type histograms of pharmacophores.
# 
# <tt>FeatureTypeHistogram</tt> is a unique associative map where the keys specify the feature type (defined in namespace Pharm.FeatureType) of the pharmacophore features and the mapped integer values correspond to the feature type frequencies.
# 
class FeatureTypeHistogram(Boost.Python.instance):

    ##
    # \brief Contructs the \c FeatureTypeHistogram instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Contructs a copy of the \c FeatureTypeHistogram instance \a ft_hist.
    # \param ft_hist The \c FeatureTypeHistogram instance to copy.
    # 
    def __init__(ft_hist: FeatureTypeHistogram) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c FeatureTypeHistogram instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c FeatureTypeHistogram instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    def getSize() -> int: pass

    def isEmpty() -> bool: pass

    def clear() -> None: pass

    ##
    # \brief Replaces the current state with a copy of the state of the \c FeatureTypeHistogram instance \a map.
    # \param map The \c FeatureTypeHistogram instance to copy.
    # \return \a self.
    # 
    def assign(map: FeatureTypeHistogram) -> FeatureTypeHistogram: pass

    def getValue(key: int) -> int: pass

    def getValue(key: int, def_value: int) -> int: pass

    def removeEntry(key: int) -> bool: pass

    def setEntry(key: int, value: int) -> None: pass

    ##
    # \brief Returns a list containing the keys of the current entries.
    # \return A list containing the requested keys.
    # 
    def getKeys() -> object: pass

    ##
    # \brief Returns a list containing the keys of the current entries.
    # \return A list containing the requested keys.
    # 
    def keys() -> object: pass

    ##
    # \brief Returns a list containing the values of the current entries.
    # \return A list containing the requested values.
    # 
    def getValues() -> object: pass

    ##
    # \brief Returns a list containing the values of the current entries.
    # \return A list containing the requested values.
    # 
    def values() -> object: pass

    ##
    # \brief Returns a list containing the current entries as (key,value) tuples.
    # \return A list containing the current entries as (key,value) tuples.
    # 
    def getEntries() -> object: pass

    ##
    # \brief Returns a list containing the current entries as (key,value) tuples.
    # \return A list containing the current entries as (key,value) tuples.
    # 
    def items() -> object: pass

    def containsEntry(key: int) -> bool: pass

    def insertEntry(key: int, value: int) -> bool: pass

    def __len__() -> int: pass

    def __getitem__(key: int) -> int: pass

    def __setitem__(key: int, value: int) -> None: pass

    def __delitem__(key: int) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(key: int) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == ft_hist</tt>.
    # \param ft_hist The \c object instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(ft_hist: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != ft_hist</tt>.
    # \param ft_hist The \c object instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(ft_hist: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self <= ft_hist</tt>.
    # \param ft_hist The \c object instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __le__(ft_hist: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self >= ft_hist</tt>.
    # \param ft_hist The \c object instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ge__(ft_hist: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self < ft_hist</tt>.
    # \param ft_hist The \c object instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __lt__(ft_hist: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self > ft_hist</tt>.
    # \param ft_hist The \c object instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __gt__(ft_hist: object) -> bool: pass

    objectID = property(getObjectID)

    size = property(getSize)

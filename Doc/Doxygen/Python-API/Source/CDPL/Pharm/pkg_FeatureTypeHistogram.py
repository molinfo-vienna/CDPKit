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
# \brief A data type for the storage of feature type histograms of pharmacophores.
# 
# <tt>FeatureTypeHistogram</tt> is an unique associative map where the keys specify the feature type (defined in namespace Pharm.FeatureType) of the pharmacophore features and the mapped integer values correspond to the feature type frequencies.
# 
class FeatureTypeHistogram(Boost.Python.instance):

    ##
    # \brief Creates an empty map.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %FeatureTypeHistogram instance.
    # \param self The \e %FeatureTypeHistogram instance to initialize.
    # \param ft_hist 
    # 
    def __init__(ft_hist: FeatureTypeHistogram) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %FeatureTypeHistogram instance this method is called upon.
    # 
    # Different Python \e %FeatureTypeHistogram instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FeatureTypeHistogram instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Returns the size (number of entries) of the map.
    # 
    # \return The size of the map.
    # 
    def getSize() -> int: pass

    ##
    # \brief Tells whether the map is empty (<tt>getSize() == 0</tt>).
    # 
    # \return <tt>True</tt> if the map is empty, and <tt>False</tt> otherwise.
    # 
    def isEmpty() -> bool: pass

    ##
    # \brief Erases all entries.
    # 
    def clear() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FeatureTypeHistogram instance \a map.
    # \param self The \e %FeatureTypeHistogram instance this method is called upon.
    # \param map The \e %FeatureTypeHistogram instance to copy.
    # \return \a self
    # 
    def assign(map: FeatureTypeHistogram) -> FeatureTypeHistogram: pass

    ##
    # \brief Returns a reference to the value associated with the specified key.
    # 
    # If the map contains the specified entry, a reference to the associated value is returned. If the map does not contain the entry and default values are enabled (that is, the template parameter <em>AllowDefValues</em> is <tt>True</tt>), a reference to a default constructed value object is returned. Otherwise, Base.ItemNotFound is thrown to indicate the error.
    # 
    # \param key The key associated with the requested value.
    # 
    # \return A reference to the requested value. 
    # 
    # \throw Base.ItemNotFound if <em>AllowDefValues</em> is <tt>False</tt> and the map does not contain an entry with the specified key.
    # 
    def getValue(key: int) -> int: pass

    ##
    # \brief Returns a reference to the value associated with the specified key, or the value given by the second argument if the specified entry does not exist.
    # 
    # If the map contains an entry with the specified key, a reference to the associated value is returned. If the map does not contain the entry, the second argument <em>def_value</em> is returned.
    # 
    # \param key The key associated with the requested value.
    # \param def_value The value which is returned if the specified entry does not exist.
    # 
    # \return A reference to the requested or default value.
    # 
    def getValue(key: int, def_value: int) -> int: pass

    ##
    # \brief Removes the entry specified by <em>key</em> from the map.
    # 
    # \param key The key specifying the entry to remove.
    # 
    def removeEntry(key: int) -> bool: pass

    ##
    # \brief Inserts a new entry or updates the value of an existing entry with the specified key and value.
    # 
    # If the map does not already contain an entry whose key is the same as <em>key</em> then a new entry will be created. Otherwise, the value of the existing entry is updated with <em>value</em>. The return value is a dereferenceable iterator that points to the newly inserted or updated entry whose key is equivalent to the specified key.
    # 
    # \param key The key of the entry to insert or update.
    # \param value The value to be associated with <em>key</em>.
    # 
    # \return An iterator that points to the newly inserted or updated entry.
    # 
    def setEntry(key: int, value: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getKeys() -> object: pass

    ##
    # \brief 
    # \return 
    #
    def getValues() -> object: pass

    ##
    # \brief 
    # \return 
    #
    def getEntries() -> object: pass

    ##
    # \brief Tells whether the map contains an entry with the specified key.
    # 
    # \param key The key specifying the entry.
    # 
    # \return <tt>True</tt> if the map contains the specified entry, and <tt>False</tt> otherwise.
    # 
    def containsEntry(key: int) -> bool: pass

    ##
    # \brief Tries to insert a new entry with specified key and value into the map.
    # 
    # Inserts a new entry if and only if the map does not already contain an entry whose key is the same as the specified key. The return value is a pair <tt>P</tt>. <tt>P.first</tt> is an iterator pointing to the entry whose key is the same as the specified key. <tt>P.second</tt> is a boolean value which is <tt>True</tt> if <em>item</em> was actually inserted, and <tt>False</tt> if the map already contained an entry with the specified key.
    # 
    # \param key The key of the entry to insert.
    # \param value The value associated with <em>key</em>.
    # 
    # \return A std::pair consisting of an iterator pointing to an entry whose key is the same as <em>key</em> and a boolean value, which is <tt>True</tt> if the insertion of <em>item</em> was successful (an entry with the specified key did not already exist), and <tt>False</tt> otherwise.
    # 
    def insertEntry(key: int, value: int) -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def __getitem__(key: int) -> int: pass

    ##
    # \brief 
    # \param key 
    # \param value 
    #
    def __setitem__(key: int, value: int) -> None: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def __delitem__(key: int) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param self The \e %FeatureTypeHistogram instance this method is called upon.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(key: int) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == ft_hist</tt>.
    # \param self The \e %FeatureTypeHistogram instance this method is called upon.
    # \param ft_hist The \e %object instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(ft_hist: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != ft_hist</tt>.
    # \param self The \e %FeatureTypeHistogram instance this method is called upon.
    # \param ft_hist The \e %object instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(ft_hist: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self <= ft_hist</tt>.
    # \param self The \e %FeatureTypeHistogram instance this method is called upon.
    # \param ft_hist The \e %object instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __le__(ft_hist: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self >= ft_hist</tt>.
    # \param self The \e %FeatureTypeHistogram instance this method is called upon.
    # \param ft_hist The \e %object instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ge__(ft_hist: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self < ft_hist</tt>.
    # \param self The \e %FeatureTypeHistogram instance this method is called upon.
    # \param ft_hist The \e %object instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __lt__(ft_hist: object) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self > ft_hist</tt>.
    # \param self The \e %FeatureTypeHistogram instance this method is called upon.
    # \param ft_hist The \e %object instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __gt__(ft_hist: object) -> bool: pass

    objectID = property(getObjectID)

    keys = property(getKeys)

    values = property(getValues)

    entries = property(getEntries)

    size = property(getSize)

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
# \brief %Base class providing methods for the storage and lookup of control-parameter values.
# 
# The purpose of <tt>ControlParameterContainer</tt> is to provide a common facility for the storage and lookup of dynamic parameter values to subclasses which can be used to control their runtime-behaviour.
# 
# Control-parameters are stored in an associative map as Base.LookupKey / Base.Any pairs. The current number of entries can be queried with the method getNumParameters(). 
# 
# For the explicit assignment of control-parameter values the method setParameter() is provided which expects the key of the control-parameter as its first and the value to assign as the second argument. The availability of a value for a particular control-parameter can be tested by the method isParameterSet(). For the retrieval of control-parameter values the getParameter() method is provided which expects the key of the control-parameter as an argument. The method getParameterOrDefault() additionally allows to specify a default value that gets returned if an entry for the requested control-parameter does not exist.
# 
# <tt>ControlParameterContainer</tt> allows for an arrangement of instances in a tree-like hierarchy where each non-root instance has exactly one parent and zero or more children. In such hierarchies, a child container forwards requests for control-parameter values to their parents if they do not contain a local entry for a given control-parameter. The parent container is set and detached by the method setParent(). A <tt>ControlParameterContainer</tt> instance automatically keeps track of any links from and to other instances in the hierarchy and detaches any parent or child containers on destruction.
# 
# For the notification of client code about any changes that affect control-parameter values, the <tt>ControlParameterContainer</tt> interface provides three methods for the registration of callback functions:
#  - registerParameterChangedCallback() <br>
#  registers callback target functions that get invoked when the value of a control-parameter has changed
#  - registerParameterRemovedCallback() <br>
#  registers callback target functions that get invoked when a control-parameter entry has been removed
#  - and registerParentChangedCallback() <br>
#  is used to register callback target functions that get invoked when the parent container has been changed or was detached
# 
# Each of these methods returns a numeric identifier for the registered callback function. For callback unregistration purposes the methods unregisterParameterChangedCallback(), unregisterParameterRemovedCallback() and unregisterParentChangedCallback() are provided. These methods require the previously obtained numeric identifier of the callback to be passed as an argument.
# 
class ControlParameterContainer(Boost.Python.instance):

    ##
    # \brief Constructs an empty <tt>ControlParameterContainer</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Sets the value of the control-parameter specified by <em>key</em> to <em>val</em>.
    # 
    # If <em>val</em> is \c None, and a control-parameter entry for <em>key</em> exists, the entry gets erased (equivalent to removeParameter() with <em>key</em> as argument). Otherwise the control-parameter is assigned the specified value and any callback functions registered by registerParameterChangedCallback() will be invoked with <em>key</em> and <em>val</em> provided as arguments. Callbacks of affected direct and indirect children which do not have an entry for the specified control-parameter also get invoked. <br>
    # 
    # \param key The key of the control-parameter value to assign or remove.
    # \param val The value of the control-parameter.
    # 
    def setParameter(key: LookupKey, val: Any) -> None: pass

    ##
    # \brief Removes the entry for the control-parameter specified by <em>key</em>.
    # 
    # If an entry for the control-parameter specified by <em>key</em> exists, the entry is removed and any callback functions registered by registerParameterRemovedCallback() will be invoked with <em>key</em> provided as an argument. Callbacks of affected direct and indirect children which do not have an entry for the specified control-parameter also get invoked. <br>
    # 
    # \param key The key of the control-parameter entry to remove.
    # 
    # \return <tt>True</tt> if an entry for <em>key</em> could be found and was removed, and <tt>False</tt> otherwise.
    # 
    def removeParameter(key: LookupKey) -> bool: pass

    ##
    # \brief Returns the value of the control-parameter specified by <em>key</em>.
    # 
    # If the container contains an entry for the specified control-parameter, the stored value will be returned. If an entry for the control-parameter does not exist, the result depends on the arguments <em>throw_</em> and <em>local</em>.
    # 
    # If a parent container has been set and the argument <em>local</em> is <tt>False</tt>, the request is forwarded to the parent (which may also forward the request). Otherwise an empty Base.Any instance is returned if <em>_throw</em> is <tt>False</tt>, and a Base.ItemNotFound exception will be thrown if <em>_throw</em> is <tt>True</tt>.
    # 
    # \param key The key of the control-parameter value to return.
    # \param throw_ Specifies whether or not to throw a Base.ItemNotFound exception if an entry for the control-parameter does not exist.
    # \param local Specifies whether or not the request shall be forwarded to the parent container if a local entry for the control-parameter does not exist.
    # 
    # \return The stored control-parameter value or an empty Base.Any instance. 
    # 
    # \throw Base.ItemNotFound if an entry for the requested control-parameter value does not exist and <em>_throw</em> is <tt>True</tt>.
    # 
    def getParameter(key: LookupKey, throw_: bool = False, local: bool = False) -> Any: pass

    ##
    # \brief Returns the value of the control-parameter specified by <em>key</em> , or the default value <em>def_val</em> if an entry does not exist.
    # 
    # If the container contains an entry for the specified control-parameter, the stored value will be returned. If an entry for the control-parameter does not exist, a parent container has been set and the argument <em>local</em> is <tt>False</tt>, the call is forwarded to the parent (which may also forward the request). Otherwise the default value specified by <em>def_val</em> is returned.
    # 
    # \param key The key of the control-parameter for which to return the stored (or specified default) value.
    # \param def_val The default value that shall be returned if an entry for the specified control-parameter does not exist.
    # \param local Specifies whether or not the request shall be forwarded to the parent container if a local entry for the control-parameter does not exist.
    # 
    # \return The stored control-parameter value or the default specified by <em>def_val</em>. 
    # 
    # 
    # 
    def getParameterOrDefault(key: LookupKey, def_val: Any, local: bool = False) -> Any: pass

    ##
    # \brief Tells whether or not a value has been assigned to the control-parameter specified by <em>key</em>.
    # 
    # If the container does not contain an entry for the specified control-parameter, a parent container has been set and the argument <em>local</em> is <tt>False</tt>, the call is forwarded to the parent (which may also forward the call). Otherwise the result of the local search is returned.
    # 
    # \param key The key of the control-parameter.
    # \param local Specifies whether or not the query shall be forwarded to the parent container if a local entry for the control-parameter does not exist.
    # 
    # \return <tt>True</tt> if an entry for the specified control-parameter could be found, and <tt>False</tt> otherwise.
    # 
    def isParameterSet(key: LookupKey, local: bool = False) -> bool: pass

    ##
    # \brief Erases all container entries.
    # 
    # For each container entry, any callback functions registered by registerParameterRemovedCallback() will be invoked with the key of the removed control-parameter entry as an argument. Callbacks of affected direct and indirect children which do not have an entry for the erased control-parameter also get invoked.
    # 
    def clearParameters() -> None: pass

    ##
    # \brief Adds the control-parameter value entries of the <tt>ControlParameterContainer</tt> instance <em>cntnr</em>.
    # 
    # %Any control-parameters which have no corresponding entry in <em>cntnr</em> are left unchanged. Otherwise the value of the local control-parameter gets overwritten by the value stored in <em>cntnr</em> and any callback functions registered by registerParameterChangedCallback() will be invoked with <em>key</em> and <em>value</em> provided as arguments. Callbacks of affected direct and indirect children which do not have an entry for the specified control-parameter also get invoked. <br>
    # 
    # \param cntnr The <tt>ControlParameterContainer</tt> instance providing the control-parameter entries to add.
    # 
    def addParameters(cntnr: ControlParameterContainer) -> None: pass

    ##
    # \brief Replaces the current control-parameter entries by a copy of the entries in <em>cntnr</em>.
    # 
    # The assignment is equivalent to first erasing all entries by calling clearParameters() and then calling setParameter() for each key/value entry in <em>cntnr</em>.
    # 
    # \param cntnr The <tt>ControlParameterContainer</tt> instance providing the control-parameter entries to copy.
    # 
    def copyParameters(cntnr: ControlParameterContainer) -> None: pass

    ##
    # \brief Returns the number of container entries.
    # 
    # \return The number of container entries.
    # 
    def getNumParameters() -> int: pass

    ##
    # \brief Registers a callback target function that gets invoked when the value of a control-parameter has changed.
    # 
    # \param func A Base.VoidLookupKeyFunctor instance wrapping the target function.
    # 
    # \return An identifier for the registered callback.
    # 
    def registerParameterChangedCallback(func: VoidLookupKeyAnyFunctor) -> int: pass

    ##
    # \brief Unregisters the callback specified by <em>id</em>.
    # 
    # If a registered callback with the identifier <em>id</em> does not exist, the method has no effect.
    # 
    # \param id The identifier of the callback to unregister.
    # 
    def unregisterParameterChangedCallback(id: int) -> None: pass

    ##
    # \brief Registers a callback target function that gets invoked when a control-parameter entry has been removed.
    # 
    # \param func A Base.VoidLookupKeyFunctor instance wrapping the target function.
    # 
    # \return An identifier for the registered callback.
    # 
    def registerParameterRemovedCallback(func: VoidLookupKeyFunctor) -> int: pass

    ##
    # \brief Unregisters the callback specified by <em>id</em>.
    # 
    # If a registered callback with the identifier <em>id</em> does not exist, the method has no effect.
    # 
    # \param id The identifier of the callback to unregister.
    # 
    def unregisterParameterRemovedCallback(id: int) -> None: pass

    ##
    # \brief Registers a callback target function that gets invoked when the parent container has been changed or was detached.
    # 
    # \param func A Base.VoidFunctor instance wrapping the target function.
    # 
    # \return An identifier for the registered callback.
    # 
    def registerParentChangedCallback(func: VoidFunctor) -> int: pass

    ##
    # \brief Unregisters the callback specified by <em>id</em>.
    # 
    # If a registered callback with the identifier <em>id</em> does not exist, the method has no effect.
    # 
    # \param id The identifier of the callback to unregister.
    # 
    def unregisterParentChangedCallback(id: int) -> None: pass

    ##
    # \brief Returns the parent control-parameter container.
    # 
    # \return A reference to the parent control-parameter container, or <tt>None</tt> if no parent container has been set. 
    # 
    # \see setParent()
    # 
    def getParent() -> ControlParameterContainer: pass

    ##
    # \brief Sets or removes the parent control-parameter container used to resolve requests for missing entries.
    # 
    # A control-parameter container that has been set as a parent gets used whenever a request for a control-parameter value cannot be satisfied locally by the container itself. That is, if a key/value entry for a given control-parameter does not exist, the request is simply forwarded to the parent container (which may also forward the request).
    # 
    # %Any callback functions registered by registerParentChangedCallback() will be invoked after the new parent container has been set (or the old container was detached by providing <tt>None</tt>). Callbacks of any direct and indirect children also get invoked.
    # 
    # \param cntnr A reference to the parent control-parameter container or <tt>None</tt>. If the reference equals <tt>None</tt>, the currently set parent container (if any) gets detached.
    # 
    def setParent(cntnr: ControlParameterContainer) -> None: pass

    ##
    # \brief Returns a list containing the keys of the current control-parameter entries.
    # \return A list containing the requested control-parameter keys.
    # 
    def getParameterKeys() -> list: pass

    ##
    # \brief Returns a list containing the values of the current control-parameter entries.
    # \return A list containing the requested control-parameter values.
    # 
    def getParameterValues() -> list: pass

    ##
    # \brief Returns a reference to itself.
    # 
    # \return \a self.
    # 
    def getParameters() -> list: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c ControlParameterContainer instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c ControlParameterContainer instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Returns the value of the control-parameter specified by <em>key</em>.
    # 
    # If the container contains an entry for the specified control-parameter, the stored value will be returned. Otherwise a Base.ItemNotFound exception will be thrown.
    # 
    # 
    # 
    # \param key The key of the control-parameter value to return.
    # 
    # 
    # 
    # \return The stored control-parameter value. 
    # 
    # \throw Base.ItemNotFound if an entry for the requested control-parameter value does not exist.
    # 
    def __getitem__(key: LookupKey) -> Any: pass

    ##
    # \brief Sets the value of the control-parameter specified by <em>key</em> to <em>val</em>.
    # 
    # If <em>val</em> is of type Base.Any and empty, i.e. the method Base.Any.isEmpty() returns <tt>True</tt>, and a control-parameter entry for <em>key</em> exists, the entry gets erased (equivalent to removeParameter() with <em>key</em> as argument). Otherwise the control-parameter is assigned the specified value and any callback functions registered by registerParameterChangedCallback() will be invoked with <em>key</em> and <em>val</em> provided as arguments. Callbacks of affected direct and indirect children which do not have an entry for the specified control-parameter also get invoked. <br>
    # 
    # \param key The key of the control-parameter value to assign or remove.
    # \param val The value of the control-parameter.
    # 
    def __setitem__(key: LookupKey, val: Any) -> None: pass

    ##
    # \brief Removes the entry for the control-parameter specified by <em>key</em>.
    # 
    # If an entry for the control-parameter specified by <em>key</em> exists, the entry is removed and any callback functions registered by registerParameterRemovedCallback() will be invoked with <em>key</em> provided as an argument. Callbacks of affected direct and indirect children which do not have an entry for the specified control-parameter also get invoked. <br>
    # 
    # \param key The key of the control-parameter entry to remove.
    # 
    # \return <tt>True</tt> if an entry for <em>key</em> could be found and was removed, and <tt>False</tt> otherwise.
    # 
    def __delitem__(key: LookupKey) -> bool: pass

    ##
    # \brief Tells whether or not a value has been assigned to the control-parameter specified by <em>key</em>.
    # 
    # 
    # 
    # \param key The key of the control-parameter.
    # 
    # 
    # \return <tt>True</tt> if an entry for the specified control-parameter could be found, and <tt>False</tt> otherwise.
    # 
    def __contains__(key: LookupKey) -> bool: pass

    ##
    # \brief Returns the number of container entries.
    # 
    # \return The number of container entries.
    # 
    def __len__() -> int: pass

    objectID = property(getObjectID)

    parent = property(getParent, setParent)

    parameterKeys = property(getParameterKeys)

    parameterValues = property(getParameterValues)

    parameters = property(getParameters)

    numParameters = property(getNumParameters)

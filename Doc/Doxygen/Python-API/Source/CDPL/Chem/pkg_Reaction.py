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
class Reaction(CDPL.Base.PropertyContainer):

    ##
    # \brief 
    #
    class ComponentSequence(Boost.Python.instance):

        ##
        # \brief Returns the result of the membership test operation <tt>mol in self</tt>.
        # \param self The \e %ComponentSequence instance this method is called upon.
        # \param mol The value to test for membership.
        # \return The result of the membership test operation.
        #
        def __contains__(self: ComponentSequence, mol: Molecule) -> bool: pass

        ##
        # \brief 
        # \param self The \e %ComponentSequence instance this method is called upon.
        # \return 
        #
        def __len__(self: ComponentSequence) -> int: pass

        ##
        # \brief 
        # \param self The \e %ComponentSequence instance this method is called upon.
        # \param idx 
        #
        def __delitem__(self: ComponentSequence, idx: int) -> None: pass

        ##
        # \brief 
        # \param self The \e %ComponentSequence instance this method is called upon.
        # \param idx 
        # \return 
        #
        def __getitem__(self: ComponentSequence, idx: int) -> Molecule: pass

    ##
    # \brief Initializes the \e %Reaction instance.
    # \param self The \e %Reaction instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    #
    def clear(self: Reaction) -> None: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \param role 
    # \return 
    #
    def addComponent(self: Reaction, role: int) -> Molecule: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \param mol 
    # \return 
    #
    def containsComponent(self: Reaction, mol: Molecule) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \param mol 
    # \return 
    #
    def getComponentRole(self: Reaction, mol: Molecule) -> int: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \param mol 
    # \return 
    #
    def getComponentIndex(self: Reaction, mol: Molecule) -> int: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \param role 
    # \return 
    #
    def getNumComponents(self: Reaction, role: int) -> int: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \return 
    #
    def getNumComponents(self: Reaction) -> int: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \param idx 
    # \param role 
    # \return 
    #
    def getComponent(self: Reaction, idx: int, role: int) -> Molecule: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getComponent(self: Reaction, idx: int) -> Molecule: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \param role 
    #
    def removeComponents(self: Reaction, role: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \param idx 
    # \param role 
    #
    def removeComponent(self: Reaction, idx: int, role: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \param idx 
    #
    def removeComponent(self: Reaction, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \param role1 
    # \param role2 
    #
    def swapComponentRoles(self: Reaction, role1: int, role2: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \return 
    #
    def clone(self: Reaction) -> Reaction: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \param rxn 
    #
    def copy(self: Reaction, rxn: Reaction) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Reaction instance \a rxn.
    # \param self The \e %Reaction instance this method is called upon.
    # \param rxn The \e %Reaction instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: Reaction, rxn: Reaction) -> Reaction: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \return 
    #
    def getReactants(self: Reaction) -> ComponentSequence: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \return 
    #
    def getAgents(self: Reaction) -> ComponentSequence: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \return 
    #
    def getProducts(self: Reaction) -> ComponentSequence: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \param key 
    # \param value 
    #
    def setProperty(self: Reaction, key: CDPL.Base.LookupKey, value: CDPL.Base.Variant) -> None: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \param key 
    # \return 
    #
    def removeProperty(self: Reaction, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \param key 
    # \param throw_ 
    # \return 
    #
    def getProperty(self: Reaction, key: CDPL.Base.LookupKey, throw_: bool = False) -> CDPL.Base.Variant: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \param key 
    # \return 
    #
    def isPropertySet(self: Reaction, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    #
    def clearProperties(self: Reaction) -> None: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \param cntnr 
    #
    def addProperties(self: PropertyContainer, cntnr: CDPL.Base.PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \param cntnr 
    #
    def copyProperties(self: PropertyContainer, cntnr: CDPL.Base.PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \param cntnr 
    #
    def swap(self: Reaction, cntnr: CDPL.Base.PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \param idx 
    # \return 
    #
    def __getitem__(self: Reaction, idx: int) -> Molecule: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \param key 
    # \return 
    #
    def __getitem__(self: PropertyContainer, key: CDPL.Base.LookupKey) -> CDPL.Base.Variant: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \param idx 
    #
    def __delitem__(self: Reaction, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \param key 
    # \return 
    #
    def __delitem__(self: Reaction, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>mol in self</tt>.
    # \param self The \e %Reaction instance this method is called upon.
    # \param mol The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(self: Reaction, mol: Molecule) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param self The \e %Reaction instance this method is called upon.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(self: Reaction, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \param key 
    # \param value 
    #
    def __setitem__(self: Reaction, key: CDPL.Base.LookupKey, value: CDPL.Base.Variant) -> None: pass

    ##
    # \brief 
    # \param self The \e %Reaction instance this method is called upon.
    # \return 
    #
    def __len__(self: Reaction) -> int: pass

    ##
    # \brief 
    #
    reactants = property(getReactants)

    ##
    # \brief 
    #
    agents = property(getAgents)

    ##
    # \brief 
    #
    products = property(getProducts)

    ##
    # \brief 
    #
    numComponents = property(getNumComponents)

    ##
    # \brief FIXME!
    #
    numReactants = property(getNumReactants)

    ##
    # \brief FIXME!
    #
    numAgents = property(getNumAgents)

    ##
    # \brief FIXME!
    #
    numProducts = property(getNumProducts)

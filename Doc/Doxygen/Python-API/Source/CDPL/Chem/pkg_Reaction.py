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
# \brief 
#
class Reaction(CDPL.Base.PropertyContainer):

    ##
    # \brief 
    #
    class ComponentSequence(Boost.Python.instance):

        ##
        # \brief Returns the result of the membership test operation <tt>mol in self</tt>.
        # \param mol The value to test for membership.
        # \return The result of the membership test operation.
        #
        def __contains__(mol: Molecule) -> bool: pass

        ##
        # \brief 
        # \return 
        #
        def __len__() -> int: pass

        ##
        # \brief 
        # \param idx 
        #
        def __delitem__(idx: int) -> None: pass

        ##
        # \brief 
        # \param idx 
        # \return 
        #
        def __getitem__(idx: int) -> Molecule: pass

    ##
    # \brief Initializes the \e %Reaction instance.
    #
    def __init__() -> None: pass

    ##
    # \brief 
    #
    def clear() -> None: pass

    ##
    # \brief 
    # \param role 
    # \return 
    #
    def addComponent(role: int) -> Molecule: pass

    ##
    # \brief 
    # \param mol 
    # \return 
    #
    def containsComponent(mol: Molecule) -> bool: pass

    ##
    # \brief 
    # \param mol 
    # \return 
    #
    def getComponentRole(mol: Molecule) -> int: pass

    ##
    # \brief 
    # \param mol 
    # \return 
    #
    def getComponentIndex(mol: Molecule) -> int: pass

    ##
    # \brief 
    # \param role 
    # \return 
    #
    def getNumComponents(role: int) -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getNumComponents() -> int: pass

    ##
    # \brief 
    # \param idx 
    # \param role 
    # \return 
    #
    def getComponent(idx: int, role: int) -> Molecule: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getComponent(idx: int) -> Molecule: pass

    ##
    # \brief 
    # \param role 
    #
    def removeComponents(role: int) -> None: pass

    ##
    # \brief 
    # \param idx 
    # \param role 
    #
    def removeComponent(idx: int, role: int) -> None: pass

    ##
    # \brief 
    # \param idx 
    #
    def removeComponent(idx: int) -> None: pass

    ##
    # \brief 
    # \param role1 
    # \param role2 
    #
    def swapComponentRoles(role1: int, role2: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def clone() -> Reaction: pass

    ##
    # \brief 
    # \param rxn 
    #
    def copy(rxn: Reaction) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Reaction instance \a rxn.
    # \param rxn The \e %Reaction instance to copy.
    # \return \a self
    #
    def assign(rxn: Reaction) -> Reaction: pass

    ##
    # \brief 
    # \return 
    #
    def getReactants() -> ComponentSequence: pass

    ##
    # \brief 
    # \return 
    #
    def getAgents() -> ComponentSequence: pass

    ##
    # \brief 
    # \return 
    #
    def getProducts() -> ComponentSequence: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def __getitem__(idx: int) -> Molecule: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def __getitem__(key: CDPL.Base.LookupKey) -> CDPL.Base.Variant: pass

    ##
    # \brief 
    # \param idx 
    #
    def __delitem__(idx: int) -> None: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def __delitem__(key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>mol in self</tt>.
    # \param mol The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(mol: Molecule) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param key 
    # \param value 
    #
    def __setitem__(key: CDPL.Base.LookupKey, value: CDPL.Base.Variant) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

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

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
# \brief Reactor.
# 
class Reactor(Boost.Python.instance):

    ##
    # \brief Constructs and initializes a <tt>Reactor</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs and initializes a <tt>Reactor</tt> instance for the specified reaction pattern.
    # 
    # \param rxn_pattern The reaction pattern describing the transformation of reactants to products.
    # 
    def __init__(rxn_pattern: Reaction) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %Reactor instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Reactor instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Allows to specify a new reaction pattern for the transformation of reactants to products.
    # 
    # \param rxn_pattern The reaction pattern describing the transformation of reactants to products.
    # 
    def setReactionPattern(rxn_pattern: Reaction) -> None: pass

    ##
    # \brief Perceives all possible reaction-sites on the reactants of the given reaction target where the specified reaction pattern can be applied.
    # 
    # The specified Chem.Reaction instance <em>rxn_target</em> serves both as a provider for the starting materials (reactant components) in a later reaction transformation (see performReaction()) as well as a container for the generated reaction products.
    # 
    # \param rxn_target The reaction target providing the reactants to be transformed.
    # 
    # \return <tt>True</tt> if matching reaction-sites were found, and <tt>False</tt> otherwise. 
    # 
    # \note Any reaction-site mappings that were recorded in a previous call to findReactionSites() will be discarded. 
    # 
    # \see performReaction()
    # 
    def findReactionSites(rxn_target: Reaction) -> bool: pass

    ##
    # \brief Returns the number of recorded reactions-sites in the last call to findReactionSites().
    # 
    # \return The number of recorded reactions-sites in the last call to findReactionSites().
    # 
    def getNumReactionSites() -> int: pass

    ##
    # \brief Returns a reference to the stored reaction-site data object at index <em>idx</em>.
    # 
    # \param idx The zero-based index of the reaction-site data object to return.
    # 
    # \return A reference to the reaction-site data object at index <em>idx</em>. 
    # 
    # \throw Base.IndexError if no reactions-site data objects are available or <em>idx</em> is not in the range [0, getNumReactionSites() - 1].
    # 
    def getReactionSite(idx: int) -> AtomBondMapping: pass

    ##
    # \brief Performs a transformation of the target reactants to corresponding products at the specified reaction-site.
    # 
    # The reactant components of the Chem.Reaction object specified in a prior call to findReactionSites() serve as starting materials for the reaction transformation into corresponding product molecules (according to the set reaction pattern). The input molecules are left unchanged by the transformation. New molecules will be generated that are directly stored as the product components of the given target reaction object. Note that the product molecules generated in a previous call will not be discarded and are still accessible after new products have been generated.
    # 
    # \param rxn_site Specifies the reaction-site where the transformation shall take place.
    # 
    # \see setReactionPattern(), findReactionSites()
    # 
    def performReaction(rxn_site: AtomBondMapping) -> None: pass

    objectID = property(getObjectID)

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
# \brief Abstract base class for all tautomerization rule implementations used by the Chem.TautomerGenerator.
# 
class TautomerizationRule(Boost.Python.instance):

    ##
    # \brief Initializes the \c %TautomerizationRule instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %TautomerizationRule instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %TautomerizationRule instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Returns the rule's identifier (see Chem.TautomerizationType).
    # 
    # \return The rule identifier.
    # 
    def getID() -> int: pass

    ##
    # \brief Sets the parent molecular graph for which the rule is to enumerate tautomers.
    # 
    # \param parent_molgraph The molecular graph to be tautomerized.
    # 
    # \return <tt>True</tt> if the rule applies to <em>parent_molgraph</em> and the iteration has been initialized, and <tt>False</tt> otherwise.
    # 
    def setup(parent_molgraph: MolecularGraph) -> bool: pass

    ##
    # \brief Generates the next tautomer.
    # 
    # \param tautomer The tautomer output molecule object.
    # 
    # \return <tt>True</tt> if a tautomer was generated, <tt>False</tt> if no more tautomers are available.
    # 
    def generate(tautomer: Molecule) -> bool: pass

    ##
    # \brief Returns a deep copy of this rule instance.
    # 
    # \return A shared reference to the cloned rule.
    # 
    def clone() -> TautomerizationRule: pass

    objectID = property(getObjectID)

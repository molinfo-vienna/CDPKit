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
# \brief A generic boolean expression interface for the implementation of query/target object equivalence tests in molecular graph matching algorithms.
# 
# The <tt>AtomMatchExpression</tt> interface abstracts the task of checking a set of constraints on the attributes of target objects when performing query object equivalence tests in molecular graph matching procedures. Subclasses of <tt>AtomMatchExpression</tt> must override one (or all, if required) of the provided function call operators to implement the logic of the constraint checks. The first form of the two operators gets called in the pre-mapping stage of the graph matching algorithm where all feasible query/target object pairings are determined. In this pre-mapping stage all sorts of query constraints can be checked that are invariant with respect to the final mapping between any of the other query and target objects. The second type of operator is invoked immediately after a complete graph mapping solution has been found and can be used to re-evaluate the validity of a given query/target object pairing in the context of the provided matching result. As soon as a pairing is found to be invalid, the current mapping solution is rejected and the algorithm proceeds to find the next possible query to target graph mapping (if any). For efficiency reasons, subclasses of <tt>AtomMatchExpression</tt> which implement the post-mapping function call operator must explicitly enable its invocation by additionally overriding the AtomMatchExpression.requiresAtomBondMapping() method. Its implementation simply has to return <tt>True</tt> (the default implementation returns <tt>False</tt>) to request the invocation of the operator.
# 
class AtomMatchExpression(Boost.Python.instance):

    ##
    # \brief Initializes the \e %AtomMatchExpression instance.
    # \param self The \e %AtomMatchExpression instance to initialize.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %AtomMatchExpression instance this method is called upon.
    # 
    # Different Python \e %AtomMatchExpression instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %AtomMatchExpression instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Tells whether the expression must be reevaluated after a query to target atom/bond mapping candidate has been found.
    # 
    # \return <tt>True</tt> if the expression needs to be evaluated again after a query to target atom/bond mapping candidate has been found, and <tt>False</tt> otherwise. 
    # 
    # \note The default implementation returns <tt>False</tt>.
    # 
    def requiresAtomBondMapping() -> bool: pass

    ##
    # \brief Performs an evaluation of the expression for the given query and target objects.
    # 
    # \param query_atom The query atom.
    # \param query_molgraph The query molecular graph.
    # \param target_atom The target atom.
    # \param target_molgraph The target molecular graph.
    # \param aux_data Provides auxiliary information for the evaluation of the expression.
    # 
    # \return The result of the expression evaluation for the specified query and target objects. 
    # 
    # \note The default implementation returns <tt>True</tt>.
    # 
    def __call__(query_atom: Atom, query_molgraph: MolecularGraph, target_atom: Atom, target_molgraph: MolecularGraph, aux_data: CDPL.Base.Any) -> bool: pass

    ##
    # \brief Performs an evaluation of the expression for the given query and target objects under consideration of the provided candidate atom/bond mapping.
    # 
    # \param query_atom The query atom.
    # \param query_molgraph The query molecular graph.
    # \param target_atom The target atom.
    # \param target_molgraph The target molecular graph.
    # \param mapping The current query to target atom/bond mapping candidate to evaluate.
    # \param aux_data Provides auxiliary information for the evaluation of the expression.
    # 
    # \return The result of the expression evaluation for the specified query and target objects. 
    # 
    # \note The default implementation returns the result of <tt>__call__(query_atom, query_molgraph, target_atom, target_molgraph, aux_data)</tt>.
    # 
    def __call__(query_atom: Atom, query_molgraph: MolecularGraph, target_atom: Atom, target_molgraph: MolecularGraph, mapping: AtomBondMapping, aux_data: CDPL.Base.Any) -> bool: pass

    objectID = property(getObjectID)

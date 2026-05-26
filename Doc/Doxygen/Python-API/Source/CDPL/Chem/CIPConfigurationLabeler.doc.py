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
# \brief Assigns Cahn-Ingold-Prelog (CIP) configuration labels to stereogenic atoms and bonds of a molecular graph.
# 
# After calling setup() for a molecular graph the per-atom or per-bond CIP descriptor (<em>R</em> / <em>S</em> / <em>E</em> / <em>Z</em> / <em>r</em> / <em>s</em> / undefined) can be queried via the getLabel() overloads. The implementation is largely based on John Mayfield's Java implementation of the CIP sequence rules [\ref CIPJM].
# 
# \see Chem.CIPDescriptor 
# 
# \since 1.1
# 
class CIPConfigurationLabeler(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>CIPConfigurationLabeler</tt> instance without an associated molecular graph.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %CIPConfigurationLabeler instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %CIPConfigurationLabeler instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the state of this labeler by a copy of the state of <em>labeler</em>.
    # 
    # \param labeler The source <tt>CIPConfigurationLabeler</tt>.
    # 
    # \return \a self
    # 
    def assign(labeler: CIPConfigurationLabeler) -> CIPConfigurationLabeler: pass

    ##
    # \brief Prepares the labeler to assign CIP descriptors for the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph to label.
    # 
    def setup(molgraph: MolecularGraph) -> None: pass

    ##
    # \brief Returns the CIP descriptor of the stereogenic atom <em>atom</em>.
    # 
    # \param atom The atom whose CIP descriptor is queried.
    # 
    # \return One of the Chem.CIPDescriptor values.
    # 
    def getLabel(atom: Atom) -> int: pass

    ##
    # \brief Returns the CIP descriptor of the stereogenic bond <em>bond</em>.
    # 
    # \param bond The bond whose CIP descriptor is queried.
    # 
    # \return One of the Chem.CIPDescriptor values.
    # 
    def getLabel(bond: Bond) -> int: pass

    objectID = property(getObjectID)

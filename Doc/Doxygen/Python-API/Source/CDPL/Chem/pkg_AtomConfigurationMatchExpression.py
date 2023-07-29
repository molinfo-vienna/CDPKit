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
# \brief AtomConfigurationMatchExpression.
# 
class AtomConfigurationMatchExpression(AtomMatchExpression):

    ##
    # \brief Initializes the \e %AtomConfigurationMatchExpression instance.
    # \param expr 
    # 
    def __init__(expr: AtomConfigurationMatchExpression) -> None: pass

    ##
    # \brief Constructs an <tt>AtomConfigurationMatchExpression</tt> instance for the specified matching mode and stereo configuration constraints.
    # 
    # \param query_stereo_descr The descriptor object specifying the query atom's stereo configuration reference atoms and associated configuration constraints on matching target atoms.
    # \param query_atom The atom for which this <tt>AtomConfigurationMatchExpression</tt> instance gets constructed.
    # \param not_match Specifies whether the stereo configuration of a target atom actually has to match (<tt>True</tt>) or <em>not</em> match (<tt>False</tt>) the query configuration constraints.
    # \param allow_part_maps Specifies whether or not a target atom that has an incomplete query to target neighbor atom/bond mapping shall be considered to match the query configuration constraints. This is important for maximum common substructure searches where the provided query to target atom mapping may not be complete.
    # 
    def __init__(query_stereo_descr: StereoDescriptor, query_atom: Atom, not_match: bool, allow_part_maps: bool) -> None: pass

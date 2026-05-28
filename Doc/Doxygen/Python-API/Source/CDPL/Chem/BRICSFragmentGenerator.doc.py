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
# \brief Chem.FragmentGenerator preconfigured with the 16 <em>BRICS</em> bond-cleavage rules and the associated exclude patterns for combinatorial fragmentation of organic molecules.
# 
# The rule and exclude-pattern set follows the original <em>Breaking of Retrosynthetically Interesting Chemical Substructures</em> publication. Each rule has the corresponding Chem.BRICSRuleID value.
# 
# \see [\ref BRICS]
# 
class BRICSFragmentGenerator(FragmentGenerator):

    ##
    # \brief Constructs the <tt>BRICSFragmentGenerator</tt> instance with the full BRICS rule and exclude-pattern set registered.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %BRICSFragmentGenerator instance \a gen.
    # \param gen The \c %BRICSFragmentGenerator instance to copy.
    # 
    def __init__(gen: BRICSFragmentGenerator) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %BRICSFragmentGenerator instance \a gen.
    # \param gen The \c %BRICSFragmentGenerator instance to copy.
    # \return \a self
    # 
    def assign(gen: BRICSFragmentGenerator) -> BRICSFragmentGenerator: pass

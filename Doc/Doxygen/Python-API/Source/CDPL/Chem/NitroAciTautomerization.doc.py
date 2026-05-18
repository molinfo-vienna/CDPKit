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
# \brief Implementation of the nitro &harr; aci-nitro tautomerization rule.
# 
# The rule is registered with TautomerizationType.NITRO_ACI and uses PatternBasedTautomerizationRule to encode the SMARTS patterns and bond-order transformations required for the interconversion of nitro and aci-nitro tautomers.
# 
class NitroAciTautomerization(PatternBasedTautomerizationRule):

    ##
    # \brief Constructs the <tt>NitroAciTautomerization</tt> instance and registers the SMARTS patterns and bond-order changes of the rule.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %NitroAciTautomerization instance \a rule.
    # \param rule The \c %NitroAciTautomerization instance to copy.
    # 
    def __init__(rule: NitroAciTautomerization) -> None: pass

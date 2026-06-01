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
# \brief Chem.TautomerGenerator preconfigured with the standard CDPKit tautomerization rules.
# 
# <tt>DefaultTautomerGenerator</tt> registers the following rules on construction (in order): Chem.GenericHydrogen13ShiftTautomerization, Chem.GenericHydrogen15ShiftTautomerization, Chem.KeteneYnolTautomerization, Chem.PhosphinicAcidTautomerization, Chem.SulfenicAcidTautomerization, and Chem.ConjugatedRingBondPatternSwitching.
# 
class DefaultTautomerGenerator(TautomerGenerator):

    ##
    # \brief Constructs the <tt>DefaultTautomerGenerator</tt> instance and registers the standard set of tautomerization rules.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %DefaultTautomerGenerator instance \a gen.
    # \param gen The \c %DefaultTautomerGenerator instance to copy.
    # 
    def __init__(gen: DefaultTautomerGenerator) -> None: pass

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
# \brief MorganNumberingCalculator.
# 
# \see [\ref MOCAN]
# 
class MorganNumberingCalculator(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>MorganNumberingCalculator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs the <tt>MorganNumberingCalculator</tt> instance and performs a canonical numbering of the atoms in the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to perform the canonical numbering.
    # \param numbering An array that contains the calculated canonical atom numbering. The numbers are stored in the same order as the atoms appear in the atom list of the molecular graph (i.e. the canonical number of an atom is accessible via its index).
    # 
    def __init__(molgraph: MolecularGraph, numbering: CDPL.Util.STArray) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %MorganNumberingCalculator instance this method is called upon.
    # 
    # Different Python \e %MorganNumberingCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MorganNumberingCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Performs a canonical numbering of the atoms in the molecular graph <em>molgraph</em>.
    # 
    # \param molgraph The molecular graph for which to perform the canonical numbering.
    # \param numbering An array that contains the calculated canonical atom numbering. The numbers are stored in the same order as the atoms appear in the atom list of the molecular graph (i.e. the canonical number of an atom is accessible via its index).
    # 
    def calculate(molgraph: MolecularGraph, numbering: CDPL.Util.STArray) -> None: pass

    objectID = property(getObjectID)

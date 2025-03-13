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
# \brief PEOESigmaChargeCalculator.
# 
# \see [\ref PEOE]
# 
class PEOESigmaChargeCalculator(Boost.Python.instance):

    ##
    # \brief 
    #
    DEF_NUM_ITERATIONS = 20

    ##
    # \brief 
    #
    DEF_DAMPING_FACTOR = 0.48

    ##
    # \brief Constructs the <tt>PEOESigmaChargeCalculator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs the <tt>PEOESigmaChargeCalculator</tt> instance and calculates the sigma charges and electronegativities of the atoms in the molecular graph <em>molgraph</em> by the <em>PEOE</em> method.
    # 
    # \param molgraph The molecular graph for which to perform the calculations.
    # 
    def __init__(molgraph: Chem.MolecularGraph) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %PEOESigmaChargeCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %PEOESigmaChargeCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Allows to specify the number of charge shifting iterations that have to be performed.
    # 
    # \param num_iter The number of iterations to perform.
    # 
    # \note By default, PEOESigmaChargeCalculator.DEF_NUM_ITERATIONS iterations are performed.
    # 
    def setNumIterations(num_iter: int) -> None: pass

    ##
    # \brief Allows to specify the applied damping factor.
    # 
    # \param factor The damping factor to apply.
    # 
    # \note The default damping factor is specified by the constant PEOESigmaChargeCalculator.DEF_DAMPING_FACTOR.
    # 
    def setDampingFactor(factor: float) -> None: pass

    ##
    # \brief Returns the number of performed charge shifting iterations.
    # 
    # \return The number of performed iterations.
    # 
    def getNumIterations() -> int: pass

    ##
    # \brief Returns the applied damping factor.
    # 
    # \return The applied damping factor.
    # 
    def getDampingFactor() -> float: pass

    ##
    # \brief Calculates the sigma charges and electronegativities of the atoms in the molecular graph <em>molgraph</em> by the <em>PEOE</em> method.
    # 
    # \param molgraph The molecular graph for which to perform the calculations. <br>
    # 
    def calculate(molgraph: Chem.MolecularGraph) -> None: pass

    ##
    # \brief Returns the calculated sigma charge of the atom with index <em>idx</em>.
    # 
    # \param idx The index of the atom for which to return the charge.
    # 
    # \throw Base.IndexError If <em>idx</em> is not in the range <em>[0, NA - 1]</em> where <em>NA</em> is the number of atoms of the molecular graph for which the calculations have been performed.
    # 
    def getCharge(idx: int) -> float: pass

    ##
    # \brief Returns the calculated sigma electronegativity of the atom with index <em>idx</em>.
    # 
    # \param idx The index of the atom for which to return the electronegativity.
    # 
    # \throw Base.IndexError If <em>idx</em> is not in the range <em>[0, NA - 1]</em> where <em>NA</em> is the number of atoms of the molecular graph for which the calculations have been performed.
    # 
    def getElectronegativity(idx: int) -> float: pass

    objectID = property(getObjectID)

    numIterations = property(getNumIterations, setNumIterations)

    dampingFactor = property(getDampingFactor, setDampingFactor)

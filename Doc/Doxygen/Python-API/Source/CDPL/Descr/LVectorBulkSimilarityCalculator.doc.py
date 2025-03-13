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
# \brief 
#
class LVectorBulkSimilarityCalculator(Boost.Python.instance):

    ##
    # \brief Initializes the \e %LVectorBulkSimilarityCalculator instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %LVectorBulkSimilarityCalculator instance \a calc.
    # \param calc The \e %LVectorBulkSimilarityCalculator instance to copy.
    # 
    def __init__(calc: LVectorBulkSimilarityCalculator) -> None: pass

    ##
    # \brief Initializes the \e %LVectorBulkSimilarityCalculator instance.
    # \param sim_func 
    # 
    def __init__(sim_func: DoubleLVector2Functor) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %LVectorBulkSimilarityCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %LVectorBulkSimilarityCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %LVectorBulkSimilarityCalculator instance \a calc.
    # \param calc The \c %LVectorBulkSimilarityCalculator instance to copy.
    # \return \a self
    # 
    def assign(calc: LVectorBulkSimilarityCalculator) -> LVectorBulkSimilarityCalculator: pass

    ##
    # \brief 
    # \param func 
    #
    def setSimilarityFunction(func: DoubleLVector2Functor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getSimilarityFunction() -> DoubleLVector2Functor: pass

    ##
    # \brief 
    #
    def clear() -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumDescriptors() -> int: pass

    ##
    # \brief 
    # \param descr 
    #
    def addDescriptor(descr: Math.LVector) -> None: pass

    ##
    # \brief 
    # \param descr 
    # \return 
    #
    def containsDescriptor(descr: Math.LVector) -> bool: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getDescriptor(idx: int) -> Math.LVector: pass

    ##
    # \brief 
    # \param idx 
    #
    def removeDescriptor(idx: int) -> None: pass

    ##
    # \brief 
    # \param descr 
    # \param sort 
    # \param sort_desc 
    #
    def calculate(descr: Math.LVector, sort: bool = False, sort_desc: bool = True) -> None: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getResult(idx: int) -> tuple: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getSimilarity(idx: int) -> float: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getDescriptorIndex(idx: int) -> int: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def __getitem__(idx: int) -> tuple: pass

    ##
    # \brief Returns the result of the membership test operation <tt>descr in self</tt>.
    # \param descr The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(descr: Math.LVector) -> bool: pass

    objectID = property(getObjectID)

    numDescriptors = property(getNumDescriptors)

    similarityFunc = property(getSimilarityFunction, setSimilarityFunction)

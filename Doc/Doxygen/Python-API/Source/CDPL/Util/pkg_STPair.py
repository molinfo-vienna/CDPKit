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
class STPair(Boost.Python.instance):

    ##
    # \brief Initializes the \e %STPair instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %STPair instance.
    # \param pair 
    #
    def __init__(pair: STPair) -> None: pass

    ##
    # \brief Initializes the \e %STPair instance.
    # \param first 
    # \param second 
    #
    def __init__(first: int, second: int) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %STPair instance \a array.
    # \param array The \e %STPair instance to copy.
    # \return \a self
    #
    def assign(array: STPair) -> STPair: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == pair</tt>.
    # \param pair The \e %STPair instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(pair: STPair) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != pair</tt>.
    # \param pair The \e %STPair instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(pair: STPair) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self <= pair</tt>.
    # \param pair The \e %STPair instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __le__(pair: STPair) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self >= pair</tt>.
    # \param pair The \e %STPair instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ge__(pair: STPair) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self < pair</tt>.
    # \param pair The \e %STPair instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __lt__(pair: STPair) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self > pair</tt>.
    # \param pair The \e %STPair instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __gt__(pair: STPair) -> bool: pass

    ##
    # \brief FIXME!
    #
    first = property(getFirst, setFirst)

    ##
    # \brief FIXME!
    #
    second = property(getSecond, setSecond)

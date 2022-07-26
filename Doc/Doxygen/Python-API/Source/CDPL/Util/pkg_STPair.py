#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
    # \param self The \e %STPair instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %STPair instance.
    # \param self The \e %STPair instance to initialize.
    # \param pair 
    #
    def __init__(self: object, pair: STPair) -> None: pass

    ##
    # \brief Initializes the \e %STPair instance.
    # \param self The \e %STPair instance to initialize.
    # \param first 
    # \param second 
    #
    def __init__(self: object, first: int, second: int) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %STPair instance \a array.
    # \param self The \e %STPair instance this method is called upon.
    # \param array The \e %STPair instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: STPair, array: STPair) -> STPair: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == pair</tt>.
    # \param self The \e %STPair instance this method is called upon.
    # \param pair The \e %STPair instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: STPair, pair: STPair) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != pair</tt>.
    # \param self The \e %STPair instance this method is called upon.
    # \param pair The \e %STPair instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: STPair, pair: STPair) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self <= pair</tt>.
    # \param self The \e %STPair instance this method is called upon.
    # \param pair The \e %STPair instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __le__(self: STPair, pair: STPair) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self >= pair</tt>.
    # \param self The \e %STPair instance this method is called upon.
    # \param pair The \e %STPair instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ge__(self: STPair, pair: STPair) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self < pair</tt>.
    # \param self The \e %STPair instance this method is called upon.
    # \param pair The \e %STPair instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __lt__(self: STPair, pair: STPair) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self > pair</tt>.
    # \param self The \e %STPair instance this method is called upon.
    # \param pair The \e %STPair instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __gt__(self: STPair, pair: STPair) -> bool: pass

    ##
    # \brief FIXME!
    #
    first = property(getFirst, setFirst)

    ##
    # \brief FIXME!
    #
    second = property(getSecond, setSecond)

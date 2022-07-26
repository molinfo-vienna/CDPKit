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
class TorsionLibrary(TorsionCategory):

    ##
    # \brief Initializes the \e %TorsionLibrary instance.
    # \param self The \e %TorsionLibrary instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %TorsionLibrary instance.
    # \param self The \e %TorsionLibrary instance to initialize.
    # \param lib 
    #
    def __init__(self: object, lib: TorsionLibrary) -> None: pass

    ##
    # \brief 
    # \param self The \e %TorsionLibrary instance this method is called upon.
    # \param is 
    #
    def load(self: TorsionLibrary, is: CDPL.Base.IStream) -> None: pass

    ##
    # \brief 
    # \param self The \e %TorsionLibrary instance this method is called upon.
    #
    def loadDefaults(self: TorsionLibrary) -> None: pass

    ##
    # \brief 
    # \param self The \e %TorsionLibrary instance this method is called upon.
    # \param os 
    #
    def save(self: TorsionLibrary, os: CDPL.Base.OStream) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %TorsionLibrary instance \a lib.
    # \param self The \e %TorsionLibrary instance this method is called upon.
    # \param lib The \e %TorsionLibrary instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: TorsionLibrary, lib: TorsionLibrary) -> TorsionLibrary: pass

    ##
    # \brief 
    # \param map 
    #
    @staticmethod
    def set(map: TorsionLibrary) -> None: pass

    ##
    # \brief 
    # \param  
    # \return 
    #
    @staticmethod
    def get(: ) -> TorsionLibrary: pass

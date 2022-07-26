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
class ReactionView2D(View2D):

    ##
    # \brief Initializes the \e %ReactionView2D instance.
    # \param self The \e %ReactionView2D instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %ReactionView2D instance.
    # \param self The \e %ReactionView2D instance to initialize.
    # \param rxn 
    #
    def __init__(self: object, rxn: CDPL.Chem.Reaction) -> None: pass

    ##
    # \brief 
    # \param self The \e %ReactionView2D instance this method is called upon.
    # \param rxn 
    #
    def setReaction(self: ReactionView2D, rxn: CDPL.Chem.Reaction) -> None: pass

    ##
    # \brief 
    # \param self The \e %ReactionView2D instance this method is called upon.
    # \return 
    #
    def getReaction(self: ReactionView2D) -> CDPL.Chem.Reaction: pass

    ##
    # \brief 
    # \param self The \e %ReactionView2D instance this method is called upon.
    # \return 
    #
    def getFontMetrics(self: ReactionView2D) -> FontMetrics: pass

    ##
    # \brief 
    #
    reaction = property(getReaction, setReaction)

    ##
    # \brief 
    #
    fontMetrics = property(getFontMetrics, setFontMetrics)

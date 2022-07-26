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
class BasicPharmacophore(Pharmacophore):

    ##
    # \brief Initializes the \e %BasicPharmacophore instance.
    # \param self The \e %BasicPharmacophore instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %BasicPharmacophore instance.
    # \param self The \e %BasicPharmacophore instance to initialize.
    # \param pharm 
    #
    def __init__(self: object, pharm: BasicPharmacophore) -> None: pass

    ##
    # \brief Initializes the \e %BasicPharmacophore instance.
    # \param self The \e %BasicPharmacophore instance to initialize.
    # \param pharm 
    #
    def __init__(self: object, pharm: Pharmacophore) -> None: pass

    ##
    # \brief Initializes the \e %BasicPharmacophore instance.
    # \param self The \e %BasicPharmacophore instance to initialize.
    # \param cntnr 
    #
    def __init__(self: object, cntnr: FeatureContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %BasicPharmacophore instance this method is called upon.
    # \param pharm 
    #
    def copy(self: BasicPharmacophore, pharm: BasicPharmacophore) -> None: pass

    ##
    # \brief 
    # \param self The \e %BasicPharmacophore instance this method is called upon.
    # \param pharm 
    #
    def copy(self: BasicPharmacophore, pharm: Pharmacophore) -> None: pass

    ##
    # \brief 
    # \param self The \e %BasicPharmacophore instance this method is called upon.
    # \param cntnr 
    #
    def copy(self: BasicPharmacophore, cntnr: FeatureContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %BasicPharmacophore instance this method is called upon.
    # \param pharm 
    #
    def append(self: BasicPharmacophore, pharm: BasicPharmacophore) -> None: pass

    ##
    # \brief 
    # \param self The \e %BasicPharmacophore instance this method is called upon.
    # \param pharm 
    #
    def append(self: BasicPharmacophore, pharm: Pharmacophore) -> None: pass

    ##
    # \brief 
    # \param self The \e %BasicPharmacophore instance this method is called upon.
    # \param cntnr 
    #
    def append(self: BasicPharmacophore, cntnr: FeatureContainer) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %BasicPharmacophore instance \a pharm.
    # \param self The \e %BasicPharmacophore instance this method is called upon.
    # \param pharm The \e %BasicPharmacophore instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: BasicPharmacophore, pharm: BasicPharmacophore) -> BasicPharmacophore: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %BasicPharmacophore instance \a pharm.
    # \param self The \e %BasicPharmacophore instance this method is called upon.
    # \param pharm The \e %BasicPharmacophore instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: BasicPharmacophore, pharm: Pharmacophore) -> BasicPharmacophore: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %BasicPharmacophore instance \a cntnr.
    # \param self The \e %BasicPharmacophore instance this method is called upon.
    # \param cntnr The \e %BasicPharmacophore instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: BasicPharmacophore, cntnr: FeatureContainer) -> BasicPharmacophore: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += pharm</tt>.
    # \param self The \e %BasicPharmacophore instance acting as in-place addend.
    # \param pharm Specifies the second addend.
    # \return The updated \e %BasicPharmacophore instance \a self.
    #
    def __iadd__(self: BasicPharmacophore, pharm: BasicPharmacophore) -> BasicPharmacophore: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += pharm</tt>.
    # \param self The \e %BasicPharmacophore instance acting as in-place addend.
    # \param pharm Specifies the second addend.
    # \return The updated \e %BasicPharmacophore instance \a self.
    #
    def __iadd__(self: BasicPharmacophore, pharm: Pharmacophore) -> BasicPharmacophore: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += cntnr</tt>.
    # \param self The \e %BasicPharmacophore instance acting as in-place addend.
    # \param cntnr Specifies the second addend.
    # \return The updated \e %BasicPharmacophore instance \a self.
    #
    def __iadd__(self: BasicPharmacophore, cntnr: FeatureContainer) -> BasicPharmacophore: pass

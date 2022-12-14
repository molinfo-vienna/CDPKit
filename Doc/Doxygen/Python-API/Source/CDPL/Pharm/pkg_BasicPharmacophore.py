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
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %BasicPharmacophore instance.
    # \param pharm 
    #
    def __init__(pharm: BasicPharmacophore) -> None: pass

    ##
    # \brief Initializes the \e %BasicPharmacophore instance.
    # \param pharm 
    #
    def __init__(pharm: Pharmacophore) -> None: pass

    ##
    # \brief Initializes the \e %BasicPharmacophore instance.
    # \param cntnr 
    #
    def __init__(cntnr: FeatureContainer) -> None: pass

    ##
    # \brief 
    # \param pharm 
    #
    def copy(pharm: BasicPharmacophore) -> None: pass

    ##
    # \brief 
    # \param pharm 
    #
    def copy(pharm: Pharmacophore) -> None: pass

    ##
    # \brief 
    # \param cntnr 
    #
    def copy(cntnr: FeatureContainer) -> None: pass

    ##
    # \brief 
    # \param pharm 
    #
    def append(pharm: BasicPharmacophore) -> None: pass

    ##
    # \brief 
    # \param pharm 
    #
    def append(pharm: Pharmacophore) -> None: pass

    ##
    # \brief 
    # \param cntnr 
    #
    def append(cntnr: FeatureContainer) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %BasicPharmacophore instance \a pharm.
    # \param pharm The \e %BasicPharmacophore instance to copy.
    # \return \a self
    #
    def assign(pharm: BasicPharmacophore) -> BasicPharmacophore: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Pharmacophore instance \a pharm.
    # \param pharm The \e %Pharmacophore instance to copy.
    # \return \a self
    #
    def assign(pharm: Pharmacophore) -> BasicPharmacophore: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FeatureContainer instance \a cntnr.
    # \param cntnr The \e %FeatureContainer instance to copy.
    # \return \a self
    #
    def assign(cntnr: FeatureContainer) -> BasicPharmacophore: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += pharm</tt>.
    # \param pharm Specifies the second addend.
    # \return The updated \e %BasicPharmacophore instance \a self.
    #
    def __iadd__(pharm: BasicPharmacophore) -> BasicPharmacophore: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += pharm</tt>.
    # \param pharm Specifies the second addend.
    # \return The updated \e %BasicPharmacophore instance \a self.
    #
    def __iadd__(pharm: Pharmacophore) -> BasicPharmacophore: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += cntnr</tt>.
    # \param cntnr Specifies the second addend.
    # \return The updated \e %BasicPharmacophore instance \a self.
    #
    def __iadd__(cntnr: FeatureContainer) -> BasicPharmacophore: pass

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
# \brief BasicPharmacophore.
# 
class BasicPharmacophore(Pharmacophore):

    ##
    # \brief Constructs an empty <tt>BasicPharmacophore</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the Pharm.Pharmacophore instance <em>pharm</em>.
    # 
    # \param pharm The other Pharm.Pharmacophore instance to copy.
    # 
    def __init__(pharm: BasicPharmacophore) -> None: pass

    ##
    # \brief Constructs a copy of the Pharm.Pharmacophore instance <em>pharm</em>.
    # 
    # \param pharm The other Pharm.Pharmacophore instance to copy.
    # 
    def __init__(pharm: Pharmacophore) -> None: pass

    ##
    # \brief Constructs a BasicPharmacophore instance with copies of the features in the Pharm.FeatureContainer instance <em>cntnr</em>.
    # 
    # \param cntnr The Pharm.FeatureContainer instance with the features to copy.
    # 
    def __init__(cntnr: FeatureContainer) -> None: pass

    ##
    # \brief Replaces the current set of pharmacophore features and properties by a copy of the features and properties of the pharmacophore <em>pharm</em>.
    # 
    # \param pharm The pharmacophore to copy.
    # 
    def copy(pharm: BasicPharmacophore) -> None: pass

    ##
    # \brief Replaces the current set of pharmacophore features and properties by a copy of the features and properties of the pharmacophore <em>pharm</em>.
    # 
    # \param pharm The pharmacophore to copy.
    # 
    def copy(pharm: Pharmacophore) -> None: pass

    ##
    # \brief Replaces the current set of pharmacophore features and properties by a copy of the features and properties of the feature container <em>cntnr</em>.
    # 
    # \param cntnr The Pharm.FeatureContainer instance providing the features and properties to copy.
    # 
    def copy(cntnr: FeatureContainer) -> None: pass

    ##
    # \brief Extends the current set of pharmacophore features by a copy of the features in the pharmacophore <em>pharm</em>.
    # 
    # \param pharm The pharmacophore providing the features to append.
    # 
    # \note Does not affect any properties.
    # 
    def append(pharm: BasicPharmacophore) -> None: pass

    ##
    # \brief Extends the current set of pharmacophore features by a copy of the features in the pharmacophore <em>pharm</em>.
    # 
    # \param pharm The pharmacophore providing the features to append.
    # 
    # \note Does not affect any properties.
    # 
    def append(pharm: Pharmacophore) -> None: pass

    ##
    # \brief Extends the current set of pharmacophore features by a copy of the features in the feature container <em>cntnr</em>.
    # 
    # \param cntnr The Pharm.FeatureContainer instance providing the features to append.
    # 
    # \note Does not affect any properties.
    # 
    def append(cntnr: FeatureContainer) -> None: pass

    ##
    # \brief Replaces the current set of pharmacophore features and properties by a copy of the features and properties of the pharmacophore <em>pharm</em>.
    # 
    # Internally calls copy() to perform the actual work.
    # 
    # \param pharm The pharmacophore to copy.
    # 
    # \return \a self
    # 
    def assign(pharm: BasicPharmacophore) -> BasicPharmacophore: pass

    ##
    # \brief Replaces the current set of pharmacophore features and properties by a copy of the features and properties of the pharmacophore <em>pharm</em>.
    # 
    # Internally calls copy() to perform the actual work.
    # 
    # \param pharm The pharmacophore to copy.
    # 
    # \return \a self
    # 
    def assign(pharm: Pharmacophore) -> BasicPharmacophore: pass

    ##
    # \brief Replaces the current set of pharmacophore features and properties by a copy of the features and properties of the feature container <em>cntnr</em>.
    # 
    # Internally calls copy() to perform the actual work.
    # 
    # \param cntnr The Pharm.FeatureContainer instance providing the features and properties to copy.
    # 
    # \return \a self
    # 
    def assign(cntnr: FeatureContainer) -> BasicPharmacophore: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += pharm</tt>.
    # \param pharm Specifies the second addend.
    # \return The updated \c %BasicPharmacophore instance \a self.
    # 
    def __iadd__(pharm: BasicPharmacophore) -> BasicPharmacophore: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += pharm</tt>.
    # \param pharm Specifies the second addend.
    # \return The updated \c %BasicPharmacophore instance \a self.
    # 
    def __iadd__(pharm: Pharmacophore) -> BasicPharmacophore: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += cntnr</tt>.
    # \param cntnr Specifies the second addend.
    # \return The updated \c %BasicPharmacophore instance \a self.
    # 
    def __iadd__(cntnr: FeatureContainer) -> BasicPharmacophore: pass

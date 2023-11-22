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
# \brief Provides constants that are used to specify the <em>E/Z</em> configuration of double bonds.
# 
class BondConfiguration(Boost.Python.instance):

    ##
    # \brief Specifies that the configuration of the bond is undefined.
    # 
    UNDEF = 0

    ##
    # \brief Specifies that a bond does not meet the requirements (e.g. not a double bond or symmetric) to be assigned a configuration.
    # 
    NONE = 1

    ##
    # \brief Specifies that the bond has <em>E (or trans)</em> configuration.
    # 
    E = 2

    ##
    # \brief Specifies that the bond has <em>trans (or E)</em> configuration.
    # 
    TRANS = 2

    ##
    # \brief Specifies that the bond has <em>Z (or cis)</em> configuration.
    # 
    Z = 4

    ##
    # \brief Specifies that the bond has <em>cis (or Z)</em> configuration.
    # 
    CIS = 4

    ##
    # \brief Specifies that the bond is a stereogenic center but has no defined configuration.
    # 
    EITHER = 8

    ##
    # \brief Specifies that the bond has <em>seqCis</em> configuration.
    # 
    seqCIS = 17

    ##
    # \brief Specifies that the bond has <em>seqTrans</em> configuration.
    # 
    seqTRANS = 16

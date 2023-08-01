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
# \param shape 
# \param xform 
#
def transform(shape: GaussianShape, xform: Math.Matrix4D) -> None: pass

##
# \brief 
# \param shape 
# \param func 
# \param back_xform 
# \param mom_eq_thresh 
# \return 
#
def centerAndAlignPrincipalAxes(shape: GaussianShape, func: GaussianShapeFunction, back_xform: Math.Matrix4D, mom_eq_thresh: float = 0.15) -> int: pass

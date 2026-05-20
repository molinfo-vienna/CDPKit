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
# \brief Tells whether <em>path1</em> and <em>path2</em> refer to the same file (after resolving symlinks and case-insensitivity rules of the underlying file system).
# 
# \param path1 The first file-system path.
# \param path2 The second file-system path.
# 
# \return <tt>True</tt> if both paths resolve to the same file, and <tt>False</tt> otherwise.
# 
def checkIfSameFile(path1: str, path2: str) -> bool: pass

##
# \brief Tells whether the file at <em>path</em> exists.
# 
# \param path The file-system path to test.
# 
# \return <tt>True</tt> if the file exists, and <tt>False</tt> otherwise.
# 
def fileExists(path: str) -> bool: pass

##
# \brief Folds the bitset <em>bs</em> the specified number of times.
# 
# Folding a bitset means that the lower and upper half of the bitset are combined by a logical OR operation to produce a new bitset which is half of the original size. This process is repeated the specified number of times. See also [\ref DTPFP].
# 
# \param bs The bitset to fold.
# \param num_times The number of times the bitset has to be folded.
# 
def fold(bs: BitSet, num_times: int) -> None: pass

##
# \brief 
# \param seq1 
# \param seq2 
# \param func 
#
def forEachPair(seq1: object, seq2: object, func: object) -> None: pass

##
# \brief 
# \param seq 
# \param func 
#
def forEach(seq: object, func: object) -> None: pass

##
# \brief Generates a temporary file path inside <em>dir</em> whose basename matches the supplied randomization <em>ptn</em> and that is guaranteed not to collide with any existing file.
# 
# \param dir The directory in which to place the file (an empty string selects the platform's temporary directory).
# \param ptn The Boost-filesystem-style randomization pattern for the basename (<tt>%</tt> characters are replaced with random hex digits).
# 
# \return The generated unique file-system path.
# 
def genCheckedTempFilePath(dir: str = '', ptn: str = '%%%%-%%%%-%%%%-%%%%') -> str: pass

## 
# DataFormatTest.py 
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
#
# This program is free software you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation either
# version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program see the file COPYING. If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
##
	
	
import unittest
	
from CDPL.Base import DataFormat

	
class TestCase(unittest.TestCase):

	def runTest(self):
		"""Testing DataFormat"""

		df1 = DataFormat('PNG', 'Portable Network Graphics', 'image/png', [ 'png', 'xng' ], True)
	
		self.assert_(df1.getName() == 'PNG')
		self.assert_(df1.name == 'PNG')
		self.assert_(df1.getDescription() == 'Portable Network Graphics')
		self.assert_(df1.description == 'Portable Network Graphics')
		self.assert_(df1.getMimeType() == 'image/png')
		self.assert_(df1.mimeType == 'image/png')
		self.assert_(df1.isMultiRecordFormat() == True)
		self.assert_(df1.multiRecordFormat == True)
	
		self.assert_(df1.getNumFileExtensions() == 2)
		self.assert_(df1.numFileExtensions == 2)
	
		self.assert_(len(df1.fileExtensions) == 2)
	
		self.assert_(df1.getFileExtension(0) == 'png')
		self.assert_(df1.getFileExtension(1) == 'xng')

		self.assert_(df1.fileExtensions[0] == 'png')
		self.assert_(df1.fileExtensions[1] == 'xng')
	
		self.assertRaises(IndexError, df1.getFileExtension, 2)
		self.assertRaises(IndexError, df1.getFileExtension, 3)

		self.assertRaises(IndexError, df1.fileExtensions.__getitem__, 2)
		self.assertRaises(IndexError, df1.fileExtensions.__getitem__, 3)
	
		self.assert_(df1.matchesName('png'))
		self.assert_(df1.matchesName('PNG'))
		self.assert_(df1.matchesName('pNg'))
		self.assert_(not df1.matchesName('pngc'))
		self.assert_(not df1.matchesName(' png'))
		self.assert_(not df1.matchesName('png '))
		self.assert_(not df1.matchesName(''))

		self.assert_(df1.matchesMimeType('image/png'))
		self.assert_(df1.matchesMimeType('IMAGE/PNG'))
		self.assert_(df1.matchesMimeType('ImAGe/pnG'))
		self.assert_(not df1.matchesMimeType('inage/png'))
		self.assert_(not df1.matchesMimeType(' image/png'))
		self.assert_(not df1.matchesMimeType('image/png '))
		self.assert_(not df1.matchesMimeType('imge/png'))
		self.assert_(not df1.matchesMimeType(''))

		self.assert_(df1.matchesFileExtension('png'))
		self.assert_(df1.matchesFileExtension('PNG'))
		self.assert_(df1.matchesFileExtension('pNg'))
		self.assert_(not df1.matchesFileExtension(' png'))
		self.assert_(not df1.matchesFileExtension('png '))
		self.assert_(not df1.matchesFileExtension('pn g'))
		self.assert_(not df1.matchesFileExtension('pnxg'))
		self.assert_(not df1.matchesFileExtension('pag'))
		self.assert_(not df1.matchesFileExtension('pg'))
		self.assert_(not df1.matchesFileExtension(''))

		self.assert_('png' in df1.fileExtensions)
		self.assert_('PNG' in df1.fileExtensions)
		self.assert_('pNg' in df1.fileExtensions)
		self.assert_(not ' png' in df1.fileExtensions)
		self.assert_(not 'png ' in df1.fileExtensions)
		self.assert_(not 'pn g' in df1.fileExtensions)
		self.assert_(not 'pnxg' in df1.fileExtensions)
		self.assert_(not 'pag' in df1.fileExtensions)
		self.assert_(not 'pg' in df1.fileExtensions)
		self.assert_(not '' in df1.fileExtensions)
	
		self.assert_(df1.matchesFileExtension('xng'))
		self.assert_(df1.matchesFileExtension('XNG'))
		self.assert_(df1.matchesFileExtension('xnG'))
		self.assert_(not df1.matchesFileExtension(' xng'))
		self.assert_(not df1.matchesFileExtension('xng '))
		self.assert_(not df1.matchesFileExtension('xn g'))
		self.assert_(not df1.matchesFileExtension('xnxg'))
		self.assert_(not df1.matchesFileExtension('xag'))
		self.assert_(not df1.matchesFileExtension('xn'))

		self.assert_('xng' in df1.fileExtensions)
		self.assert_('XNG' in df1.fileExtensions)
		self.assert_('xnG' in df1.fileExtensions)
		self.assert_(not ' xng' in df1.fileExtensions)
		self.assert_(not 'xng ' in df1.fileExtensions)
		self.assert_(not 'xn g' in df1.fileExtensions)
		self.assert_(not 'xnxg' in df1.fileExtensions)
		self.assert_(not 'xag' in df1.fileExtensions)
		self.assert_(not 'xn' in df1.fileExtensions)

		#-----
		
		df2 = DataFormat('PNG', 'Portable Network Graphics', 'image/png', True)
	
		self.assert_(df2.getName() == 'PNG')
		self.assert_(df2.name == 'PNG')
		self.assert_(df2.getDescription() == 'Portable Network Graphics')
		self.assert_(df2.description == 'Portable Network Graphics')
		self.assert_(df2.getMimeType() == 'image/png')
		self.assert_(df2.mimeType == 'image/png')
		self.assert_(df2.isMultiRecordFormat() == True)
		self.assert_(df2.multiRecordFormat == True)
	
		self.assert_(df2.getNumFileExtensions() == 0)
		self.assert_(df2.numFileExtensions == 0)
	
		self.assert_(len(df2.fileExtensions) == 0)
	
		self.assertRaises(IndexError, df2.getFileExtension, 0)
		self.assertRaises(IndexError, df2.getFileExtension, 1)

		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 0)
		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 0)
	
		self.assert_(df2.matchesName('png'))
		self.assert_(df2.matchesName('PNG'))
		self.assert_(df2.matchesName('pNg'))
		self.assert_(not df2.matchesName('pngc'))
		self.assert_(not df2.matchesName(' png'))
		self.assert_(not df2.matchesName('png '))
		self.assert_(not df2.matchesName(''))
	
		self.assert_(df2.matchesMimeType('image/png'))
		self.assert_(df2.matchesMimeType('IMAGE/PNG'))
		self.assert_(df2.matchesMimeType('ImAGe/pnG'))
		self.assert_(not df2.matchesMimeType('inage/png'))
		self.assert_(not df2.matchesMimeType(' image/png'))
		self.assert_(not df2.matchesMimeType('image/png '))
		self.assert_(not df2.matchesMimeType('imge/png'))
		self.assert_(not df2.matchesMimeType(''))

		self.assert_(not df2.matchesFileExtension('png'))
		self.assert_(not df2.matchesFileExtension('PNG'))
		self.assert_(not df2.matchesFileExtension('pNg'))
		self.assert_(not df2.matchesFileExtension(' png'))
		self.assert_(not df2.matchesFileExtension('png '))
		self.assert_(not df2.matchesFileExtension('pn g'))
		self.assert_(not df2.matchesFileExtension('pnxg'))
		self.assert_(not df2.matchesFileExtension('pag'))
		self.assert_(not df2.matchesFileExtension('pg'))
		self.assert_(not df2.matchesFileExtension(''))
	
		#-----
	
		df2 = DataFormat()
	
		self.assert_(df2.getName() == '')
		self.assert_(df2.name == '')
		self.assert_(df2.getDescription() == '')
		self.assert_(df2.description == '')
		self.assert_(df2.getMimeType() == '')
		self.assert_(df2.mimeType == '')
		self.assert_(df2.isMultiRecordFormat() == False)
		self.assert_(df2.multiRecordFormat == False)
	
		self.assert_(df2.getNumFileExtensions() == 0)
		self.assert_(df2.numFileExtensions == 0)
	
		self.assertRaises(IndexError, df2.getFileExtension, 0)
		self.assertRaises(IndexError, df2.getFileExtension, 1)

		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 0)
		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 1)
	
		self.assert_(len(df2.fileExtensions) == 0)
	
		#-----
	
		df2.setName('Name1')
	
		self.assert_(df2.getName() == 'Name1')
		self.assert_(df2.name == 'Name1')
		self.assert_(df2.getDescription() == '')
		self.assert_(df2.description == '')
		self.assert_(df2.getMimeType() == '')
		self.assert_(df2.mimeType == '')
		self.assert_(df2.isMultiRecordFormat() == False)
		self.assert_(df2.multiRecordFormat == False)
	
		self.assert_(df2.getNumFileExtensions() == 0)
		self.assert_(df2.numFileExtensions == 0)
	
		self.assertRaises(IndexError, df2.getFileExtension, 0)
		self.assertRaises(IndexError, df2.getFileExtension, 1)

		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 0)
		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 1)
	
		self.assert_(len(df2.fileExtensions) == 0)

		#-----
	
		df2.name = 'Name'
	
		self.assert_(df2.getName() == 'Name')
		self.assert_(df2.name == 'Name')
		self.assert_(df2.getDescription() == '')
		self.assert_(df2.description == '')
		self.assert_(df2.getMimeType() == '')
		self.assert_(df2.mimeType == '')
		self.assert_(df2.isMultiRecordFormat() == False)
		self.assert_(df2.multiRecordFormat == False)
	
		self.assert_(df2.getNumFileExtensions() == 0)
		self.assert_(df2.numFileExtensions == 0)
	
		self.assertRaises(IndexError, df2.getFileExtension, 0)
		self.assertRaises(IndexError, df2.getFileExtension, 1)

		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 0)
		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 1)
	
		self.assert_(len(df2.fileExtensions) == 0)
	
		#-----

		df2.description = 'Description1'
	
		self.assert_(df2.getName() == 'Name')
		self.assert_(df2.name == 'Name')
		self.assert_(df2.getDescription() == 'Description1')
		self.assert_(df2.description == 'Description1')
		self.assert_(df2.getMimeType() == '')
		self.assert_(df2.mimeType == '')
		self.assert_(df2.isMultiRecordFormat() == False)
		self.assert_(df2.multiRecordFormat == False)
	
		self.assert_(df2.getNumFileExtensions() == 0)
		self.assert_(df2.numFileExtensions == 0)
	
		self.assertRaises(IndexError, df2.getFileExtension, 0)
		self.assertRaises(IndexError, df2.getFileExtension, 1)

		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 0)
		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 1)
	
		self.assert_(len(df2.fileExtensions) == 0)

		#-----
			
		df2.setDescription('Description')

		self.assert_(df2.getName() == 'Name')
		self.assert_(df2.name == 'Name')
		self.assert_(df2.getDescription() == 'Description')
		self.assert_(df2.description == 'Description')
		self.assert_(df2.getMimeType() == '')
		self.assert_(df2.mimeType == '')
		self.assert_(df2.isMultiRecordFormat() == False)
		self.assert_(df2.multiRecordFormat == False)
	
		self.assert_(df2.getNumFileExtensions() == 0)
		self.assert_(df2.numFileExtensions == 0)
	
		self.assertRaises(IndexError, df2.getFileExtension, 0)
		self.assertRaises(IndexError, df2.getFileExtension, 1)

		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 0)
		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 1)
	
		self.assert_(len(df2.fileExtensions) == 0)
		
		#-----
	
		df2.setMimeType('mime/type1')

		self.assert_(df2.getName() == 'Name')
		self.assert_(df2.name == 'Name')
		self.assert_(df2.getDescription() == 'Description')
		self.assert_(df2.description == 'Description')
		self.assert_(df2.getMimeType() == 'mime/type1')
		self.assert_(df2.mimeType == 'mime/type1')
		self.assert_(df2.isMultiRecordFormat() == False)
		self.assert_(df2.multiRecordFormat == False)
	
		self.assert_(df2.getNumFileExtensions() == 0)
		self.assert_(df2.numFileExtensions == 0)
	
		self.assertRaises(IndexError, df2.getFileExtension, 0)
		self.assertRaises(IndexError, df2.getFileExtension, 1)

		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 0)
		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 1)
	
		self.assert_(len(df2.fileExtensions) == 0)

		#-----
	
		df2.mimeType = 'mime/type'

		self.assert_(df2.getName() == 'Name')
		self.assert_(df2.name == 'Name')
		self.assert_(df2.getDescription() == 'Description')
		self.assert_(df2.description == 'Description')
		self.assert_(df2.getMimeType() == 'mime/type')
		self.assert_(df2.mimeType == 'mime/type')
		self.assert_(df2.isMultiRecordFormat() == False)
		self.assert_(df2.multiRecordFormat == False)
	
		self.assert_(df2.getNumFileExtensions() == 0)
		self.assert_(df2.numFileExtensions == 0)
	
		self.assertRaises(IndexError, df2.getFileExtension, 0)
		self.assertRaises(IndexError, df2.getFileExtension, 1)

		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 0)
		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 1)
	
		self.assert_(len(df2.fileExtensions) == 0)
		
		#-----
	
		df2.setMultiRecordFormat(True)

		self.assert_(df2.getName() == 'Name')
		self.assert_(df2.name == 'Name')
		self.assert_(df2.getDescription() == 'Description')
		self.assert_(df2.description == 'Description')
		self.assert_(df2.getMimeType() == 'mime/type')
		self.assert_(df2.mimeType == 'mime/type')
		self.assert_(df2.isMultiRecordFormat() == True)
		self.assert_(df2.multiRecordFormat == True)
	
		self.assert_(df2.getNumFileExtensions() == 0)
		self.assert_(df2.numFileExtensions == 0)
	
		self.assertRaises(IndexError, df2.getFileExtension, 0)
		self.assertRaises(IndexError, df2.getFileExtension, 1)

		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 0)
		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 1)
	
		self.assert_(len(df2.fileExtensions) == 0)
		self.assert_(not df2.fileExtensions)

		#-----
	
		df2.multiRecordFormat = False

		self.assert_(df2.getName() == 'Name')
		self.assert_(df2.name == 'Name')
		self.assert_(df2.getDescription() == 'Description')
		self.assert_(df2.description == 'Description')
		self.assert_(df2.getMimeType() == 'mime/type')
		self.assert_(df2.mimeType == 'mime/type')
		self.assert_(df2.isMultiRecordFormat() == False)
		self.assert_(df2.multiRecordFormat == False)
	
		self.assert_(df2.getNumFileExtensions() == 0)
		self.assert_(df2.numFileExtensions == 0)
	
		self.assertRaises(IndexError, df2.getFileExtension, 0)
		self.assertRaises(IndexError, df2.getFileExtension, 1)

		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 0)
		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 1)
	
		self.assert_(len(df2.fileExtensions) == 0)
		self.assert_(not df2.fileExtensions)

		#-----

		df2.setMultiRecordFormat(True)
		df2.addFileExtension('ext1')
	
		self.assert_(df2.getName() == 'Name')
		self.assert_(df2.name == 'Name')
		self.assert_(df2.getDescription() == 'Description')
		self.assert_(df2.description == 'Description')
		self.assert_(df2.getMimeType() == 'mime/type')
		self.assert_(df2.mimeType == 'mime/type')
		self.assert_(df2.isMultiRecordFormat() == True)
		self.assert_(df2.multiRecordFormat == True)
	
		self.assert_(df2.getNumFileExtensions() == 1)
		self.assert_(df2.numFileExtensions == 1)
		
		self.assert_(df2.getFileExtension(0) == 'ext1')
		self.assert_(df2.fileExtensions[0] == 'ext1')
	
		self.assertRaises(IndexError, df2.getFileExtension, 1)
		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 1)
	
		self.assert_(len(df2.fileExtensions) == 1)
		self.assert_(df2.fileExtensions)
		
		self.assert_(df2.matchesFileExtension('ext1'))
		self.assert_(not df2.matchesFileExtension('ext2'))
		self.assert_(not df2.matchesFileExtension(''))

		self.assert_('ext1' in df2.fileExtensions)
		self.assert_(not 'ext2' in df2.fileExtensions)
		self.assert_(not '' in df2.fileExtensions)
	
		#-----
	
		df2.addFileExtension('ext2')
	
		self.assert_(df2.getName() == 'Name')
		self.assert_(df2.name == 'Name')
		self.assert_(df2.getDescription() == 'Description')
		self.assert_(df2.description == 'Description')
		self.assert_(df2.getMimeType() == 'mime/type')
		self.assert_(df2.mimeType == 'mime/type')
		self.assert_(df2.isMultiRecordFormat() == True)
		self.assert_(df2.multiRecordFormat == True)
	
		self.assert_(df2.getNumFileExtensions() == 2)
		self.assert_(df2.numFileExtensions == 2)
		
		self.assert_(df2.getFileExtension(0) == 'ext1')
		self.assert_(df2.fileExtensions[0] == 'ext1')
		self.assert_(df2.getFileExtension(1) == 'ext2')
		self.assert_(df2.fileExtensions[1] == 'ext2')
	
		self.assertRaises(IndexError, df2.getFileExtension, 2)
		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 2)
	
		self.assert_(len(df2.fileExtensions) == 2)
		self.assert_(df2.fileExtensions)
		
		self.assert_(df2.matchesFileExtension('ext1'))
		self.assert_(df2.matchesFileExtension('ext2'))
		self.assert_(not df2.matchesFileExtension(''))

		self.assert_('ext1' in df2.fileExtensions)
		self.assert_('ext2' in df2.fileExtensions)
		self.assert_(not '' in df2.fileExtensions)
	
		#-----
	
		df2.addFileExtension('')
	
		self.assert_(df2.getName() == 'Name')
		self.assert_(df2.name == 'Name')
		self.assert_(df2.getDescription() == 'Description')
		self.assert_(df2.description == 'Description')
		self.assert_(df2.getMimeType() == 'mime/type')
		self.assert_(df2.mimeType == 'mime/type')
		self.assert_(df2.isMultiRecordFormat() == True)
		self.assert_(df2.multiRecordFormat == True)
	
		self.assert_(df2.getNumFileExtensions() == 3)
		self.assert_(df2.numFileExtensions == 3)
		
		self.assert_(df2.getFileExtension(0) == 'ext1')
		self.assert_(df2.fileExtensions[0] == 'ext1')
		self.assert_(df2.getFileExtension(1) == 'ext2')
		self.assert_(df2.fileExtensions[1] == 'ext2')
		self.assert_(df2.getFileExtension(2) == '')
		self.assert_(df2.fileExtensions[2] == '')
	
		self.assertRaises(IndexError, df2.getFileExtension, 3)
		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 3)
	
		self.assert_(len(df2.fileExtensions) == 3)
		self.assert_(df2.fileExtensions)
		
		self.assert_(df2.matchesFileExtension('ext1'))
		self.assert_(df2.matchesFileExtension('ext2'))
		self.assert_(df2.matchesFileExtension(''))

		self.assert_('ext1' in df2.fileExtensions)
		self.assert_('ext2' in df2.fileExtensions)
		self.assert_('' in df2.fileExtensions)
		
		#-----
	
		df2.setFileExtension(2, 'ext3')
	
		self.assertRaises(IndexError, df2.setFileExtension, 3, 'ext4')

		self.assert_(df2.getName() == 'Name')
		self.assert_(df2.name == 'Name')
		self.assert_(df2.getDescription() == 'Description')
		self.assert_(df2.description == 'Description')
		self.assert_(df2.getMimeType() == 'mime/type')
		self.assert_(df2.mimeType == 'mime/type')
		self.assert_(df2.isMultiRecordFormat() == True)
		self.assert_(df2.multiRecordFormat == True)
	
		self.assert_(df2.getNumFileExtensions() == 3)
		self.assert_(df2.numFileExtensions == 3)
		
		self.assert_(df2.getFileExtension(0) == 'ext1')
		self.assert_(df2.fileExtensions[0] == 'ext1')
		self.assert_(df2.getFileExtension(1) == 'ext2')
		self.assert_(df2.fileExtensions[1] == 'ext2')
		self.assert_(df2.getFileExtension(2) == 'ext3')
		self.assert_(df2.fileExtensions[2] == 'ext3')
	
		self.assertRaises(IndexError, df2.getFileExtension, 3)
		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 3)
	
		self.assert_(len(df2.fileExtensions) == 3)
		self.assert_(df2.fileExtensions)
		
		self.assert_(df2.matchesFileExtension('ext1'))
		self.assert_(df2.matchesFileExtension('ext2'))
		self.assert_(df2.matchesFileExtension('ext3'))
		self.assert_(not df2.matchesFileExtension(''))
		self.assert_(not df2.matchesFileExtension(' '))

		self.assert_('ext1' in df2.fileExtensions)
		self.assert_('ext2' in df2.fileExtensions)
		self.assert_('ext3' in df2.fileExtensions)
		self.assert_(not '' in df2.fileExtensions)
		self.assert_(not ' ' in df2.fileExtensions)
	
		#-----
	
		df2.fileExtensions[2] = 'ext'

		self.assertRaises(IndexError, df2.fileExtensions.__setitem__, 3, 'ext4')
			
		self.assert_(df2.getName() == 'Name')
		self.assert_(df2.name == 'Name')
		self.assert_(df2.getDescription() == 'Description')
		self.assert_(df2.description == 'Description')
		self.assert_(df2.getMimeType() == 'mime/type')
		self.assert_(df2.mimeType == 'mime/type')
		self.assert_(df2.isMultiRecordFormat() == True)
		self.assert_(df2.multiRecordFormat == True)
	
		self.assert_(df2.getNumFileExtensions() == 3)
		self.assert_(df2.numFileExtensions == 3)
		
		self.assert_(df2.getFileExtension(0) == 'ext1')
		self.assert_(df2.fileExtensions[0] == 'ext1')
		self.assert_(df2.getFileExtension(1) == 'ext2')
		self.assert_(df2.fileExtensions[1] == 'ext2')
		self.assert_(df2.getFileExtension(2) == 'ext')
		self.assert_(df2.fileExtensions[2] == 'ext')
	
		self.assertRaises(IndexError, df2.getFileExtension, 3)
		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 3)
	
		self.assert_(len(df2.fileExtensions) == 3)
		self.assert_(df2.fileExtensions)
		
		self.assert_(df2.matchesFileExtension('ext1'))
		self.assert_(df2.matchesFileExtension('ext2'))
		self.assert_(df2.matchesFileExtension('ext'))
		self.assert_(not df2.matchesFileExtension(''))
		self.assert_(not df2.matchesFileExtension(' '))

		self.assert_('ext1' in df2.fileExtensions)
		self.assert_('ext2' in df2.fileExtensions)
		self.assert_('ext' in df2.fileExtensions)
		self.assert_(not '' in df2.fileExtensions)
		self.assert_(not ' ' in df2.fileExtensions)
		
		#-----

		df2.fileExtensions[2] = 'ext3'
		
		self.assertRaises(IndexError, df2.fileExtensions.__setitem__, 3, 'ext4')
	
		self.assert_(df2.getName() == 'Name')
		self.assert_(df2.name == 'Name')
		self.assert_(df2.getDescription() == 'Description')
		self.assert_(df2.description == 'Description')
		self.assert_(df2.getMimeType() == 'mime/type')
		self.assert_(df2.mimeType == 'mime/type')
		self.assert_(df2.isMultiRecordFormat() == True)
		self.assert_(df2.multiRecordFormat == True)
	
		self.assert_(df2.getNumFileExtensions() == 3)
		self.assert_(df2.numFileExtensions == 3)
		
		self.assert_(df2.getFileExtension(0) == 'ext1')
		self.assert_(df2.fileExtensions[0] == 'ext1')
		self.assert_(df2.getFileExtension(1) == 'ext2')
		self.assert_(df2.fileExtensions[1] == 'ext2')
		self.assert_(df2.getFileExtension(2) == 'ext3')
		self.assert_(df2.fileExtensions[2] == 'ext3')
	
		self.assertRaises(IndexError, df2.getFileExtension, 3)
		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 3)
	
		self.assert_(len(df2.fileExtensions) == 3)
		self.assert_(df2.fileExtensions)
		
		self.assert_(df2.matchesFileExtension('ext1'))
		self.assert_(df2.matchesFileExtension('ext2'))
		self.assert_(df2.matchesFileExtension('ext3'))
		self.assert_(not df2.matchesFileExtension('ext'))
		self.assert_(not df2.matchesFileExtension(''))
		self.assert_(not df2.matchesFileExtension(' '))

		self.assert_('ext1' in df2.fileExtensions)
		self.assert_('ext2' in df2.fileExtensions)
		self.assert_('ext3' in df2.fileExtensions)
		self.assert_(not 'ext' in df2.fileExtensions)
		self.assert_(not '' in df2.fileExtensions)
		self.assert_(not ' ' in df2.fileExtensions)
	
		#-----
	
		df2.removeFileExtension(1)
	
		self.assertRaises(IndexError, df2.removeFileExtension, 2)

		self.assert_(df2.getName() == 'Name')
		self.assert_(df2.name == 'Name')
		self.assert_(df2.getDescription() == 'Description')
		self.assert_(df2.description == 'Description')
		self.assert_(df2.getMimeType() == 'mime/type')
		self.assert_(df2.mimeType == 'mime/type')
		self.assert_(df2.isMultiRecordFormat() == True)
		self.assert_(df2.multiRecordFormat == True)
	
		self.assert_(df2.getNumFileExtensions() == 2)
		self.assert_(df2.numFileExtensions == 2)
		
		self.assert_(df2.getFileExtension(0) == 'ext1')
		self.assert_(df2.fileExtensions[0] == 'ext1')
		self.assert_(df2.getFileExtension(1) == 'ext3')
		self.assert_(df2.fileExtensions[1] == 'ext3')
	
		self.assertRaises(IndexError, df2.getFileExtension, 2)
		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 2)
	
		self.assert_(len(df2.fileExtensions) == 2)
		self.assert_(df2.fileExtensions)
		
		self.assert_(df2.matchesFileExtension('ext1'))
		self.assert_(not df2.matchesFileExtension('ext2'))
		self.assert_(df2.matchesFileExtension('ext3'))
		self.assert_(not df2.matchesFileExtension('ext'))
		self.assert_(not df2.matchesFileExtension(''))
		self.assert_(not df2.matchesFileExtension(' '))

		self.assert_('ext1' in df2.fileExtensions)
		self.assert_(not 'ext2' in df2.fileExtensions)
		self.assert_('ext3' in df2.fileExtensions)
		self.assert_(not 'ext' in df2.fileExtensions)
		self.assert_(not '' in df2.fileExtensions)
		self.assert_(not ' ' in df2.fileExtensions)
		
		#-----
	
		del df2.fileExtensions[0]

		self.assertRaises(IndexError, df2.fileExtensions.__delitem__, 1)
	
		self.assert_(df2.getName() == 'Name')
		self.assert_(df2.name == 'Name')
		self.assert_(df2.getDescription() == 'Description')
		self.assert_(df2.description == 'Description')
		self.assert_(df2.getMimeType() == 'mime/type')
		self.assert_(df2.mimeType == 'mime/type')
		self.assert_(df2.isMultiRecordFormat() == True)
		self.assert_(df2.multiRecordFormat == True)
	
		self.assert_(df2.getNumFileExtensions() == 1)
		self.assert_(df2.numFileExtensions == 1)
		
		self.assert_(df2.getFileExtension(0) == 'ext3')
		self.assert_(df2.fileExtensions[0] == 'ext3')
	
		self.assertRaises(IndexError, df2.getFileExtension, 1)
		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 1)
	
		self.assert_(len(df2.fileExtensions) == 1)
		self.assert_(df2.fileExtensions)
		
		self.assert_(not df2.matchesFileExtension('ext1'))
		self.assert_(not df2.matchesFileExtension('ext2'))
		self.assert_(df2.matchesFileExtension('ext3'))
		self.assert_(not df2.matchesFileExtension('ext'))
		self.assert_(not df2.matchesFileExtension(''))
		self.assert_(not df2.matchesFileExtension(' '))

		self.assert_(not 'ext1' in df2.fileExtensions)
		self.assert_(not 'ext2' in df2.fileExtensions)
		self.assert_('ext3' in df2.fileExtensions)
		self.assert_(not 'ext' in df2.fileExtensions)
		self.assert_(not '' in df2.fileExtensions)
		self.assert_(not ' ' in df2.fileExtensions)
	
		#-----
	
		df2.clearFileExtensions()
	
		self.assert_(df2.getName() == 'Name')
		self.assert_(df2.name == 'Name')
		self.assert_(df2.getDescription() == 'Description')
		self.assert_(df2.description == 'Description')
		self.assert_(df2.getMimeType() == 'mime/type')
		self.assert_(df2.mimeType == 'mime/type')
		self.assert_(df2.isMultiRecordFormat() == True)
		self.assert_(df2.multiRecordFormat == True)
	
		self.assert_(df2.getNumFileExtensions() == 0)
		self.assert_(df2.numFileExtensions == 0)
	
		self.assertRaises(IndexError, df2.getFileExtension, 0)
		self.assertRaises(IndexError, df2.getFileExtension, 1)

		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 0)
		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 1)
	
		self.assert_(len(df2.fileExtensions) == 0)
		self.assert_(not df2.fileExtensions)
	
		#-----
	
		df2.setName('')
	
		self.assert_(df2.getName() == '')
		self.assert_(df2.getDescription() == 'Description')
		self.assert_(df2.getMimeType() == 'mime/type')
		self.assert_(df2.isMultiRecordFormat() == True)
	
		self.assert_(df2.getNumFileExtensions() == 0)
		self.assert_(df2.numFileExtensions == 0)
	
		self.assert_(len(df2.fileExtensions) == 0)
		self.assert_(not df2.fileExtensions)

		self.assertRaises(IndexError, df2.getFileExtension, 0)
		self.assertRaises(IndexError, df2.getFileExtension, 1)

		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 0)
		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 1)
		
		self.assert_(not df2.matchesFileExtension('ext1'))
		self.assert_(not df2.matchesFileExtension('ext2'))
		self.assert_(not df2.matchesFileExtension('ext3'))
		self.assert_(not df2.matchesFileExtension(''))
		self.assert_(not df2.matchesFileExtension(' '))
	
		#-----
	
		df2.setDescription('')
	
		self.assert_(df2.getName() == '')
		self.assert_(df2.getDescription() == '')
		self.assert_(df2.getMimeType() == 'mime/type')
		self.assert_(df2.isMultiRecordFormat() == True)

		self.assert_(df2.getNumFileExtensions() == 0)
		self.assert_(df2.numFileExtensions == 0)

		self.assertRaises(IndexError, df2.getFileExtension, 0)
		self.assertRaises(IndexError, df2.getFileExtension, 1)

		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 0)
		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 1)
	
		self.assert_(len(df2.fileExtensions) == 0)
		self.assert_(not df2.fileExtensions)

		self.assert_(not df2.matchesFileExtension('ext1'))
		self.assert_(not df2.matchesFileExtension('ext2'))
		self.assert_(not df2.matchesFileExtension('ext3'))
		self.assert_(not df2.matchesFileExtension(''))
		self.assert_(not df2.matchesFileExtension(' '))
	
		#-----
	
		df2.setMimeType('')
	
		self.assert_(df2.getName() == '')
		self.assert_(df2.getDescription() == '')
		self.assert_(df2.getMimeType() == '')
		self.assert_(df2.isMultiRecordFormat() == True)

		self.assert_(df2.getNumFileExtensions() == 0)
		self.assert_(df2.numFileExtensions == 0)

		self.assertRaises(IndexError, df2.getFileExtension, 0)
		self.assertRaises(IndexError, df2.getFileExtension, 1)

		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 0)
		self.assertRaises(IndexError, df2.fileExtensions.__getitem__, 1)

		self.assert_(len(df2.fileExtensions) == 0)
		self.assert_(not df2.fileExtensions)

		self.assert_(not df2.matchesFileExtension('ext1'))
		self.assert_(not df2.matchesFileExtension('ext2'))
		self.assert_(not df2.matchesFileExtension('ext3'))
		self.assert_(not df2.matchesFileExtension(''))
		self.assert_(not df2.matchesFileExtension(' '))
	
		#-----
	
		self.assert_(not (df1 == df2))
		self.assert_(df1 != df2)
	
		df2.setName(df1.getName())
	
		self.assert_(not (df1 == df2))
		self.assert_(df1 != df2)
	
		df2.mimeType = df1.mimeType
	
		self.assert_(df1 == df2)
		self.assert_(not (df1 != df2))
	
		#-----

		df3 = DataFormat()

		self.assert_(not (df1 == df3))
		self.assert_(df1 != df3)

		df3.assign(df1)

		self.assert_(df1 == df3)
		self.assert_(not (df1 != df3))

		self.assert_(df1.getName() == df3.name)
		self.assert_(df1.getDescription() == df3.description)
		self.assert_(df1.getMimeType() == df3.mimeType)
		self.assert_(df1.isMultiRecordFormat() == df3.multiRecordFormat)

		self.assert_(df1.getNumFileExtensions() == df3.numFileExtensions)

		#-----

		df4 = DataFormat(df1)
		
		self.assert_(df1 == df4)
		self.assert_(not (df1 != df4))

		self.assert_(df4.getName() == df1.name)
		self.assert_(df4.getDescription() == df1.description)
		self.assert_(df4.getMimeType() == df1.mimeType)
		self.assert_(df4.isMultiRecordFormat() == df1.multiRecordFormat)

		self.assert_(df4.getNumFileExtensions() == df1.numFileExtensions)

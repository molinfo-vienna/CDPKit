## 
# LookupKeyTest.py 
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

from CDPL.Base import LookupKey


class TestCase(unittest.TestCase):

    def checkProperties(self, key):
        self.assert_(key.name == key.getName())
        self.assert_(key.__str__() == ('CDPL.Base.LookupKey(id=' + str(key.getID()) + ', name=\'' + key.getName() + '\')'))
        self.assert_(key.numericID == key.getID())

    def runTest(self):
        """Testing LookupKey"""

        self.checkProperties(LookupKey.NONE)

        self.assert_(LookupKey.NONE.getName() == 'NONE')

        # ---------

        key1 = LookupKey.create('key1')

        self.checkProperties(key1)

        self.assert_(key1.getName() == 'key1')

        key2 = LookupKey.create('key2')

        self.checkProperties(key2)

        self.assert_(key2.getName() == 'key2')

        key1.setName('keyX')

        self.checkProperties(key1)
        
        self.assert_(key1.getName() == 'keyX')
        self.assert_(key2.getName() == 'key2')

        key2.setName('keyY')

        self.checkProperties(key2)

        self.assert_(key1.getName() == 'keyX')
        self.assert_(key2.getName() == 'keyY')

        key2.name = 'keyX'

        self.checkProperties(key2)

        self.assert_(key1.getName() == 'keyX')
        self.assert_(key2.getName() == 'keyX')

        key3 = LookupKey.create('keyX')

        self.checkProperties(key3)

        self.assert_(key1.getName() == 'keyX')
        self.assert_(key2.getName() == 'keyX')
        self.assert_(key3.getName() == 'keyX')

        key1.name = 'keyZ'

        self.checkProperties(key1)

        self.assert_(key1.getName() == 'keyZ')
        self.assert_(key2.getName() == 'keyX')
        self.assert_(key3.getName() == 'keyX')	

        key4 = LookupKey.create('')

        self.checkProperties(key4)

        self.assert_(key4.getName() == '')

        key1.setName('')

        self.checkProperties(key1)

        self.assert_(key1.getName() == '')

        # ---------

        self.assert_(not (key1 == key2))
        self.assert_(key1 != key2)
        self.assert_(key1.getID() != key2.getID())

        self.assert_(key1 < key2)

        key5 = LookupKey(key1)
        
        self.checkProperties(key1)
        self.checkProperties(key5)

        self.assert_(key5.getName() == key1.getName())
        self.assert_(key5.getName() != 'key1')

        key5.name = 'key1'

        self.checkProperties(key1)
        self.checkProperties(key5)

        self.assert_(key5.getName() == 'key1')
        self.assert_(key5.getName() == key1.getName())

        self.assert_(key1 == key5)
        self.assert_(not (key1 != key5))
        self.assert_(key1.getID() == key5.getID())
        
        self.assert_(not (key2 == key5))
        self.assert_(key2 != key5)
        self.assert_(key2.getID() != key5.getID())

        key5.assign(key2)
        
        self.checkProperties(key2)
        self.checkProperties(key5)
        
        self.assert_(key5.getName() == key2.getName())
        self.assert_(key5.getName() != key1.getName())

        self.assert_(key2 == key5)
        self.assert_(not (key2 != key5))
        self.assert_(key2.getID() == key5.getID())

        self.assert_(not (key1 == key5))
        self.assert_(key1 != key5)
        self.assert_(key1.getID() != key5.getID())

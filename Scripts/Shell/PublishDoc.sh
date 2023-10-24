#!/bin/sh

##
# PublishDoc.sh  
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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
##

if [[ $# -ne 2 ]]; then
    echo "Usage: PublishDoc.sh <CDPKit build dir> <Output dir within local CDPKit-Doc repository copy>" >&2
    exit 2
fi

cd $1
make doc

rm -rf $2
cp -r $1/Doc/html $2

cd $2/..
docs-versions-menu --no-downloads-file --no-write-index-html

for i in `find . -name "docs-versions-menu.js"`; do cp docs-versions-menu-cdpkit.js $i; done

git add -A
git commit -a -m "Documentation update"
git push

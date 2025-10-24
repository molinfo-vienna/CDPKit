#!/bin/bash

##
# build_wheels.sh  
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


cd /build/CDPKit
git pull

rm -rf dist

for PY_VERS in 3.8 3.9 3.10 3.11 3.12 3.13 3.13t 3.14 3.14t
do
    PY_VERS_NO_DOT="$(echo $PY_VERS | tr -d .)"
    PY_VERS_NO_DOT_NO_T="$(echo $PY_VERS_NO_DOT | tr -d t)"
    
    for PY_INST in /opt/python/cp*
    do
        if [[ ! $PY_INST =~ ^/opt/python/cp${PY_VERS_NO_DOT_NO_T}-cp${PY_VERS_NO_DOT} ]]; then
            continue;
        fi

        if [[ "$PY_VERS_NO_DOT" = "$PY_VERS_NO_DOT_NO_T" ]]; then
            BOOST_LIBRARYDIR="/usr/local/lib/"
        else
            BOOST_LIBRARYDIR="/usr/local/lib/python_ft/"
        fi
        
        echo "Building wheel for Python version ${PY_VERS}..."
        
        ${PY_INST}/bin/python -m build --wheel \
        -C="--build-option=-DBOOST_LIBRARYDIR=${BOOST_LIBRARYDIR}" \
        -C="--build-option=-DBOOST_PYTHON_VERSIONS=${PY_VERS_NO_DOT_NO_T}" \
        -C="--build-option=-DPYPI_MANYLINUX_PACKAGE_BUILD=TRUE"
        break;
    done
done

cd /build
rm -rf wheelhouse

for WHEEL_FILE in /build/CDPKit/dist/*.whl
do
    auditwheel repair "${WHEEL_FILE}"
done

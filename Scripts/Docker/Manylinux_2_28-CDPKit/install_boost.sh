#!/bin/bash

##
# install_boost.sh
#
# Based on a script written by Barry Muldrey (https://gitlab.com/bjmuld/manylinux-boost)
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2023 Barry Muldrey, Thomas Seidel <thomas.seidel@univie.ac.at>
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


set -exu

PY_VERS_TO_BUILD="$*"

# build all boost-libraries except boost_python
BOOST_ROOT="$( find /boost/* -maxdepth 0 -type d -name 'boost*' )"

echo "Found boost sources at: $BOOST_ROOT"

cd "${BOOST_ROOT}"
./bootstrap.sh --without-libraries=python
./b2 --without-python threading=multi install > /dev/null
./b2 --clean  > /dev/null
./b2 --clean-all > /dev/null

# for each installed python version build only boost_python 
echo "Will try building boost.python for python versions: ${PY_VERS_TO_BUILD}"

for PY_VERS in ${PY_VERS_TO_BUILD}; do
    echo "#####################################################################"
    echo "trying to build python version ${PY_VERS} as requested"
    echo "#####################################################################"

    PY_VERS_NO_T="$(echo $PY_VERS | tr -d t)"
    PY_VERS_NO_DOT="$(echo $PY_VERS | tr -d .)"
    PY_VERS_NO_DOT_NO_T="$(echo $PY_VERS_NO_DOT | tr -d t)"
    CONFIG_FILE="/io/user-config.jam"
    
    if [[ "$PY_VERS_NO_DOT" = "$PY_VERS_NO_DOT_NO_T" ]]; then
        CONFIG_FILE="/io/user-config.jam"
    else
        CONFIG_FILE="/io/user-config-ft.jam"
    fi
    
    found_one=0

    for PYBIN in /opt/python/cp*/bin; do
        if [[ ! $PYBIN =~ ^/opt/python/cp${PY_VERS_NO_DOT_NO_T}-cp${PY_VERS_NO_DOT}/bin ]]; then
            continue;
        else
            found_one=1
        fi

        if [[ $(${PYBIN}/python -c "import sys; print(sys.maxunicode)") == 1114111 ]]; then
            ENCODING="ucs4"
        else
            ENCODING="ucs2"
        fi

        echo "Building boost.python for requested version: ${PY_VERS} using python binary: ${PYBIN} and ENCODING: ${ENCODING}"

        ./bootstrap.sh --with-python="${PYBIN}/python"
        ./b2 \
            --with-python \
            --user-config="${CONFIG_FILE}" \
            --enable-unicode="${ENCODING}" \
            threading=multi \
            python="${PY_VERS_NO_T}" \
            install > /dev/null
        ./b2 --with-python --clean > /dev/null
        ./b2 --with-python --clean-all > /dev/null
        break;
    done

    if [[ $found_one == 0 ]]; then
        echo "Did not find an installed python env at /opt/python/ that matches ${PY_VERS_NO_DOT}"
        exit 1
    fi
done

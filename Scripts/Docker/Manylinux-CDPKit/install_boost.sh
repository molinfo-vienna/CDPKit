#!/bin/bash
# Script based on https://gitlab.com/bjmuld/manylinux-boost

set -exu

PY_VERSIONS_TO_BUILD="$*"

# build all boost-libraries except boost_python
BOOST_ROOT="$( find /boost/* -maxdepth 0 -type d -name 'boost*' )"
echo "Found boost sources at: $BOOST_ROOT"
cd "${BOOST_ROOT}"

./bootstrap.sh --without-libraries=python

./b2 \
    --without-python \
    install > /dev/null

./b2 \
    --clean \
    > /dev/null

./b2 \
    --clean-all \
    > /dev/null

# for each installed python version build only boost_python 
echo "Will try building boost.python for python versions: ${PY_VERSIONS_TO_BUILD}"

for python_version_2_build in ${PY_VERSIONS_TO_BUILD}; do

    echo "#####################################################################"
    echo "trying to build python version ${python_version_2_build} as requested"
    echo "#####################################################################"

    if [[ $python_version_2_build =~ [0-9][.][0-9]*$ ]]; then
        # not unicode suffix
        PYVER_DOT="$python_version_2_build"
        PYVER="$(echo $PYVER_DOT | tr -d .)"
        PY_BID=""
        CONFIG_FILE="/io/user-config.jam"
        echo "no unicode suffix"

    elif [[ $python_version_2_build =~ [0-9][.][0-9]*u$ ]]; then
        PYVER_DOT="$(echo $python_version_2_build | tr -d u)"
        PYVER="$(echo $PYVER_DOT | tr -d .)"
        PY_BID="u"
        CONFIG_FILE="/io/user-config.unicode.jam"
        echo "with unicode suffix"
    else
        echo "Requested python version: \"${python_version_2_build}\" doesn\'t match any known patterns"
        exit 1;
    fi

    found_one=0

    for PYBIN in /opt/python/cp*/bin; do

        if [[ ! $PYBIN =~ ^/opt/python/cp${PYVER}-* ]]; then
            continue;
        else
            found_one=1
        fi

        if [[ $(${PYBIN}/python -c "import sys; print(sys.maxunicode)")  == 1114111 ]]; then
            ENCODING="ucs4"
        else
            ENCODING="ucs2"
        fi

        echo "Building boost.python for requested version: ${python_version_2_build} using python binary: ${PYBIN} (PYVER: ${PYVER} and PYVER_DOT: ${PYVER_DOT} and ENCODING: ${ENCODING})"

        #./bootstrap.sh --prefix=/usr --libdir=/usr/lib64 --includedir=/usr/include
        ./bootstrap.sh --with-python="${PYBIN}/python"

        ./b2 \
            --with-python \
            --user-config="${CONFIG_FILE}" \
            --python-buildid=${PY_BID} \
            --enable-unicode="${ENCODING}" \
            python="${PYVER_DOT}" \
            install > /dev/null

        ./b2 \
            --with-python \
            --clean \
            > /dev/null

        ./b2 \
            --with-python \
            --clean-all \
            > /dev/null

        break;

    done

    if [[ $found_one == 0 ]]; then
        echo "Did not find an installed python env at /opt/python/ that matches ${PYVER}"
        exit 1
    fi
done

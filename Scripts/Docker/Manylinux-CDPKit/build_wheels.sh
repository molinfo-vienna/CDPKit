#!/bin/bash

cd /build/CDPKit
git pull

rm -rf dist

for PY_VERS in 3.6 3.7 3.8 3.9 3.10 3.11
do
    PY_VERS_NO_DOT="$(echo $PY_VERS | tr -d .)"

    for PY_INST in /opt/python/cp*
    do
        if [[ ! $PY_INST =~ ^/opt/python/cp${PY_VERS_NO_DOT}-* ]]; then
            continue;
        fi

        echo "Building wheel for Python version ${PY_VERS}..."

        ${PY_INST}/bin/python setup.py bdist_wheel -DBOOST_PYTHON_VERSIONS="${PY_VERS_NO_DOT}" -DIGNORE_PYTHON_DEVEL_NOT_FOUND=TRUE
    done
done

rm -rf ../wheels
mv dist ../wheels

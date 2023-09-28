#!/bin/bash

for py_dir in /opt/python/cp*
do
    $py_dir/bin/pip install scikit-build
done

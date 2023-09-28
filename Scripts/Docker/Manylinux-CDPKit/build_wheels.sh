#!/bin/bash

cd /build/CDPKit
git pull

for py_dir in /opt/python/cp*
do
    echo $py_dir
done

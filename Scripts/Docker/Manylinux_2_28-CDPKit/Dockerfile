##
# Dockerfile
#
# Based on work by Barry Muldrey (https://gitlab.com/bjmuld/manylinux-boost)
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

# fetch base image
FROM quay.io/pypa/manylinux_2_28_x86_64

# do a dnf install
RUN dnf install -y automake autoconf libtool emacs cppunit-devel zlib-devel bzip2-devel cairo-devel git ninja-build

# inject files
COPY . /io
ADD https://boostorg.jfrog.io/artifactory/main/release/1.86.0/source/boost_1_86_0.tar.gz /io/boost.tgz

# unpack boost
RUN mkdir /boost
RUN tar -xzf /io/boost.tgz -C /boost/

# run boost build script
RUN chmod +x /io/install_boost.sh
RUN /io/install_boost.sh "3.6 3.7 3.8 3.9 3.10 3.11 3.12 3.13"

# install required pip packages for all versions
RUN chmod +x /io/install_pip_packages.sh
RUN /io/install_pip_packages.sh

# setup the wheel build folder
RUN mkdir /build
RUN mv /io/build_wheels.sh /build
RUN chmod +x /build/build_wheels.sh

# fetch CDPKit sources from the github repo
RUN git clone https://github.com/molinfo-vienna/CDPKit.git /build/CDPKit

# cleanup
RUN rm -rf /io/*
RUN rm -rf /boost

# Dockerfile based on https://gitlab.com/bjmuld/manylinux-boost

FROM quay.io/pypa/manylinux2014_x86_64

# do a yum install
RUN yum install -y automake autoconf libtool emacs cppunit-devel zlib-devel bzip2-devel cairo-devel

# inject files
COPY . /io
ADD https://boostorg.jfrog.io/artifactory/main/release/1.80.0/source/boost_1_80_0.tar.gz /io/boost.tgz

# unpack boost
RUN mkdir /boost
RUN tar -xzf /io/boost.tgz -C /boost/

## run boost build script
RUN chmod +x /io/install_boost.sh
RUN /io/install_boost.sh "3.6 3.7 3.8 3.9 3.10 3.11"

## cleanup
RUN rm -rf /io

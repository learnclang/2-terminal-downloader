#!/bin/bash
# NOTE: All additinal arguments are passed to cmake unaltered

curl_dir=`dirname $(cd ${0%/*} && echo $PWD/${0##*/})`/../lib/curl/any/noarch
if [ ! -d $curl_dir ]; then
	echo "ERROR: curl source directory at $curl_dir didn't exist - please use 'git submodule update --init --recursive' to put it there and rerun this script" 1>&2
	exit 2
fi
build_dir=$curl_dir/build/auto-build
if [ -d $build_dir ]; then
	echo "WARNING: curl build directory at $build_dir already exists - reconfiguration might not yield expected results. Removed directory if in doubt and rerun this script" 1>&2
fi
mkdir -p $build_dir
cd $build_dir
install_dir=$build_dir/install

cmake ../.. -DCMAKE_BUILD_TYPE=Release \
            -DCURL_STATICLIB=on \
            -DHTTP_ONLY=on \
       		-DCMAKE_INSTALL_PREFIX=$install_dir \
       		-DBUILD_CURL_TESTS=off \
       		-DBUILD_CURL_EXE=off \
       		-DCMAKE_USE_OPENSSL=off \
       		-DCURL_ZLIB=off \
       		-DCURL_DISABLE_LDAP=off \
       		-DCURL_DISABLE_LDAPS=off \
       		-DCURL_DISABLE_CRYPTO_AUTH=off \
       		"$@" || { echo "CMAKE FAILED - please check output and fix this script" && exit 1; }

export MAKEFLAGS="-j4"
cmake --build . --config Release --target install || exit $?
echo "Installation built successfully. You should now copy the build result at '$install_dir' to lib/<curl-version>/<curl-platform> and add it to git"
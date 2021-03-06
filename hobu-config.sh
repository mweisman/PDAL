USR_LOCAL="/usr/local"
USR="/usr"
TIFF_HOME=$USR_LOCAL
LASZIP_HOME=$USR_LOCAL
LIBXML2_HOME=$USR
GEOTIFF_HOME=$USR_LOCAL
P2G_HOME=$USR_LOCAL
SO_EXT=dylib
EMBED=ON
CC=/Users/hobu/bin/clang
CXX=/Users/hobu/bin/clang++

ORACLE_HOME=$HOME/oracle
export ORACLE_HOME
CONFIG="Unix Makefiles"

if ! [ -z "$1" ]; then
    CONFIG="$1"
fi

cmake   -G "$CONFIG"  \
        -DCMAKE_BUILD_TYPE=RelWithDebInfo \
        -DCMAKE_INSTALL_PREFIX=/Users/hobu \
        -DPDAL_EMBED_BOOST=${EMBED} \
        -DWITH_GDAL=ON \
        -DWITH_ICONV=ON \
        -DWITH_ORACLE=ON \
        -DWITH_GEOTIFF=ON \
        -DWITH_LASZIP=ON \
        -DWITH_LIBXML2=ON \
        -DWITH_PYTHON=ON \
        -DWITH_FLANN=ON \
        -DWITH_SOCI=ON \
        -DWITH_P2G=ON \
        -DGEOTIFF_INCLUDE_DIR=${GEOTIFF_HOME}/include/ \
        -DGEOTIFF_LIBRARY=${GEOTIFF_HOME}/lib/libgeotiff.${SO_EXT} \
        -DICONV_INCLUDE_DIR=/usr/include \
        -DP2G_INCLUDE_DIR=${P2G_HOME}/include \
        -DP2G_LIBRARY=${P2G_HOME}/lib/libpts2grd.${SO_EXT} \
        -DLASZIP_INCLUDE_DIR=${LASZIP_HOME}/include \
        -DLASZIP_LIBRARY=${LASZIP_HOME}/lib/liblaszip.${SO_EXT} \
        -DLIBXML2_INCLUDE_DIR=${LIBXML2_HOME}/include/libxml2 \
        -DLIBXML2_LIBRARIES=${LIBXML2_HOME}/lib/libxml2.${SO_EXT} \
        -DTIFF_INCLUDE_DIR=/${TIFF_HOME}/include \
        -DTIFF_LIBRARY=${TIFF_HOME}/lib/libtiff.${SO_EXT} 

    # -DUSE_PDAL_PLUGIN_SOCI=ON \
    # -DUSE_PDAL_PLUGIN_PCD=ON \
    # -DUSE_PDAL_PLUGIN_OCI=ON \
    # -DUSE_PDAL_PLUGIN_TEXT=ON \

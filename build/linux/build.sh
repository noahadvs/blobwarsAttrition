#!/bin/bash -e

cd `dirname $0`

BUILDROOT="build/linux"

cd ../..

VERSION=$1

make clean
make src-dist

make clean
make LOCALE_DIR=locale
make dist

rm -rf blobWarsAttrition

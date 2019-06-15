#!/bin/bash

version="1.2.2"

wget --quiet "https://github.com/USCiLab/cereal/archive/v${version}.tar.gz"

tar xzf "v${version}.tar.gz"
# x: This option tells tar to extract the files.
# v: The “v” stands for “verbose.” This option will list all of the files one by one in the archive.
# z: The z option is very important and tells the tar command to uncompress the file (gzip).
# f: This options tells tar that you are going to give it a file name to work with.

rm "v${version}.tar.gz"

find "./cereal-${version}" -mindepth 1 -maxdepth 1 ! -iname "include" -exec rm -rf {} \;


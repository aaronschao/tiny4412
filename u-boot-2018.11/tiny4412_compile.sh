#!/bin/sh

SD_PATH=$1
if [ -z "$SD_PATH" ]; then
    echo "sd card path is error, please input again"
    exit 1
fi

if [ "${TOPDIR}" = "" ]; then
    echo "+++++++++++++++++++++++++++++++++++++++++++++++++"
    echo
    echo "\033[31mno configuration environment!!!!!!!!!!\033[0m"
    echo "eg: cd .. && source set_env"
    echo
    echo "+++++++++++++++++++++++++++++++++++++++++++++++++"
    exit 1
fi



make distclean

make tiny4412_defconfig

make -j`nproc`


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

INSTALL_DIR=${TOPDIR}/net_system/tftp

make distclean

make tiny4412_defconfig

make -j`nproc`

[ -z "${INSTALL_DIR}" ] && mkdir -p ${INSTALL_DIR}
cp arch/arm/boot/zImage ${INSTALL_DIR}
cp arch/arm/boot/dts/exynos4412-tiny4412.dtb ${INSTALL_DIR}

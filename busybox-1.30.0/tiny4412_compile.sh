#!/bin/sh

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

[ ! -d "${TOPDIR}/net_system/nfs" ] && mkdir ${TOPDIR}/net_system/nfs
rm ${TOPDIR}/net_system/nfs/* -rf
make install

cd  ${TOPDIR}/net_system/nfs

[ ! -d "dev" ] && mkdir dev
[ ! -e "dev/console" ] && sudo mknod dev/console c 5 1
[ ! -e "dev/null" ] && sudo mknod dev/null c 1 3

[ ! -d "proc" ] && mkdir proc
[ ! -d 'sys' ] && mkdir sys

[ ! -d "etc" ] && mkdir etc
echo "proc  /proc   proc    defaults    0   0"  >   ./etc/fstab
echo "sysfs /sys    sysfs   defaults    0   0"  >>  ./etc/fstab
echo "::sysinit:/etc/init.d/rcS"    >   ./etc/inittab
echo "console::askfirst:-/bin/sh"   >>  ./etc/inittab
echo "::ctrlaltdel:/sbin/reboot"    >>  ./etc/inittab
echo "::shutdown:/bin/umount -a -r" >>  ./etc/inittab
[ ! -d "etc/init.d" ] && mkdir etc/init.d
echo "#!/bin/sh"    >   ./etc/init.d/rcS
echo "mount -a"     >>  ./etc/init.d/rcS
chmod +x ./etc/init.d/rcS

[ ! -d "lib" ] && mkdir lib
cp -rfd ${TOPDIR}/buildroot-2022.02.9/output/host/arm-buildroot-linux-gnueabihf/sysroot/lib/*.so* lib

cd ${TOPDIR}

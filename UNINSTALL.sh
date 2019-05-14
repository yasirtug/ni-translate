#!/bin/bash
if ! [ $(id -u) = 0 ]; then
   echo "Please run as root!"
   exit 1
fi
systemctl stop ni-translate.service
rm -f /etc/systemd/system/ni-translate.service
rm -f /usr/bin/ni-translate
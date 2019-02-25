if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

systemctl stop ni-translate.service
rm -f /etc/systemd/system/ni-translate.service
rm -f /usr/bin/ni-translate
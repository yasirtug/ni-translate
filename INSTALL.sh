# will create a new service, copy ni-translate executable file into /usr/bin/ and start the service.

# check for running as root
if [ "$EUID" -ne 0 ]
  then echo "Please run as root"
  exit
fi

cat > /etc/systemd/system/ni-translate.service << EOF1
[Unit]
Description=ni-translate service/
After=x11-common
StartLimitIntervalSec=0

[Service]
Environment="DISPLAY=:0"
Environment="XAUTHORITY=$XAUTHORITY"
User=root
Restart=always
RestartSec=5
ExecStart=/usr/bin/env ni-translate

[Install]
WantedBy = multi-user.target
EOF1
cp ./ni-translate /usr/bin/
systemctl enable ni-translate.service
systemctl start ni-translate.service
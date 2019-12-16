#!/bin/bash

# check if running as root
if [ $(id -u) = 0 ]; 
then
	echo "Please run without root privileges."
	exit 1
fi

# create autostart file
echo "[Desktop Entry]
Type=Application
Terminal=false
Exec=$HOME/.local/bin/ni-translate
Name=ni-translate" >> $HOME/.config/autostart/ni-translate.desktop

# copy executable file
mkdir -p $HOME/.local $HOME/.local/bin 
cp -r ./ni-translate $HOME/.local/bin

# run file
$HOME/.local/bin/ni-translate &

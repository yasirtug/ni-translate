#!/bin/bash

# check if running as root
if [ $(id -u) = 0 ]; 
then
	echo "Please run without root privileges."
	exit 1
fi

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"


# kill previous running processes
killall -q ni-translate

# create autostart file
mkdir -p $HOME/.config/autostart
echo "[Desktop Entry]
Type=Application
Terminal=false
Exec=$HOME/.local/bin/ni-translate
Name=ni-translate
Icon=ni-translate" > $HOME/.config/autostart/ni-translate.desktop

# copy executable file
mkdir -p $HOME/.local/bin 
cp -r ./ni-translate $HOME/.local/bin

# copy icon file
mkdir -p $HOME/.local/share/icons
cp $SCRIPT_DIR/resources/icon.png $HOME/.local/share/icons/ni-translate.png

# run file
$HOME/.local/bin/ni-translate &

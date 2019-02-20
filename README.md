
![Screenshot](screenshot.png)

Because of the background keyboard watching, it needs to run with root privileges.

Build Steps:

Install qmake and base Qt 5 development files:\
`sudo apt-get install qt5-default`

Create a folder for build files and `cd` into it.\
Run this from your folder:\
`qmake <project_files_folder>/ni-translate.pro -spec linux-g++`\
This should have extracted Makefile in your build folder. Run `make` there.

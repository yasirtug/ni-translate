# ni-translate

![Screenshot](screenshot.png)

Because of the background keyboard watching, it needs to run with root privileges.

## Build Steps:
### 1. Install dependencies:
- Install qmake and base Qt5 development files:

    `sudo apt-get install qt5-default`

## 2. Build project:

- Create a folder for build files and `cd` into it.
- Run this command from your folder:

    `qmake <project_files_folder>/ni-translate.pro -spec linux-g++`

- This should have extracted Makefile in your build folder.
- Run `make` there.

## 3. Install:
- To install, run this from the build folder.

    `sudo <project_files_folder>/INSTALL.sh`

- This will create a new service, copy `ni-translate` executable file into `/usr/bin/` and enable the service.

- It will also start the service and program will appear.
- Default hotkey is Caps Lock key.
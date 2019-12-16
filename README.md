# ni-translate

![Screenshot](screenshot.png)

## Build Steps:
### 1. Install dependencies:
- Install qmake and base Qt5 development files:

    `sudo apt-get install qt5-default`
    
- Install XInput2 extension:

    `sudo apt-get install libxi-dev`

## 2. Build project:

- Create a folder for build files and `cd` into it.
- Run this command from your folder:

    `qmake <project_files_folder>/ni-translate.pro -spec linux-g++`

- This should have extracted Makefile in your build folder.
- Run `make` there.

## 3. Install:
- To install, run this from the build folder:

    `<project_files_folder>/INSTALL.sh`
    
    This will create a desktop file in `~/.config/autostart`, copy executable file into `~/.local/bin` and run the program for the first time.

Default hotkey is Caps Lock key.

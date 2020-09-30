### This project is not being maintained. See [Crow Translate](https://github.com/crow-translate/crow-translate).
# ni-translate

![](action.gif)

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

Default hotkey should be Caps Lock. You can change it from the settings menu.

## OCR

![](ocr_action.gif)

There is also an experimantal OCR feature implemented using [Tesseract](https://github.com/tesseract-ocr/tesseract). 

- To enable it, you should install libtesseract and build the project with `ocr` config:

    `sudo apt-get install libtesseract-dev`\
    `sudo apt-get install tesseract-ocr-eng`\
    `qmake <project_files_folder>/ni-translate.pro -spec linux-g++ -config ocr`

- It may be necessary to force rebuild after config change:
    
    `make clean`\
    `make`
    
Language files you installed will be available to select in the settings menu.

`sudo apt-get install tesseract-ocr-jpn`

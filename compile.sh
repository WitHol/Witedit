#!/bin/bash

gcc src/main.cpp src/editor_window/editor_window.cpp src/key_detection/key_detection-windows.cpp src/extras/extras.cpp src/file_management/text_file.cpp -o wited.exe -lncurses -DNCURSES_STATIC -lstdc++
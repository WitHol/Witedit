gcc src/main.cpp src/terminal_windows/editor_window.cpp src/terminal_windows/text_window.cpp src/key_detection/key_detection-windows.cpp src/extras/extras.cpp src/file_management/text_file.cpp -o wited.exe -lncursesw -DNCURSES_STATIC -lstdc++
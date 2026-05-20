g++ main.cpp sample_backend.cpp sample_display_terminal.cpp -o sample
./sample.exe
sample.exe



g++ main.cpp sample_backend.cpp sample_display_terminal.cpp sample_frontend.cpp -o scheduler




g++ sample.cpp sample_frontend.cpp sample_backend.cpp sample_display_terminal.cpp -o sample -lsfml-graphics -lsfml-window -lsfml-system
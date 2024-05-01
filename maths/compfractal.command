g++ ../maths/fractal.cpp -I .. -o fractal.out -std=c++11 $(pkg-config --libs --cflags raylib)

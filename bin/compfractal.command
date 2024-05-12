# run this in terminal to compile fractal.cpp file with raylib library
# you can ./ this on mac, idk about windows tho
g++ ../maths/fractal.cpp -I .. -o fractal.out -std=c++11 $(pkg-config --libs --cflags raylib)

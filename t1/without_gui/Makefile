FILES = $(wildcard ./*.cpp)
all:
	g++ $(FILES) -o gomoku `pkg-config gtkmm-3.0 --cflags --libs` -Wall -Werror -std=c++14 
#!/usr/bin/env bash
make -C libft/
gcc -o col_game *.c -I./ -I./libft/ libft/libft.a 'sdl2-config --cflags' 'sdl2-config --libs' -lm

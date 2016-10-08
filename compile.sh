#!/usr/bin/env bash
make -C libft/
gcc -o col_game *.c -I./ -I./libft/ libft/libft.a -I/usr/include/SDL2 -D_REENTRANT -L/usr/lib/x86_64-linux-gnu -lSDL2 -lm

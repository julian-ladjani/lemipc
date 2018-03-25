/*
** EPITECH PROJECT, 2018
** PSU_lemipc_2017
** File description:
** 	display source file
*/

#include <ncurses.h>
#include "struct.h"

void init_display()
{
	initscr();
	noecho();
	curs_set(FALSE);
}

void clean_display()
{
	endwin();
}

void display_players(lemipc_shared_struct_t *shared_struct)
{
	int i;

	mvprintw(0, 0, "#");
	for (i = 0; i < map_width; i++) {
		mvprintw(i + 1, 0, "#%s#", shared_struct->map[i]);
	}
	mvprintw(i + 1, 0, "*");
	refresh();
}
/*
Originally from https://rosettacode.org/wiki/Towers_of_Hanoi#C
Fixed and formatted to follow https://suckless.org/coding_style/
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hanoi.h"


Tower *
new_tower(int cap)
{
	Tower *t = calloc(1, sizeof (Tower) + sizeof (int) * cap);
	t->disks = (int *)(t + 1);
	return t;
}

void
text(int y, int i, int d, const char *s)
{
	printf("\033[%d;%dH", 
		height - y + 1, 
		(height + 1) * (2 * i + 1) - d);
	while (d--)
		fputs(s, stdout);
}

void
add_disk(int i, int d)
{
	towers[i]->disks[towers[i]->size++] = d;
	text(towers[i]->size, i, d, TOWER_BLOCK);

	nanosleep((const struct timespec[]){{0, SLEEP_TIME}}, NULL);
	fflush(stdout);
}

int
remove_disk(int i)
{
	int d = towers[i]->disks[--towers[i]->size];
	text(towers[i]->size + 1, i, d, EMPTY_BLOCK);
	return d;
}

void
move(int n, int from, int to, int via)
{
	if (!n)
		return;
	move(n - 1, from, via, to);
	add_disk(to, remove_disk(from));
	move(n - 1, via, to, from);
}


int
main(int argc, char *argv[])
{
	puts("\033[H\033[J");

	if (argc <= 1 || (height = atoi(argv[1])) <= 0)
		height = 8;
	for (argc = 0; argc < N_TOWERS; argc++)
		towers[argc] = new_tower(height);
	for (argc = height; argc; argc--)
		add_disk(0, argc);

	move(height, 0, 2, 1);
	text(1, 0, 1, "\n");
	return 0;
}

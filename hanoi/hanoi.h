#ifndef HANOI_H
#define HANOI_H

#define NS_MULTIPLIER	1000000
#define SLEEP_TIME		50 * NS_MULTIPLIER /* 50 ms */
#define TOWER_BLOCK		"=="
#define EMPTY_BLOCK		"  "
#define N_TOWERS		3

typedef struct Tower { int *disks, size; } Tower;

Tower	*towers[N_TOWERS];
int		 height;

Tower	*new_tower(int cap);
void	 text(int y, int i, int d, const char *s);
void	 add_disk(int i, int d);
int		 remove_disk(int i);
void	 move(int n, int from, int to, int via);

#endif /* HANOI_H */

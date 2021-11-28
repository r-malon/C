#ifndef HANOI
#define HANOI

#define SLEEP_TIME 100000

typedef struct Tower { int *x, n; } Tower;

Tower *t[3];
int    height;

Tower *new_tower(int cap);
void text(int y, int i, int d, const char *s);
void add_disk(int i, int d);
int remove_disk(int i);
void move(int n, int from, int to, int via);

#endif /* HANOI */

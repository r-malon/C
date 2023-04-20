size_t
count(const char *s, char c)
{
	size_t r = 0;
	for (; *s; s++)
		r += (*s == c);
	return r;
}

double
notetohertz(char note[])
{
	if (strlen(note) < 1)
		return 0;
	double val = 0;
	char substr[10];
	int posStr = 1, curr = 0;
	posStr += val += count(note, '#');
	val -= count(note, 'b');
	posStr += count(note, 'b');

	switch (note[0]) {
	case 'A': case 'B': case 'E': case 'D':
	case 'G': val += 2;
	case 'C':
	case 'F': val++;
	default: break;
	}
	while (curr < strlen(note)) {
		substr[curr] = note[posStr + curr];
		curr++;
	}
	substr[curr] = '\0';
	int n_octaves = atoi(substr);
	if (substr[0] == '\0')
		n_octaves = 4; /* default */
	val += 12 * n_octaves;
	return 440.0 * pow(2.0, (val - 58.0)/12.0);
}

char *
hertztonote(double hertz)
{
	if (hertz < 16.35)
		return "";
	char nota[20], octaves[18];
	double val = round(log10(hertz/440.0) / log10(2.0)*12.0 + 58.0);
	int n_octaves = (int)floor(val/12);
	val -= n_octaves*12;
	/* B C C# D D# E F F# G G# A A# */
	nota[0] = (--val >= 0) ? (--val>0) ? ((val-=2)>0) ? 
	  ((val-=2) >= 0) ? (--val > 0) ? ((val-=2) > 0) ? 
	  ((val-=2) > 0) ? '.' : 'A' : 'G' : 'F' : 'E' : 'D' : 'C' : 'B';
	if (nota[0] == 'B')
		n_octaves--;
	itoa(n_octaves, octaves, 10);
	strcat(nota, (val == 0) ? '#' : '');
	strcat(nota, octaves);
	nota[strlen(nota)] = '\0';
	char *ret = malloc(strlen(nota));
	strcpy(ret, nota);
	return ret;
}

void
list_notes(int amount)
{
	for (double n = 1.0; n <= amount; n++) {
		double Hz = 440.0 * pow(2.0, (n - 58.0)/12.0);
		char *Nt = hertztonote(Hz);
		printf("%s - %.2fHz (%d)\n", hertztonote(Hz), notetohertz(Nt), (int)n);
	}
}

#include <fcntl.h>
#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>

int main(int c, char **v)
{
    	char *line;
    	int r = 1;
    	int or;
	int nbl;
    	line = NULL;
	int cc;
    	if (c == 2)
	{
		printf("Trying basic input :\n");
		or = open(v[1], O_RDONLY);
    		while (r == 1)
    		{
    			r = get_next_line(or, &line);
    			printf("%d|%s\n", r, line);
    			free(line);
    		}
	}
	else if (c == 3)
	{
		printf("calling gnl after it returns 0 :\n");
		nbl = atoi(v[2]);
		or = open(v[1], O_RDONLY);
		while (nbl > 0)
		{
			r = get_next_line(or, &line);
			printf("%d|%s\n", r, line);
			free(line);
			nbl--;	
		}
	}
	else
	{
		printf("1 - Trying NULL parameter :\n");
		printf("2 - Trying invalid fd :\n");
		printf("3 - Try to read from stdin :\n");
		scanf("%d", &cc);
		or = open("main.c", O_RDONLY);
		if (cc == 1)	
		{
			while (r == 1)
			{
			r = get_next_line(or, NULL);
			printf("%d || %s\n", r, line);
			}
		}
		else if (cc == 2)
		{
			while (r == 1)
			{
			r = get_next_line(-1, &line);
			printf("%d || %s\n", r, line);
			}
		}
		else if (cc == 3)
		{
			while (r == 1)
			{
				r = get_next_line(0, &line);
				printf("%d || %s\n", r, line);
				free(line);
			}
		}
	}
    	return (0);
}
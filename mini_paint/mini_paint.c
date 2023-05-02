#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_zone
{
	int		w;
	int		h;
	char	c;

}	t_zone;

typedef struct s_forma
{
	char	type;
	float	x;
	float	y;
	float	r;
	char	c;

}	t_forma;

int	main(int argc, char **argv)
{
	int		y;
	int		x;
	FILE	*fl;
	char	mat[300][300];
	t_zone	zone;
	t_forma	forma;
	float	dist;
	int		check;

	if (argc != 2)
		return(write(1, "Error: Argument\n", 16) - 15);
	fl = fopen(argv[1], "r");
	if (!fl)
		return(write(1, "Error: Operation file corrupted\n", 32) - 31);
	if (fscanf(fl, "%d %d %c\n", &zone.w, &zone.h, &zone.c) != 3 || zone.w <= 0 || zone.h <= 0 || zone.w > 300 || zone.h > 300)
		return(write(1, "Error: Operation file corrupted\n", 32) - 31);
	y = 0;
	while (y < zone.h)
	{
		x = 0;
		while (x < zone.w)
		{
			mat[y][x] = zone.c;
			x++;
		}
		y++;
	}
	check = -1;
	while ((check = fscanf(fl, " %c %f %f %f %c", &forma.type, &forma.x, &forma.y, &forma.r,
		&forma.c)) == 5)
	{
		if (forma.r <= 0 || (forma.type != 'c' && forma.type != 'C'))
			return(write(1, "Error: Operation file corrupted\n", 32) - 31);
		y = 0;
		while (y < zone.h)
		{
			x = 0;
			while (x < zone.w)
			{
				dist = sqrtf((x - forma.x) * (x - forma.x) + (y - forma.y) * (y - forma.y));
				if ((forma.r - dist) < 1 && (forma.r - dist) >= 0 && forma.type == 'c')
					mat[y][x] = forma.c;
				else if (dist <= forma.r && forma.type == 'C')
					mat[y][x] = forma.c;
				x++;
			}
			y++;
		}
	}
	if (check != 5 && check != -1)
		return(write(1, "Error: Operation file corrupted\n", 32) - 31);
	y = 0;
	while (y < zone.h)
	{
		x = 0;
		while (x < zone.w)
		{
			write(1, &mat[y][x], 1);
			x++;
		}
		y++;
		write(1, "\n", 1);
	}
}

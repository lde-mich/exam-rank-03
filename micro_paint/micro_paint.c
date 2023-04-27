/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:58:08 by lde-mich          #+#    #+#             */
/*   Updated: 2023/04/27 16:46:22 by lde-mich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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
	float	w;
	float	h;
	char	c;

}	t_forma;

int	main(int argc, char **argv)
{
	int		i;
	int		j;
	FILE	*fl;
	char	mat[300][300];
	t_zone	zone;
	t_forma	forma;
	int		check;

	if (argc != 2)
		return(write(1, "Error: Argument\n", 16) - 15);
	fl = fopen(argv[1], "r");
	if (!fl)
		return(write(1, "Error: Operation file corrupted\n", 32) - 31);
	if (fscanf(fl, "%d %d %c\n", &zone.w, &zone.h, &zone.c) != 3 || zone.w <= 0 || zone.h <= 0 || zone.w > 300 || zone.h > 300)
		return(write(1, "Error: Operation file corrupted\n", 32) - 31);
	i = 0;
	while (i < zone.h)
	{
		j = 0;
		while (j < zone.w)
		{
			mat[i][j] = zone.c;
			j++;
		}
		i++;
	}
	check = -1;
	while ((check = fscanf(fl, " %c %f %f %f %f %c\n", &forma.type, &forma.x, &forma.y, &forma.w,
		&forma.h, &forma.c)) == 6)
	{
		if (forma.w <= 0 || forma.h <= 0 || (forma.type != 'r' && forma.type != 'R'))
			return(write(1, "Error: Operation file corrupted\n", 32) - 31);
		i = 0;
		while (i < zone.h)
		{
			j = 0;
			while (j < zone.w)
			{
				if (forma.x <= j && j <= forma.w + forma.x && forma.y <= i && i <= forma.h + forma.y)
				{
					if(i < forma.y + 1 || j <= forma.x + 1 || i >= forma.h + forma.y - 1 || j > forma.w + forma.x - 1)
						mat[i][j] = forma.c;
					else if (forma.type == 'R')
						mat[i][j] = forma.c;
						
				}
				j++;
			}
			i++;
		}
	}
	if (check != 6 && check != -1)
		return(write(1, "Error: Operation file corrupted\n", 32) - 31);
	i = 0;
	while (i < zone.h)
	{
		j = 0;
		while (j < zone.w)
		{
			write(1, &mat[i][j], 1);
			j++;
		}
		i++;
		write(1, "\n", 1);
	}
	return (0);
}

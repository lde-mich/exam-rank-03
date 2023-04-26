/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:58:08 by lde-mich          #+#    #+#             */
/*   Updated: 2023/04/26 12:50:04 by lde-mich         ###   ########.fr       */
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

int	main(void)
{
	int		i;
	int		j;
	FILE	*fl;
	char	mat[300][300];
	t_zone	zone;
	t_forma	forma;

	fl = fopen("test1.txt", "r");
	fscanf(fl, "%d %d %c", &zone.w, &zone.h, &zone.c);
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
	while (fscanf(fl, " %c %f %f %f %f %c", &forma.type, &forma.x, &forma.y, &forma.w,
		&forma.h, &forma.c) != -1)
	{
		i = 0;
		while (i < zone.h)
		{
			j = 0;
			while (j < zone.w)
			{
				if (forma.x <= j && j <= forma.w + forma.x && forma.y <= i && i <= forma.h + forma.y)
				{
					if((i >= forma.y && i <= forma.y + 1) || (j >= forma.x && j <= forma.x + 1)
					|| (i <= forma.h + forma.y && i >= forma.h + forma.y - 1) || (j <= forma.w + forma.x && j >= forma.w + forma.x - 1))
						mat[i][j] = forma.c;
					else if (forma.type == 'R')
						mat[i][j] = forma.c;
						
				}
				j++;
			}
			i++;
		}
	}
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
}

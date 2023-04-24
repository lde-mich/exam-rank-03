/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:58:08 by lde-mich          #+#    #+#             */
/*   Updated: 2023/04/24 18:01:02 by lde-mich         ###   ########.fr       */
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
	int		l;
	FILE	*fl;
	char	backg[300][300];
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
			backg[i][j] = zone.c;
			j++;
		}
		i++;
	}
	fscanf(fl, " %c %f %f %f %f %c", &forma.type, &forma.x, &forma.y, &forma.w,
		&forma.h, &forma.c);
	i = 0;
	while (i < forma.h)
	{
		j = 0;
		while (j < forma.w)
		{
			if (forma.x <= j <= forma.w && forma.y <= i <= forma.h)
				backg[i][j] = forma.c;
			j++;
		}
		i++;
	}
	i = 0;
	while (i < zone.h)
	{
		j = 0;
		while (j < zone.w)
		{
			write(1, &backg[i][j], 1);
			j++;
		}
		i++;
		write(1, "\n", 1);
	}
}

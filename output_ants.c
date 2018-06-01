/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_ants.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismus <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 16:27:11 by ismus             #+#    #+#             */
/*   Updated: 2018/05/15 16:27:11 by ismus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	print_step(t_way *way, int k)
{
	int i;
	int q;

	k = 0;
	q = 0;
	while (way && way->way)
	{
		i = -1;
		while (++i < way->len)
		{
			if (way->an_w[i] && way->way[i])
			{
				q++;
				if (k == 0)
				{
					ft_printf("%s-%s", way->an_w[i], way->way[i]);
					++k;
				}
				else
					ft_printf(" %s-%s", way->an_w[i], way->way[i]);
			}
		}
		way = way->next;
	}
	return (q != 0 ? ft_printf("\n") : 0);
}

static void	make_step(t_way *way)
{
	int i;

	while (way && way->way)
	{
		i = way->len - 1;
		while (i >= -1)
		{
			if (i == -1)
				way->an_w[0] = 0;
			else if (i == way->len - 1 && way->an_w[i])
			{
				free(way->an_w[i]);
				way->an_w[i] = 0;
			}
			else if (i != way->len - 1)
			{
				way->an_w[i + 1] = way->an_w[i];
			}
			i--;
		}
		way = way->next;
	}
}

static int	new_ants(t_way *way, int n, int an)
{
	int	l;

	l = way->len + 1;
	way->an_w[0] = joinfree("L\0", ft_itoa(an), 2);
	an++;
	if (an > n)
		return (an);
	way = way->next;
	while (way && way->way && an <= n)
	{
		if (way->len - l > n - an)
			break ;
		way->an_w[0] = joinfree("L\0", ft_itoa(an), 2);
		an++;
		way = way->next;
	}
	return (an);
}

static void	where_ants(t_way *way, int i)
{
	while (way && way->way)
	{
		way->an_w = (char **)malloc(sizeof(char *) * (way->len + 1));
		i = -1;
		while (++i <= way->len)
			way->an_w[i] = 0;
		way = way->next;
	}
}

int			take_turns(int n, t_way **way, char **argv)
{
	int i;
	int an;

	where_ants(*way, 0);
	i = 0;
	an = 1;
	pr_all_way(*way, argv, 0, 0);
	while (1)
	{
		make_step(*way);
		if (an <= n)
			an = new_ants(*way, n, an);
		if (mascmp("-colour\0", argv) == 0)
		{
			if (print_step_col(*way, 0, 0, 0) == 0)
				break ;
		}
		else if (print_step(*way, 0) == 0)
			break ;
	}
	return (1);
}

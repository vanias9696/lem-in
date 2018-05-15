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

int			all_a(char *name, int n)
{
	int i;

	ft_printf("\nL%i-%s", 1, name);
	i = 1;
	while(++i <= n)
		ft_printf(" L%i-%s", i, name);
	ft_printf("\n");
	return (1);
}

static int	print_step(t_way *way)
{
	int i;
	int k;
	int q;

	k = 0;
	q = 0;
	while (way && way->way)
	{
		i = 0;
		while (i < way->len)
		{
			if (way->an_w[i])
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
			i++;
		}
		way = way->next;
	}
	if (q != 0)
		ft_printf("\n");
	return (q);
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
		if (way->len - l >= n - an)
			break ;
		way->an_w[0] = joinfree("L\0", ft_itoa(an), 2);
		an++;
		way = way->next;
	}
	return (an);
}

int			take_turns(int n, t_way **way)
{
	int		r;
	t_way	*h;
	int		i;
	int		an;

	r = 0;
	h = *way;
	while(h && h->way)
	{
		h->an_w = (char **)malloc(sizeof(char *) * (h->len + 1));
		i = -1;
		while (++i <= h->len)
			h->an_w[i] = 0;
		h = h->next;
		r++;
	}
	i = 0;
	an = 1;
	while (1)
	{
		make_step(*way);
		if (an <= n)
			an = new_ants(*way, n, an);
		if (print_step(*way) == 0)
			break ;
	}
	return (1);
}





















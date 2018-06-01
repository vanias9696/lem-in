/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismus <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 15:41:59 by ismus             #+#    #+#             */
/*   Updated: 2018/05/18 15:42:00 by ismus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		get_arg(int ac, char **av)
{
	int k;

	k = 0;
	while (++k < ac)
	{
		if (ft_strcmp(av[k], "-colour\0") != 0 && ft_strcmp(av[k],
			"-error\0") != 0)
			return (0);
	}
	return (1);
}

void	pr_all_way(t_way *way, char **argv, int i, int k)
{
	if (mascmp("-colour\0", argv) == 0)
	{
		while (way)
		{
			ft_printf("\x1b[0;35mWay %i:\n", ++k);
			i = -1;
			while (way->way[++i + 1])
				ft_printf("\x1b[1;33m%s\x1b[1;37m->", way->way[i]);
			ft_printf("\x1b[1;32m%s\n", way->way[i]);
			way = way->next;
		}
	}
	else
	{
		while (way)
		{
			ft_printf("Way %i:\n", ++k);
			i = -1;
			while (way->way[++i + 1])
				ft_printf("%s->", way->way[i]);
			ft_printf("%s\n", way->way[i]);
			way = way->next;
		}
	}
	ft_printf("\n");
}

void	correct_data(void)
{
	ft_printf("Comments can be anywhere! They must begin with '#'.");
	ft_printf("But if you enter '##start' or '##end' you must enter data abo");
	ft_printf("ut first or last room respectively in next line.\nThe first ");
	ft_printf("line should contain the number of ants. This number must be ");
	ft_printf("more than 0, but less than 2147483648.\nIf you want to create");
	ft_printf(" a room, you must declare it as [name_room] [x] [y]. The nam");
	ft_printf("es of rooms should not be repeated.\nIf you want to pave the ");
	ft_printf("way between rooms, you should to do this as follows: [name1]-");
	ft_printf("[name2].\nAlso, every your thought must end with '\\n'!\n");
	ft_printf("Good luck next time:)\n");
}

int		non_existent_room(t_lm *data, t_tr *t)
{
	int		i;
	int		l;
	t_tr	*h;

	i = 0;
	while (data->coments[i])
	{
		h = t;
		l = 0;
		while (data->coments[i + l] && data->coments[i + l] != '-'
			&& data->coments[i + l] != '\n')
			l++;
		while (h && ft_strncmp(data->coments + i, h->name, l) != 0)
			h = h->next;
		if (!h)
		{
			ft_printf("\x1b[1;31mThe data has non-existent rooms!\n");
			return (0);
		}
		i = data->coments[i + l] != '\0' ? i + l + 1 : i + l;
	}
	return (1);
}

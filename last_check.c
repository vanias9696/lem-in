/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismus <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 15:24:34 by ismus             #+#    #+#             */
/*   Updated: 2018/05/02 15:24:35 by ismus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	same_names(t_tr *t)
{
	t_tr *help;
	t_tr *ch;

	help = t;
	while (help)
	{
		ch = help->next;
		while (ch)
		{
			if (ft_strcmp(help->name, ch->name) == 0)
			{
				ft_printf("\x1b[1;31mThe room names are repeated\n");
				return (0);
			}
			ch = ch->next;
		}
		help = help->next;
	}
	return (1);
}

static int	identical_links(t_tr *t)
{
	t_tr	*help;
	int		i;
	int		k;

	i = 0;
	help = t;
	while (help)
	{
		i = 0;
		while (help->rooms[i + 1])
		{
			k = i;
			while (help->rooms[++k])
				if (ft_strcmp(help->rooms[i], help->rooms[k]) == 0)
				{
					free(help->rooms[k]);
					while(help->rooms[k + 1])
					{
						help->rooms[k] = help->rooms[k + 1];
						k++;
					}
					help->rooms[k] = help->rooms[k + 1];
					k = i;
				}
			i++;
		}
		help = help->next;
	}
	return (1);
}

static int	existence_rooms(t_tr *t)
{
	t_tr	*help;
	t_tr	*nt;
	int		i;

	help = t;
	while (help)
	{
		i = -1;
		while (help->rooms[++i])
		{
			nt = t;
			while (nt && ft_strcmp(nt->name, help->rooms[i]) != 0)
				nt = nt->next;
			if (nt == 0)
			{
				ft_printf("\x1b[1;31mThe data has non-existent rooms\n");
				return (0);
			}
		}
		help = help->next;
	}
	return (1);
}

static int	first_L(t_tr *t)
{
	while (t)
	{
		if (t->name[0] == 'L')
		{
			ft_printf("\x1b[1;31mThe room's name cannot begin with 'L'!\n");
			return (0);
		}
		t = t->next;
	}
	return (1);
}

int			last_check(t_tr *t)
{
	if (same_names(t) == 0)
		return (0);
	if (identical_links(t) == 0)
		return (0);
	if (existence_rooms(t) == 0)
		return (0);
	if (first_L(t) == 0)
		return (0);
	return (1);
}

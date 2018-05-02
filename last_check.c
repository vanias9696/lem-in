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

int			pr_free(char *str, char *line, int n)
{
	ft_printf("\x1b[1;31m%s\n", str);
	if (line)
		free(line);
	return (n);
}

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
					ft_printf("\x1b[1;31mIdentical links\n");
					return (0);
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

int			last_check(t_tr *t)
{
	if (same_names(t) == 0)
		return (0);
	if (identical_links(t) == 0)
		return (0);
	if (existence_rooms(t) == 0)
		return (0);
	return (1);
}

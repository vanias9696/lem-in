/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismus <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 15:05:44 by ismus             #+#    #+#             */
/*   Updated: 2018/04/30 15:05:45 by ismus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char	*check_sl(char *sl, int i, int k)
{
	char	*name;

	while (sl[i] && sl[i] != ' ')
		i++;
	if (sl[i] != ' ')
		return (0);
	name = (char *)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (sl[++i] != ' ')
		name[i] = sl[i];
	name[i] = '\0';
	while (sl[++i] <= '9' && sl[i] >= '0')
		i = i + 0;
	k = i;
	while (sl[++i] <= '9' && sl[i] >= '0')
		i = i + 0;
	if (sl[k] != ' ' || sl[i] != '\0')
	{
		free(name);
		return (0);
	}
	return (name);
}

static int	first_last(t_tr *t, char *sl, char *com, int n)
{
	t->rooms = 0;
	t->next = 0;
	t->note = n;
	t->name = check_sl(sl, 0, 0);
	if (t->name == 0)
		return (0);
	t->x = ft_atoi(sl + 1 + ft_strlen(t->name));
	t->y = ft_atoi(sl + 1 + ft_strlen(t->name) + len_num(t->x));
	if (com)
		n++;
	t->rooms = comm_betw_rooms(com, t->name);
	if (t->rooms == 0)
		return (0);
	return (1);
}

static int	else_room(t_tr *a, t_lm *d, int n)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (++i != n)
		k = k + ft_while_not_n(d->rooms + k, '\n') + 1;
	i = 0;
	while (d->rooms[i + k] != ' ')
		i++;
	a->note = 0;
	if (!(a->name = (char *)malloc(sizeof(char *) * (i + 1))))
		return (-1);
	a->name = ft_strncpy(a->name, d->rooms + k, i);
	a->name[i] = '\0';
	a->x = ft_atoi(d->rooms + k + 1 + i);
	a->y = ft_atoi(d->rooms + k + 1 + i + len_num(a->x));
	if (i == 0)
		return (-1);
	a->rooms = comm_betw_rooms(d->coments, a->name);
	if (a->rooms == 0)
		return (-1);
	if (ft_while_not_n(d->rooms + k, '\n') < 0)
		return (0);
	return (n + 1);
}

static int	for_else(t_tr *all, int i, t_lm *data)
{
	t_tr	*temp;

	i = 1;
	while (i != 0)
	{
		if (!(temp = (t_tr *)malloc(sizeof(t_tr))))
			return (0);
		all->next = temp;
		all = temp;
		i = else_room(all, data, i);
		if (i < 0)
		{
			ft_printf("\x1b[1;31mError\n");
			return (0);
		}
	}
	all->next = 0;
	return (1);
}

int			get_tree(t_tr *t, t_lm *data, int i)
{
	t_tr	*all;

	if (!first_last(t, data->start, data->coments, 1))
	{
		ft_printf("\x1b[1;31mThe data about first room ");
		ft_printf("was incorrectly entered!\n");
		return (0);
	}
	if (!(all = (t_tr *)malloc(sizeof(t_tr))))
		return (0);
	t->next = all;
	if (!first_last(all, data->end, data->coments, 2))
	{
		ft_printf("\x1b[1;31mThe data about last room ");
		ft_printf("was incorrectly entered!\n");
		return (0);
	}
	if (for_else(all, i, data) == 0)
		return (0);
	return (1);
}

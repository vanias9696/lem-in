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
	t->rooms = comm_betw_rooms(com, t->name);
	if (t->rooms == 0)
		return (0);
	return (1);
}

int			get_tree(t_tr *t, t_lm *data)
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
	return (1);
}

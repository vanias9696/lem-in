/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique_ways.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismus <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 14:15:05 by ismus             #+#    #+#             */
/*   Updated: 2018/05/02 14:15:06 by ismus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			unique_ways(t_tr *t, t_way *way, t_lm *data)
{
	t_tr	*h;
	int		i;

	h = t->next;
	way->way = 0;
	way->used_rooms = 0;
	way->an_w = 0;
	i = -1;
	while(t->rooms[++i])
		if (ft_strcmp(h->name, t->rooms[i]) == 0)
			break ;
	if (t->rooms[i])
		return (1);
	i = 0;
	while(t->rooms[i] && h->rooms[i])
		i++;
	if (i > 0)
		return(many_way(&way, t, data->n_rm, i));
	else
		return(pr_free("Way not found!", 0, 0));
	return (0);
}

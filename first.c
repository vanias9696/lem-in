/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismus <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 15:10:53 by ismus             #+#    #+#             */
/*   Updated: 2018/04/26 15:10:54 by ismus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	free_data(t_lm *data)
{
	if (data->rooms)
		free(data->rooms);
	if (data->coments)
		free(data->coments);
	if (data->start)
		free(data->start);
	if (data->end)
		free(data->end);
	free(data);
}

static void	free_tree(t_tr *t)
{
	t_tr	*temp;
	int		i;

	while(t)
	{
		if (t->name)
			free(t->name);
		if (t->rooms)
		{
			i = 0;
			while(t->rooms[i])
				free(t->rooms[i++]);
			free(t->rooms);
		}
		temp = t;
		t = t->next;
		free(temp);
	}
}

int			check(void)
{
	t_lm	*data;
	t_tr	*t;

	if (!(data = (t_lm *)malloc(sizeof(t_lm))))
		return (0);
	data->rooms = NULL;
	data->coments = NULL;
	data->start = NULL;
	data->end = NULL;
	if (get_data(data) == 0)
	{
		ft_printf("\x1b[1;37m\n");
		free_data(data);
		return (0);
	}
	if (!(t = (t_tr *)malloc(sizeof(t_tr))))
		return (0);
	if (get_tree(t, data) == 0)
	{
		ft_printf("\x1b[1;37m\n");
		free_tree(t);
		free_data(data);
		return (0);
	}
	else
	{
		ft_printf("\x1b[1;37mAll good\n");
		free_tree(t);
		free_data(data);

	}
	return (1);
}

int			main(void)
{
	check();
	system("leaks lem-in -quiet");
	return (1);
}

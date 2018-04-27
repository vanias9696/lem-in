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

#include "lem-in.h"

#include <stdio.h>

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


int		check(void)
{
	t_lm	*data;

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
	else
	{
		ft_printf("\x1b[1;37m\n");
		ft_printf("ants -> %i\n----------------\n", data->ants);
		if (data->rooms)
			ft_printf("rooms:\n%s\n----------------\n", data->rooms);
		if (data->coments)
			ft_printf("coments:\n%s\n----------------\n", data->coments);
		if (data->start)
			ft_printf("start -> %s\n----------------\n", data->start);
		if (data->end)
			ft_printf("end -> %s\n----------------\n", data->end);
		free_data(data);
		ft_printf("All good\n");
	}
	return (1);
}

int main()
{
	check();
	system("leaks lem-in -quiet");
	return (1);
}

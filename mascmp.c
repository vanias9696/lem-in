/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mascmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismus <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 18:37:27 by ismus             #+#    #+#             */
/*   Updated: 2018/05/03 18:37:27 by ismus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		mascmp(char *s, char **m)
{
	int k;

	k = 0;
	if (!m)
		return (1);
	while (m[k] && ft_strcmp(m[k], s) != 0)
		k++;
	return (!(m[k]) ? 1 : 0);
}

int		pr_free(char *str, char *line, char *l, int n)
{
	ft_printf("\x1b[1;31m%s\n", str);
	if (line)
		free(line);
	if (l)
		free(l);
	return (n);
}

int		second_word(char *com, char *name, int i, int *n)
{
	int l;

	l = ft_strlen(name);
	while (com[i] != '-')
		i++;
	i++;
	if (ft_strncmp(com + i, name, l) == 0)
	{
		i = i + ft_strlen(name);
		if (com[i] == '\n' || com[i] == '\0')
			(*n)++;
	}
	while (com[i] && com[i] != '\n')
		i++;
	return (i);
}

int		all_a(char *name, int n, char **argv)
{
	int i;

	if (mascmp("-colour\0", argv) == 0)
	{
		ft_printf("\x1b[1;34mL%i\x1b[1;37m-\x1b[1;32m%s", 1, name);
		i = 1;
		while (++i <= n)
			ft_printf("\x1b[1;34m L%i\x1b[1;37m-\x1b[1;32m%s", i, name);
		ft_printf("\x1b[1;37m\n");
		return (1);
	}
	ft_printf("L%i-%s", 1, name);
	i = 1;
	while (++i <= n)
		ft_printf(" L%i-%s", i, name);
	ft_printf("\n");
	return (1);
}

int		print_step_col(t_way *way, int k, int i, int q)
{
	while (way && way->way && (i = -1))
	{
		while (++i < way->len)
			if (way->an_w[i] && way->way[i] && ++q)
			{
				if (k == 0 && ++k)
				{
					ft_printf("\x1b[1;34m%s\x1b[1;37m-", way->an_w[i]);
					if (!way->way[i + 1])
						ft_printf("\x1b[1;32m%s", way->way[i]);
					else
						ft_printf("\x1b[1;33m%s", way->way[i]);
				}
				else
				{
					ft_printf("\x1b[1;34m %s\x1b[1;37m-", way->an_w[i]);
					if (!way->way[i + 1])
						ft_printf("\x1b[1;32m%s", way->way[i]);
					else
						ft_printf("\x1b[1;33m%s", way->way[i]);
				}
			}
		way = way->next;
	}
	return (q != 0 ? ft_printf("\n") : 0);
}

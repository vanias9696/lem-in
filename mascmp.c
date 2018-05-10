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

int	mascmp(char *s, char **m)
{
	int k;

	k = 0;
	if (!m)
		return (1);
	while (m[k] && ft_strcmp(m[k], s) != 0)
		k++;
	return (!(m[k]) ? 1 : 0);
}

int			pr_free(char *str, char *line, int n)
{
	ft_printf("\x1b[1;31m%s\n", str);
	if (line)
		free(line);
	return (n);
}

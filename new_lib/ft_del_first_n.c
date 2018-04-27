/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_first_n.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismus <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 20:24:37 by ismus             #+#    #+#             */
/*   Updated: 2017/12/07 20:24:38 by ismus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_del_first_n(char *str, int n)
{
	int	l;
	int j;

	l = ft_strlen(str);
	j = 0;
	while (j < l - n && j < l)
	{
		str[j] = str[j + n];
		j++;
	}
	while (j < l)
	{
		str[j] = '\0';
		j++;
	}
}
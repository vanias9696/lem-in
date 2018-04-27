/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join3free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismus <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 16:45:08 by ismus             #+#    #+#             */
/*   Updated: 2018/04/27 16:45:09 by ismus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	sfree(int n, char *s1, char *s2, char *s3)
{
	if (n == 1 || n == 4 || n == 5 || n == 7)
		free(s1);
	if (n == 2 || n == 4 || n == 6 || n == 7)
		free(s2);
	if (n == 3 || n == 5 || n == 6 || n == 7)
		free(s3);
}

char		*join3free(char *s1, char *s2, char *s3, int n)
{
	char	*new;
	int		l;
	int		i;

	if (!s1 || !s2 || !s3)
		return (0);
	l = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	if (!(new = (char *)malloc(l + 1)))
		return (0);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	l = 0;
	while (s2[l])
		new[i++] = s2[l++];
	l = 0;
	while (s3[l])
		new[i++] = s3[l++];
	new[i] = '\0';
	sfree(n, s1, s2, s3);
	return (new);
}

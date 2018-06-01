/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commun_rooms.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismus <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:59:28 by ismus             #+#    #+#             */
/*   Updated: 2018/04/30 16:59:29 by ismus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	num_link(char *com, char *name, int i, int n)
{
	int l;

	l = ft_strlen(name);
	while (com[i] != '\0')
	{
		if (ft_strncmp(com + i, name, l) == 0 &&
			com[i + ft_strlen(name)] == '-')
		{
			i = i + 1 + ft_strlen(name);
			if (ft_strncmp(com + i, name, l) == 0 &&
				(com[i + ft_strlen(name)]
				== '\n' || com[i + 1 + ft_strlen(name)] == '\0'))
				return (0);
			n++;
			while (com[i] && com[i] != '\n')
				i++;
		}
		else
			i = second_word(com, name, i, &n);
		if (com[i] == '\n')
			i++;
	}
	return (n);
}

static char	*first_part(int *m, char *com, char *name, int p)
{
	int		i;
	int		k;
	char	*room;

	i = *m;
	i = i + ft_strlen(name) + 1;
	k = i;
	while (com[k] && com[k] != '\n')
		k++;
	room = (char *)malloc(sizeof(char *) * (k - i + 1));
	room = ft_strncpy(room, com + i, k - i);
	room[k - i] = '\0';
	*m = p == 1 ? 0 : k + 1;
	return (room);
}

static char	*second_part(int *m, char *com, char *name, int p)
{
	int		i;
	int		k;
	char	*room;

	i = *m - 1;
	k = i;
	while (k != 0 && com[k - 1] != '\n')
		k--;
	room = (char *)malloc(sizeof(char *) * (i - k + 1));
	room = ft_strncpy(room, com + k, i - k);
	room[i - k] = '\0';
	i = p == 1 ? 0 : i + 2 + ft_strlen(name);
	*m = i;
	return (room);
}

static char	*fill_rooms(char *name, char *com, int p)
{
	static int	i;
	int			l;

	l = ft_strlen(name);
	while (com[i] != '\0')
	{
		if (ft_strncmp(com + i, name, l) == 0 &&
			com[i + ft_strlen(name)] == '-')
			return (first_part(&i, com, name, p));
		else
		{
			i = i == 0 ? i + 1 : i;
			while (com[i - 1] != '-')
				i++;
			if (ft_strncmp(com + i, name, l) == 0 &&
				(com[i + l] == '\0' || com[i + l] == '\n'))
				return (second_part(&i, com, name, p));
			while (com[i - 1] && com[i - 1] != '\n')
				i++;
		}
	}
	i = 0;
	return (0);
}

char		**comm_betw_rooms(char *com, char *name)
{
	int		l;
	char	**rooms;
	int		i;
	int		k;

	k = 0;
	i = -1;
	l = num_link(com, name, 0, 0);
	if (l == 0)
		return (0);
	if (!(rooms = (char **)malloc(sizeof(char **) * (l + 1))))
		return (0);
	while (++i <= l)
		rooms[i] = 0;
	i = 0;
	while (i < l)
	{
		rooms[i] = fill_rooms(name, com, i + 1 == l ? 1 : 0);
		if (rooms[i] == 0)
			return (0);
		i++;
	}
	return (rooms);
}

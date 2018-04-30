/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismus <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 15:13:35 by ismus             #+#    #+#             */
/*   Updated: 2018/04/26 15:13:36 by ismus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include <unistd.h>
# include <stdlib.h>
# include "new_lib/libft.h"
# include "lem_in.h"

typedef struct		s_trees
{
	int				note;
	char			*name;
	int				x;
	int				y;
	char			**rooms;
	struct s_trees	*next;
}					t_tr;

typedef struct		s_lem_in
{
	int				ants;
	char			*rooms;
	char			*coments;
	char			*start;
	char			*end;
}					t_lm;

int					get_data(t_lm *data);
int					get_tree(t_tr *t, t_lm *data);
char				**comm_betw_rooms(char *com, char *name);

#endif

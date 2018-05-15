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

typedef struct		s_ways
{
	int				num;
	int				len;
	char			**way;
	char			**used_rooms;
	char			**an_w;
	struct s_ways	*next;
}					t_way;

typedef struct		s_lem_in
{
	int				ants;
	int				n_rm;
	int				n_way;
	char			*rooms;
	char			*coments;
	char			*start;
	char			*end;
}					t_lm;

int					get_data(t_lm *data, char *line);
int					get_tree(t_tr *t, t_lm *data, int i);
char				**comm_betw_rooms(char *com, char *name);
int					last_check(t_tr *t);
int					pr_free(char *str, char *line, int n);
int					unique_ways(t_tr *t, t_way *way, t_lm *data);
int					mascmp(char *s, char **m);
int					many_way(t_way **way, t_tr *t, int n_rm, int n_way);
int					all_a(char *name, int n);
int					take_turns(int n, t_way **way);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 22:28:38 by segurbuz          #+#    #+#             */
/*   Updated: 2023/11/17 04:45:05 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include "../libarys/mlx/mlx.h"
# include "../libarys/libft/libft.h"
# include "../libarys/get_next_line/get_next_line.h"

enum	e_map
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING,
	MAP,
};

typedef struct s_map
{
	char			*line;
	int				type;
	struct s_map	*next;
	struct s_map	*prev;		
}					t_map;

typedef struct s_attr
{
	t_map	*map;
	t_map	*texture;
	t_map	*color;
}			t_attr;

typedef struct s_data
{
	t_map	*map_cub;
	char	*map_arg;
	t_attr	*attr;
}	t_data;

void	ft_parse(t_data *data);
t_map	*ms_lstnew(int type, void *content);
void	ms_lstadd_back(t_map **lst, t_map *new);
t_map	*ms_lstlast(t_map *lst);
void	ft_error(void);
void	map_attr_add_data(t_data *data);
bool	map_find_attr(char *line, char *find);
void	read_map(t_data *data);
void	map_invalid_char(char *line, bool **flag);
void	parse_with_color(char *line, bool *flag, int *rule);
void	parse_with_map_content(char *line, bool *flag, int *check);
bool	map_find_attr(char *line, char *find);
bool	is_check(char c);
void	found_and_implement(t_map *map, int i, bool **flag);
void	map_find_space_in_content(t_map *map, bool **flag);
void	find_tab_in_map(t_map *map, bool *flag);
void	parse_with_color2(char *line, int *check, int *rule, bool *flag);
void	parse_with_color3(char *line, int *digit_check, bool *flag, int *i);
void	read_map_2(t_data *data, t_map *map, enum e_map type);

#endif
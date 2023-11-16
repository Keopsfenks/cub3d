/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 22:28:38 by segurbuz          #+#    #+#             */
/*   Updated: 2023/11/16 19:32:16 by segurbuz         ###   ########.fr       */
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
	int 			type;
	struct s_map	*next;
	struct s_map	*prev;		
}					t_map;

typedef struct s_attr
{
	t_map	*map;
	t_map 	*texture;
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

#endif
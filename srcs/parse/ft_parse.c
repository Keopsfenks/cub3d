/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segurbuz <segurbuz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 22:10:10 by segurbuz          #+#    #+#             */
/*   Updated: 2023/11/16 19:43:23 by segurbuz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	map_find_attr(char *line, char *find)
{
	int	i;
	int	size;

	i = -1;
	size = ft_strlen(find);
	while (line[++i] != '\0')
	{
		if (size == 2)
			if (line[i] == find[0] \
				&& line[i + 1] == find[1])
				return (true);
		if (size == 1)
			if (line[i] == find[0])
				return (true);
	}
	return (false);
}

void	parse_with_map_content(char *line, bool *flag, int *check)
{
	int flag2;

	flag2 = 1;
	if (ft_strncmp(line, "SO", 2) == 0)
	{
		*check += 1;
		flag2 = 0;
	}
	else if (ft_strncmp(line, "NO", 2) == 0)
	{
		*check += 1;
		flag2 = 0;
	}
	else if (ft_strncmp(line, "WE", 2) == 0)
	{
		*check += 1;
		flag2 = 0;
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		*check += 1;
		flag2 = 0;
	}
	if (*(line + 2) != ' ')
		*flag = true;
	if (flag2 == 1)
		*flag = true;
}

void	parse_with_color(char *line, bool *flag, int *rule)
{
	int	comma;
	int	i;
	int	check;
	int	digit_check;

	comma = 2;
	check = 0;
	digit_check = 0;
	i = -1;
	if (ft_strncmp(line, "F", 1) == 0)
	{
		if (*(line + 1) != ' ')
			*flag = true;
		check = 1;
		*rule += 1;
	}
	else if (ft_strncmp(line, "C", 1) == 0)
	{
		if (*(line + 1) != ' ')
			*flag = true;
		check = 1;
		*rule += 1;
	}
	if (check == 0)
		*flag = true;
	while (line[++i] != '\0')
		if (ft_isdigit(line[i]))
			break ;
	check = 0;
	while (line[i])
	{
		while (comma == 0 && line[i] == ' ')
			i++;
		if (!(ft_isdigit(line[i]) || line[i] == ' ' \
			|| line[i] == ',') && comma != 0)
			*flag = true;
		if (ft_isdigit(line[i]))
			check += 1;
		if (comma == 0 && !(ft_isdigit(line[i]) || line[i] == '\n'))
			*flag = true;
		if (line[i] == ',' || line[i] == '\n')
		{
			if (check >= 1)
				digit_check += 1;
			comma--;
			check = 0;
		}
		i++;
	}
	if (digit_check != 3)
		*flag = true;
}

void	map_invalid_char(char *line, bool **flag)
{
	int	i;

	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '1' \
			&& line[i] != '0' && line[i] != '2' \
			&& line[i] != 'N' && line[i] != 'S' \
			&& line[i] != 'E' && line[i] != 'W' && line[i] != '\n')
			**flag = true;
	}
}

bool	map_botandtop_wall_check2(t_map *map, int i)
{
	int	wall_end;
	int	j;

	j = i;
	while (map->line[j] && map->line[j] == ' ')
		j++;
	while (map && map->line[i] == ' ')
	{
		if (map->line[j] != '1' || map->line[i - 1] != '1')
			return (true);
		map = map->next;
	}
	wall_end = j;
	i -= 1;
	while (map->line[i] != '\0' && i != wall_end)
	{
		if (map->line[i] != '1')
			return (true);
		i++;
	}
	return (false);
}

bool	map_botandtop_wall_check3(t_map *map, int i)
{
	int	wall_end;
	int	j;

	j = i;
	while (map->line[j] && map->line[j] == ' ')
		j++;
	while (map && map->line[i] == ' ')
	{
		if (map->line[j] != '1' || map->line[i - 1] != '1')
			return (true);
		map = map->prev;
	}
	wall_end = j;
	i -= 1;
	while (map->line[i] != '\0' && i != wall_end)
	{
		if (map->line[i] != '1')
			return (true);
		i++;
	}
	return (false);
}

bool	is_check(char c)
{
	if (c == ' ' || c == '\n' || c == '\0')
		return (true);
	return (false);
}

void	found_and_implement(t_map *map, int i, bool **flag)
{
	if (is_check(map->line[i + 1]) || is_check(map->line[i - 1]))
		**flag = true;
	if (map->prev && is_check(map->prev->line[i]))
		**flag = true;
	if (map->next && is_check(map->next->line[i]))
		**flag = true;
}

void	map_find_space_in_content(t_map *map, bool **flag)
{
	t_map	*tmp;
	int		i;

	tmp = map;
	while (tmp)
	{
		i = -1;
		while (tmp->line[++i])
			if (tmp->line[i] == '0' || map->line[i] == 'S' \
				|| map->line[i] == 'N' || map->line[i] == 'E' \
				|| map->line[i] == 'W')
				found_and_implement(tmp, i, flag);
		tmp = tmp->next;
	}
}

void	map_botandtop_wall_check(t_map *map, bool **flag)
{
	int			i;
	static bool	flag2 = true;
	t_map		*last;

	i = -1;
	last = ms_lstlast(map);
	if ((map->prev->line[0] == '\0' || map->prev->line[0] == '\n') \
		&& ft_strlen(map->prev->line) <= 1 && flag2)
	{
		while (map->line[++i] != '\n' && map->line[i] != '\0')
		{
			if (map->line[i] != '1' && map->line[i] != ' ')
				**flag = true;
			else if (map->line[i] == ' ' \
				&& map->line[i + 1] == '1'
				&& map->line[i - 1] == '1')
				if (map_botandtop_wall_check2(map, i))
					**flag = true;
		}
	}
	i = -1;
	while (last->line[++i] != '\n' && last->line[i] != '\0' && flag2)
	{
		if (last->line[i] != '1' && last->line[i] != ' ')
			**flag = true;
		else if (last->line[i] == ' ' \
			&& last->line[i + 1] == '1'
			&& last->line[i - 1] == '1')
			if (map_botandtop_wall_check3(last, i))
				**flag = true;
	}
	flag2 = false;
}

void	map_left_wall_check(t_map *map, bool **flag)
{
	int	i;

	i = 0;
	while (map->line[i] && map->line[i] == ' ')
		i++;
	if (map->line[i] != '1')
		**flag = true;
}

void	which_select_parse2(t_map *map, bool *flag)
{
	bool	check;

	check = true;
	while (map && *flag == false)
	{
		if ((map->line[0] == '\0' || map->line[0] == '\n')
			&& ft_strlen(map->line) <= 1 && check)
		{
			map = map->next;
			continue ;
		}
		check = false;
		if ((map->line[0] == '\0' || map->line[0] == '\n')
			&& ft_strlen(map->line) <= 1)
			*flag = true;
		map_find_space_in_content(map, &flag);
		map_invalid_char(map->line, &flag);
		map_botandtop_wall_check(map, &flag);
		map_left_wall_check(map, &flag);
		map = map->next;
	}
}

bool	where_attr_map(t_map *map, bool *flag)
{
	if (!map)
		return (*flag = true, true);
	if (map && map->line[0] == '\0')
		return (*flag = true, true);
	return (true);
}

bool	which_select_parse(t_data *data)
{
	t_map	*tmp;
	bool	flag;
	int		check;

	flag = false;
	check = 0;
	tmp = data->map_cub;
	while (tmp)
	{
		if (map_find_attr(tmp->line, "SO")
			|| map_find_attr(tmp->line, "NO")
			|| map_find_attr(tmp->line, "WE")
			|| map_find_attr(tmp->line, "EA"))
			parse_with_map_content(tmp->line, &flag, &check);
		if (map_find_attr(tmp->line, "F") \
			|| map_find_attr(tmp->line, "C"))
			parse_with_color(tmp->line, &flag, &check);
		tmp = tmp->next;
		if (check == 6)
			if (where_attr_map(tmp, &flag))
				break ;
	}
	if (flag == false)
		which_select_parse2(tmp, &flag);
	return (flag);
}

void	ft_parse(t_data *data)
{
	read_map(data);
	if (which_select_parse(data))
		ft_error();
	map_attr_add_data(data);
}

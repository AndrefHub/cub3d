/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsherry <lsherry@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:49:03 by lsherry           #+#    #+#             */
/*   Updated: 2022/11/09 18:49:05 by lsherry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc_bonus/cub3d_bonus.h"

int	cmp_string_number(void *lhs, void *rhs)
{
	if (ft_strlen(lhs) != ft_strlen(rhs))
		return (ft_strlen(lhs) < ft_strlen(rhs));
	else
		return (ft_strncmp(lhs, rhs, ft_strlen(lhs)));
}

int	cmp_lb_entry(void *lhs, void *rhs)
{
	return (((t_lb_entry *)lhs)->score_num < ((t_lb_entry *)rhs)->score_num);
}

t_lb_entry	*lb_entry_new(char *name, char *score)
{
	t_lb_entry	*entry;

	entry = malloc(sizeof(*entry));
	if (entry)
	{
		entry->name = name;
		entry->score = score;
		entry->score_num = ft_atoi(score);
	}
	return (entry);
}

t_lb_entry	*parse_lb_entry(char *line)
{
	t_lb_entry	*entry;
	char		**split;

	entry = NULL;
	split = ft_split(line, '\t');
	if (ft_arraylen((void **)split) == 2)
	{
		entry = lb_entry_new(split[0], split[1]);
		free(split);
	}
	else
		ft_freesplit(split);
	return (entry);
}

t_list	*get_leaderboard(char *filename)
{
	t_list		*lb;
	t_lb_entry	*entry;
	char		*line;
	int			fd;

	lb = NULL;
	fd = open(filename, O_RDONLY);
	if (fd >= 0)
	{
		line = skip_empty_lines(fd);
		while (line)
		{
			entry = parse_lb_entry(line);
			if (entry)
				ft_lstadd_back(&lb, ft_lstnew(entry));
			free(line);
			line = skip_empty_lines(fd);
		}
		if (lb)
			ft_lstsort(&lb, cmp_lb_entry);
		close(fd);
	}
	return (lb);
}

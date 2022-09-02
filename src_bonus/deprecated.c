
int	is_prefix_number_old(char *line, char *prefix, int counter)
{
	return (line && !ft_strncmp(line, prefix, ft_strlen(prefix))
		&& ft_atoi(line + ft_strlen(prefix)) == counter);
}

t_list	*get_textures_list_old(int fd, char *prefix, char **line)
{
	t_list		*lst;
	int			counter;

	lst = NULL;
	counter = 0;
	if (is_prefix_number(*line, prefix, counter))
	{
		ft_lstadd_back(&lst, ft_lstnew(crop_prefix(*line, prefix)));
		++counter;
	}
	*line = get_texture(fd);
	while (is_prefix_number(*line, prefix, counter))
	{
		ft_lstadd_back(&lst, ft_lstnew(crop_prefix(*line, prefix)));
		++counter;
		*line = get_texture(fd);
	}
	return (lst);
}
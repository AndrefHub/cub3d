#include "../inc_bonus/cub3d_bonus.h"

char	**charlist_to_matrix(t_list *list)
{
	int	length;
	int	i;
	char **matrix;

	length = ft_lstsize(list);
	matrix = (char **) malloc(sizeof(char *) * length + 1);
	if (matrix == NULL)
		return NULL;
	i = 0;
	while (i < length)
	{
		matrix[i] = list->content;
		list = list->next;
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
}
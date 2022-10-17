#include "../inc_bonus/cub3d_bonus.h"

void	print_lb(t_list *lb)
{
	t_lb_entry	*entry;

	while (lb)
	{
		entry = lb->content;
		printf("%s, %s\n", entry->name, entry->score);
		lb = lb->next;
	}
}

void	ft_lst_insert(t_list **lst, t_list *to_insert, int cmp(void *, void *))
{
	t_list	*tmp;

	if (!lst || !*lst || cmp((*lst)->content, to_insert->content))
	{
		to_insert->next = *lst;
		*lst = to_insert;
	}	
	else
	{
		tmp = *lst;
		while (tmp->next && !cmp(tmp->next->content, to_insert->content))
			tmp = tmp->next;
		to_insert->next = tmp->next;
		tmp->next = to_insert;
	}
}

void	update_leaderboard_file(t_game *game)
{
	int		fd;
	int		counter;
	t_list	*lb;

	counter = -1;
	lb = game->leaderboard;
	fd = open(game->lb_filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd >= 0)
	{
		while (lb && ++counter < 10)
		{
			ft_putstr_fd(((t_lb_entry *)lb->content)->name, fd);
			ft_putchar_fd('\t', fd);
			ft_putendl_fd(((t_lb_entry *)lb->content)->score, fd);
			lb = lb->next;
		}
	}
	error_exit(game, 0, NULL);
}
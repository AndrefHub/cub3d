#include "../inc_bonus/cub3d_bonus.h"

void	ft_lstdelbyaddr(t_list **lst, t_list *to_del, void (*del)(void *))
{
	t_list	*prev;
	t_list	*curr;

	prev = *lst;
	curr = *lst;
	if (curr == to_del)
	{
		*lst = curr->next;
		ft_lstdelone(curr, del);
		return ;
	}
	while (curr)
	{
		if (curr == to_del)
		{
			prev->next = curr->next;
			ft_lstdelone(curr, del);
			return ;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
//		printf("%p %p\n", prev, curr);
	}
}

/*
{
    List* p,*q;
    p=q=*head;

    if((*head)->data == value)
    {
        *head = (*head)->next;
        free(p);
        return;
    }
    else
    {
        while(p->next != NULL)
        {
            if(p->data == value)
            {
                q->next = p->next;
                free(p);
            }
            else
            {
                q = p;
                p = p->next;
             }
        } // while loop ends

    } // outer else ends

} // del function ends
*/

void	eat_by_coords(t_game *game, t_vector pos)
{
	t_list      *objects;
	t_object    *object;

//		printf("i\'m in\n");
	objects = game->objects;
	while (objects)
	{
		object = objects->content;
		if ((int)object->pos.x == pos.x && (int)object->pos.y == pos.y)
		{
			game->hud.score.value += 100 + (game->map->map[pos.y][pos.x] == 'o') * 400;
			ft_lstdelbyaddr(&game->objects, objects, free);
			game->map->map[pos.y][pos.x] = '0';
			return ;
		}
		objects = objects->next;
	}
}

void	player_eat(t_game *game)
{
	const t_vector	pos = {game->player.pos.x, game->player.pos.y};

	if (is_edible(game->map->map[pos.y][pos.x]))
	{
//		printf("found edible\n");
		eat_by_coords(game, pos);
	}
}
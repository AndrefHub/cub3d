#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "libft/libft.h"
# include "stdio.h"

# define BAD_FILE -2
# define BAD_COLOUR (1 << 24)

typedef struct s_map
{
	t_list	*map;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int		F;
	int		C;
} t_map;

t_map	*create_empty_map(void);

int		ft_arraylen(void **arr);

#endif
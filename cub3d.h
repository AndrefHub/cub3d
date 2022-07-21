#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "libft/libft.h"

# define BAD_FILE -2

typedef struct s_map
{
	char	**map;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int		C;
	int		F;
} t_map;

t_map	*create_empty_map(void);

#endif
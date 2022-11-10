/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdancy <kdancy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:28:32 by kdancy            #+#    #+#             */
/*   Updated: 2022/11/10 18:46:22 by kdancy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "constants.h"

# include <stdbool.h>
# include <stdlib.h>
# include "stdio.h"
# include "math.h"
# include "X11/X.h"
# include "X11/keysym.h"
# include <time.h>
# include <signal.h>
# include <sys/time.h>
# include "../cute_sound/cute_sound.h"
# ifdef __APPLE__
#  include "../mlx/mlx.h"
# else
#  include "../mlx_linux/mlx.h"
# endif
# include "structures.h"
# include "prototypes.h"

#endif

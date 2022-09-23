#include "../inc_bonus/cub3d_bonus.h"

//void	draw_floor_textured(t_game *game, t_vector cur);

void	draw_wall_scaled(t_img *img, const t_img *texture,
	const struct s_column *column, int x, t_game * game)
{
	double	step = (double ) texture->size.y / column->height;
	unsigned	tex_x = (unsigned ) column->texture_pos % texture->size.x;
	int				y;
	double			tex_y;
	int 			max_height;

	tex_y = fmaxf(0.f, step * (column->height / 2 - img->size.y / 2 + game->z_offset));
	y = ft_max(0,img->size.y / 2 - column->height / 2 - game->z_offset);
	max_height = ft_min(img->size.y, img->size.y / 2 + column->height / 2 - game->z_offset);
	while (y < max_height)
	{
		put_pixel(img, (t_vector) {x, y}, texture->addr[(unsigned )tex_y * texture->size.x + tex_x]);
		tex_y += step;
		y++;
	}
//	if (y < img->size.y)
//	{
//		draw_floor_textured(game, (t_vector) {x, max_height});
//	}
}

void	draw_walls(t_game *game)
{
	int				x;
//	unsigned int	texture_id;

	x = 0;
	while (x < game->img.size.x)
	{
		game->column[x].height = (int) (ABS_WALL_SIZE / game->column[x].perp_dist);
		draw_texture_set(game, &game->column[x]);
//		texture_id = ft_strchr(CARDINAL_POINTS, game->column[x].dir) - CARDINAL_POINTS;
//		ft_putnbr_fd(texture_id, 1);
		draw_wall_scaled(&game->img, &game->textures[game->column[x].texture_id],
						 &game->column[x], x, game);
		x++;
	}
}

/*
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	vec2 realUV = (fragCoord.xy - 0.5*iResolution.xy)/iResolution.y;
	vec2 uv = realUV;

	// Ray angle
	float angle = uv.x * FOV + iTime*0.1;

	// Ceiling
	if(uv.y > 0.0)
	{
		//uv.y = pow(uv.y*2.0, (sin(iTime) + 1.0) * 0.5 + 1.0);
		uv.y *= uv.y * (sin(iTime)+1.0);

		//angle += iTime * 0.3;
	}

	// Pixel distance in the map
	float dist = 1.0 / ((abs(uv.y) + 0.001) * cos(uv.x * FOV * 1.0));

	// Get floor/ceiling coordinates
	vec2 floorUV = vec2(cos(angle), sin(angle)) * dist;
	//vec2 id = floor(floorUV);
	//floorUV = fract(floorUV); // This seems to cause some weird aliasing issues?

	// Get texture
	vec3 col = texture(iChannel0, floorUV).rgb;

	// Fog
	col *= pow(abs(uv.y*2.0), 0.7);

	// If uv.y and realUV.y are "disagreeing",
	// then this row of pixels is just staring into the infinite
	col *= uv.y * realUV.y < 0.0 ? 0.0 : 1.0;

	// Output to screen
	fragColor = vec4(col, 1.0);
}*/

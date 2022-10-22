#include "cub3d.h"

unsigned int	get_texture_pixel(t_game *game, int idx_x, \
										t_vector2 *wall_line, int cur_idx_y)
{
	t_ray * const	cur_ray = &game->ray_data[idx_x];
	t_img_data		*texture_img;
	t_vector2		ratio_pos_texture;
	int				texture_idx_x;
	int				texture_idx_y;

	texture_img = &game->texture[cur_ray->hit_wall_side].img_data;
	texture_idx_x = game->texture[cur_ray->hit_wall_side].texture_width;
	texture_idx_y = game->texture[cur_ray->hit_wall_side].texture_height;
	ratio_pos_texture.x = cur_ray->hit_texture_point;
	ratio_pos_texture.y = \
				(cur_idx_y - wall_line->x) / (wall_line->y - wall_line->x);
	texture_idx_x *= ratio_pos_texture.x;
	texture_idx_y *= ratio_pos_texture.y;
	return (*(unsigned int *)(texture_img->addr + \
			texture_idx_y * texture_img->line_length + texture_idx_x * \
											(texture_img->bits_per_pixel / 8)));
}

void	put_pixel_wall(t_game *game, int idx_x, t_vector2 *wall_line, t_vector2 *wall_pixel)
{
	t_img_data * const	view_data = &game->view_data;
	char				*dst;
	int					cur_idx_y;

	cur_idx_y = wall_pixel->x;
	while (cur_idx_y < wall_pixel->y)
	{
		dst = view_data->addr + (cur_idx_y * view_data->line_length + \
								 idx_x * (view_data->bits_per_pixel / 8));
		*(unsigned int *)dst = \
						get_texture_pixel(game, idx_x, wall_line, cur_idx_y);
		cur_idx_y++;
	}
}
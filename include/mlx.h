/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:45:13 by jeportie          #+#    #+#             */
/*   Updated: 2025/01/19 21:32:31 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_H
# define MLX_H

# include "mlx_int.h"

t_mlx_app	*my_mlx_app_create(int width, int height, const char *title);

void		*mlx_init(void);
void		*mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);
int			mlx_clear_window(void *mlx_ptr, void *win_ptr);
int			mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);
/*
**  origin for x & y is top left corner of the window
**  y down is positive
**  color is 0x00RRGGBB
*/

void	*mlx_new_image(void *mlx_ptr,int width,int height);
/*
**  return void *0 if failed
**  obsolete : image2 data is stored using bit planes
**  void	*mlx_new_image2(void *mlx_ptr,int width,int height);
*/
char		*mlx_get_data_addr(void *img_ptr, int *bits_per_pixel,
			   int *size_line, int *endian);
/*
**  endian : 0 = sever X is little endian, 1 = big endian
**  for mlx_new_image2, 2nd arg of mlx_get_data_addr is number_of_planes
*/
int			mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr,
				int x, int y);
int			mlx_get_color_value(void *mlx_ptr, int color);

// dealing with Events
// In mlx.h

int			mlx_key_hook(void *win_ptr, int (*funct)(void *, void *),
				void *param);

int			mlx_mouse_hook(void *win_ptr, int (*funct)(void *, void *),
				void *param);

int			mlx_expose_hook(void *win_ptr, int (*funct)(void *, void *),
				void *param);

int			mlx_hook(void *win_ptr, int x_event, int x_mask,
				int (*funct)(void *, void *), void *param);

int		mlx_flush_event(t_xvar *xvar);

int			mlx_loop_hook(void *mlx_ptr, int (*funct)(void *), void *param);

int			mlx_loop(void *mlx_ptr);
int			mlx_loop_end(void *mlx_ptr);

/*
**  hook funct are called as follow :
**
**   expose_hook(void *param);
**   key_hook(int keycode, void *param);
**   mouse_hook(int button, int x,int y, void *param);
**   loop_hook(void *param);
**
*/

int			mlx_string_put(void *mlx_ptr, void *win_ptr, int x, int y, int color,
		       char *string);
int		mlx_set_font(void *mlx_ptr, void *win_ptr, char *name);
void	*mlx_xpm_to_image(void *mlx_ptr, char **xpm_data,
			  int *width, int *height);
void	*mlx_xpm_file_to_image(void *mlx_ptr, char *filename,
			       int *width, int *height);
int			mlx_destroy_window(void *mlx_ptr, void *win_ptr);

int			mlx_destroy_image(void *mlx_ptr, void *img_ptr);

int		mlx_destroy_display(void *mlx_ptr);

/*
**  generic hook system for all events, and minilibX functions that
**    can be hooked. Some macro and defines from X11/X.h are needed here.
*/

int		mlx_do_key_autorepeatoff(void *mlx_ptr);
int		mlx_do_key_autorepeaton(void *mlx_ptr);
int		mlx_do_sync(void *mlx_ptr);

int			mlx_mouse_get_pos(void *mlx_ptr, void *win_ptr, int *x, int *y);
int		mlx_mouse_move(void *mlx_ptr, void *win_ptr, int x, int y);
int		mlx_mouse_hide(void *mlx_ptr, void *win_ptr);
int		mlx_mouse_show(void *mlx_ptr, void *win_ptr);

int			mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey);

#endif /* MLX_H */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:45:49 by jeportie          #+#    #+#             */
/*   Updated: 2025/01/19 21:27:34 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_INT_H
# define MLX_INT_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <X11/extensions/XShm.h>
# include <X11/XKBlib.h>
# include "define.h"

typedef int	(*t_mlx_event_f)(void *event_data, void *user_param);

typedef int	(*t_mlx_loop_f)(void *user_param);

typedef struct s_mlx_key_data
{
	int	keycode;
}				t_mlx_key_data;

typedef struct s_mlx_btn_data
{
	int	button;
	int	x;
	int	y;
}				t_mlx_btn_data;

typedef struct s_mlx_motion_data
{
	int	x;
	int	y;
}				t_mlx_motion_data;

typedef struct s_mlx_expose_data
{
	int	placeholder;
}				t_mlx_expose_data;

typedef struct s_xpm_col
{
	int		name;
	int		col;
}				t_xpm_col;

struct	s_col_name
{
	char	*name;
	int		color;
};

typedef struct s_event_list
{
	int				mask;
	t_mlx_event_f	hook;
	void			*param;
}				t_event_list;

typedef struct s_win_list
{
	Window				window;
	GC					gc;
	struct s_win_list	*next;
	t_event_list		hooks[MLX_MAX_EVENT];
}				t_win_list;

typedef struct s_img
{
	XImage			*image;
	Pixmap			pix;
	GC				gc;
	int				size_line;
	int				bpp;
	int				width;
	int				height;
	int				type;
	int				format;
	char			*data;
	XShmSegmentInfo	shm;
}				t_img;

typedef struct s_xvar
{
	Display		*display;
	Window		root;
	int			screen;
	int			depth;
	Visual		*visual;
	Colormap	cmap;
	int			private_cmap;
	t_win_list	*win_list;
	t_mlx_loop_f	loop_hook;
	void			*loop_param;
	int			use_xshm;
	int			pshm_format;
	int			do_flush;
	int			decrgb[6];
	Atom		wm_delete_window;
	Atom		wm_protocols;
	int			end_loop;
}				t_xvar;

typedef struct s_mlx_app
{
	t_xvar	*mlx_ptr;
	void	*win_ptr;
}				t_mlx_app;

int	mlx_int_do_nothing(void *param);
int		mlx_int_get_visual(t_xvar *xvar);
int	mlx_int_wait_first_expose(t_xvar *xvar, Window win);
void	mlx_int_rgb_conversion(t_xvar *xvar);
int	mlx_int_deal_shm(t_xvar *xvar);
void	*mlx_int_new_xshm_image();
char	**mlx_int_str_to_wordtab();
void	*mlx_new_image();
int		shm_att_pb();
int	mlx_int_set_win_event_mask(t_xvar *xvar);
int		mlx_int_str_str_cote(char *str, char *find, int len);
int		mlx_int_str_str(char *str, char *find, int len);
int	mlx_handle_event(t_xvar *xvar, XEvent *ev, t_win_list *win);

#endif /* MLX_INT_H */

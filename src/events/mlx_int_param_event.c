/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_param_event.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 00:34:40 by jeportie          #+#    #+#             */
/*   Updated: 2025/01/19 21:22:23 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mlx_int.h"

/*
** Fallback: does nothing if no hook or unrecognized event.
*/
static int	mlx_int_param_undef(void *event_data, void *user_param)
{
	(void)event_data;
	(void)user_param;
	return (0);
}

/*
** KEY PRESS
*/
static int	mlx_int_param_KeyPress(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
	t_mlx_key_data	key_data;

	key_data.keycode = XkbKeycodeToKeysym(xvar->display,
			ev->xkey.keycode, 0, 0);
	return (win->hooks[KeyPress].hook((void *)&key_data,
			win->hooks[KeyPress].param));
}

/*
** KEY RELEASE
*/
static int	mlx_int_param_KeyRelease(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
	t_mlx_key_data	key_data;

	key_data.keycode = XkbKeycodeToKeysym(xvar->display,
			ev->xkey.keycode, 0, 0);
	return (win->hooks[KeyRelease].hook((void *)&key_data,
			win->hooks[KeyRelease].param));
}

/*
** MOUSE PRESS
*/
static int	mlx_int_param_ButtonPress(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
	t_mlx_btn_data	btn_data;

	(void)xvar;
	btn_data.button = ev->xbutton.button;
	btn_data.x = ev->xbutton.x;
	btn_data.y = ev->xbutton.y;
	return (win->hooks[ButtonPress].hook((void *)&btn_data,
			win->hooks[ButtonPress].param));
}

/*
** MOUSE RELEASE
*/
static int	mlx_int_param_ButtonRelease(t_xvar *xvar,
	XEvent *ev, t_win_list *win)
{
	t_mlx_btn_data	btn_data;

	(void)xvar;
	btn_data.button = ev->xbutton.button;
	btn_data.x = ev->xbutton.x;
	btn_data.y = ev->xbutton.y;
	return (win->hooks[ButtonRelease].hook((void *)&btn_data,
			win->hooks[ButtonRelease].param));
}

/*
** MOUSE MOTION
*/
static int	mlx_int_param_MotionNotify(t_xvar *xvar,
	XEvent *ev, t_win_list *win)
{
	t_mlx_motion_data	motion;

	(void)xvar;
	motion.x = ev->xbutton.x;
	motion.y = ev->xbutton.y;
	return (win->hooks[MotionNotify].hook((void *)&motion,
			win->hooks[MotionNotify].param));
}

/*
** EXPOSE EVENT
*/
static int	mlx_int_param_Expose(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
	t_mlx_expose_data	ex_data;

	(void)xvar;
	ex_data.placeholder = 0;
	if (!ev->xexpose.count)
		return (win->hooks[Expose].hook((void *)&ex_data,
				win->hooks[Expose].param));
	return (0);
}

/*
** Generic fallback: call the hook with (void *)param or do nothing.
*/
static int	mlx_int_param_generic(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
	(void)xvar;
	return (win->hooks[ev->type].hook(NULL, win->hooks[ev->type].param));
}

/*
** Single dispatcher function, called from mlx_loop.
** We use if/else (no switch) to match 42 style.
*/
int	mlx_handle_event(t_xvar *xvar, XEvent *ev, t_win_list *win)
{
	if (ev->type == KeyPress && win->hooks[KeyPress].hook)
		mlx_int_param_KeyPress(xvar, ev, win);
	else if (ev->type == KeyRelease && win->hooks[KeyRelease].hook)
		mlx_int_param_KeyRelease(xvar, ev, win);
	else if (ev->type == ButtonPress && win->hooks[ButtonPress].hook)
		mlx_int_param_ButtonPress(xvar, ev, win);
	else if (ev->type == ButtonRelease && win->hooks[ButtonRelease].hook)
		mlx_int_param_ButtonRelease(xvar, ev, win);
	else if (ev->type == MotionNotify && win->hooks[MotionNotify].hook)
		mlx_int_param_MotionNotify(xvar, ev, win);
	else if (ev->type == Expose && win->hooks[Expose].hook)
		mlx_int_param_Expose(xvar, ev, win);
	else if (ev->type < MLX_MAX_EVENT && win->hooks[ev->type].hook)
		mlx_int_param_generic(xvar, ev, win);
	else
		mlx_int_param_undef(NULL, NULL);
	return (0);
}

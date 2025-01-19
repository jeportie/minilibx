/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 23:19:46 by jeportie          #+#    #+#             */
/*   Updated: 2025/01/19 21:36:07 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mlx_int.h"

/*
** Generic hooking function for event x_event with x_mask.
** `funct` must be: int my_hook(void *ev_data, void *user_param)
*/

int	mlx_hook(t_win_list *win, int x_event, int x_mask,
	int (*funct)(void *, void *), void *param)
{
	win->hooks[x_event].hook = (t_mlx_event_f)funct;
	win->hooks[x_event].param = param;
	win->hooks[x_event].mask = x_mask;
	return (0);
}

int	mlx_do_key_autorepeatoff(t_xvar *xvar)
{
	XAutoRepeatOff(xvar->display);
	return (0);
}

int	mlx_do_key_autorepeaton(t_xvar *xvar)
{
	XAutoRepeatOn(xvar->display);
	return (0);
}

int	mlx_do_sync(t_xvar *xvar)
{
	XSync(xvar->display, False);
	return (0);
}

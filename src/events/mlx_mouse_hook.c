/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse_hook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 00:18:25 by jeportie          #+#    #+#             */
/*   Updated: 2025/01/19 21:00:38 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mlx_int.h"

/*
** Now expects a callback of type: int my_mouse_cb(void *ev_data, void *param).
** This sets the ButtonPress hook.
*/
int	mlx_mouse_hook(t_win_list *win, int (*funct)(void *, void *), void *param)
{
	win->hooks[ButtonPress].hook = (t_mlx_event_f)funct;
	win->hooks[ButtonPress].param = param;
	win->hooks[ButtonPress].mask = ButtonPressMask;
	return (0);
}

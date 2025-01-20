/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_string_put.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:59:42 by jeportie          #+#    #+#             */
/*   Updated: 2025/01/20 14:02:20 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mlx_int.h"

int	mlx_string_put(t_xvar *xvar, t_win_list *win, int x, int y, int color,
	char *string)
{
	XGCValues	xgcv;

	xgcv.foreground = mlx_int_get_good_color(xvar, color);
	XChangeGC(xvar->display, win->gc, GCForeground, &xgcv);
	XDrawString(xvar->display, win->window, win->gc, x, y,
		string, strlen(string));
	if (xvar->do_flush)
		XFlush(xvar->display);
	return (0);
}

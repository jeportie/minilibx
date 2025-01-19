/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 00:30:30 by jeportie          #+#    #+#             */
/*   Updated: 2025/01/19 21:15:38 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mlx_int.h"

static int	win_count(t_xvar *xvar)
{
	int			i;
	t_win_list	*win;

	i = 0;
	win = xvar->win_list;
	while (win)
	{
		win = win->next;
		++i;
	}
	return (i);
}

int	mlx_loop_end(t_xvar *xvar)
{
	xvar->end_loop = 1;
	return (1);
}

int	mlx_loop(t_xvar *xvar)
{
	XEvent		ev;
	t_win_list	*win;

	mlx_int_set_win_event_mask(xvar);
	xvar->do_flush = 0;
	while (win_count(xvar) && !xvar->end_loop)
	{
		while (!xvar->end_loop && (!xvar->loop_hook || XPending(xvar->display)))
		{
			XNextEvent(xvar->display, &ev);
			win = xvar->win_list;
			while (win && (win->window != ev.xany.window))
				win = win->next;
			if (win && ev.type == ClientMessage
				&& ev.xclient.message_type == xvar->wm_protocols
				&& ev.xclient.data.l[0] == xvar->wm_delete_window
				&& win->hooks[DestroyNotify].hook)
				win->hooks[DestroyNotify].hook(NULL,
					win->hooks[DestroyNotify].param);
			else if (win)
				mlx_handle_event(xvar, &ev, win);
		}
		XSync(xvar->display, False);
		if (xvar->loop_hook)
			xvar->loop_hook(xvar->loop_param);
	}
	return (0);
}

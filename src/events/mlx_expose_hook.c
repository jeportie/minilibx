/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_expose_hook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 23:04:37 by jeportie          #+#    #+#             */
/*   Updated: 2025/01/19 21:21:00 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mlx_int.h"

/*
** Set up the Expose hook to use our unified callback signature.
*/
int	mlx_expose_hook(t_win_list *win, int (*funct)(void *, void *), void *param)
{
	win->hooks[Expose].hook = (t_mlx_event_f)funct;
	win->hooks[Expose].param = param;
	win->hooks[Expose].mask = ExposureMask;
	return (0);
}

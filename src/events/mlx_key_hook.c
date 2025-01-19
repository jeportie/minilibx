/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 12:18:24 by jeportie          #+#    #+#             */
/*   Updated: 2025/01/19 21:00:14 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mlx_int.h"

/*
** Now that we have a unified callback signature,
** we store it as (t_mlx_event_f).
*/

int	mlx_key_hook(t_win_list *win, int (*funct)(void *, void *), void *param)
{
	win->hooks[KeyRelease].hook = (t_mlx_event_f)funct;
	win->hooks[KeyRelease].param = param;
	win->hooks[KeyRelease].mask = KeyReleaseMask;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_loop_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 00:29:24 by jeportie          #+#    #+#             */
/*   Updated: 2025/01/19 21:14:05 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mlx_int.h"

/*
** We define mlx_loop_hook to store the given function pointer
** into xvar->loop_hook, plus the user param in xvar->loop_param.
**
** The user function signature is: int loop_func(void *param)
*/
int	mlx_loop_hook(t_xvar *xvar, int (*funct)(void *), void *param)
{
	xvar->loop_hook = funct;
	xvar->loop_param = param;
	return (0);
}

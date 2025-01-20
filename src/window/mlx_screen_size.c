/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_screen_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:35:38 by jeportie          #+#    #+#             */
/*   Updated: 2025/01/20 09:37:49 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mlx_int.h"

int	mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey)
{
	XWindowAttributes	xwattr;
	Status				ret;
	t_xvar				*xvar;

	xvar = mlx_ptr;
	ret = XGetWindowAttributes(xvar->display, xvar->root, &xwattr);
	(*sizex) = xwattr.width;
	(*sizey) = xwattr.height;
	return (0);
}

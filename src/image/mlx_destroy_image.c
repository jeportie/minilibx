/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_destroy_image.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 10:49:15 by jeportie          #+#    #+#             */
/*   Updated: 2025/01/20 12:44:10 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mlx_int.h"

int	mlx_destroy_image(t_xvar *xvar, t_img *img)
{
	if (img->type == MLX_TYPE_SHM_PIXMAP
		|| img->type == MLX_TYPE_SHM)
	{
		XShmDetach(xvar->display, &(img->shm));
		shmdt(img->shm.shmaddr);
	}
	XDestroyImage(img->image);
	XFreePixmap(xvar->display, img->pix);
	if (img->gc)
		XFreeGC(xvar->display, img->gc);
	free(img);
	if (xvar->do_flush)
		XFlush(xvar->display);
	return (0);
}

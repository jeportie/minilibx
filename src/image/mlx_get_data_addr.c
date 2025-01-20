/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_get_data_addr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:50:17 by jeportie          #+#    #+#             */
/*   Updated: 2025/01/20 12:52:00 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mlx_int.h"

char	*mlx_get_data_addr(t_img *img, int *bits_per_pixel,
		int *size_line, int *endian)
{
	*bits_per_pixel = img->bpp;
	*size_line = img->size_line;
	*endian = img->image->byte_order;
	return (img->data);
}

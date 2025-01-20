/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_lib_xpm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 13:20:26 by jeportie          #+#    #+#             */
/*   Updated: 2025/01/20 14:28:39 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mlx_int.h"

#include "../../include/define.h"
#include <string.h> /* for memcpy (or bcopy) */

/*
** Compare two XImages to see if they have identical format/dimensions.
** Return 1 if exactly the same, 0 otherwise.
*/
int	mlx_int_egal_img(XImage *img1, XImage *img2)
{
	if (!img1 || !img2)
		return (0);
	if (img1->width != img2->width || img1->height != img2->height)
		return (0);
	if (img1->xoffset != img2->xoffset || img1->format != img2->format)
		return (0);
	if (img1->byte_order != img2->byte_order)
		return (0);
	if (img1->bitmap_unit != img2->bitmap_unit
		|| img1->bitmap_bit_order != img2->bitmap_bit_order
		|| img1->bitmap_pad != img2->bitmap_pad
		|| img1->depth != img2->depth)
		return (0);
	if (img1->bytes_per_line != img2->bytes_per_line
		|| img1->bits_per_pixel != img2->bits_per_pixel)
		return (0);
	if (img1->red_mask != img2->red_mask
		|| img1->green_mask != img2->green_mask
		|| img1->blue_mask != img2->blue_mask)
		return (0);
	return (1);
}

/*
** Cleanup helper for partial failures or finishing in mlx_int_xpm_f_image.
** If 'img2' is not NULL, we free it, etc.
*/

static void	*mlx_xpm_img_cleanup(XImage *img1, XImage *img2,
	t_img *im2, t_xvar *xvar)
{
	if (img2)
		XDestroyImage(img2);
	if (!im2 && img1)
		XDestroyImage(img1);
	if (im2 && !mlx_int_egal_img(im2->image, img1))
	{
		if (im2->type > MLX_TYPE_XIMAGE)
		{
			XShmDetach(xvar->display, &im2->shm);
			shmdt(im2->data);
		}
		if (im2->image)
			XDestroyImage(im2->image);
		XFreePixmap(xvar->display, im2->pix);
		free(im2);
		im2 = NULL;
	}
	return (im2);
}

/*
** Create a new image from XPM data using xpm_func (XpmReadFileToImage or
** XpmCreateImageFromData). Then wrap it in a t_img struct for MiniLibX usage.
*/

void	*mlx_int_xpm_f_image(t_xvar *xvar, int *width, int *height,
	int (*xpm_func)(), void *param)
{
	XpmAttributes	xpm_att;
	XImage			*img1;
	XImage			*img2;
	t_img			*im2;

	im2 = NULL;
	img1 = NULL;
	img2 = NULL;
	xpm_att.visual = xvar->visual;
	xpm_att.colormap = xvar->cmap;
	xpm_att.depth = xvar->depth;
	xpm_att.bitmap_format = ZPixmap;
	xpm_att.valuemask = (XpmDepth | XpmBitmapFormat | XpmVisual | XpmColormap);
	if (xpm_func(xvar->display, param, &img1, &img2, &xpm_att) != 0 || !img1)
		return (mlx_xpm_img_cleanup(img1, img2, im2, xvar));
	if (!(im2 = (t_img *)mlx_new_image(xvar, img1->width, img1->height)))
		return (mlx_xpm_img_cleanup(img1, img2, im2, xvar));
	*width = img1->width;
	*height = img1->height;
	if (mlx_int_egal_img(im2->image, img1))
	{
		memcpy(im2->data, img1->data, (size_t)(img1->height
			* img1->bytes_per_line));
		XDestroyImage(img1);
		XDestroyImage(img2);
		return (im2);
	}
	if (im2->type > MLX_TYPE_XIMAGE)
		XShmDetach(xvar->display, &im2->shm);
	XDestroyImage(im2->image);
	im2->image = img1;
	im2->data = img1->data;
	im2->type = MLX_TYPE_XIMAGE;
	im2->size_line = img1->bytes_per_line;
	im2->bpp = img1->bits_per_pixel;
	return (mlx_xpm_img_cleanup(img1, img2, im2, xvar));
}

void	*mlx_xpm_file_to_image(t_xvar *xvar,char *filename,
			       int *width,int *height)
{
	return (mlx_int_xpm_f_image(xvar,width,height,XpmReadFileToImage,filename));
}


void	*mlx_xpm_to_image(t_xvar *xvar,char **data,int *width,int *height)
{
	return (mlx_int_xpm_f_image(xvar,width,height,XpmCreateImageFromData,(void *)data));
}

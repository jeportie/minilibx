/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_xpm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <user> <user@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:02:59 by <user>            #+#    #+#             */
/*   Updated: 2025/01/20 14:45:43 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mlx_int.h"

/*
** We keep the color table in a different file, or as 'extern struct s_col_name'
** declared in some .c. That is unchanged. So no global macros here.
*/
extern struct s_col_name mlx_col_name[];

char	*mlx_int_get_line(char *ptr, int *pos, int size)
{
	int	pos2;
	int	pos3;
	int	pos4;

	pos2 = mlx_int_str_str(ptr + *pos, "\"", size - *pos);
	if (pos2 == -1)
		return (NULL);
	pos3 = mlx_int_str_str(ptr + *pos + pos2 + 1, "\"",
			size - *pos - pos2 - 1);
	if (pos3 == -1)
		return (NULL);
	*(ptr + *pos + pos2) = '\0';
	*(ptr + *pos + pos2 + 1 + pos3) = '\0';
	pos4 = *pos + pos2 + 1;
	*pos += (pos2 + pos3 + 2);
	return (ptr + pos4);
}

/*
** A simpler version of strlcpy, if we want to avoid macros or certain C libs.
*/
unsigned int	strlcpy_is_not_posix(char *dest, char *src, unsigned int size)
{
	unsigned int	count;
	unsigned int	i;

	count = 0;
	while (src[count])
		count++;
	i = 0;
	while (src[i] && i + 1 < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (count);
}

char	*mlx_int_static_line(char **xpm_data, int *pos, int size)
{
	static char	*copy = NULL;
	static int	copy_len = 0;
	char		*str;
	int			len2;

	(void)size;
	str = xpm_data[*pos];
	(*pos)++;
	if (!str)
		return (NULL);
	len2 = (int)strlen(str);
	if (len2 > copy_len)
	{
		if (copy)
			free(copy);
		copy = malloc(len2 + 1);
		if (!copy)
			return (NULL);
		copy_len = len2;
	}
	strlcpy_is_not_posix(copy, str, (unsigned int)len2 + 1);
	return (copy);
}

int	mlx_int_get_col_name(char *str, int size)
{
	int	result;

	result = 0;
	while (size--)
		result = (result << 8) + (unsigned char)(*str++);
	return (result);
}

/*
** Map a color name to a numeric color. e.g. "red" -> 0xFF0000.
** or "#FFFFFF" -> 0xFFFFFF
*/
int	mlx_int_get_text_rgb(char *name, char *end)
{
	int		i;
	char	buff[64];

	if (*name == '#')
		return ((int)strtol(name + 1, NULL, 16));
	if (end)
	{
		snprintf(buff, 64, "%s %s", name, end);
		name = buff;
	}
	i = 0;
	while (mlx_col_name[i].name)
	{
		if (!strcasecmp(mlx_col_name[i].name, name))
			return (mlx_col_name[i].color);
		i++;
	}
	return (0);
}

/*
** Writes one pixel 'col' into data, respecting the image's endianness.
*/
int	mlx_int_xpm_set_pixel(t_img *img, char *data, int opp, int col, int x)
{
	int	dec;

	dec = opp;
	while (dec--)
	{
		if (img->image->byte_order)
			*(data + x * opp + dec) = (col & 0xFF);
		else
			*(data + x * opp + (opp - dec - 1)) = (col & 0xFF);
		col >>= 8;
	}
	return (0);
}

int	mlx_int_file_get_rid_comment(char *ptr, int size)
{
	int	com_begin;
	int	com_end;

	while ((com_begin = mlx_int_str_str_cote(ptr, "/*", size)) != -1)
	{
		com_end = mlx_int_str_str(ptr + com_begin + 2, "*/", size - com_begin - 2);
		if (com_end == -1)
			break ;
		memset(ptr + com_begin, ' ', (size_t)com_end + 4);
	}
	while ((com_begin = mlx_int_str_str_cote(ptr, "//", size)) != -1)
	{
		com_end = mlx_int_str_str(ptr + com_begin + 2, "\n", size - com_begin - 2);
		if (com_end == -1)
			break ;
		memset(ptr + com_begin, ' ', (size_t)com_end + 3);
	}
	return (0);
}

static int	parse_xpm_header(char *line, int *width, int *height,
	int *nc, int *cpp)
{
	char	**tab;

	tab = mlx_int_str_to_wordtab(line);
	if (!tab)
		return (0);
	*width = atoi(tab[0]);
	*height = atoi(tab[1]);
	*nc = atoi(tab[2]);
	*cpp = atoi(tab[3]);
	free(tab);
	if (*width <= 0 || *height <= 0 || *nc <= 0 || *cpp <= 0)
		return (0);
	return (1);
}

/*
** If cpp <= 2, we store colors in a direct array: "colors_direct[size]" 
** else we store them in an array of t_xpm_col: "colors[size]" 
*/
static int	parse_xpm_colors(t_xvar *xvar, void *info, int info_size,
	char *(*f)(), int cpp, int nc, t_xpm_col **colors, int **colors_direct)
{
	int		i;
	int		pos;
	char	*line;
	char	**tab;
	int		rgb_col;
	int		method;

	i = 0;
	pos = 0;
	method = (cpp <= 2); /* 1 => direct array, 0 => t_xpm_col array */

	if (method)
	{
		*colors_direct = malloc((cpp == 2 ? 65536 : 256) * sizeof(int));
		if (!(*colors_direct))
			return (0);
	}
	else
	{
		*colors = malloc(nc * sizeof(**colors));
		if (!(*colors))
			return (0);
	}
	while (i < nc)
	{
		line = f(info, &pos, info_size);
		if (!line)
			return (0);
		/* skip 'cpp' chars, parse the remainder with mlx_int_str_to_wordtab */
		tab = mlx_int_str_to_wordtab(line + cpp);
		if (!tab)
			return (0);
		rgb_col = 0;
		rgb_col = mlx_int_get_text_rgb(tab[1], tab[2]); /* looking for "c" ? */
		if (method)
		{
			/* direct color array: index by color name's int code */
			(*colors_direct)[mlx_int_get_col_name(line, cpp)] = rgb_col;
		}
		else
		{
			(*colors)[nc - 1 - i].name = mlx_int_get_col_name(line, cpp);
			(*colors)[nc - 1 - i].col = rgb_col;
		}
		i++;
		free(tab);
	}
	return (1);
}

static int	parse_xpm_pixels(t_img *img, t_xvar *xvar, void *info,
	char *(*f)(), int info_size, int width, int height,
	int nc, int cpp, t_xpm_col *colors, int *colors_direct)
{
	char		*line;
	char		*data;
	int			i;
	int			x;
	int			col;
	int			col_name;
	int			pos;
	int			opp;

	pos = 0;
	opp = img->bpp / 8;
	i = height;
	data = img->data;
	while (i--)
	{
		line = f(info, &pos, info_size);
		if (!line)
			return (0);
		x = 0;
		while (x < width)
		{
			col = 0;
			col_name = mlx_int_get_col_name(line + (cpp * x), cpp);
			if (colors_direct)
				col = colors_direct[col_name];
			else
				col = find_color_in_tab(col_name, colors, nc);
			/*
			** if col == -1 => "transparent"? You might do something else
			** but for simplicity, let's assign 0xFF000000 if that matters.
			*/
			if (col == -1)
				col = 0xFF000000;
			mlx_int_xpm_set_pixel(img, data, opp, col, x);
			x++;
		}
		data += img->size_line;
	}
	return (1);
}

/*
** A small helper to find 'col_name' in the array 'colors'. 
** Typically, you stored them in reverse order with "nc - 1 - i" 
** but that depends on your original logic.
*/
static int	find_color_in_tab(int col_name, t_xpm_col *colors, int nc)
{
	int	j;

	j = 0;
	while (j < nc)
	{
		if (colors[j].name == col_name)
			return (colors[j].col);
		j++;
	}
	return (-1);
}

/* ------------------------------------------------------------------------ */
/*                          The main parse function                          */
/* ------------------------------------------------------------------------ */

static void	*mlx_int_parse_xpm(t_xvar *xvar, void *info, int info_size,
	char *(*f)())
{
	t_img		*img;
	t_xpm_col	*colors;
	int			*colors_direct;
	int			width;
	int			height;
	int			nc;
	int			cpp;
	char		*line;
	int			pos;

	img = NULL;
	colors = NULL;
	colors_direct = NULL;
	pos = 0;
	line = f(info, &pos, info_size);
	if (!line)
		return (NULL);
	if (!parse_xpm_header(line, &width, &height, &nc, &cpp))
		return (NULL);
	if (!parse_xpm_colors(xvar, info, info_size, f,
			cpp, nc, &colors, &colors_direct))
		return (NULL);
	img = mlx_new_image(xvar, width, height);
	if (!img)
	{
		if (colors)
			free(colors);
		if (colors_direct)
			free(colors_direct);
		return (NULL);
	}
	if (!parse_xpm_pixels(img, xvar, info, f, info_size,
			width, height, nc, cpp, colors, colors_direct))
	{
		/* possibly free 'img', 'colors', 'colors_direct' on failure */
		if (colors)
			free(colors);
		if (colors_direct)
			free(colors_direct);
		XDestroyImage(img->image);
		XFreePixmap(xvar->display, img->pix);
		free(img);
		return (NULL);
	}
	if (colors)
		free(colors);
	if (colors_direct)
		free(colors_direct);
	return (img);
}

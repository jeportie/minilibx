/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_app_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 22:13:24 by jeportie          #+#    #+#             */
/*   Updated: 2025/01/18 22:32:53 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mlx.h"
#include "../../include/mlx_int.h"
#include "../../include/define.h"

t_mlx_app	*my_mlx_app_create(int width, int height, const char *title)
{
	t_mlx_app	*app;

	app = malloc(sizeof(t_mlx_app));
	if (!app)
	{
		fprintf(stderr, ERR_MALLOC);
		return (NULL);
	}
	app->mlx_ptr = mlx_init();
	if (!app->mlx_ptr)
	{
		fprintf(stderr, ERR_NO_X_DISPLAY);
		free(app);
		return (NULL);
	}
	app->win_ptr = mlx_new_window(app->mlx_ptr, width, height, (char *)title);
	if (!app->win_ptr)
	{
		fprintf(stderr, ERR_WINDOW_CREATION);
		mlx_destroy_display(app->mlx_ptr);
		free(app);
		return (NULL);
	}
	return (app);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeportie <jeportie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 22:20:18 by jeportie          #+#    #+#             */
/*   Updated: 2025/01/18 22:31:12 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# define MLX_TYPE_SHM_PIXMAP 3
# define MLX_TYPE_SHM 2
# define MLX_TYPE_XIMAGE 1

# define MLX_MAX_EVENT LASTEvent

# define ENV_DISPLAY "DISPLAY"
# define LOCALHOST "localhost"

/**************************ERROR MESSAGES**************************************/

# define ERR_MALLOC				"Mlx Error: malloc() failed\n"
# define ERR_NO_X_DISPLAY		"Mlx Error: Could not open X Display\n"
# define ERR_WINDOW_CREATION	"Mlx Error: Could not create new Window\n"
# define ERR_NO_TRUECOLOR		"Mlx Error: No TrueColor Visual available\n"
# define WARN_SHM_ATTACH		"Mlx Warning: server can't attach shrd memory\n"

#endif /* DEFINE_H */

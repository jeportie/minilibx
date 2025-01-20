/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <user> <user@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 22:20:18 by <user>            #+#    #+#             */
/*   Updated: 2025/01/20 14:16:06 by jeportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# include <X11/X.h>  /* for LASTEvent, etc. */

/************************** SHM / IMAGE TYPES ********************************/
# define MLX_TYPE_SHM_PIXMAP 3
# define MLX_TYPE_SHM 2
# define MLX_TYPE_XIMAGE 1

# define MLX_MAX_EVENT LASTEvent

# define ENV_DISPLAY "DISPLAY"
# define LOCALHOST "localhost"

/************************** ERROR/WARN MESSAGES *******************************/
# define ERR_MALLOC				"Mlx Error: malloc() failed\n"
# define ERR_NO_X_DISPLAY		"Mlx Error: Could not open X Display\n"
# define ERR_WINDOW_CREATION	"Mlx Error: Could not create new Window\n"
# define ERR_NO_TRUECOLOR		"Mlx Error: No TrueColor Visual available\n"
# define WARN_SHM_ATTACH		"Mlx Warning: server can't attach shrd memory\n"

# define ERR_XPM_PARSE			"Mlx Error: XPM parse failure\n"
# define ERR_XPM_ALLOC			"Mlx Error: XPM memory allocation failed\n"

#endif /* DEFINE_H */


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:15:01 by yguaye            #+#    #+#             */
/*   Updated: 2018/07/20 15:23:48 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft_base/io.h>
#include "nm/nm.h"

int					nm_perror(const char *file, const char *msg)
{
	ft_putstr_fd("ft_nm: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	return (0);
}

int					nm_rerror(t_macho64_obj *obj, const char *msg)
{
	ft_putstr_fd("ft_nm: ", STDERR_FILENO);
	ft_putstr_fd(obj->name, STDERR_FILENO);
	ft_putchar_fd(' ', STDERR_FILENO);
	if (msg)
	{
		ft_putendl_fd(msg, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:15:01 by yguaye            #+#    #+#             */
/*   Updated: 2018/07/17 18:52:55 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft_base/io.h>
#include "nm/errors.h"

static const char	*g_errmap[] =
{
	"No error",
	"No such file or directory.",
	"fstat() failed",
	"mmap() failed",
	"The file was not recognized as a valid object file",
	"<placeholder>",
	"<placeholder>",
	"<placeholder>",
	"Unknown error"
};

int					nm_perror(const char *prefix, t_nm_errtype err, int ret)
{
	ft_putstr_fd("ft_nm: ", STDERR_FILENO);
	ft_putstr_fd(prefix, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	err = err > NMERR_UNKNOWN ? NMERR_UNKNOWN : err;
	ft_putendl_fd(g_errmap[err], STDERR_FILENO);
	return (ret);
}

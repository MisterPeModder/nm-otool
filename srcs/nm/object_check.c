/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 05:43:22 by yguaye            #+#    #+#             */
/*   Updated: 2018/07/22 04:40:28 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <mach-o/loader.h>
#include <libft_base/io.h>
#include "nm/nm.h"

static int			nm_check_m64header(t_macho64_obj *obj)
{
	uint32_t		ft;
	const char		*msg;

	ft = obj->header->filetype & 0xfffff;
	if (obj->header->magic != MH_MAGIC_64
			|| (ft != MH_OBJECT && ft != MH_EXECUTE))
	{
		msg = "The file was not recognized as a valid object file";
		return (nm_rerror(obj, msg));
	}
	else if (obj->header->sizeofcmds > obj->size)
	{
		msg = OBJ_TRUNC "load commands extend past the end of the file)";
		return (nm_rerror(obj, msg));
	}
	return (1);
}

static int			nm_check_lcmd(t_macho64_obj *obj, const t_mlcmd *cmd,
		uint32_t i)
{
	const char		*msg;

	if (cmd->cmdsize < 8)
		msg = " with size less than 8 bytes)";
	else if (cmd->cmdsize % 8)
		msg = " cmdsize not a multiple of 8)";
	else
	{
		if (cmd->cmd == LC_SEGMENT_64)
		{
			obj->nsects = ((const struct segment_command_64 *)cmd)->nsects;
			obj->sec_hdrs = (const t_msec64 *)
				((const struct segment_command_64 *)cmd + 1);
		}
		return (1);
	}
	nm_rerror(obj, NULL);
	ft_putstr_fd(OBJ_TRUNC"load command ", STDERR_FILENO);
	ft_putnbr_fd((int)i, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	return (0);
}

int					nm_check_object(t_macho64_obj *obj)
{
	const t_mlcmd	*cmd;
	uint32_t		i;

	if (!nm_check_m64header(obj))
		return (0);
	obj->lcmds = (const t_mlcmd *)(obj->header + 1);
	obj->sec_hdrs = NULL;
	cmd = obj->lcmds;
	i = 0;
	while (i < obj->header->ncmds)
	{
		if (!nm_check_lcmd(obj, cmd, i))
			return (0);
		++i;
	}
	return (1);
}

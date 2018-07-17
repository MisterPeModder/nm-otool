/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 11:34:06 by yguaye            #+#    #+#             */
/*   Updated: 2018/07/17 16:39:11 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <mach-o/nlist.h>
#include <libft_base/io.h>
#include <mach-o/loader.h>
#include "nm/obj_defs.h"

#include <stdio.h>

static int				nm_error(const char *msg, int ret)
{
	ft_putendl_fd(msg, 2);
	return (ret);
}

static int				nm_filesize(int fd, size_t *fsize)
{
	struct stat			st;

	if (fstat(fd, &st) == -1)
		return (nm_error("failed to get file size", 0));
	*fsize = (size_t)st.st_size;
	return (1);
}

static void				nm_obj_print_sym(const void *obj,
		const struct symtab_command *s)
{
	const struct nlist_64	*sym;
	const char				*str_table;
	uint32_t				i;

	sym = (const struct nlist_64 *)((const char *)obj + s->symoff);
	str_table = (const char *)obj + s->stroff;
	i = 0;
	while (i < s->nsyms)
	{
/*		printf("offset: %8lx\n", (char *)(sym + i) - (char *)obj);
		printf("str table index: %x\n", sym[i].n_un.n_strx);*/
		printf("%s\n", str_table + sym[i].n_un.n_strx);
		++i;
	}
}

static int				nm_obj_sym(const void *obj)
{
	const t_nm_lcmd		*lc;
	uint32_t			i;

	lc = (const t_nm_lcmd *)((const t_nm_header *)obj + 1);
	i = 0;
	while (i < ((t_nm_header *)obj)->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			nm_obj_print_sym(obj, (const struct symtab_command *)lc);
			break ;
		}
		lc = (const t_nm_lcmd *)((const char *)lc + lc->cmdsize);
		++i;
	}
	if (i == ((t_nm_header *)obj)->ncmds)
		return (nm_error("no symbol table load command found!", 0));
	return (1);
}

int						main(int ac, char **av)
{
	int					fd;
	size_t				fsize;
	void				*buf;

	if (ac != 2)
		return (nm_error("Wrong number of arguments!", 1));
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (nm_error("Failed to open file", 2));
	if (!nm_filesize(fd, &fsize))
		return (3);
	if ((buf = mmap(NULL, fsize, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (nm_error("Failed to mmap file", 4));
	if (!nm_obj_sym(buf))
		return (5);
	munmap(buf, fsize);
	close(fd);
}

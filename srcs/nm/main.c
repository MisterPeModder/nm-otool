/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 11:34:06 by yguaye            #+#    #+#             */
/*   Updated: 2018/07/17 19:25:24 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <mach-o/nlist.h>
#include <libft_base/io.h>
#include <mach-o/loader.h>
#include "nm/errors.h"
#include "nm/obj_defs.h"

#include <stdio.h>

static int				nm_filesize(int fd, size_t *fsize)
{
	struct stat			st;

	if (fstat(fd, &st) == -1)
		return (0);
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

static int				nm_obj_header_check(const t_nm_header *h)
{
	if (h->magic == MH_MAGIC_64 && h->filetype == MH_OBJECT)
		return (1);
	return (0);
}

static t_nm_errtype		nm_parse_obj_header(const void *obj)
{
	const t_nm_header	*h;
	const t_nm_lcmd		*lc;
	uint32_t			i;

	h = (const t_nm_header *)obj;
	if (!nm_obj_header_check(h))
		return (NMERR_BAD_OBJ);
	lc = (const t_nm_lcmd *)(h + 1);
	i = 0;
	while (i < h->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			nm_obj_print_sym(obj, (const struct symtab_command *)lc);
			break ;
		}
		lc = (const t_nm_lcmd *)((const char *)lc + lc->cmdsize);
		++i;
	}
	return (NMERR_OK);
}

static t_nm_errtype		ft_nm(const char *file)
{
	int					fd;
	size_t				fsize;
	void				*buf;
	t_nm_errtype		err;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (NMERR_NO_FILE);
	if (!nm_filesize(fd, &fsize))
	{
		close(fd);
		return (NMERR_STAT_FAIL);
	}
	if ((buf = mmap(NULL, fsize, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		close(fd);
		return (NMERR_MMAP_FAIL);
	}
	err = nm_parse_obj_header(buf);
	munmap(buf, fsize);
	close(fd);
	return (err);
}

int						main(int ac, char **av)
{
	t_nm_errtype		ret;
	t_nm_errtype		tmp;
	int					i;

	if (ac == 1 && !((ret = ft_nm("a.out")) * 0))
		return (ret == NMERR_OK ? EXIT_SUCCESS :
				nm_perror("a.out", ret, EXIT_FAILURE));
	ret = NMERR_OK;
	i = 0;
	while (++i < ac)
	{
		if ((tmp = ft_nm(av[i])) != NMERR_OK)
		{
			nm_perror(av[i], tmp, 0);
			ret = tmp;
		}
	}
	return (ret == NMERR_OK ? EXIT_SUCCESS : EXIT_FAILURE);
}

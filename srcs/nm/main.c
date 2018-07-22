/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 11:34:06 by yguaye            #+#    #+#             */
/*   Updated: 2018/07/22 01:49:58 by yguaye           ###   ########.fr       */
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
#include "nm/nm.h"

static int				nm_filesize(int fd, uint64_t *fsize)
{
	struct stat			st;

	if (fstat(fd, &st) == -1)
		return (0);
	*fsize = (uint64_t)st.st_size;
	return (1);
}

static int				nm_parse_obj_header(t_macho64_obj *obj, int print_file)
{
	const t_mlcmd		*lc;
	uint32_t			i;

	lc = obj->lcmds;
	i = 0;
	while (i < obj->header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			if (!nm_obj_print_syms(obj, (const struct symtab_command *)lc,
						print_file))
				return (0);
			break ;
		}
		lc = (const t_mlcmd *)((const char *)lc + lc->cmdsize);
		++i;
	}
	return (1);
}

static int				ft_nm(const char *path, int print_file)
{
	int					fd;
	t_macho64_obj		obj;
	int					err;

	obj.name = path;
	if ((fd = open(path, O_RDONLY)) == -1)
		return (nm_perror(path, "No such file or directory."));
	if (!nm_filesize(fd, &obj.size))
	{
		close(fd);
		return (nm_perror(path, "fstat() failed."));
	}
	if ((obj.header = mmap(NULL, obj.size, PROT_READ,
					MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		close(fd);
		return (nm_perror(path, "mmap failed()."));
	}
	if ((err = nm_check_object(&obj)))
		err = nm_parse_obj_header(&obj, print_file);
	munmap((void *)obj.header, obj.size);
	close(fd);
	return (err);
}

int						main(int ac, char **av)
{
	int					ret;
	int					i;

	if (ac == 1)
		return (ft_nm("a.out", 0) ? EXIT_SUCCESS : EXIT_FAILURE);
	i = 0;
	ret = 1;
	while (++i < ac)
	{
		if (!ft_nm(av[i], ac > 2))
			ret = 0;
	}
	return (ret ? EXIT_SUCCESS : EXIT_FAILURE);
}

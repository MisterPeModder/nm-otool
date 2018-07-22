/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 18:05:11 by yguaye            #+#    #+#             */
/*   Updated: 2018/07/22 05:07:08 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include <mach-o/nlist.h>
# include <mach-o/loader.h>

typedef struct mach_header_64	t_mh64;
typedef struct load_command		t_mlcmd;
typedef struct section_64		t_msec64;

typedef struct		s_macho64_obj
{
	const char		*name;
	uint64_t		size;
	const t_mh64	*header;
	const t_mlcmd	*lcmds;
	uint32_t		nsects;
	const t_msec64	*sec_hdrs;
}					t_macho64_obj;

# define OBJ_TRUNC "truncated or malformed object ("

int					nm_perror(const char *file, const char *msg);
int					nm_rerror(t_macho64_obj *obj, const char *msg);

int					nm_check_object(t_macho64_obj *obj);

int					nm_obj_print_syms(t_macho64_obj *obj,
		const struct symtab_command *s, int print_file);

typedef struct		s_msym
{
	const char		*name;
	uint64_t		address;
	int				print_address;
	char			type;
}					t_msym;

int					nm_sort_syms(t_msym *to_sort, uint32_t size);

#endif

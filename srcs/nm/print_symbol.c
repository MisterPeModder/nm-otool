/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 16:01:28 by yguaye            #+#    #+#             */
/*   Updated: 2018/07/22 05:10:52 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft_base/io.h>
#include <libft_base/stringft.h>
#include "nm/nm.h"

static char			nm_get_sym_type(t_macho64_obj *obj,
		const struct nlist_64 *sym, int *print_address)
{
	char			ret;

	ret = '?';
	if (sym->n_type & N_STAB)
		return (0);
	else if ((sym->n_type & N_TYPE) == N_SECT)
	{
		if (obj->sec_hdrs == NULL || sym->n_sect == NO_SECT
				|| sym->n_sect > obj->nsects)
			ret = 's';
		else if (ft_strequ(obj->sec_hdrs[sym->n_sect - 1].sectname, SECT_TEXT))
			ret = 't';
		else if (ft_strequ(obj->sec_hdrs[sym->n_sect - 1].sectname, SECT_BSS))
			ret = 'b';
		else if (ft_strequ(obj->sec_hdrs[sym->n_sect - 1].sectname, SECT_DATA))
			ret = 'd';
		else
			ret = 's';
		*print_address = 1;
	}
	else if ((sym->n_type & N_TYPE) == N_UNDF)
		ret = 'u';
	else if ((sym->n_type & N_TYPE) == N_ABS)
		ret = 'a';
	return (sym->n_type & N_EXT && ret >= 'a' && ret <= 'z' ? ret - 32 : ret);
}

static t_msym		*nm_make_symtab(t_macho64_obj *obj,
		const struct symtab_command *s)
{
	t_msym					*table;
	const struct nlist_64	*sym;
	const char				*str_table;
	uint32_t				i;

	if (!(table = malloc(sizeof(t_msym) * s->nsyms)))
		return (NULL);
	sym = (const struct nlist_64 *)((const char *)obj->header + s->symoff);
	str_table = (const char *)obj->header + s->stroff;
	i = 0;
	while (i < s->nsyms)
	{
		table[i].name = str_table + sym[i].n_un.n_strx;
		table[i].address = sym[i].n_value;
		table[i].print_address = 0;
		table[i].type = nm_get_sym_type(obj, sym + i, &table[i].print_address);
		++i;
	}
	return (table);
}

static void			nm_obj_print_sym(t_msym *sym)
{
	const char		*base = "0123456789abcdef";
	uint64_t		i;

	if (!sym->type)
		return ;
	if (sym->print_address)
	{
		i = 0x1000000000000000;
		while (i > 1)
		{
			ft_putchar(base[sym->address / i % 16]);
			i /= 16;
		}
		ft_putchar(base[sym->address % 16]);
	}
	else
		ft_putstr("                ");
	ft_putchar(' ');
	ft_putchar(sym->type);
	ft_putchar(' ');
	ft_putendl(sym->name);
}

int					nm_obj_print_syms(t_macho64_obj *obj,
		const struct symtab_command *s, int print_file)
{
	t_msym			*table;
	uint32_t		i;

	if (!(table = nm_make_symtab(obj, s)))
		return (0);
	if (!nm_sort_syms(table, s->nsyms))
	{
		free(table);
		return (0);
	}
	if (print_file)
	{
		ft_putchar('\n');
		ft_putstr(obj->name);
		ft_putendl(":");
	}
	i = 0;
	while (i < s->nsyms)
		nm_obj_print_sym(&table[i++]);
	free(table);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 02:04:02 by yguaye            #+#    #+#             */
/*   Updated: 2018/07/20 16:47:10 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft_base/stringft.h>
#include "nm/nm.h"

static void			nmssym_split(t_msym *a, t_msym *b, const size_t d[3])
{
	size_t			i;
	size_t			j;
	size_t			k;

	if (d[2] - d[0] < 2)
		return ;
	nmssym_split(b, a, (const size_t[]){d[0], (d[0] + d[1]) / 2, d[1]});
	nmssym_split(b, a, (const size_t[]){d[1], (d[1] + d[2]) / 2, d[2]});
	i = d[0];
	j = d[1];
	k = d[0];
	while (k < d[2])
	{
		if (i < d[1] && (j >= d[2] || !(ft_strcmp(b[i].name, b[j].name) > 0)))
			a[k] = b[i++];
		else
			a[k] = b[j++];
		++k;
	}
}

int					nm_sort_syms(t_msym *to_sort, uint32_t size)
{
	uint32_t		i;
	t_msym			*tmp;

	if (!(tmp = (t_msym *)malloc(sizeof(t_msym) * size)))
		return (0);
	i = 0;
	while (i < size)
	{
		tmp[i] = to_sort[i];
		++i;
	}
	nmssym_split(to_sort, tmp, (const size_t[]){0, size / 2, size});
	free(tmp);
	return (1);
}

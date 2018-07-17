/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:21:37 by yguaye            #+#    #+#             */
/*   Updated: 2018/07/17 18:54:55 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

typedef enum
{
	NMERR_OK,
	NMERR_NO_FILE,
	NMERR_STAT_FAIL,
	NMERR_MMAP_FAIL,
	NMERR_BAD_OBJ,
	NMERR_UNKNOWN
}	t_nm_errtype;

int					nm_perror(const char *prefix, t_nm_errtype err, int ret);

#endif

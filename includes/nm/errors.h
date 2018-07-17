/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:21:37 by yguaye            #+#    #+#             */
/*   Updated: 2018/07/17 18:08:21 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

typedef enum
{
	NMERR_OK,
	NMERR_BAD_OBJ,
	NMERR_LCST_NOT_FOUND,
	NMERR_LCST_2BIG,
	NMERR_LCST,
	NMERR_UNKNOWN
}	t_nm_errtype;

int					nm_perror(const char *prefix, t_nm_errtype err, int ret);

#endif

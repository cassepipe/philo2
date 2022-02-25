/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <tpouget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:48:54 by tpouget           #+#    #+#             */
/*   Updated: 2022/02/25 12:48:54 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "get_time.h"
#include "structs.h"
#include "defines.h"

int	get_time(unsigned long *time)
{
	struct timeval	tv;
	unsigned long	ret;

	if (gettimeofday(&tv, NULL) != 0)
		return (ERROR);
	ret = 1000 * (unsigned long)(tv.tv_sec);
	ret += (unsigned long)(tv.tv_usec) / 1000;
	*time = ret;
	return (NOERROR);
}

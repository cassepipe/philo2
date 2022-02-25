/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep_ms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <tpouget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:52:12 by tpouget           #+#    #+#             */
/*   Updated: 2022/02/25 12:52:12 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "usleep_ms.h"
#include "defines.h"

void	usleep_ms(unsigned int time_in_ms)
{
	float	time;
	int		i;

	i = 0;
	time = ((float) time_in_ms) * 1000.0 / USLEEP_SPLIT;
	while (i < USLEEP_SPLIT)
	{
		usleep(time);
		i++;
	}
}

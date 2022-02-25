/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <tpouget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:51:41 by tpouget           #+#    #+#             */
/*   Updated: 2022/02/25 12:51:41 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "think.h"
#include "structs.h"
#include "defines.h"

int	think(t_philo *philo, t_env *env)
{
	unsigned long	time;

	if (get_time(&time) == ERROR)
		return (ERROR);
	print_philo_think(time, philo, env);
	usleep(1000);
	return (DONE_THINKING);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <tpouget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:51:00 by tpouget           #+#    #+#             */
/*   Updated: 2022/02/25 12:51:00 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routine.h"
#include "structs.h"
#include "defines.h"
#include <unistd.h>

void	*routine(void *arg)
{
	t_philo	*philo;
	t_env	*env;

	philo = (t_philo *) arg;
	env = philo->env;
	get_time(&philo->last_meal_time);
	if (philo->id % 2)
		usleep(env->time_to_eat * 1000 / 2);
	while (1)
	{
		if (check_state(philo, env) != ALIVE)
			break ;
		if (eat(philo, env) != DONE_EATING)
			break ;
		if (check_state(philo, env) != ALIVE)
			break ;
		if (sleeph(philo, env) != DONE_SLEEPING)
			break ;
		if (check_state(philo, env) != ALIVE)
			break ;
		if (think(philo, env) != DONE_THINKING)
			break ;
	}
	return (NULL);
}

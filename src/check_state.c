/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <tpouget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:53:00 by tpouget           #+#    #+#             */
/*   Updated: 2022/02/25 12:53:00 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "defines.h"
#include "check_state.h"

int	check_state(t_philo *philo, t_env *env)
{
	unsigned long	time;
	unsigned long	time_since_last_meal;

	if (env->quit > 0)
		return (DEAD);
	if (philo->meals_left == 0)
		return (DONE_EATING);
	if (get_time(&time) == ERROR)
		return (ERROR);
	time_since_last_meal = time - philo->last_meal_time;
	if (time_since_last_meal > (unsigned long)env->time_to_die)
	{
		print_philo_death(time, philo, env);
		env->quit++;
		return (DEAD);
	}
	return (ALIVE);
}

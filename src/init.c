/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <tpouget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:49:06 by tpouget           #+#    #+#             */
/*   Updated: 2022/02/25 12:49:06 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "init.h"
#include "structs.h"
#include "defines.h"

int	init_forks(t_env *env)
{
	int	i;
	int	ret;

	i = 0;
	while (i < env->nb_philo)
	{
		ret = pthread_mutex_init(&env->forks[i].mutex, NULL);
		if (ret)
			return (ret);
		env->forks[i].status = UNLOCKED;
		i++;
	}
	return (0);
}

int	init_locks(t_env *env)
{
	int	ret;

	ret = init_forks(env);
	if (ret)
		return (ret);
	ret = pthread_mutex_init(&env->quitlock, NULL);
	if (ret)
		return (ret);
	ret = pthread_mutex_init(&env->printlock, NULL);
	if (ret)
		return (ret);
	return (0);
}

int	init_philosophers(t_env *env, t_philo *philos)
{
	int	i;
	int	j;

	i = 0;
	while (i < env->nb_philo)
	{
		philos[i].env = env;
		philos[i].id = i + 1;
		philos[i].own_fork = &env->forks[i];
		j = (philos[i].id != env->nb_philo) * (i + 1);
		philos[i].borrowed_fork = &env->forks[j];
		philos[i].last_meal_time = 0;
		if (env->must_eat_times < 1)
			philos[i].meals_left = -1;
		else
			philos[i].meals_left = env->must_eat_times;
		philos[i].is_uneven = (philos[i].id % 2);
		philos[i].is_first = (philos[i].is_uneven && philos[i].id == 1);
		philos[i].is_last = (philos[i].is_uneven
				&& philos[i].id == env->nb_philo);
		i++;
	}
	return (0);
}

int	init_env(t_env *env, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (7);
	if (get_nb_philo(env, av))
		return (1);
	if (get_time_to_die(env, av))
		return (2);
	if (get_time_to_eat(env, av))
		return (3);
	if (get_time_to_sleep(env, av))
		return (4);
	if (ac == 6)
		if (get_must_eat_times(env, av))
			return (5);
	env->philosophers = malloc(env->nb_philo * sizeof(t_philo));
	env->forks = malloc(env->nb_philo * sizeof(t_fork));
	if (env->forks == NULL || env->philosophers == NULL)
		return (8);
	init_philosophers(env, env->philosophers);
	if (init_locks(env))
		return (9);
	if (get_time(&env->starting_time))
		return (10);
	return (0);
}

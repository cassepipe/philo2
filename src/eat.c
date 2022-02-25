/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <tpouget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:53:10 by tpouget           #+#    #+#             */
/*   Updated: 2022/02/25 12:53:10 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "structs.h"
#include "defines.h"
#include "eat.h"

int	eat_action(t_philo *philo, t_env *env)
{
	unsigned long	time;

	if (get_time(&time) == ERROR)
		return (ERROR);
	print_philo_eat(time, philo, env);
	philo->last_meal_time = time;
	if (env->must_eat_times > 0)
		philo->meals_left--;
	time = env->time_to_eat;
	if (env->time_to_eat > env->time_to_die)
		time = env->time_to_die;
	usleep_ms(time);
	return (DONE_EATING);
}

int	eat_cycle(t_philo *philo, t_env *env, t_fork *fork1, t_fork *fork2)
{
	if (take_fork(fork1) == DID_NOT_TAKE)
	{
		usleep(500);
		return (DID_NOT_EAT);
	}
	/*print_philo_own_fork(0, philo, env);*/
	if (take_fork(fork2) == DID_NOT_TAKE)
	{
		put_down_fork(fork1);
		usleep(500);
		return (DID_NOT_EAT);
	}
	/*print_philo_borrowed_fork(0, philo, env);*/
	if (eat_action(philo, env) == ERROR)
	{
		put_down_both_forks(philo);
		return (ERROR);
	}
	put_down_both_forks(philo);
	return (DONE_EATING);
}

int	eat(t_philo *philo, t_env *env)
{
	t_fork	*fork1;
	t_fork	*fork2;
	int		state;

	assign_forks(&fork1, &fork2, philo);
	state = eat_cycle(philo, env, fork1, fork2);
	while (state != DONE_EATING)
	{
		state = eat_cycle(philo, env, fork1, fork2);
	}
	return (DONE_EATING);
}

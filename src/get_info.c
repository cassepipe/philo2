/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <tpouget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:48:29 by tpouget           #+#    #+#             */
/*   Updated: 2022/02/25 12:48:33 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_info.h"
#include "structs.h"

int	get_nb_philo(t_env *env, char **av)
{
	int	nb_philo;

	nb_philo = ft_atoi(av[1]);
	if (nb_philo <= 0)
		return (-1);
	else
		env->nb_philo = nb_philo;
	return (0);
}

int	get_time_to_die(t_env *env, char **av)
{
	int	time_to_die;

	time_to_die = ft_atoi(av[2]);
	if (time_to_die <= 0)
		return (-1);
	else
		env->time_to_die = time_to_die;
	return (0);
}

int	get_time_to_eat(t_env *env, char **av)
{
	int	time_to_eat;

	time_to_eat = ft_atoi(av[3]);
	if (time_to_eat <= 0)
		return (-1);
	else
		env->time_to_eat = time_to_eat;
	return (0);
}

int	get_time_to_sleep(t_env *env, char **av)
{
	int	time_to_sleep;

	time_to_sleep = ft_atoi(av[4]);
	if (time_to_sleep <= 0)
		return (-1);
	else
		env->time_to_sleep = time_to_sleep;
	return (0);
}

int	get_must_eat_times(t_env *env, char **av)
{
	int	must_eat_times;

	must_eat_times = ft_atoi(av[5]);
	if (must_eat_times <= 0)
		return (-1);
	else
		env->must_eat_times = must_eat_times;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <tpouget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:49:42 by tpouget           #+#    #+#             */
/*   Updated: 2022/02/25 12:49:42 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <threads.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

#include "main.h"
#include "structs.h"

int	start_dinner(t_env *env)
{
	int	i;
	int	ret;

	i = 0;
	while (i < env->nb_philo)
	{
		ret = pthread_create(&env->philosophers[i].thread,
				NULL, &routine, &env->philosophers[i]);
		if (ret)
			return (10);
		i++;
	}
	return (0);
}

void	wait_end(t_env *env)
{
	int	i;
	int r;

	i = 0;
	while (i < env->nb_philo)
	{
		r = pthread_join(env->philosophers[i].thread, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	int		ret;
	t_env	*env;

	env = new_env();
	if (!env)
		return (1);
	ret = init_env(env, ac, av);
	if (!ret)
		ret = start_dinner(env);
	if (!ret)
		wait_end(env);
	free_env(env);
	return (ret);
}

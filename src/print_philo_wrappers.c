/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_philo_wrappers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <tpouget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:50:48 by tpouget           #+#    #+#             */
/*   Updated: 2022/02/25 12:50:48 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print_philo_wrappers.h"
#include "structs.h"
#include "defines.h"

void	print_philo_fork(unsigned long time, const t_philo *philo,
		t_env *env)
{
	if (env->quit == 0)
		print_philo(time, philo, FORK_STR, sizeof(FORK_STR) - 1);
}

void	print_philo_death(unsigned long time, const t_philo *philo, t_env *env)
{
	if (env->quit == 0)
		print_philo(time, philo, DIE_STR, sizeof(DIE_STR) - 1);
}

void	print_philo_eat(unsigned long time, const t_philo *philo, t_env *env)
{
	if (env->quit == 0)
	{
		print_philo_fork(time, philo, env);
		print_philo_fork(time, philo, env);
		print_philo(time, philo, EAT_STR, sizeof(EAT_STR) - 1);
	}
}

void	print_philo_sleep(unsigned long time, const t_philo *philo, t_env *env)
{
	if (env->quit == 0)
		print_philo(time, philo, SLEEP_STR, sizeof(SLEEP_STR) - 1);
}

void	print_philo_think(unsigned long time, const t_philo *philo, t_env *env)
{
	if (env->quit == 0)
		print_philo(time, philo, THINK_STR, sizeof(THINK_STR) - 1);
}


/*void	print_philo_own_fork(unsigned long time, const t_philo *philo,*/
/*        t_env *env)*/
/*{*/
/*    if (env->quit == 0)*/
/*        print_philo(time, philo, FORK1_STR, sizeof(FORK1_STR) - 1);*/
/*}*/

/*void	print_philo_borrowed_fork(unsigned long time, const t_philo *philo,*/
/*        t_env *env)*/
/*{*/
/*    if (env->quit == 0)*/
/*        print_philo(time, philo, FORK2_STR, sizeof(FORK2_STR) - 1);*/
/*}*/

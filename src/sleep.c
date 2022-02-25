/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <tpouget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:51:13 by tpouget           #+#    #+#             */
/*   Updated: 2022/02/25 12:51:13 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sleep.h"
#include "structs.h"
#include "defines.h"

int	sleeph(t_philo *philo, t_env *env)
{
	unsigned long	time;
	/*unsigned long	time_since_start;*/
	/*unsigned long	time_since_last_meal;*/
	/*unsigned long	since_last_meal_plus_sleep;*/

	if (get_time(&time) == ERROR)
		return (ERROR);
	/*time_since_start = time - philo->starting_time;*/
	print_philo_sleep(time, philo, env);
	/*time_since_last_meal = time - philo->last_meal_time;*/
	/*since_last_meal_plus_sleep = time_since_last_meal + (unsigned long)(env->time_to_sleep);*/
	/*if (since_last_meal_plus_sleep > (unsigned long)(env->time_to_die))*/
	/*    time_since_last_meal = env->time_to_die - time_since_last_meal;*/
	/*else*/
	/*    time_since_last_meal = env->time_to_sleep;*/
	/*usleep(time_since_last_meal * 1000);*/
	usleep_ms(env->time_to_sleep);
	return (DONE_SLEEPING);
	/*Donc si le temps écoulé depuis le dernier repas ajouté au temps de sommeil est supérieur au temps de la mort, tu fais dormir ton philo la diff entre le temps*/
	/*de mort et le temps écoulé depuis le dernier repas. Mindfuck*/
}

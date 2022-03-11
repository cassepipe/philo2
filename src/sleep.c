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
	unsigned long	time_to_sleep;

	if (get_time(&time) == ERROR)
		return (ERROR);
	if (philo->last_meal_time + env->time_to_sleep < philo->last_meal_time + env->time_to_die)
		time_to_sleep = env->time_to_die;
	else
		time_to_sleep = env->time_to_sleep;
	print_philo_sleep(time, philo, env);
	usleep_ms(time_to_sleep);
	return (DONE_SLEEPING);
	/*Donc si le temps écoulé depuis le dernier repas ajouté au temps de sommeil est supérieur au temps de la mort, tu fais dormir ton philo la diff entre le temps*/
	/*de mort et le temps écoulé depuis le dernier repas. Mindfuck*/
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <tpouget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 14:36:00 by tpouget           #+#    #+#             */
/*   Updated: 2022/02/25 14:36:00 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

#include <pthread.h>
#include <stdbool.h>

typedef pthread_mutex_t t_mutex;

typedef struct s_fork {
	t_mutex mutex;
	bool	status;
} t_fork;

typedef struct s_philo t_philo;

typedef struct s_env {
	t_philo *philosophers;
	t_fork	*forks;
	t_mutex quitlock;
	t_mutex	printlock;
	int	nb_philo;
	int quit;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	must_eat_times;
	unsigned long 	starting_time;
} t_env;

typedef struct s_philo {
	t_env	*env;
	t_fork	*own_fork;
	t_fork	*borrowed_fork;
	pthread_t	thread;
	unsigned long	last_meal_time;
	int		meals_left;
	int 	id;
	int		is_uneven;
	int		is_first;
	int		is_last;
} t_philo;

#endif /* STRUCTS_H */

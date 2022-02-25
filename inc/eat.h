#ifndef EAT_H
#define EAT_H

#include "structs.h"

void assign_forks(t_fork **fork1,t_fork **fork2,t_philo *philo);
int eat(t_philo *philo,t_env *env);
void put_down_both_forks(t_philo *philo);
void put_down_fork(t_fork *fork);
int take_fork(t_fork *fork);
int eat_cycle(t_philo *philo,t_env *env,t_fork *fork1,t_fork *fork2);
void usleep_ms(unsigned int time_in_ms);
void print_philo_eat(unsigned long time,const t_philo *philo,t_env *env);
int get_time(unsigned long *time);
int eat_action(t_philo *philo,t_env *env);

#endif /* EAT_H */

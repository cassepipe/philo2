#ifndef ROUTINE_H
#define ROUTINE_H

#include "structs.h"

int think(t_philo *philo,t_env *env);
int sleeph(t_philo *philo,t_env *env);
int eat(t_philo *philo,t_env *env);
int check_state(t_philo *philo,t_env *env);
void usleep_ms(unsigned int time_in_ms);
int get_time(unsigned long *time);
void *routine(void *arg);

#endif /* ROUTINE_H */

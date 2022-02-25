#ifndef CHECK_STATE_H
#define CHECK_STATE_H

#include "structs.h"
#include "structs.h"

void print_philo_death(unsigned long time,const t_philo *philo,t_env *env);
int get_time(unsigned long *time);
int check_state(t_philo *philo,t_env *env);

#endif /* CHECK_STATE_H */

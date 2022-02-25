#ifndef THINK_H
#define THINK_H

#include "structs.h"

void print_philo_think(unsigned long time,const t_philo *philo,t_env *env);
int get_time(unsigned long *time);
int think(t_philo *philo,t_env *env);

#endif /* THINK_H */

#ifndef FORKS_H
#define FORKS_H

#include <pthread.h>
#include "structs.h"

void put_down_both_forks(t_philo *philo);
void put_down_fork(t_fork *fork);
int lock(t_mutex *mutex);
int unlock(t_mutex *mutex);
int take_fork(t_fork *fork);
void assign_forks(t_fork **fork1,t_fork **fork2,t_philo *philo);

#endif /* FORKS_H */

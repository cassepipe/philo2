#ifndef SLEEP_H
#define SLEEP_H

#include "structs.h"

void usleep_ms(unsigned int time_in_ms);
void print_philo_sleep(unsigned long time,const t_philo *philo,t_env *env);
int get_time(unsigned long *time);
int sleeph(t_philo *philo,t_env *env);

#endif /* SLEEP_H */

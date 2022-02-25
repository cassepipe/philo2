#ifndef PRINT_PHILO_WRAPPERS_H
#define PRINT_PHILO_WRAPPERS_H

#include "structs.h"

void print_philo_borrowed_fork(unsigned long time,const t_philo *philo,t_env *env);
void print_philo_own_fork(unsigned long time,const t_philo *philo,t_env *env);
void print_philo_think(unsigned long time,const t_philo *philo,t_env *env);
void print_philo_sleep(unsigned long time,const t_philo *philo,t_env *env);
void print_philo_eat(unsigned long time,const t_philo *philo,t_env *env);
void print_philo(unsigned long time,const t_philo *philo,const char *action,int act_len);
void print_philo_death(unsigned long time,const t_philo *philo,t_env *env);

#endif /* PRINT_PHILO_WRAPPERS_H */

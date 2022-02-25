#ifndef INIT_H
#define INIT_H

#include "structs.h"

int get_must_eat_times(t_env *env,char **av);
int get_time_to_sleep(t_env *env,char **av);
int get_time_to_eat(t_env *env,char **av);
int get_time_to_die(t_env *env,char **av);
int get_nb_philo(t_env *env,char **av);
int init_env(t_env *env,int ac,char **av);
int init_philosophers(t_env *env,t_philo *philos);
int init_locks(t_env *env);
int init_forks(t_env *env);
int get_time(unsigned long *time);

#endif /* INIT_H */

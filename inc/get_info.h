#ifndef GET_INFO_H
#define GET_INFO_H

#include "structs.h"

int get_must_eat_times(t_env *env,char **av);
int get_time_to_sleep(t_env *env,char **av);
int get_time_to_eat(t_env *env,char **av);
int get_time_to_die(t_env *env,char **av);
int ft_atoi(const char *nptr);
int get_nb_philo(t_env *env,char **av);

#endif /* GET_INFO_H */

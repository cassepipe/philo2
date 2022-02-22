/* This file was automatically generated.  Do not edit! */
#undef INTERFACE
int start_dinner(t_env *env);
void *routine(void *arg);
int eat(t_philo *self,t_env *env);
void free_env(t_env *env);
int init_env(t_env *env,int ac,char **av);
int init_philosophers(t_env *env,t_philo *philos);
int init_locks(t_env *env);
int init_forks(t_env *env);
int get_must_eat_times(t_env *env,char **av);
int get_time_to_sleep(t_env *env,char **av);
int get_time_to_eat(t_env *env,char **av);
int get_time_to_die(t_env *env,char **av);
int get_nb_philo(t_env *env,char **av);
int ft_atoi(const char *nptr);
int ft_isdigit(int c);
void mark_fork_as_unlocked(t_fork *fork);
void mark_fork_as_locked(t_fork *fork);
int unlock_fork(t_fork *fork);
int unlock(t_mutex *mutex);
int lock_fork(t_fork *fork);
int lock(t_mutex *mutex);
t_env *new_env();
void *ft_memset(void *s,int c,size_t n);

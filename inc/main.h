#ifndef MAIN_H
#define MAIN_H

#include "structs.h"

void free_env(t_env *env);
int init_env(t_env *env,int ac,char **av);
t_env *new_env();
void wait_end(t_env *env);
void *routine(void *arg);
int start_dinner(t_env *env);

#endif /* MAIN_H */

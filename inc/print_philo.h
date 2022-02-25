#ifndef PRINT_PHILO_H
#define PRINT_PHILO_H

#include <stdlib.h>
#include "structs.h"

void *ft_memcpy(void *dest,const void *src,size_t n);
char *ulong_repr(long n,char *buffer,int *len);
int get_time(unsigned long *time);
void print_philo(unsigned long time,const t_philo *philo,const char *action,int act_len);

#endif /* PRINT_PHILO_H */

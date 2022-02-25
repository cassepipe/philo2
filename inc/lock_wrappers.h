#ifndef LOCK_WRAPPERS_H
#define LOCK_WRAPPERS_H

#include "structs.h"

int unlock_fork(t_fork *fork);
int unlock(t_mutex *mutex);
int lock_fork(t_fork *fork);
int lock(t_mutex *mutex);

#endif /* LOCK_WRAPPERS_H */

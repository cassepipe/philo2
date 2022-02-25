/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_wrappers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <tpouget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:49:20 by tpouget           #+#    #+#             */
/*   Updated: 2022/02/25 12:49:20 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lock_wrappers.h"
#include "structs.h"

int	lock(t_mutex *mutex)
{
	return (pthread_mutex_lock(mutex));
}

int	lock_fork(t_fork *fork)
{
	return (pthread_mutex_lock(&fork->mutex));
}

int	unlock(t_mutex *mutex)
{
	return (pthread_mutex_unlock(mutex));
}

int	unlock_fork(t_fork *fork)
{
	return (pthread_mutex_unlock(&fork->mutex));
}

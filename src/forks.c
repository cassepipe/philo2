/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <tpouget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:53:18 by tpouget           #+#    #+#             */
/*   Updated: 2022/02/25 12:53:18 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "forks.h"
#include "defines.h"
#include "structs.h"

void	assign_forks(t_fork **fork1, t_fork **fork2, t_philo *philo)
{
	*fork1 = philo->own_fork;
	*fork2 = philo->borrowed_fork;
	/*if (philo->id % 2)*/
	/*{*/
	/*    *fork1 = philo->borrowed_fork;*/
	/*    *fork1 = philo->own_fork;*/
	/*}*/
}

/*Can't the lock happen inside the if statement ?*/
int	take_fork(t_fork *fork)
{
	int	ret;

	ret = DID_NOT_TAKE;
	lock(&fork->mutex);
	if (fork->status == UNLOCKED)
	{
		fork->status = LOCKED;
		ret = DID_TAKE;
	}
	unlock(&fork->mutex);
	return (ret);
}

void	put_down_fork(t_fork *fork)
{
	lock(&fork->mutex);
	fork->status = UNLOCKED;
	unlock(&fork->mutex);
}

void	put_down_both_forks(t_philo *philo)
{
	put_down_fork(philo->own_fork);
	put_down_fork(philo->borrowed_fork);
}

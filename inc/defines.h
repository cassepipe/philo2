/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <tpouget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 13:17:35 by tpouget           #+#    #+#             */
/*   Updated: 2022/02/25 13:17:35 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
#define DEFINES_H

#define LOCKED true
#define UNLOCKED false

#define FORK_STR " has taken a fork\n"
#define FORK1_STR " has taken a fork (1/2)\n"
#define FORK2_STR " has taken a fork (2/2)\n"
#define DIE_STR " has died\n"
#define EAT_STR " is eating\n"
#define SLEEP_STR " is sleeping\n"
#define THINK_STR " is thinking\n"

#define NOERROR 0
#define ERROR	-1
#define	ALIVE	0
#define	DEAD	1
#define DONE_EATING 2
#define DID_NOT_EAT 3
#define DID_TAKE 4
#define DID_NOT_TAKE 5
#define DONE_THINKING 6
#define DONE_SLEEPING 7
#define USLEEP_SPLIT 10.0

#endif /* DEFINES_H */

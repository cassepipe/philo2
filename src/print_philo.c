/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <tpouget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:50:31 by tpouget           #+#    #+#             */
/*   Updated: 2022/02/25 12:50:31 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "print_philo.h"
#include "structs.h"

void	print_philo(unsigned long time, const t_philo *philo, const char *action, int act_len)
{
	char			buffer[256];
	int				len;

	len = 0;
	get_time(&time);
	time = time - philo->env->starting_time;
	ulong_repr(time, buffer, &len);
	ft_memcpy(buffer + len, "ms Philo ", sizeof("ms Philo ") - 1);
	len += sizeof("ms Philo ") - 1;
	ulong_repr(philo->id, buffer + len, &len);
	ft_memcpy(buffer + len, action, act_len);
	len += act_len;
	write(STDOUT_FILENO, buffer, len);
}

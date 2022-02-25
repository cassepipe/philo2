/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpouget <tpouget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 12:48:24 by tpouget           #+#    #+#             */
/*   Updated: 2022/02/25 12:48:24 by tpouget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "free_env.h"
#include "structs.h"

void free_env(t_env *env)
{
	free(env->forks);
	free(env->philosophers);
	free(env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:19:12 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/10 04:33:46 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	simulation(t_data *data)
{
	((void)data);
	return (true);
}

void	*routine(void *phcontext)
{
	((void)phcontext);
	return (NULL);
}

// if (philo->left_mutex == philo->right_mutex)
//	pick only one fork, else pick both forks, then my_usleep
//	it should just kill the lone philosopher

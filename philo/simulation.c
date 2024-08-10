/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:19:12 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/10 06:04:06 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	join_threads(t_philo *philos, t_data *data);

bool	start_sim(t_data *data)
{
	if (!init_threads(data->philos))
		return (false);
	while (true)
	{
		if (check_meals(data->philos, data))
			break ;
		if (check_death(data->philos))
		{
			pthread_mutex_lock(&data->print_mutex);
			printf("%lld %d died\n",
				my_gettime() - data->start_time, data->philos->id);
			pthread_mutex_unlock(&data->print_mutex);
			break ;
		}
	}
	join_threads(data->philos, data);
	return (true);
}

void	*routine(void *phcontext)
{
	((void)phcontext);
	return (NULL);
}

void	join_threads(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}
// if (philo->left_mutex == philo->right_mutex)
//	pick only one fork, else pick both forks, then my_usleep
//	it should just kill the lone philosopher

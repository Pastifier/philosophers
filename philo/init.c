/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 05:12:42 by ebinjama          #+#    #+#             */
/*   Updated: 2024/07/20 04:51:51y ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

bool	init_philo_attr(t_philo *const *philos, t_data *context, char *argv[],
			int i)
{
	t_eint	fetcher;

	(*philos)[i] = (t_philo){0};
	(*philos)[i].id = i + 1;
	(*philos)[i].context = context;
	fetcher = ft_atoi(argv[2]);
	if (fetcher.error || fetcher.value < 0)
		return (write_error("Time to die: "INVALID_VALUE), false);
	(*philos)[i].time_to_die = fetcher.value;
	fetcher = ft_atoi(argv[3]);
	if (fetcher.error || fetcher.value < 0)
		return (write_error("Time to eat: "INVALID_VALUE), false);
	(*philos)[i].time_to_eat = fetcher.value;
	fetcher = ft_atoi(argv[4]);
	if (fetcher.error || fetcher.value < 0)
		return (write_error("Time to sleep: "INVALID_VALUE), false);
	(*philos)[i].time_to_sleep = fetcher.value;
	return (true);
}

bool	init_threads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->context->philo_count)
	{
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]))
			return (write_error(THREAD_FAILED), false);
		i++;
	}
	return (true);
}

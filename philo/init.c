/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 05:12:42 by ebinjama          #+#    #+#             */
/*   Updated: 2024/07/13 05:28:00 by ebinjama         ###   ########.fr       */
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
		return (write_error(INVALID_VALUE), false);
	(*philos)[i].time_to_die = fetcher.value;
	fetcher = ft_atoi(argv[3]);
	if (fetcher.error || fetcher.value < 0)
		return (write_error(INVALID_VALUE), false);
	(*philos)[i].time_to_eat = fetcher.value;
	fetcher = ft_atoi(argv[4]);
	if (fetcher.error || fetcher.value < 0)
		return (write_error(INVALID_VALUE), false);
	(*philos)[i].time_to_sleep = fetcher.value;
	return (true);
}

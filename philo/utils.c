/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 05:51:39 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/14 12:43:34 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

t_ll	my_gettime(void)
{
	struct timeval	timeofday;

	if (gettimeofday(&timeofday, NULL) == -1)
		return (write_error(GETTIMEOFDAY_FAILED), -1);
	return ((timeofday.tv_sec * 1000) + (timeofday.tv_usec / 1000));
}

void	write_error(const char *msg)
{
	size_t	len;

	len = 0;
	while (msg[len])
		len++;
	write(2, msg, len);
	write(2, "\n", 1);
}

ssize_t	my_usleep(size_t time, t_philo *philo)
{
	size_t	start;

	start = my_gettime();
	while (my_gettime() - start < time)
	{
		if (check_death_status(philo))
			return (-1);
		usleep(250);
	}
	return (0);
}

void	print_philo_status(t_philo *philo, const char *msg)
{
	t_ll	timestamp;

	timestamp = my_gettime() - philo->context->start_time;
	pthread_mutex_lock(&philo->context->print_mutex);
	if (!check_death_status(philo))
		printf("%lld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->context->print_mutex);
}

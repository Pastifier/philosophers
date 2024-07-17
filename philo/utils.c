/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:40:53 by ebinjama          #+#    #+#             */
/*   Updated: 2024/07/18 02:17:20 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

size_t	my_gettime(void)
{
	struct timeval	timeofday;

	if (gettimeofday(&timeofday, NULL) == -1)
		return (/*log=GETTIMEOFDAYFAILED*/-1);
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

ssize_t	my_usleep(size_t time, t_data *context)
{
	size_t	start;
	size_t	curr;

	start = my_gettime();
	curr = start;
	while (curr - start < time)
	{
		usleep(100);
		curr = my_gettime();
		pthread_mutex_lock(&context->death_mutex);
		if (context->death_flag)
		{
			pthread_mutex_unlock(&context->death_mutex);
			return (-1);
		}
		pthread_mutex_unlock(&context->death_mutex);
	}
	return (curr);
}

void	print_philo_status(t_philo *philo, const char *msg)
{
	ssize_t	timestamp;

	pthread_mutex_lock(&philo->context->time_mutex);
	timestamp = my_gettime() - philo->context->start_time;
	pthread_mutex_unlock(&philo->context->time_mutex);
	if (timestamp == -1)
		return ;
	pthread_mutex_lock(&philo->context->print_mutex);
	printf("%zd %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->context->print_mutex);
}

bool	check_death(t_philo *philo)
{
	ssize_t	curr_time;

	//pthread_mutex_lock(&philo->context->time_mutex);
	curr_time = my_gettime();
	//pthread_mutex_unlock(&philo->context->time_mutex);
	if (curr_time == -1)
		return (true);
	if (curr_time - philo->last_eat > philo->time_to_die)
	{
		pthread_mutex_lock(&philo->context->print_mutex);
		printf("%zd %d %s\n", curr_time - philo->context->start_time, philo->id, MSG_DIED);
		pthread_mutex_unlock(&philo->context->print_mutex);
		return (true);
	}
	return (false);
}

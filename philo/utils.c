/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:40:53 by ebinjama          #+#    #+#             */
/*   Updated: 2024/07/21 12:47:50 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

t_ll	my_gettime(void)
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

ssize_t	my_usleep(size_t time, t_philo *philo)
{
	size_t	start;
	size_t	curr;

	start = my_gettime();
	curr = start;
	while (curr - start < time)
	{
		usleep(100);
		curr = my_gettime();
		// The fact that it's printing in the function is causing it to
		// print the death of each philosopher, when it should probably
		// only print the first death and terminate.
		if (check_death(philo))
			return (-1);
	}
	return (curr);
}

void	print_philo_status(t_philo *philo, const char *msg)
{
	t_ll	timestamp;

	pthread_mutex_lock(&philo->context->time_mutex);
	timestamp = my_gettime() - philo->context->start_time;
	pthread_mutex_unlock(&philo->context->time_mutex);
	if (timestamp == -1)
		return ;
	pthread_mutex_lock(&philo->context->print_mutex);
	printf("%lld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->context->print_mutex);
}

bool	check_death(t_philo *philo)
{
	t_ll	curr_time;

	//pthread_mutex_lock(&philo->context->time_mutex);
	curr_time = my_gettime();
	//pthread_mutex_unlock(&philo->context->time_mutex);
	if (curr_time == -1)
		return (false);
	if (curr_time - philo->last_eat > philo->time_to_die)
	{
		//pthread_mutex_lock(&philo->context->print_mutex);
		pthread_mutex_lock(&philo->context->death_mutex);
		philo->context->death_flag = philo->id;
		//printf("%lld %d %s\n", curr_time - philo->context->start_time,
		//		philo->id, MSG_DIED);
		//pthread_mutex_unlock(&philo->context->print_mutex);
		pthread_mutex_unlock(&philo->context->death_mutex);
		return (true);
	}
	return (false);
}

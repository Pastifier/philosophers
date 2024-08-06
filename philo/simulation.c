/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:06:16 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/07 00:15:50 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

static void philo_eat(t_philo *philo);

bool	start_sim(t_philo *philos, t_data *context)
{
	(void)context;
	if (!init_threads(philos))
		return (false);
	while (true)
	{
		if (check_death(philos))
			break;
	}
	join_threads(philos, context);
	return (true);
}

void	join_threads(t_philo *philos, t_data *context)
{
	int	i;

	i = 0;
	while (i < context->philo_count)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

void	*routine(void *phcontext)
{
	t_philo	*philo;

	philo = (t_philo *)phcontext;
	while (true && philo->eat_count != 0)
	{
		pthread_mutex_lock(&philo->context->death_mutex);
		if (philo->context->death_flag != -1)
		{
			if (philo->context->death_flag == philo->id)
			{
				pthread_mutex_unlock(&philo->context->death_mutex);
				pthread_mutex_lock(&philo->context->print_mutex);
				printf("%lld %d %s\n", my_gettime() - philo->context->start_time,
					   philo->id, MSG_DIED);
				pthread_mutex_unlock(&philo->context->print_mutex);
			}
			break;
		}
		pthread_mutex_unlock(&philo->context->death_mutex);
		philo_eat(philo);
		// philo_sleep(philo);
		// philo_think(philo);
	}
	return (NULL);
}

static void philo_eat(t_philo *philo)
{
	if (philo->eat_count != -1 && philo->eat_count == 0)
		return ;
	if (philo->id % 2)
		usleep(100);
	pthread_mutex_lock(&philo->left_mutex);
	printf("Fork address: %p\n", (void*)&philo->left_mutex);
	print_philo_status(philo, MSG_FORK);
	if (philo->right_mutex)
	{
		pthread_mutex_lock(philo->right_mutex);
		printf("Fork address: %p\n", (void*)philo->right_mutex);
		print_philo_status(philo, MSG_FORK);
		pthread_mutex_lock(&philo->context->time_mutex);
		philo->last_eat = my_gettime();
		pthread_mutex_unlock(&philo->context->time_mutex);
		philo->eat_count--;
		print_philo_status(philo, MSG_EATING);
		my_usleep(philo->time_to_eat, philo);
		pthread_mutex_unlock(philo->right_mutex);
		pthread_mutex_unlock(&philo->left_mutex);
	}
	else
	{
		my_usleep(philo->time_to_die, philo);
		pthread_mutex_unlock(&philo->left_mutex);
	}
	check_death(philo);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:06:16 by ebinjama          #+#    #+#             */
/*   Updated: 2024/07/18 02:15:45 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static void philo_eat(t_philo *philo);

int	start_sim(t_data *context, t_philo *philos)
{
	// pthread_t		*threads;
	// pthread_mutex_t	*forks;
	// if (init_threads())
	//	return (/*log=THREAD_FAILED*/EXIT_FAILURE);
	(void)philos; (void)context;
	return (1);
}

void	routine(t_philo *philo)
{
	while (true)
	{
		pthread_mutex_lock(&philo->context->death_mutex);
		if (philo->context->death_flag)
		{
			pthread_mutex_unlock(&philo->context->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->context->death_mutex);
		philo_eat(philo);
	}
}

static void philo_eat(t_philo *philo)
{
	if (philo->id % 2)
		usleep(100);
	pthread_mutex_lock(&philo->left_mutex);
	print_philo_status(philo, MSG_FORK);
	if (philo->right_mutex)
	{
		pthread_mutex_lock(philo->right_mutex);
		print_philo_status(philo, MSG_FORK);
		philo->last_eat = my_gettime();
		philo->eat_count++;
		print_philo_status(philo, MSG_EATING);
		my_usleep(philo->time_to_eat, philo->context);
		pthread_mutex_unlock(philo->right_mutex);
		pthread_mutex_unlock(&philo->left_mutex);
	}
	else
		pthread_mutex_unlock(&philo->left_mutex);
}

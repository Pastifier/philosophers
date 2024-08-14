/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:19:12 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/14 14:02:00 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

void	join_threads(t_philo *philos, t_data *data);
void	fork_alternation(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep_and_think(t_philo *philo);

void	*routine(void *phcontext)
{
	t_philo	*philo;

	philo = (t_philo *)phcontext;
	if (philo->context->philo_count == 1)
	{
		print_philo_status(philo, MSG_FORK);
		my_usleep(philo->time_to_die, philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		my_usleep(50, philo);
	while (!check_death_status(philo))
	{
		philo_eat(philo);
		philo_sleep_and_think(philo);
	}
	return (NULL);
}

void	philo_eat(t_philo *philo)
{
	fork_alternation(philo);
	pthread_mutex_lock(&philo->context->meal_mutex);
	philo->last_eat = my_gettime();
	philo->is_eating = true;
	philo->eat_count++;
	pthread_mutex_unlock(&philo->context->meal_mutex);
	print_philo_status(philo, "is eating");
	philo->right_fork->is_taken = true;
	philo->left_fork->is_taken = true;
	my_usleep(philo->time_to_eat, philo);
	pthread_mutex_lock(&philo->context->meal_mutex);
	philo->is_eating = false;
	pthread_mutex_unlock(&philo->context->meal_mutex);
	philo->right_fork->is_taken = false;
	philo->left_fork->is_taken = false;
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

void	philo_sleep_and_think(t_philo *philo)
{
	print_philo_status(philo, "is sleeping");
	my_usleep(philo->time_to_sleep, philo);
	print_philo_status(philo, "is thinking");
}

bool	check_death_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->context->death_mutex);
	if (philo->context->death_flag)
	{
		pthread_mutex_unlock(&philo->context->death_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->context->death_mutex);
	return (false);
}

void	fork_alternation(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		print_philo_status(philo, MSG_FORK);
		pthread_mutex_lock(&philo->right_fork->mutex);
		print_philo_status(philo, MSG_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		print_philo_status(philo, MSG_FORK);
		pthread_mutex_lock(&philo->left_fork->mutex);
		print_philo_status(philo, MSG_FORK);
	}
}

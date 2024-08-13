/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:19:12 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/13 05:45:23 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

void	join_threads(t_philo *philos, t_data *data);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);

bool	start_sim(t_data *data)
{
	bool	stop;

	if (!init_threads(data->philos))
		return (false);
	stop = false;
	while (true)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (check_death(data->philos) || data->done_eating)
		{
			pthread_mutex_unlock(&data->meal_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->meal_mutex);
		//pthread_mutex_lock(&data->meal_mutex);
		//if (data->done_eating)
		//{
		//	pthread_mutex_lock(&data->print_mutex);
		//	printf("All philosophers have eaten enough\n");
		//	pthread_mutex_unlock(&data->print_mutex);
		//	pthread_mutex_unlock(&data->meal_mutex);
		//	break ;
		//}
		//pthread_mutex_unlock(&data->meal_mutex);
	}
	join_threads(data->philos, data);
	return (true);
}

void	*routine(void *phcontext)
{
	t_philo	*philo;

	philo = (t_philo *)phcontext;
	if (philo->id % 2)
		usleep(100);
	//while (!check_death_status((t_philo *)phcontext)
	//	&& !check_meals_((t_philo *)phcontext))
	while (true)
	{
		check_death_status((t_philo *)phcontext);
		pthread_mutex_lock(&philo->context->death_mutex);
		if (philo->context->death_flag != -1)
		{
			pthread_mutex_unlock(&philo->context->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->context->death_mutex);
		if (/*check_death_status((t_philo *)phcontext)
			|| */check_meals_((t_philo *)phcontext))
			break ;
		philo_eat((t_philo *)phcontext);
		philo_sleep((t_philo *)phcontext);
	}
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

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	philo->left_fork->is_taken = true;
	print_philo_status(philo, "has taken a fork");
	if (philo->left_fork != philo->right_fork)
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		philo->right_fork->is_taken = true;
		print_philo_status(philo, "has taken a fork");
		print_philo_status(philo, "is eating");
		pthread_mutex_lock(&philo->context->meal_mutex);
		if (philo->eat_count != -1 && philo->eat_count > 0)
			philo->eat_count--;
		philo->last_eat = my_gettime();
		my_usleep(philo->time_to_eat, philo);
		pthread_mutex_unlock(&philo->context->meal_mutex);
		philo->right_fork->is_taken = false;
		pthread_mutex_unlock(&philo->right_fork->mutex);
	}
	else
		my_usleep(philo->time_to_die, philo);
	philo->left_fork->is_taken = false;
	pthread_mutex_unlock(&philo->left_fork->mutex);
}

void	philo_sleep(t_philo *philo)
{
	print_philo_status(philo, "is sleeping");
	my_usleep(philo->time_to_sleep, philo);
	print_philo_status(philo, "is thinking");
}

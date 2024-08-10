/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arbitration.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:19:12 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/10 11:27:38 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

void	join_threads(t_philo *philos, t_data *data);
void	philo_eat(t_philo *philo);

bool	start_sim(t_data *data)
{
	if (!init_threads(data->philos))
		return (false);
	while (true)
	{
		usleep(1);
		if (check_death(data->philos) || check_meals(data->philos, data))
			break ;
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
	while (!check_death(philo))
	{
		philo_eat(philo);
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
// if (philo->left_mutex == philo->right_mutex)
//	pick only one fork, else pick both forks, then my_usleep
//	it should just kill the lone philosopher

void	philo_eat(t_philo *philo)
{
	int		right_fork_idx;

	right_fork_idx = (philo->id + 1) % philo->context->philo_count;
	pthread_mutex_lock(philo->left_mutex);
	philo->context->forks[philo->id].is_taken = true;
	print_philo_status(philo, "has taken a fork");
	if (philo->context->philo_count == 1)
	{
		my_usleep(philo->time_to_die, philo);
		philo->context->forks[philo->id].is_taken = false;
		pthread_mutex_unlock(philo->left_mutex);
		return ;
	}
	pthread_mutex_lock(philo->right_mutex);
	philo->context->forks[right_fork_idx].is_taken = true;
	philo->last_eat = my_gettime();
	pthread_mutex_lock(&philo->context->meal_mutex);
	philo->eat_count--;
	pthread_mutex_unlock(&philo->context->meal_mutex);
	print_philo_status(philo, "is eating");
	my_usleep(philo->time_to_eat, philo);
	philo->context->forks[philo->id].is_taken = false;
	philo->context->forks[right_fork_idx].is_taken = false;
	pthread_mutex_unlock(philo->left_mutex);
	pthread_mutex_unlock(philo->right_mutex);
}

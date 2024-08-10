/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:19:12 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/10 13:05:04 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

void	join_threads(t_philo *philos, t_data *data);
void	philo_eat(t_philo *philo);

bool	start_sim(t_data *data)
{
	if (!init_threads(data->philos))
		return (false);
	while (true)
	{
		if (check_death(data->philos))
		{
			pthread_mutex_lock(&data->print_mutex);
			printf("%lld %d died\n",
				my_gettime() - data->start_time, data->philos->id);
			pthread_mutex_unlock(&data->print_mutex);
			break ;
		}
	}
	join_threads(data->philos, data);
	return (true);
}

void	*routine(void *phcontext)
{
	while (!check_death((t_philo *)phcontext))
	{
		philo_eat((t_philo *)phcontext);
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
	if (philo->id % 2 == 0)
		usleep(200);
	pthread_mutex_lock(philo->left_mutex);
	print_philo_status(philo, "has taken a fork");
	if (philo->context->philo_count == 1)
	{
		my_usleep(philo->time_to_die, philo);
		pthread_mutex_unlock(philo->left_mutex);
		return ;
	}
	pthread_mutex_lock(philo->right_mutex);
	print_philo_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->context->meal_mutex);
	philo->last_eat = my_gettime();
	philo->eat_count--;
	pthread_mutex_unlock(&philo->context->meal_mutex);
	print_philo_status(philo, "is eating");
	my_usleep(philo->time_to_eat, philo);
	philo->context->forks[philo->id - 1].is_taken = false;
	pthread_mutex_unlock(philo->left_mutex);
	pthread_mutex_unlock(philo->right_mutex);
}

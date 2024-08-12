/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:19:12 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/13 02:31:04 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

void	join_threads(t_philo *philos, t_data *data);
void	philo_eat(t_philo *philo);
bool	check_death(t_philo *philos);
void	philo_sleep(t_philo *philo);

bool	start_sim(t_data *data)
{
	if (!init_threads(data->philos))
		return (false);
	while (true)
	{
		//if (check_death(data->philos))
		//	break ;
		pthread_mutex_lock(&data->death_mutex);
		if (data->death_flag != -1)
		{
			pthread_mutex_lock(&data->print_mutex);
			printf("%lld %lld died\n",
				my_gettime() - data->start_time, data->death_flag);
			pthread_mutex_unlock(&data->print_mutex);
			pthread_mutex_unlock(&data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->death_mutex);
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
	while (!check_death_status((t_philo *)phcontext))
	{
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
// if (philo->left_mutex == philo->right_mutex)
//	pick only one fork, else pick both forks, then my_usleep
//	it should just kill the lone philosopher

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
		philo->last_eat = my_gettime();
		if (philo->eat_count != -1 && philo->eat_count > 0)
			philo->eat_count--;
		pthread_mutex_unlock(&philo->context->meal_mutex);
		my_usleep(philo->time_to_eat, philo);
		philo->right_fork->is_taken = false;
		pthread_mutex_unlock(&philo->right_fork->mutex);
	}
	else
		my_usleep(philo->time_to_die, philo);
	philo->left_fork->is_taken = false;
	pthread_mutex_unlock(&philo->left_fork->mutex);
}

bool	check_death(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->context->philo_count)
	{
		pthread_mutex_lock(&philos[i].context->death_mutex);
		if (philos[i].time_to_die <= my_gettime() - philos[i].last_eat)
		{
			printf("%lld %d died\n",
				my_gettime() - philos[i].context->start_time, philos[i].id);
			philos->context->death_flag = philos[i].id;
			pthread_mutex_unlock(&philos[i].context->death_mutex);
			return (true);
		}
		pthread_mutex_unlock(&philos[i].context->death_mutex);
		i++;
	}
	return (false);
}

void	philo_sleep(t_philo *philo)
{
	print_philo_status(philo, "is sleeping");
	my_usleep(philo->time_to_sleep, philo);
	print_philo_status(philo, "is thinking");
}

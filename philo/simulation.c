/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 00:19:12 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/13 03:49:32 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

void	join_threads(t_philo *philos, t_data *data);
void	philo_eat(t_philo *philo);
bool	check_death(t_philo *philos);
bool	check_meals_(t_philo *philo);
void	philo_sleep(t_philo *philo);

bool	start_sim(t_data *data)
{
	if (!init_threads(data->philos))
		return (false);
	while (true)
	{
		//pthread_mutex_lock(&data->death_mutex);
		//if (data->death_flag != -1 && data->death_flag != -2)
		//{
		//	pthread_mutex_lock(&data->print_mutex);
		//	printf("%lld %lld died\n",
		//		my_gettime() - data->start_time, data->death_flag);
		//	pthread_mutex_unlock(&data->print_mutex);
		//	pthread_mutex_unlock(&data->death_mutex);
		//	break ;
		//}
		//pthread_mutex_unlock(&data->death_mutex);
		if (check_death(data->philos))
			break ;
		pthread_mutex_lock(&data->meal_mutex);
		if (data->done_eating)
		{
			pthread_mutex_lock(&data->print_mutex);
			printf("All philosophers have eaten enough\n");
			pthread_mutex_unlock(&data->print_mutex);
			pthread_mutex_unlock(&data->meal_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->meal_mutex);
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
	while (!check_death_status((t_philo *)phcontext)
			&& !check_meals_((t_philo *)phcontext))
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

bool	check_death(t_philo *philos)
{
	t_data	*data;

	data = philos->context;
	pthread_mutex_lock(&philos->context->death_mutex);
	if (philos->context->death_flag != -2
		&& philos->context->death_flag != -1)
	{
			pthread_mutex_lock(&data->print_mutex);
			printf("%lld %lld died\n",
				my_gettime() - data->start_time, data->death_flag);
			pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&philos->context->death_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philos->context->death_mutex);
	return (false);
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

bool	check_meals_(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->context->meal_mutex);
	if (philo->eat_count == -1)
	{
		pthread_mutex_unlock(&philo->context->meal_mutex);
		return (false);
	}
	i = 0;
	while (i < philo->context->philo_count)
	{
		if (philo->context->philos[i].eat_count != -1
			&& philo->context->philos[i].eat_count > 0)
		{
			pthread_mutex_unlock(&philo->context->meal_mutex);
			return (false);
		}
		i++;
	}
	philo->context->done_eating = true;
	pthread_mutex_lock(&philo->context->death_mutex);
	philo->context->death_flag = -2;
	pthread_mutex_unlock(&philo->context->death_mutex);
	pthread_mutex_unlock(&philo->context->meal_mutex);
	return (true);
}

//bool	check_death(t_philo *philos)
//{
//	int	i;

//	i = 0;
//	while (i < philos->context->philo_count)
//	{
//		pthread_mutex_lock(&philos[i].context->death_mutex);
//		if (philos[i].context->death_flag != -2
//			&& philos[i].time_to_die <= my_gettime() - philos[i].last_eat)
//		{
//			printf("%lld %d died\n",
//				my_gettime() - philos[i].context->start_time, philos[i].id);
//			philos->context->death_flag = philos[i].id;
//			pthread_mutex_unlock(&philos[i].context->death_mutex);
//			return (true);
//		}
//		pthread_mutex_unlock(&philos[i].context->death_mutex);
//		i++;
//	}
//	return (false);
//}

void	philo_sleep(t_philo *philo)
{
	print_philo_status(philo, "is sleeping");
	my_usleep(philo->time_to_sleep, philo);
	print_philo_status(philo, "is thinking");
}

bool	check_meals(t_philo *philos, t_data *phcontext)
{
	(void)philos;
	pthread_mutex_lock(&phcontext->meal_mutex);
	if (phcontext->feast_count == phcontext->philo_count)
	{
		phcontext->done_eating = true;
		pthread_mutex_unlock(&phcontext->meal_mutex);
		pthread_mutex_lock(&phcontext->death_mutex);
		pthread_mutex_lock(&phcontext->print_mutex);
		phcontext->death_flag = -2;
		pthread_mutex_unlock(&phcontext->print_mutex);
		pthread_mutex_unlock(&phcontext->death_mutex);
		return (true);
	}
	pthread_mutex_unlock(&phcontext->meal_mutex);
	return (true);
}

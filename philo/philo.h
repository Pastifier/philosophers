/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebinjama <ebinjama@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 05:52:53 by ebinjama          #+#    #+#             */
/*   Updated: 2024/08/14 12:19:53 by ebinjama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <sys/time.h>
# include <sys/types.h> // For ssize_t
# include <stddef.h>
# include <pthread.h>

# define STATE_ONLY 1
# define FORKS_ONLY 2
# define ALL_MUTEXES 3

/* --- ERROR MESSAGES ---*/

# define INVALID_NUMBER "Invalid number of philosophers"
# define INVALID_VALUE "Invalid value"
# define WRONG "Usage:\n\t./philo number_of_philosophers time_to_die time_to_"
# define _USAGE "eat time_to_sleep [number_of_times_each_philosopher_must_eat]"
# define MUTEX_INIT_FAILED "Mutex initialization failed"
# define MALLOC_FAILED "Malloc failed"
# define GETTIMEOFDAY_FAILED "Gettimeofday failed"
# define THREAD_FAILED "Thread creation failed"

void	write_error(const char *msg);

/* --- LOG MESSAGES ---*/

# define MSG_EATING "is eating"
# define MSG_FORK "has taken a fork"
# define MSG_THINKING "is thinking"
# define MSG_SLEEPING "is sleeping"
# define MSG_DIED "died"

typedef unsigned long long	t_ull;
typedef long long			t_ll;
typedef struct s_philo		t_philo;

typedef struct s_error_int
{
	int		value;
	int		operations;
	bool	error;
}	t_eint;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	bool			is_taken;
}	t_fork;

typedef struct s_data
{
	int					philo_count;
	int					meal_amount;
	t_ll				start_time;
	bool				death_flag;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		meal_mutex;
	bool				done_eating;
	t_philo				*philos;
	t_fork				*forks;
}	t_data;

typedef struct s_philo
{
	int				id;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_data			*context;
	int				eat_count;
	bool			is_eating;
	t_ll			last_eat;
	t_ll			time_to_die;
	t_ll			time_to_eat;
	t_ll			time_to_sleep;
	pthread_t		thread;
}	t_philo;

/*---- UTILITY -- FUNCTIONS ---*/

t_ll	my_gettime(void);
t_eint	ft_atoi(const char *str);
ssize_t	my_usleep(size_t time, t_philo *philo);
void	print_philo_status(t_philo *philo, const char *msg);
bool	check_death_status(t_philo *philo);

/*---- INITIALIZATION FUNCTIONS ----*/
bool	init_data(t_data *context, int argc, char *argv[]);
bool	init_threads(t_philo *philos);

/* --- SIMULATION ---*/

bool	start_sim(t_data *context);
void	join_threads(t_philo *philos, t_data *context);
void	*routine(void *phcontext);

/* --- ARBITER FUCNTIONS ---*/

bool	check_death(t_philo *philos);
bool	check_meals(t_philo *philos);

/*--- DESTROY FUNCTIONS ---*/

void	destroy(t_data *data, t_philo *philos);
void	mutex_massacre(t_data *data, int mutex_count, u_int8_t bit_flag);

#endif // !PHILO_H

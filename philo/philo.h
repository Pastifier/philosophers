#ifndef PHILO_H
# define PHILO_H

#include <stdbool.h>
#include <sys/time.h>
#include <sys/types.h> // For ssize_t
#include <stddef.h>
#include <pthread.h>

/* --- ERROR MESSAGES ---*/

#define INVALID_NUMBER "Invalid number of philosophers"
#define WRONG "Usage: ./philo number_of_philosophers time_to_die time_to_eat "
#define _USAGE "time_to_sleep [number_of_times_each_philosopher_must_eat]"
#define MUTEX_INIT_FAILED "Mutex initialization failed"
#define MALLOC_FAILED "Malloc failed"
#define GETTIMEOFDAY_FAILED "Gettimeofday failed"

void	write_error(const char *msg);

typedef unsigned long long	t_ull;

typedef struct s_error_int
{
	int		value;
	int		operations;
	bool	error;
}	t_eint;


typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				last_user_id;
	bool			is_taken;
}	t_fork;

typedef struct s_data
{
	int				philo_count;
	ssize_t			curr_timestamp;
	ssize_t			start_time;
	bool			death_flag;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	time_mutex;
	t_fork			*forks;
	
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	left_mutex;
	pthread_mutex_t	*right_mutex;
	t_data			*context;
	int				eat_count;
	size_t			last_eat;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
}	t_philo;

/*---- UTILITY -- FUNCTIONS ---*/

size_t	my_gettime(void);
t_eint	ft_atoi(const char *str);

#endif // !PHILO_H

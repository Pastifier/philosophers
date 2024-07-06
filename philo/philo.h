#ifndef PHILO_H
# define PHILO_H

#include <stdbool.h>
#include <sys/time.h>


typedef unsigned long long	t_ull;

typedef struct s_error_int
{
	int		value;
	int		operations;
	bool	error;
}	t_eint;

typedef struct s_philo
{
	int	id;
	int	left_fork;
	int	right_fork;
	int	eat_count;
	int	last_eat;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
}	t_philo;

typedef struct s_data
{
	int				philo_count;
	struct timeval	start;
	bool			dead;
}	t_data;

t_eint	ft_atoi(const char *str);

#endif // !PHILO_H

#ifndef PHILO_H
# define PHILO_H

#include <stdbool.h>
#include <sys/time.h>
#include <stddef.h>


typedef unsigned long long	t_ull;

typedef struct s_error_int
{
	int		value;
	int		operations;
	bool	error;
}	t_eint;

typedef struct s_philo
{
	int					id;
	bool				left_fork;
	bool				*right_fork;
	int					eat_count;
	struct timeval		last_eat;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
}	t_philo;

typedef struct s_data
{
	int		philo_count;
	size_t	start;
	bool	dead;
}	t_data;

/*---- UTILITY -- FUNCTIONS ---*/

t_eint	ft_atoi(const char *str);
size_t	my_gettime(void);

#endif // !PHILO_H

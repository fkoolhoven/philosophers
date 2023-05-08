/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:32:48 by felicia           #+#    #+#             */
/*   Updated: 2023/05/08 11:58:26 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h> 
# include <unistd.h> 
# include <stdbool.h>

// =====FORK AVAILABILITY=======================================================
# define AVAILABLE 0
# define UNAVAILABLE 1

// =====PHILOSOPHER STATES======================================================
# define FORK 0
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DIED 4

// =====STRUCTS=================================================================

typedef struct s_data
{
	int				nbr_of_philosophers;
	int				nbr_of_forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				**forks;
	pthread_mutex_t	**mutexes;
}	t_data;

typedef struct s_philo
{
	pthread_t	thread;
	int			philo_nbr;
	t_data		*data;
}	t_philo;

// =====FUNCTIONS===============================================================

void	validate_input(int argc);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_error_message(char *message);
t_data	*store_data_in_struct(int argc, char **argv);
void	*routine(void *phil);

#endif
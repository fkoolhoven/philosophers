/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:32:48 by felicia           #+#    #+#             */
/*   Updated: 2023/05/02 17:50:20 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h> 
# include <unistd.h> 

// =====STRUCTS=================================================================

typedef struct s_data
{
	int	nbr_of_philosophers;
	int	nbr_of_forks;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}	t_data;

typedef struct s_philo
{
	pthread_t	threads;
}	t_philo;


// =====FUNCTIONS===============================================================

void	validate_input(int argc);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_error_message(char *message);
void	*routine(void *phil);

#endif
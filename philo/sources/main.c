/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:31:13 by felicia           #+#    #+#             */
/*   Updated: 2023/05/01 17:00:28 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// number_of_philosophers time_to_die time_to_eat
// time_to_sleep

t_data	*store_data_in_struct(char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
	{
		printf("Error message malloc\n");
		exit (EXIT_FAILURE);
	}
	data->nbr_of_philosophers = ft_atoi(argv[1]);
	data->nbr_of_forks = data->nbr_of_philosophers;
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	return (data);
}

void	*routine()
{
	struct timeval current_time;
	struct timeval new_time;

	// protect with mutex?
	gettimeofday(&current_time, NULL);
	printf("old miliseconds = %d\n", current_time.tv_usec);
	usleep(1000000);
	gettimeofday(&new_time, NULL);
	printf("new miliseconds = %d time passed = %d\n", new_time.tv_usec, new_time.tv_usec - current_time.tv_usec);
	return (NULL);
}

void	join_philosopher_threads(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philosophers)
	{
		pthread_join(philo[i].threads, NULL);
		i++;
	}
}

t_philo	*create_philosopher_threads(t_data *data)
{
	int		i;
	t_philo	*philo;

	philo = malloc(data->nbr_of_philosophers * sizeof(pthread_t));
	if (philo == NULL)
	{
		printf("Error message malloc\n");
		exit (EXIT_FAILURE);
	}
	i = 0;
	while (i < data->nbr_of_philosophers)
	{
		pthread_create(&philo[i].threads, NULL, &routine, NULL);
		i++;
	}
	return (philo);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philo;

	validate_input(argc);
	data = store_data_in_struct(argv);
	philo = create_philosopher_threads(data);
	join_philosopher_threads(data, philo);
	// free mem
	return (EXIT_SUCCESS);
}

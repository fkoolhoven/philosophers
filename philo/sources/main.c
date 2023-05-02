/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:31:13 by felicia           #+#    #+#             */
/*   Updated: 2023/05/02 18:09:03 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// number_of_philosophers time_to_die time_to_eat
// time_to_sleep

t_data	*store_data_in_struct(int argc, char **argv)
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
	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	return (data);
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
	int		*phil;
	t_philo	*philo;

	philo = malloc(data->nbr_of_philosophers * sizeof(t_philo));
	if (philo == NULL)
	{
		printf("Error message malloc\n");
		exit (EXIT_FAILURE);
	}
	i = 0;
	while (i < data->nbr_of_philosophers)
	{
		phil = malloc(sizeof(int *));
		*phil = i;
		pthread_create(&philo[i].threads, NULL, &routine, phil);
		i++;
	}
	return (philo);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*philo;

	validate_input(argc);
	data = store_data_in_struct(argc, argv);
	pthread_mutex_init();
	pthread_mutex_destroy();
	philo = create_philosopher_threads(data);
	join_philosopher_threads(data, philo);
	// free mem
	return (EXIT_SUCCESS);
}

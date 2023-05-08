/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:31:13 by felicia           #+#    #+#             */
/*   Updated: 2023/05/08 12:51:05 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// number_of_philosophers time_to_die time_to_eat
// time_to_sleep



void	join_philosopher_threads(t_data *data, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < data->nbr_of_philosophers)
	{
		pthread_join((*philo[i]).thread, NULL);
		i++;
	}
}

t_philo	**create_philosopher_threads(t_data *data)
{
	int		i;
	t_philo	**philo;

	philo = malloc(data->nbr_of_philosophers * sizeof(t_philo *));
	if (philo == NULL)
	{
		// handle error
		exit (EXIT_FAILURE);
	}
	i = 0;
	while (i < data->nbr_of_philosophers)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (philo[i] == NULL)
		{
			// handle error
			exit (EXIT_FAILURE);
		}
		philo[i]->philo_nbr = i;
		philo[i]->data = data;
		pthread_create(&(*philo[i]).thread, NULL, &routine, philo[i]);
		i++;
	}
	return (philo);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	**philo;

	validate_input(argc);
	data = store_data_in_struct(argc, argv);
	philo = create_philosopher_threads(data);
	join_philosopher_threads(data, philo);
	// destroy mutexes pthread_mutex_destroy(&data->mutex);
	// free mem
	return (EXIT_SUCCESS);
}

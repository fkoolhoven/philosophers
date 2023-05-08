/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:31:13 by felicia           #+#    #+#             */
/*   Updated: 2023/05/08 15:54:28 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
		error_message_exit("Malloc fail");
	i = 0;
	while (i < data->nbr_of_philosophers)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (philo[i] == NULL)
			error_message_exit("Malloc fail");
		philo[i]->philo_nbr = i + 1;
		philo[i]->data = data;
		philo[i]->state = THINKING;
		philo[i]->meals_had = 0;
		philo[i]->right_fork = philo[i]->philo_nbr - 1;
		if (philo[i]->philo_nbr != data->nbr_of_philosophers)
			philo[i]->left_fork = philo[i]->philo_nbr;
		else
			philo[i]->left_fork = 0;
		pthread_create(&(*philo[i]).thread, NULL, &dining, philo[i]);
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

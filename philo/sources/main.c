/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:31:13 by felicia           #+#    #+#             */
/*   Updated: 2023/06/20 15:28:15 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	free_mem_and_return_failure(t_philo **philo, t_data *data)
{
	if (!philo && !data->fork_mutexes)
		free(data);
	else if (!philo)
		free_memory(NULL, data);
	else if (data->initialization_failed)
	{
		join_philosopher_threads(philo, data);
		free_memory(philo, data);
	}
	return (EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	**philo;

	if (argc != 5 && argc != 6)
	{
		print_input_error_message("incorrect number of arguments");
		return (EXIT_FAILURE);
	}
	data = store_arguments_in_data_struct(argc, argv);
	if (data == NULL)
		return (EXIT_FAILURE);
	if (!input_validation(data))
		return (free_mem_and_return_failure(NULL, data));
	if (!initialize_mutexes_in_data_struct(data))
		return (free_mem_and_return_failure(NULL, data));
	philo = initialize_philosopher_threads(data);
	if (data->initialization_failed)
		return (free_mem_and_return_failure(philo, data));
	let_dinner_start(data);
	monitor_dining(philo, data);
	join_philosopher_threads(philo, data);
	free_memory(philo, data);
	return (EXIT_SUCCESS);
}

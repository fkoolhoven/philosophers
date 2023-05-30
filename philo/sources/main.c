/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:31:13 by felicia           #+#    #+#             */
/*   Updated: 2023/05/30 17:34:58 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_leaks(void)
{
	system("leaks -q philo");
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	**philo;

	atexit(check_leaks);
	if (argc != 5 && argc != 6)
	{
		print_input_error_message("incorrect number of arguments");
		return (EXIT_FAILURE);
	}
	data = store_arguments_in_data_struct(argc, argv);
	if (data == NULL)
		return (EXIT_FAILURE);
	if (!input_validation(data))
	{
		free(data);
		return (EXIT_FAILURE);
	}
	if (initialize_mutexes_in_data_struct(data) == NULL)
	{
		free_memory(NULL, data);
		return (EXIT_FAILURE);
	}
	philo = initialize_philosopher_threads(data);
	if (data->initialization_failed)
	{
		join_philosopher_threads(philo, data);
		free_memory(philo, data);
		return (EXIT_FAILURE);
	}
	let_dinner_start(data);
	monitor_dining(philo, data);
	join_philosopher_threads(philo, data);
	free_memory(philo, data);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:31:13 by felicia           #+#    #+#             */
/*   Updated: 2023/05/19 14:04:27 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_leaks()
{
	system("leaks -q philo");
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	**philo;

	atexit(check_leaks);
	if (argc != 5 && argc != 6)
		print_input_error_message_and_exit("incorrect number of arguments");
	data = store_arguments_in_data_struct(argc, argv);
	input_validation(data);
	initialize_mutexes(data);
	philo = initialize_philosopher_threads(data);
	monitor_dining(philo, data);
	join_philosopher_threads(philo, data);
	free_memory(philo, data);
	return (EXIT_SUCCESS);
}

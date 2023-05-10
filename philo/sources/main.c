/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:31:13 by felicia           #+#    #+#             */
/*   Updated: 2023/05/10 12:10:30 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	**philos;

	validate_input(argc);
	data = initialize_data_struct(argc, argv);
	philos = initialize_philosopher_threads(data);
	monitor(philos, data);
	join_philosopher_threads(data, philos);
	// destroy mutexes pthread_mutex_destroy(&data->mutex);
	// free mem
	return (EXIT_SUCCESS);
}

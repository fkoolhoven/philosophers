/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:31:13 by felicia           #+#    #+#             */
/*   Updated: 2023/05/18 16:53:59 by fkoolhov         ###   ########.fr       */
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
	validate_input(argc);
	data = initialize_data_struct(argc, argv);
	philo = initialize_philosopher_threads(data);
	monitor_dining(philo, data);
	if (data->enough_meals)
		meals_quota_message(data);
	clean_memory(philo, data);
	return (EXIT_SUCCESS);
}
 
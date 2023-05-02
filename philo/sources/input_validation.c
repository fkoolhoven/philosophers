/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:34:48 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/05/02 17:36:01 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// check if args are valid numbers
void	validate_input(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error message args\n");
		exit (EXIT_FAILURE);
	}
}

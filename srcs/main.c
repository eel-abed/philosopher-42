/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:57:35 by eel-abed          #+#    #+#             */
/*   Updated: 2025/01/20 14:58:58 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philos;

	if (argc < 5 || argc > 6)
		return (printf("Usage: ./philo [args]\n"), 1);
	if (init_data(&data, argc, argv))
		return (1);
	philos = init_philos(&data);
	if (!philos)
		return (1);
	monitor(philos); // Lancer la surveillance
	return (0);
}

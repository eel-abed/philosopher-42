/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:57:35 by eel-abed          #+#    #+#             */
/*   Updated: 2025/01/31 15:35:16 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor;
	t_philo		*philos;

	philos = data->philos;
	data->start_time = get_time();
	i = 0;
	while (i < data->philo_count)
	{
		philos[i].last_meal = data->start_time;
		if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]))
			return (1);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, data))
		return (1);
	pthread_join(monitor, NULL);
	return (0);
}

void	end_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	print_meal_counts(data);
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->writing);
	pthread_mutex_destroy(&data->meal_check);
	free(data->forks);
	free(data->philos);
}

static	int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
		return (1);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static	int	handle_errors(t_data *data, int argc, char **argv)
{
	if (check_args(argc, argv))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	if (init_data(data, argc, argv))
	{
		printf("Error: Invalid values\n");
		return (1);
	}
	if (init_mutex(data) || init_philos(data))
	{
		printf("Error: Initialization failed\n");
		return (1);
	}
	if (start_simulation(data))
	{
		printf("Error: Thread creation failed\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (handle_errors(&data, argc, argv))
		return (1);
	while (!data.dead)
		;
	end_simulation(&data);
	return (0);
}

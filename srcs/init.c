/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:57:42 by eel-abed          #+#    #+#             */
/*   Updated: 2025/01/20 15:02:29 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (1);
	i = -1;
	while (++i < data->num_philos)
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
	if (pthread_mutex_init(&data->print_lock, NULL))
		return (1);
	if (pthread_mutex_init(&data->meal_lock, NULL))
		return (1);
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	memset(data, 0, sizeof(t_data));
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_meals = ft_atoi(argv[5]);
	data->start_time = get_time();
	return (init_mutexes(data));
}

t_philo	*init_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!philos)
		return (NULL);
	i = -1;
	while (++i < data->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		philos[i].last_meal = data->start_time;
		philos[i].meals_eaten = 0;
		if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]))
			return (NULL);
	}
	return (philos);
}

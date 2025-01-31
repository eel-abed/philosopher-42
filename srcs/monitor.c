/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:58:10 by eel-abed          #+#    #+#             */
/*   Updated: 2025/01/31 18:42:36 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static	int	check_if_all_ate(t_data *data)
{
	int	i;

	if (data->must_eat_count == -1)
		return (0);
	i = 0;
	while (i < data->philo_count)
	{
		if (data->philos[i].ate_count < data->must_eat_count)
			return (0);
		i++;
	}
	data->dead = 1;
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!data->dead)
	{
		i = 0;
		while (i < data->philo_count)
		{
			if (check_death(data, &data->philos[i]))
				return (NULL);
			i++;
		}
		if (check_if_all_ate(data))
			break ;
		usleep(1000);
	}
	return (NULL);
}

void	print_meal_counts(t_data *data)
{
	int	i;

	printf("\n--- Final meal counts ---\n");
	i = 0;
	while (i < data->philo_count)
	{
		printf("Philosopher %d ate %d times\n",
			data->philos[i].id, data->philos[i].ate_count);
		i++;
	}
	printf("------------------------\n");
}

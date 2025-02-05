/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:58:10 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/05 17:24:57 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_if_all_ate(t_data *data)
{
	int	i;

	if (data->must_eat_count == -1)
		return (0);
	i = 0;
	while (i < data->philo_count)
	{
		if (int_getter(&data->ate_count_mtx,
				&data->philos[i].ate_count) < data->must_eat_count)
			return (0);
		i++;
	}
	int_setter(&data->meal_check, &data->dead, 1);
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!int_getter(&data->meal_check, &data->dead))
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

int	int_getter(pthread_mutex_t *mtx, int *value)
{
	int	tmp;

	pthread_mutex_lock(mtx);
	tmp = *value;
	pthread_mutex_unlock(mtx);
	return (tmp);
}

void	int_setter(pthread_mutex_t *mtx, int *value, int new_value)
{
	pthread_mutex_lock(mtx);
	*value = new_value;
	pthread_mutex_unlock(mtx);
}

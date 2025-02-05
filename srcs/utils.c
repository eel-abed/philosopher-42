/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:58:03 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/05 16:45:58 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

long	long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_status(t_data *data, int id, char *status)
{
	pthread_mutex_lock(&data->writing);
	if (!data->dead)
		printf("%lld %d %s\n", get_time() - data->start_time, id, status);
	pthread_mutex_unlock(&data->writing);
}

void	smart_sleep(long long time, t_data *data)
{
	long long	start;

	start = get_time();
	while (!int_getter(&data->meal_check, &data->dead))
	{
		if (get_time() - start >= time)
			break ;
		usleep(100);
	}
}

int	check_death(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->meal_check);
	if (get_time() - philo->last_meal >= data->time_to_die)
	{
		print_status(data, philo->id, "died");
		data->dead = 1;
		pthread_mutex_unlock(&data->meal_check);
		return (1);
	}
	pthread_mutex_unlock(&data->meal_check);
	return (0);
}

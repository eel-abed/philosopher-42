/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:57:42 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/05 17:53:07 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi_safe(const char *str, int *result)
{
	long long	tmp;
	int			sign;
	int			i;

	tmp = 0;
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
		tmp = tmp * 10 + (str[i] - '0');
		if ((sign == 1 && tmp > INT_MAX) || (sign == -1 && -tmp < INT_MIN))
			return (0);
		i++;
	}
	*result = (int)(tmp * sign);
	return (1);
}

int	init_data(t_data *data, int argc, char **argv)
{
	int	tmp;

	if (!ft_atoi_safe(argv[1], &tmp) || tmp <= 0)
		return (1);
	data->philo_count = tmp;
	if (!ft_atoi_safe(argv[2], &tmp) || tmp <= 0)
		return (1);
	data->time_to_die = tmp;
	if (!ft_atoi_safe(argv[3], &tmp) || tmp <= 0)
		return (1);
	data->time_to_eat = tmp;
	if (!ft_atoi_safe(argv[4], &tmp) || tmp <= 0)
		return (1);
	data->time_to_sleep = tmp;
	data->dead = 0;
	data->must_eat_count = -1;
	if (argc == 6)
	{
		if (!ft_atoi_safe(argv[5], &tmp) || tmp < 0)
			return (1);
		data->must_eat_count = tmp;
	}
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->writing, NULL))
		return (1);
	if (pthread_mutex_init(&data->meal_check, NULL))
		return (1);
	if (pthread_mutex_init(&data->ate_count_mtx, NULL))
		return (1);
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos)
		return (1);
	i = 0;
	while (i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].ate_count = 0;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->philo_count;
		data->philos[i].last_meal = 0;
		data->philos[i].data = data;
		i++;
	}
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_count == 1)
	{
		print_status(philo->data, philo->id, "has taken a fork");
		smart_sleep(philo->data->time_to_die, philo->data);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!int_getter(&philo->data->meal_check, &philo->data->dead))
	{
		if (philo->data->must_eat_count != -1
			&& philo->ate_count >= philo->data->must_eat_count)
			break ;
		eat(philo);
		sleep_think(philo);
	}
	return (NULL);
}

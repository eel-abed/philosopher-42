/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:57:57 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/05 17:29:18 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static	void	take_forks(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->data->philo_count;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[right_fork]);
		pthread_mutex_lock(&philo->data->forks[left_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[left_fork]);
		pthread_mutex_lock(&philo->data->forks[right_fork]);
	}
	pthread_mutex_lock(&philo->data->meal_check);
	print_status(philo->data, philo->id, "has taken a fork");
	pthread_mutex_unlock(&philo->data->meal_check);
	pthread_mutex_lock(&philo->data->meal_check);
	print_status(philo->data, philo->id, "has taken a fork");
	pthread_mutex_unlock(&philo->data->meal_check);
}

static	void	drop_forks(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->data->philo_count;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->data->forks[right_fork]);
		pthread_mutex_unlock(&philo->data->forks[left_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[left_fork]);
		pthread_mutex_unlock(&philo->data->forks[right_fork]);
	}
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->data->meal_check);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->meal_check);
	print_status(philo->data, philo->id, "is eating");
	smart_sleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_lock(&philo->data->ate_count_mtx);
	philo->ate_count++;
	pthread_mutex_unlock(&philo->data->ate_count_mtx);
	drop_forks(philo);
}

static int	calculate_think_time(t_philo *philo)
{
	int	think_time;

	think_time = (philo->data->time_to_eat * 2)
		- philo->data->time_to_sleep;
	if (think_time > 0)
		return (think_time);
	return (0);
}

void	sleep_think(t_philo *philo)
{
	int	think_time;

	print_status(philo->data, philo->id, "is sleeping");
	smart_sleep(philo->data->time_to_sleep, philo->data);
	print_status(philo->data, philo->id, "is thinking");
	if (philo->data->philo_count % 2 != 0)
	{
		think_time = calculate_think_time(philo);
		if (think_time > 0)
			smart_sleep(think_time, philo->data);
	}
}

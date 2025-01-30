/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:57:57 by eel-abed          #+#    #+#             */
/*   Updated: 2025/01/20 18:27:38 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static	void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_status(philo->data, philo->id, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_status(philo->data, philo->id, "has taken a fork");
}

static	void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->data->meal_check);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->meal_check);
	print_status(philo->data, philo->id, "is eating");
	smart_sleep(philo->data->time_to_eat, philo->data);
	philo->ate_count++;
	drop_forks(philo);
}

void	sleep_think(t_philo *philo)
{
	print_status(philo->data, philo->id, "is sleeping");
	smart_sleep(philo->data->time_to_sleep, philo->data);
	print_status(philo->data, philo->id, "is thinking");
}

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo->data->dead)
	{
		if (philo->data->must_eat_count != -1 &&
			philo->ate_count >= philo->data->must_eat_count)
			break;
		eat(philo);
		sleep_think(philo);
	}
	return (NULL);
}

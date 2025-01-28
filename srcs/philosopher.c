/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:57:49 by eel-abed          #+#    #+#             */
/*   Updated: 2025/01/28 17:18:04 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	// Add initial delay for even-numbered philosophers
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2);

	while (1)
	{
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		
		// Check if max meals reached before continuing
		pthread_mutex_lock(&philo->data->meal_lock);
		if (philo->data->max_meals > 0 && 
			philo->meals_eaten >= philo->data->max_meals)
		{
			pthread_mutex_unlock(&philo->data->meal_lock);
			break;
		}
		pthread_mutex_unlock(&philo->data->meal_lock);

		print_status(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

void	eat(t_philo *philo)
{
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_lock);
	ft_usleep(philo->data->time_to_eat);
	
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:57:57 by eel-abed          #+#    #+#             */
/*   Updated: 2025/01/20 16:01:29 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Fonction pour prendre les fourchettes (mutex)
void	take_forks(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->data->num_philos;

	// Pour éviter un deadlock, on impose un ordre pour prendre les fourchettes
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

	// Loguer la prise des fourchettes
	print_status(philo, "has taken a fork");
	print_status(philo, "has taken a fork");
}

// Fonction pour relâcher les fourchettes (mutex)
void	release_forks(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = philo->id % philo->data->num_philos;

	// Relâcher les fourchettes dans l'ordre inverse
	pthread_mutex_unlock(&philo->data->forks[left_fork]);
	pthread_mutex_unlock(&philo->data->forks[right_fork]);
}

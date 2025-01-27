/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:57:10 by eel-abed          #+#    #+#             */
/*   Updated: 2025/01/20 19:10:53 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <malloc.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data {
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meal_lock;
}	t_data;

typedef struct s_philo {
	int				id;
	pthread_t		thread;
	long			last_meal;
	int				meals_eaten;
	t_data			*data;
}	t_philo;

// Initialisation
int		init_data(t_data *data, int argc, char **argv);
t_philo	*init_philos(t_data *data);
int	ft_atoi(const char *str);
void	take_forks(t_philo *philo);
void	release_forks(t_philo *philo);


// Utilitaires
long	get_time(void);
void	ft_usleep(long milliseconds);
void	print_status(t_philo *philo, char *msg);

// Philosophe
void	*philo_routine(void *arg);
void	eat(t_philo *philo);

// Surveillance
void	*monitor(void *arg);

#endif

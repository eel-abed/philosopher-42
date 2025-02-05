/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:57:10 by eel-abed          #+#    #+#             */
/*   Updated: 2025/02/05 17:21:13 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				ate_count;
	int				left_fork;
	int				right_fork;
	long long		last_meal;
	struct s_data	*data;
	pthread_t		thread;
}	t_philo;

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				dead;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	writing;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	ate_count_mtx;
	t_philo			*philos;
}	t_data;

int			init_data(t_data *data, int argc, char **argv);
int			init_mutex(t_data *data);
int			init_philos(t_data *data);
int			ft_atoi(const char *str);
long long	get_time(void);
void		print_status(t_data *data, int id, char *status);
void		smart_sleep(long long time, t_data *data);
int			check_death(t_data *data, t_philo *philo);
void		*philo_routine(void *arg);
void		eat(t_philo *philo);
void		sleep_think(t_philo *philo);
int			start_simulation(t_data *data);
void		end_simulation(t_data *data);
void		*monitor_routine(void *arg);
int			int_getter(pthread_mutex_t *mtx, int *value);
void		int_setter(pthread_mutex_t *mtx, int *value, int new_value);

#endif

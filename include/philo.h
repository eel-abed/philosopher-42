/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:44:59 by eel-abed          #+#    #+#             */
/*   Updated: 2025/01/18 17:01:49 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

typedef struct philo {
    int id;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    long long last_meal;
    int meals_eaten;
    int num_meals;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int *dead;
    pthread_mutex_t *write_mutex;
} philo_t;

typedef pthread_mutex_t fork_t;

int init_simulation(int argc, char **argv, philo_t *philos, fork_t *forks);
void *philosopher(void *arg);
void take_forks(philo_t *philo);
void put_forks(philo_t *philo);
void eat(philo_t *philo);
void sleep_(philo_t *philo);
void think(philo_t *philo);
void monitor(philo_t *philos, int num_philos);
long long get_time();
void log_message(philo_t *philo, char *message);

#endif

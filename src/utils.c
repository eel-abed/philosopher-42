/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:45:45 by eel-abed          #+#    #+#             */
/*   Updated: 2025/01/18 17:02:57 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long long get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000LL + ts.tv_nsec / 1000000LL;
}

void log_message(philo_t *philo, char *message) {
    pthread_mutex_lock(philo->write_mutex);
    printf("%lld %d %s\n", get_time(), philo->id, message);
    pthread_mutex_unlock(philo->write_mutex);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdyli <aabdyli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:48:35 by aabdyli           #+#    #+#             */
/*   Updated: 2023/10/26 10:48:38 by aabdyli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

time_t	ft_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

time_t	ft_time_microsec(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000000) + (tv.tv_usec));
}

void	is_writing(t_philo *philo, int statut)
{
	time_t	timestamp_in_ms;

	death_function(philo);
	pthread_mutex_lock(&philo->room->write_mutex);
	if (philo->room->death_variable == 0)
	{
		timestamp_in_ms = ft_time() - philo->room->starting_time;
		if (statut == EATING)
			printf("%ld %d is eating\n", timestamp_in_ms, philo->id);
		else if (statut == FORK)
			printf("%ld %d has taken a fork\n", timestamp_in_ms, philo->id);
		else if (statut == THINKING)
			printf("%ld %d is thinking\n", timestamp_in_ms, philo->id);
		else if (statut == SLEEPING)
			printf("%ld %d is sleeping\n", timestamp_in_ms, philo->id);
	}
	pthread_mutex_unlock(&philo->room->write_mutex);
	death_function(philo);
}

void	ft_usleep(time_t waiting_time, t_philo *philo)
{
	if (death_function(philo) == DIED || waiting_time <= 0)
		return ;
	waiting_time = waiting_time + ft_time();
	while (waiting_time > ft_time())
	{
		if (death_function(philo) == DIED)
			return ;
		usleep(10);
		if (death_function(philo) == DIED)
			return ;
	}
	death_function(philo);
}

int	death_function(t_philo *philo)
{
	pthread_mutex_lock(&philo->room->death_mutex);
	if (philo->room->death_variable != 0)
	{
		pthread_mutex_unlock(&philo->room->death_mutex);
		return (DIED);
	}
	pthread_mutex_unlock(&philo->room->death_mutex);
	if (ft_time() - philo->last_meal >= philo->room->death_time)
	{
		pthread_mutex_lock(&philo->room->death_mutex);
		pthread_mutex_lock(&philo->room->write_mutex);
		if (philo->room->death_variable == 0)
			printf("%ld %d died\n", \
				ft_time() - philo->room->starting_time, philo->id);
		philo->room->death_variable = 1;
		pthread_mutex_unlock(&philo->room->write_mutex);
		pthread_mutex_unlock(&philo->room->death_mutex);
		return (DIED);
	}
	return (0);
}

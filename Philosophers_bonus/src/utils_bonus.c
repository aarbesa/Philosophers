/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdyli <aabdyli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:48:59 by aabdyli           #+#    #+#             */
/*   Updated: 2023/10/26 10:49:01 by aabdyli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

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
	sem_wait(philo->room->write_sem);
	if (philo->room->death_variable == 0)
	{
		timestamp_in_ms = ft_time() - philo->room->starting_time;
		if (statut == EATING)
			printf("% 10ld %d is eating\n", timestamp_in_ms, philo->id);
		else if (statut == FORK)
			printf("% 10ld %d has taken a fork\n", timestamp_in_ms, philo->id);
		else if (statut == THINKING)
			printf("% 10ld %d is thinking\n", timestamp_in_ms, philo->id);
		else if (statut == SLEEPING)
			printf("% 10ld %d is sleeping\n", timestamp_in_ms, philo->id);
	}
	sem_post(philo->room->write_sem);
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
	sem_wait(philo->room->death_sem);
	if (philo->room->death_variable != 0)
	{
		sem_post(philo->room->death_sem);
		return (DIED);
	}
	sem_post(philo->room->death_sem);
	if (ft_time() - philo->last_meal >= philo->room->death_time)
	{
		sem_wait(philo->room->death_sem);
		sem_wait(philo->room->write_sem);
		if (philo->room->death_variable == 0)
			printf("% 10ld %d died\n", \
				ft_time() - philo->room->starting_time, philo->id);
		philo->room->death_variable = 1;
		sem_post(philo->room->write_sem);
		sem_post(philo->room->death_sem);
		return (DIED);
	}
	return (0);
}

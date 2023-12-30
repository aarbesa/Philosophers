/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdyli <aabdyli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:48:56 by aabdyli           #+#    #+#             */
/*   Updated: 2023/10/26 10:48:57 by aabdyli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

static void	*routine(void *arg);
static void	ft_eating(t_philo *philo);
static void	ft_end(t_room *room);

int	ft_philo(int argc, char **argv)
{
	int		i;
	t_room	*room;

	room = malloc(sizeof(t_room));
	if (!room)
		return (1);
	memset(room, 0, sizeof(t_room));
	if (ft_init(room, argv, argc) == 1)
		return (free(room), 1);
	i = 0;
	while (i < room->nb_philos)
	{
		pthread_create(&room->tab_threads[i], NULL, \
			&routine, (void *)room->tab_philo[i]);
		i++;
	}
	ft_end(room);
	return (0);
}

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	usleep((philo->room->starting_time - ft_time()) * 800);
	while (ft_time_microsec() < philo->room->starting_time * 1000)
		usleep(100);
	if (philo->id % 2 == 1)
	{
		is_writing(philo, THINKING);
		ft_usleep((philo->room->eat_time), philo);
	}
	while (1)
	{
		ft_eating(philo);
		is_writing(philo, SLEEPING);
		ft_usleep(philo->room->sleep_time, philo);
		is_writing(philo, THINKING);
		if (philo->nb_of_meals == philo->room->nb_of_meals_needed)
			return (NULL);
		ft_usleep(philo->room->think_time, philo);
		if (death_function(philo) == DIED)
			return (NULL);
	}
	return (NULL);
}

static void	ft_eating(t_philo *philo)
{
	sem_wait(philo->forks_sem);
	death_function(philo);
	is_writing(philo, FORK);
	sem_wait(philo->forks_sem);
	death_function(philo);
	is_writing(philo, FORK);
	death_function(philo);
	is_writing(philo, EATING);
	philo->nb_of_meals += 1;
	if (death_function(philo) != DIED)
		philo->last_meal = ft_time();
	death_function(philo);
	ft_usleep(philo->room->eat_time, philo);
	sem_post(philo->forks_sem);
	death_function(philo);
	sem_post(philo->forks_sem);
	death_function(philo);
}

static void	ft_end(t_room *room)
{
	int	i;

	i = 0;
	while (i < room->nb_philos)
	{
		pthread_join(room->tab_threads[i], NULL);
		i++;
	}
	sem_close(room->death_sem);
	sem_close(room->write_sem);
	sem_close(room->forks);
	sem_unlink("death_sem");
	sem_unlink("write_sem");
	sem_unlink("forks");
	ft_free_philos(room);
	free(room);
}

void	ft_free_philos(t_room *room)
{
	int	i;

	i = 0;
	while (room->tab_philo && room->tab_philo[i])
	{
		free(room->tab_philo[i]);
		i++;
	}
	if (room->tab_philo)
		free(room->tab_philo);
}

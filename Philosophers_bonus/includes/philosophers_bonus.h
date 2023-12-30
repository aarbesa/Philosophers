/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdyli <aabdyli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:48:45 by aabdyli           #+#    #+#             */
/*   Updated: 2023/10/26 10:48:47 by aabdyli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
# include <semaphore.h>
# include <fcntl.h>
# include <stdlib.h>
# define THINKING 1
# define SLEEPING 2
# define EATING 3
# define FORK 4
# define DIED 5
# define MAX_NB_PHILOS 200

typedef struct s_room	t_room;

typedef struct s_philo
{
	int				id;
	int				nb_of_meals;
	sem_t			*forks_sem;
	time_t			last_meal;
	t_room			*room;
}	t_philo;

typedef struct s_room
{
	time_t			eat_time;
	time_t			sleep_time;
	time_t			think_time;
	time_t			death_time;
	time_t			starting_time;
	int				nb_philos;
	int				nb_of_meals_needed;
	int				death_variable;
	sem_t			*death_sem;
	sem_t			*write_sem;
	sem_t			*forks;
	pthread_t		tab_threads[MAX_NB_PHILOS];
	t_philo			**tab_philo;
}	t_room;

time_t	ft_time(void);
time_t	ft_time_microsec(void);
void	is_writing(t_philo *philo, int statut);
void	ft_usleep(time_t waiting_time, t_philo *philo);
int		death_function(t_philo *philo);

int		ft_init(t_room *room, char **argv, int argc);
int		ft_philo(int argc, char **argv);
void	ft_free_philos(t_room *room);

#endif
#ifndef PHILOSHOPERS_H_
# define PHILOSHOPERS_H_

#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct      s_philosopher
{
    int 	        i;
    pthread_t       handler;
    char            state;
    int             time_to_think;
    int             time_to_eat;
    int             time_to_rest;
    char            *name;
    int             rice;
    int             hunger;
    char            *color;
    char 	        states[512];
    int 	        st_i;
}                   t_philosopher;

extern int       	 	        g_chopsticks[7];
extern t_philosopher           g_dudes[7];
extern pthread_mutex_t 	    g_choose;

void    init_resources(void);
void    wait_for(void);
void    *set_brain(void *arg);
void 	philosopher_relax(t_philosopher *p);
void 	philosopher_thinking(t_philosopher *p);
void 	philosopher_eating(t_philosopher *p);
void    init_colors(void);
void    init_resources(void);
void 	print_states_history(void);

#endif /* !PHILOSHOPERS_H_ */
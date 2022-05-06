#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define n 5
#define left phil
#define front phil % 4

sem_t room;
sem_t fks[n];
sem_t bowl[4];

void *philosopher(void *);
void eat(int);
void finish_eat(int);
int main()
{
    int i, a[5];
    pthread_t nmm[5];

    sem_init(&room, 0, 4);

    for (i = 0; i < 5; i++)
        sem_init(&fks[i], 0, 1);

    for (i = 0; i < 4; i++)
        sem_init(&bowl[i], 0, 1);

    for (i = 0; i < 5; i++)
    {
        a[i] = i;
        pthread_create(&nmm[i], NULL, philosopher, (void *)&a[i]);
    }
    for (i = 0; i < 5; i++)
        pthread_join(nmm[i], NULL);
}

void *philosopher(void *num)
{
    int phil = *(int *)num;

    while (1)
    {
        sem_wait(&room);
        printf("\nPhilosopher %d has entered room", phil);
        sem_wait(&fks[left]);
        sem_wait(&bowl[front]);

        eat(phil);
        sleep(2);
        finish_eat(phil);
        sem_post(&fks[left]);
        sem_post(&bowl[front]);
        sem_post(&room);
    }
}

void eat(int phil)
{
    printf("\nPhilosopher %d is eating", phil);
    printf("\nPhilosopher %d takes fork %d and bowl %d",
           phil, left, front);
}

void finish_eat(int phil)
{
    printf("\nPhilosopher %d has finished eating", phil);
    printf("\nPhilosopher %d puts fork %d and bowl %d down",
           phil, left, front);
}
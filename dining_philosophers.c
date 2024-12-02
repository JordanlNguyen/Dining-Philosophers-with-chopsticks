#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdbool.h>



typedef struct{
    int id;
    int number_times_eaten;
}philospher;

void down(philospher ph, int *chop_stick){
    while(chop_stick[ph.id] == 0);
    chop_stick[ph.id] = 0;
    printf("philosopher %d picked up their left chopstick\n", ph.id);
    for(int i = 0; i < 5; i++){
        printf("%d\n", chop_stick[i]);
    }
    while(chop_stick[(ph.id + 1) % 5] == 0);
    chop_stick[(ph.id + 1) % 5] = 0;
    printf("philospher %d picked up their right chopstick\n", ph.id);
    printf("philosopher %d is eating\n", ph.id);
    sleep((rand() % 10) + 1);
    ph.number_times_eaten = ph.number_times_eaten + 1;
    printf("philosopher %d is done eating, they ate %d times\n", ph.id, ph.number_times_eaten);
}

void up(philospher ph, int *chop_stick){
    chop_stick[ph.id] = 1;
    chop_stick[(ph.id + 1) % 5] = 1;
}

void dining(philospher ph, int *chop_stick){
    while(true){
        sleep((rand() % 10) + 1);
        printf("philosopher %d is thinking\n", ph.id);
        sleep((rand()%10) + 1);
        printf("philosopher %d is hungry\n", ph.id);
        down(ph, chop_stick);
        up(ph, chop_stick);
    }

}

int main(){
    int chop_stick0[5] = {1,1,1,1,1}; //1 indicates that it has not been picked up
    int *chop_stick = chop_stick0;
    philospher p0, p1, p2, p3, p4;
    philospher philosopher_list[5] = {p0,p1,p2,p3,p4};
    //initialize the data in philosopher
    for(int i = 0; i < 5; i++){
        philosopher_list[i].id = i;
        philosopher_list[i].number_times_eaten = 0;
    }
    //pass philosophers into dining using fork
    for(int i = 0; i < 5; i++){
        int pid = fork();
        if(pid == 0){
            dining(philosopher_list[i], chop_stick);
            break;
        }
    }
    return 0;
}

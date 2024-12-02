#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdbool.h>

int chop_stick[5] = {1,1,1,1,1}; //1 indicates that it has not been picked up

typedef struct{
    int id;
    int number_times_eaten;
    bool left_hand;
    bool right_hand;
}philospher;

void dining(philospher ph){
    while(true){
        printf("philosopher %d is thinking\n", ph.id);
        sleep((rand()%5) + 1);
        printf("philosopher %d is hungry\n", ph.id);
    }

}

int main(){
    
    philospher p0, p1, p2, p3, p4;
    philospher philosopher_list[5] = {p0,p1,p2,p3,p4};
    //initialize the data in philosopher
    for(int i = 0; i < 5; i++){
        philosopher_list[i].id = i;
        philosopher_list[i].number_times_eaten = 0;
        philosopher_list[i].left_hand = false;
        philosopher_list[i].right_hand = false;
    }
    //pass philosophers into dining using fork
    for(int i = 0; i < 5; i++){
        int pid = fork();
        if(pid == 0){
            dining(philosopher_list[i]);
            break;
        }
    }
    return 0;
}

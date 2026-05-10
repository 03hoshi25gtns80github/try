#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* joujou(void* num);
void baibai(int num);

int main(){
    pthread_t thread_id;
    int a;
    int b;

    printf("乗乗したい数字を入力");
    scanf("%d",&a);
    printf("倍倍したい数字を入力");
    scanf("%d",&b);

    pthread_create(&thread_id, NULL, joujou, (void*)&a);
    baibai(b);
    pthread_join(thread_id, NULL);

    return 0;
}

void* joujou(void* num){
    int* unum = (int*)num;
    for(int i =0; i<=5; i++){
        *unum = *unum * *unum;
        usleep(1500000);
        printf("%d 回目の乗乗",i);
        printf("%d\n",*unum);
    }
    return (void*)num;
}

void baibai(int num){
    for(int i =0; i<=10; i++){
        num = num * 2;
        usleep(500000);
        printf("%d 回目の倍倍",i);
        printf("%d\n",num);
    }
}
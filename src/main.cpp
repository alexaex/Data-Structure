#include <iostream>
#include "linear_container.h"


int main(){

    container::seq_queue<int> queue{ 1,2,3,4,5,6,7,8 };
    queue.traverse();


    queue.push(3);

    int a = 5;
    queue.push(a);

    printf("%d \n", queue.front());



    queue.pop();

    printf("%d \n", queue.front());


    queue.clear();
}
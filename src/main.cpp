#include <iostream>
#include "linear_container.h"


int main(){
    container::linked_queue queue{1,2,3,4,5,6,7};
    queue.traverse();

    queue.clear();
    std::cout<<queue.is_empty()<<std::endl;

    queue.push(1),queue.push(2),queue.push(3);
    std::cout << queue.front() << std::endl;
    queue.traverse();

    queue.pop();
    queue.traverse();

    queue.clear();
    std::cout<<queue.is_empty()<<std::endl;

}
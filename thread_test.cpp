#include <iostream>
#include <thread>
#include <vector>

std::vector<std::thread> workers;

void PrintHelloWorld(int threadNumber){
    std::cout << "Hello, World! (from Thread #" << threadNumber << ")" << std::endl;
}

void PrintFromManyThreads(int threadCount){
    // First is put all the workers in the vector
    for (int i = 0; i < threadCount; i++)
    {
        workers.emplace_back(PrintHelloWorld, i);
    }

    // Then .join() for each of em
    for (std::thread& worker : workers){
        worker.join();
    }
}

int main()
{
    std::cout << "Hello, I am Main Thread!" << std::endl;

    PrintFromManyThreads(50);

    return 0;
}
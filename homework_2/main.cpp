#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <vector>
#include <algorithm>
#include <chrono>
#include "blocking_queue.h"

int main(){
    std::queue<int> m_queue;
    blocking_queue<int> queue(5);
    std::vector<std::thread> given;
    for(int i=0;i<10;i++){
        given.push_back(std::thread([&m_queue,i](){
            m_queue.push(i);
        }));
    }
    std::vector<std::thread> taken;
    for(int i=0;i<10;i++){
        given.push_back(std::thread([&m_queue,i](){
            m_queue.pop();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }));
    }
    std::for_each(given.begin(), given.end(), [](std::thread& thread) {
		thread.join();
		});
	std::for_each(taken.begin(), taken.end(), [](std::thread& thread) {
		thread.join();
		});
}

#include <core/sybling.h>
#include <core/process_logger.h>
#include <chrono>
#include <thread>
#include <iostream>

using namespace sybil;

int main() {
    process* process1 = new process("./thingy.sh");
    process* process2 = new process("./thingy2.sh");
    sybling s1(process1);
    sybling s2(process2);
    s1.set_name("thingy1");
    s2.set_name("thingy2");
    sybling::read_thread(&s1);
    sybling::read_thread(&s2);
    process_logger pl1(&s1);
    process_logger pl2(&s2);
    process_logger::start_logger(&pl1);
    process_logger::start_logger(&pl2);
    s1.begin();
    s2.begin();
    bool exit = false;
    while (!exit) {
        exit = s1.is_stopped() && s2.is_stopped();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "both finished!\n";
    return 0;
}
#include <iostream>
#include <chrono>
#include <thread>
#include <core/process.h>
#include <core/logger.h>
#include <core/overseer.h>

/*
 * main.cpp is currently just the testing file for this project.
 * in the coming months this file will completely change.
 */


int main() {
    sybil::logger::get()->set_level(sybil::logger::DEBUG);
    sybil::logger::get()->standard("starting sybil...");

    std::string process = "/bin/ls";
    sybil::process* sy = new sybil::process(process);
    sy->add_args("-a");
    sybil::overseer o(sy);
    o.begin();
    o.read_process();
    std::cout << "called execute() with: " << o.get_running_command() << std::endl;
    std::cout << "about to call terminate() on process\n";
    o.stop();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    sybil::logger::get()->standard("getting last few lines");
    sybil::logger::get()->print_latest(5);
    return 0;
}
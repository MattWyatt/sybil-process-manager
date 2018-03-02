#include <iostream>
#include <chrono>
#include <thread>
#include <core/sybling.h>
#include <core/logger.h>

/*
 * main.cpp is currently just the testing file for this project.
 * in the coming months this file will completely change.
 */


int main() {
    sybil::logger::get()->write("starting sybil...", sybil::logger::STANDARD);

    std::string process = "/bin/yes";
    sybil::sybling sy(process, {"y"});
    sy.execute();
    std::cout << "called execute() with: " << sy.get_running_command() << std::endl;
    std::cout << "about to call terminate() on process\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    sy.terminate();
    return 0;
}
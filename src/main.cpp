#include <iostream>
#include <chrono>
#include <thread>
#include <core/process.h>
#include <core/logger.h>

/*
 * main.cpp is currently just the testing file for this project.
 * in the coming months this file will completely change.
 */


int main() {
    sybil::logger::get()->set_level(sybil::logger::DEBUG);
    sybil::logger::get()->write("starting sybil...", sybil::logger::STANDARD);

    std::string process = "/bin/yes";
    sybil::process sy(process, {"y"});
    sy.execute();
    std::cout << "called execute() with: " << sy.get_running_command() << std::endl;
    std::cout << "about to call terminate() on process\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    sy.terminate();
    sybil::logger::get()->write("getting last few lines", sybil::logger::STANDARD);
    sybil::logger::get()->print_latest(5);
    return 0;
}
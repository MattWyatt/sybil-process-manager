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
    sybil::logger::get()->write("starting sybil...", sybil::logger::STANDARD);

    std::string process = "/bin/yes";
    sybil::process* sy = new sybil::process(process, {"y"});
    sybil::overseer o(sy);
    o.begin();
    std::cout << "called execute() with: " << o.get_running_command() << std::endl;
    std::cout << "about to call terminate() on process\n";
    o.stop();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    sybil::logger::get()->write("getting last few lines", sybil::logger::STANDARD);
    sybil::logger::get()->print_latest(5);
    return 0;
}
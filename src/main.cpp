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

    std::string process = "/bin/sh";
    sybil::process* sy = new sybil::process(process);
    sybil::overseer o(sy);
    o.begin();
    o.write_process("touch somefile.txt");
    sybil::logger::get()->debug({"called execute with: ", o.get_running_command()});
    sybil::logger::get()->debug("about to call terminate()...");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    o.stop();
    sybil::logger::get()->standard({"child process output: \n", o.read_process()});
    return 0;
}
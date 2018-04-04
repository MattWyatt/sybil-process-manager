#include <core/process.h>
#include <core/logger.h>
#include <core/sybling.h>
#include <iostream>
#include <chrono>
#include <thread>

/*
 * this test helps assert that the process starts correctly
 * by running a program to have it create a file
 */


int main() {
    sybil::logger::get()->set_level(sybil::logger::VERBOSE);
    sybil::logger::get()->standard("starting sybil...");

    std::string process = "/bin/sh";
    sybil::process* sy = new sybil::process(process);
    sybil::sybling o(sy);
    o.begin();
    sybil::sybling::read_thread(&o);
    o.write_process("touch somefile.txt");
    sybil::logger::get()->debug({"called execute with: ", o.get_running_command()});
    sybil::logger::get()->debug("about to call terminate()...");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    //o.stop();
    sybil::logger::get()->standard({"child process output: \n", o.get_output()});
    return 0;
}
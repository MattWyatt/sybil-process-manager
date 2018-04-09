#include <core/process.h>
#include <core/sybling.h>
#include <core/process_logger.h>
#include <iostream>
#include <fstream>

using namespace sybil;

int main() {
    process* process1 = new process("./thingy.sh");
    sybling sybling1(process1);
    std::cout << sybling1.get_running_command() << std::endl;
    sybling1.set_name("thingy");
    sybling::read_thread(&sybling1);
    process_logger pl(&sybling1);
    std::cout << "name: " << pl.get_name() << std::endl;
    std::cout << "path: " << pl.get_path() << std::endl;
    sybling1.begin();
    process_logger::start_logger(&pl);
    sybling1.wait_for_exit();
    return 0;
}
#include <iostream>
#include <core/sybling.h>

int main() {
    std::string process = "/opt/google/chrome/google-chrome";
    sybil::sybling sy(process);
    sy.execute();
    std::cout << "called execute() with: " << sy.get_running_command() << std::endl;
    return 0;
}
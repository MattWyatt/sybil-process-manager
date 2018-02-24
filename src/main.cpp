#include <core/sybling.h>

int main() {
    std::string process = "/bin/ls";
    sybil::sybling sy(process);
    sy.add_args("-a");
    sy.execute();
    return 0;
}
#include <core/daemon.h>
#include <core/logger.h>

using namespace sybil;

int main() {
    logger::get()->set_level(logger::VERBOSE);
    daemon d;
    return 0;
}
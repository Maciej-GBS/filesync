#include "../inc/context.h"

int main(int argc, char* argv[]) {
    filesync::context::Context ctxt;
    return ctxt.run(argc, argv);
}

#include "StardustApp.h"

int main(int argc, char **argv) {
    StardustApp app;
    app.init();
    app.run();
    app.cleanup();

    return 0;
}

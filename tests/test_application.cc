#include "symphony/application.h"

int main(int argc, char** argv) {
    symphony::Application app;
    if (app.init(argc, argv)) {
        return app.run();
    }
    return 0;
}
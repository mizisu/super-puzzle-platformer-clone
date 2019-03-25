#include "base/application.h"

int main(int argc, char* args[]) {
  Application app;
  if (app.Initialize()) app.Run();
  return 0;
}

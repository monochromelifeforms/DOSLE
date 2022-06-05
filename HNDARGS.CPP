#include "hndargs.hpp"

#include "display.hpp"
#include "dmdasimp.hpp"
#include "dmda.hpp"

#include <iostream.h>
#include <string.h>

CDisplay* HandleArguments(int argc, char **argv)
{
  if (argc == 1) {
    // TODO: Auto-detect graphics adapter.
    return new CDisplayMdaSimple(17, 3);
  } else if (strcmp(argv[1], "/h") == 0) {
    // Help message.
    cout << "Usage: " << argv[0] << " </[hmM]>\n"
	 << "  /h Print this help message.\n"
	 << "  /m Run simple MDA version [default].\n"
	 << "  /M Run text-mode graphical MDA version.\n"
	 << flush;
    return NULL;
  } else if (strcmp(argv[1], "/m") == 0) {
    return new CDisplayMdaSimple(17, 3);
  } else if (strcmp(argv[1], "/M") == 0) {
    return new CDisplayMda();
  }

  cout << "Unknown option '" << argv[1] << "'." << endl;
  return NULL;
}

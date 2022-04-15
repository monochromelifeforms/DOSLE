#include "display.hpp"

#include <fstream.h>
#include <string.h>
#include <mem.h>

void AddToList(char* list, char character)
{
  if (strchr(list, character) == NULL)
  {
    char* strEnd = strchr(list, 0);
    strEnd[0] = character;
    strEnd[1] = 0; // terminate string
  }
}


CDisplay::CDisplay()
  : s_saveFile(NULL)
{
  p_unused[0] = 0;
  p_used[0] = 0;
  p_rightPlace[0] = 0;
  memset((void*)a_stats, 0, sizeof(unsigned)*7);
}

void CDisplay::LockWord(unsigned row, const char* answer, const char* guess)
{
  unsigned i;
  unsigned char printedBitPattern = 0;
  unsigned char usedBitPattern = 0;

  // First, print all right-place characters.
  for (i = 0; i < 5; ++i)
    if (answer[i] == guess[i]) {
      ShowCharacter(i, row, guess[i], StyleRightPlace);
      AddToList(p_rightPlace, guess[i]); // append current "right-place" character to list
      usedBitPattern |= (1<<i); // We've used this for reporting already.
      printedBitPattern |= (1<<i); // We don't want to go over this again in the second iteration.
    }

  // Now, go through the remaining characters.
  for (i = 0; i < 5; ++i) {
    if (printedBitPattern & (1<<i))
      continue; // This was in the right place and already printed above.
    // Is the character used anywhere?
    int flagFound = 0;
    for (unsigned j = 0; j < 5; ++j) {
      if (usedBitPattern & (1<<j))
	continue; // We already used this character for reporting.
      if (answer[j] == guess[i]) {
	flagFound = !0;
	usedBitPattern |= (1<<j);
	break;
      }
    }
    if (flagFound) {
      ShowCharacter(i, row, guess[i], StyleUsed);
      AddToList(p_used, guess[i]);
    }
    else {
      ShowCharacter(i, row, guess[i], StyleUnused);
      AddToList(p_unused, guess[i]);
    }
  }
}

void CDisplay::LoadStats(const char* exeFile)
{
  if (s_saveFile != NULL)
    delete s_saveFile;

  const size_t pathLength = strlen(exeFile);
  s_saveFile = new char[pathLength + 1];
  strcpy(s_saveFile, exeFile); // copies too much
  strcpy(s_saveFile + pathLength - 3, "SAV"); // modify extension

  ifstream fs(s_saveFile, ios::in | ios::binary);
  fs.read((char*)&a_stats[0], 7*sizeof(unsigned));
}

CDisplay::~CDisplay()
{
  if (s_saveFile != NULL)
  {
    ofstream fs(s_saveFile, ios::out | ios::trunc | ios::binary);
    fs.write((char*)&a_stats[0], 7*sizeof(unsigned));
    delete s_saveFile;
  }
}


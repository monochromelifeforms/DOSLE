#include "display.hpp"

#include <string.h>

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
{
  p_unused[0] = 0;
  p_used[0] = 0;
  p_rightPlace[0] = 0;
}

void CDisplay::LockWord(unsigned row, const char* answer, const char* guess)
{
  unsigned i;

  // Find "right-place" characters.
  unsigned char rightPlaceBitPattern;
  for (i = 0; i < 5; ++i)
    if (answer[i] == guess[i])
    {
      ShowCharacter(i, row, guess[i], StyleRightPlace);
      AddToList(p_rightPlace, guess[i]); // append current "right-place" character to list
      rightPlaceBitPattern |= (1<<i); // keep track of right-place characters
    }

  // Go through remaining characters.
  for (i = 0; i < 5; ++i)
  {
    if (rightPlaceBitPattern & (1<<i))
      continue; // This character was in the right place, so we ignore it here.
    unsigned flagIsUsed = 0;
    for (unsigned j = 0; j < 5; ++j)
    {
      if (rightPlaceBitPattern & (1<<j))
	continue; // Ignore it in both answer and guess words.
      if (guess[i] == answer[j])
      {
	flagIsUsed = !0;
	break;
      }
    }
    if (flagIsUsed)
    {
      AddToList(p_used, guess[i]);
      ShowCharacter(i, row, guess[i], StyleUsed);
    }
    else
    {
      AddToList(p_unused, guess[i]);
      ShowCharacter(i, row, guess[i], StyleUnused);
    }
  }
}

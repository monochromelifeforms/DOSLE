#include "prox.hpp"

#include "conio.h"
#include "string.h"

void PrintProximity(const char* guess, const char* word)
{
  cprintf("     ");
  for (unsigned i = 0; i < 5; ++i)
  {
    if (strchr(word, guess[i]) == NULL)
    {
      // The letter is not even in the word.
      textattr(0x07);
    }
    else if (guess[i] == word[i])
    {
      // Correct letter in the correct position!
      textattr(0x70);
    }
    else
    {
      // Letter exists in word, but at a different location.
      textattr(0x0F);
    }
    cprintf("%c", guess[i]);
  }
  textattr(0x07);
  cprintf("\n\r");
}

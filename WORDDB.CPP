#include "worddb.hpp"

#include <stdlib.h>
//#include <stdio.h>

CWordDb::CWordDb(const unsigned* indeces, const char* wordList)
  : p_indeces(indeces), p_wordList(wordList)
{
  s_currentWord[0] = 0;
  randomize();
}


void CWordDb::ChooseRandomWord()
{
  const int idx = random(p_indeces[26]);
  for (unsigned i = 0; i < 26; ++i)
  {
    if (idx >= p_indeces[i] && idx < p_indeces[i+1])
    {
      s_currentWord[0] = 'A' + i;
      break;
    }
  }
  //strncpy(&s_currentWord[1], &p_wordList[idx<<2], 4);
  for (unsigned j = 0; j < 4; ++j)
  {
    s_currentWord[1 + j] = p_wordList[(idx<<2) + j];
  }
  s_currentWord[5] = 0; // zero-terminate string
}

int CWordDb::IsValidWord(const char* word) const
{
  // TODO: Not yet implemented.
  return 0;
}

#include "worddb.hpp"

#include <stdlib.h>
#include <string.h>

CWordDb::CWordDb(const unsigned* indeces, const char* wordList)
  : p_indeces(indeces), p_wordList(wordList)
{
  s_currentWord[5] = 0; // That way, the string is always zero-terminated.
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
  strncpy(&s_currentWord[1], &p_wordList[idx<<2], 4);
}

int CWordDb::IsValidWord(const char* word) const
{
  if (word[0] < 'A' || word[0] > 'Z')
    return 0;

  unsigned idxLo = p_indeces[word[0] - 'A'];
  unsigned idxHi = p_indeces[word[0] - 'A' + 1];
  while (idxLo + 1 < idxHi)
  {
    const unsigned idxMid = (idxLo + idxHi) >> 1;
    const int result = strncmp(&p_wordList[idxMid<<2], &word[1], 4);
    if (result == 0)
      return !0;
    else if (result < 0)
      idxLo = idxMid + 1;
    else
      idxHi = idxMid;
  }
  return 0;
}

#include "worddb.hpp"
#include "wordle.hpp"

#include <iostream.h>
#include <conio.h>

int main(void)
{
  CWordDb answers(answerWordIndeces, answerWords);
  for (unsigned i = 0; i < 10; ++i)
  {
    answers.ChooseRandomWord();
    cout << answers.CurrentWord() << endl;
  }

  getch();
  return 0;
}
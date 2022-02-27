#include "worddb.hpp"
#include "wordle.hpp"

#include <iostream.h>
#include <conio.h>

int main(void)
{
  CWordDb answers(answerWordIndeces, answerWords);
  CWordDb allowed(allowedWordIndeces, allowedWords);
  for (unsigned i = 0; i < 10; ++i)
  {
    answers.ChooseRandomWord();
    allowed.ChooseRandomWord();
    cout << answers.CurrentWord() << ": " << answers.IsValidWord(answers.CurrentWord()) << endl;
    cout << allowed.CurrentWord() << ": " << answers.IsValidWord(allowed.CurrentWord()) << endl;
  }
  cout << answers.IsValidWord("12345") << endl;

  getch();
  return 0;
}
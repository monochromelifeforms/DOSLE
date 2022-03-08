#include "worddb.hpp"
#include "wordle.hpp"
#include "prox.hpp"
#include "dmgasimp.hpp"

#include <iostream.h>
#include <conio.h>
#include <string.h>

int main(void)
{
  CDisplay* display = new CDisplayMgaSimple();
  display->ClearScreen();
  display->ShowGrid();

  CWordDb answers(answerWordIndeces, answerWords);
  CWordDb allowed(allowedWordIndeces, allowedWords);

#ifdef dfjkhdkjfghdfhk
  answers.ChooseRandomWord();
  cout << "Start guessing..." << endl;
  const unsigned maxRounds = 6;
  int flagWon = 0;
  for (unsigned round = 0; round < maxRounds; ++round)
  {
    char guess[80];
    cout << round+1 << "/" << maxRounds << ": ";
    cin >> guess;

    // Sanitize guess.
    for (unsigned i = 0; i < 5; ++i)
    {
      if (guess[i] >= 'a' && guess[i] <= 'z')
      {
	guess[i] -= 'a';
	guess[i] += 'A';
      }
    }
    guess[5] = 0;

    if (!answers.IsValidWord(guess) && !allowed.IsValidWord(guess))
    {
      cout << "'" << guess << "' is not a valid word. Try again." << endl;
      --round;
      continue;
    }
    if (strncmp(guess, answers.CurrentWord(), 5) == 0)
    {
      cout << "Congratulations! '" << answers.CurrentWord() << "' was the sought word!" << endl;
      flagWon = !0;
      break;
    }

    PrintProximity(guess, answers.CurrentWord());
  }

  if (!flagWon)
    cout << "Sorry. The word was '" << answers.CurrentWord() << "'. Better luck next time!" << endl;
#endif

  getch();
  return 0;
}
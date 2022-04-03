#include "worddb.hpp"
#include "wordle.hpp"
#include "prox.hpp"
#include "dmgasimp.hpp"

#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
  CDisplay* display = new CDisplayMgaSimple(5, 2);
  display->ClearScreen();
  display->ShowGrid();

  CWordDb answers(answerWordIndeces, answerWords);
  CWordDb allowed(allowedWordIndeces, allowedWords);

  answers.ChooseRandomWord();

  unsigned col = 0;
  unsigned row = 0;
  char guess[6]; // includes zero-termination
  while (1)
  {
    display->IndicateRow(row);
    const char c = getch();
    display->ClearMessage(); // In case we displayed something in the previous iteration.
    guess[col] = c;
    if (c == 27) // ESC
      break;
    if (col < 5 && c >= ' ')
      display->ShowCharacter(col++, row, c, StyleNeutral);
    if (c == 8 && col > 0) // backspace
      display->ShowCharacter(--col, row, ' ', StyleNeutral);
    if (c == 13 && col == 5) // enter
    {
      // Sanitize guess.
      for (unsigned i = 0; i < 5; ++i)
	if (guess[i] >= 'a' && guess[i] <= 'z')
	  guess[i] = guess[i] - 'a' + 'A';
      guess[5] = 0;

      if (!answers.IsValidWord(guess) && !allowed.IsValidWord(guess))
      {
	char message[80];
	sprintf(message, "'%s' is not a valid word. Try again.", guess);
	display->ShowMessage(message);
	for (col = 0; col < 5; ++col)
	  display->ShowCharacter(col, row, ' ', StyleNeutral);
	col = 0;
	continue;
      }
      if (strncmp(guess, answers.CurrentWord(), 5) == 0)
      {
	char message[80];
	sprintf(message, "Congratulations! '%s' was the sought word!", guess);
	display->ShowMessage(message);
	getch();
	break;
      }
      // TODO: display prxomity correctly
      col = 0;
      ++row;
    }
  };

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

    PrintProximity(guess, answers.CurrentWord());
  }

  if (!flagWon)
    cout << "Sorry. The word was '" << answers.CurrentWord() << "'. Better luck next time!" << endl;
#endif

  return 0;
}
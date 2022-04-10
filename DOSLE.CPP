#include "worddb.hpp"
#include "wordle.hpp"
#include "dmgasimp.hpp"

#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>

int main(int /*argc*/, char **argv)
{
  CDisplay* display = new CDisplayMgaSimple(17, 3);
  display->ClearScreen();
  display->ShowGrid();
  display->LoadStats(argv[0]);
  display->ShowStats();

  CWordDb answers(answerWordIndeces, answerWords);
  CWordDb allowed(allowedWordIndeces, allowedWords);

  answers.ChooseRandomWord();

  unsigned col = 0;
  unsigned row = 0;
  char guess[6]; // includes zero-termination
  while (1)
  {
    display->IndicateRow(row);
    display->ShowKeyboard();
    if (row == 6)
    {
      char message[80];
      sprintf(message, "Sorry. The word was '%s'. Better luck next time!", answers.CurrentWord());
      display->ShowMessage(message);
      display->AddStat(); // game lost
      display->ShowStats();
      getch();
      break;
    }

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
      // Is this a valid word?
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
      // Display the word.
      display->LockWord(row, answers.CurrentWord(), guess);
      // Is this the solution?
      if (strncmp(guess, answers.CurrentWord(), 5) == 0)
      {
	display->ShowKeyboard();
	char message[80];
	sprintf(message, "Congratulations! '%s' was the sought word!", guess);
	display->ShowMessage(message);
	display->AddStat(row + 1);
	display->ShowStats();
	getch();
	break;
      }
      // Advance to next row.
      col = 0;
      ++row;
    }
  };

  // Clean-Up
  delete display; // Apparently, BC3.1 does not call the destructor after program termination.

  return 0;
}
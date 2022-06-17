#!/bin/zsh

allowedButNotAnswers=$(mktemp)
comm wordle-allowed-guesses.txt wordle-answers-alphabetical.txt -23 > $allowedButNotAnswers

echo "#ifdef dosle_wordle_h
#define dosle_wordle_h

namespace wordle
{
    const char* answers = \"$(tr --delete '\n' < wordle-answers-alphabetical.txt)\";
    const size_t answersLength = sizeof(answers);

    const char* allowed = \"$(tr --delete '\n' < $allowedButNotAnswers)\";
    const size_t allowedLength = sizeof(allowed);
} // namespace wordle
#endif // dosle_wordle_h" > wordle.h

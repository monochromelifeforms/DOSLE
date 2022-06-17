#!/usr/bin/env python3

import textwrap

with open("wordle-allowed-guesses.txt") as wIs:
    allowedWords = wIs.readlines()
with open("wordle-answers-alphabetical.txt") as wIs:
    answerWords = wIs.readlines()


def Process(words):
    idx = 0
    prev = ord('a')
    indeces = [0]
    singleList = ""
    for word in words:
        while ord(word[0]) != prev:
            indeces += [idx]
            prev += 1
        singleList += word[1:-1].upper()
        idx += 1
    indeces += [idx]
    return indeces, singleList

print("""#ifndef dosle_wordle_h
#define dosle_wordle_h
""")
names = [ "answerWord", "allowedWord" ]
for i, words in enumerate([answerWords, sorted(list(set(allowedWords) - set(answerWords)))]):
    processed = Process(words)
    print('const unsigned {0}Indeces[27] = {{{1}}};'.format(names[i], ", ".join(str(idx) for idx in processed[0])))
    print('const char* {0}s = "{1}";'.format(names[i], "\\\n".join(textwrap.wrap(processed[1], 80))))
    print()

print("#endif // dosle_wordle_h")

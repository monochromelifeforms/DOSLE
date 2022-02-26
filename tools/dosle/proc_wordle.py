#!/usr/bin/env python3

with open("wordle-allowed-guesses.txt") as wIs:
    allowedWords = wIs.readlines()
with open("wordle-answers-alphabetical.txt") as wIs:
    answerWords = wIs.readlines()

def Process(words):
    idx = 0
    prev = None
    indeces = []
    singleList = ""
    for word in words:
        if word[0] != prev:
            indeces += [idx]
            prev = word[0]
        singleList += word[1:-1].upper()
        idx += 1
    indeces += [idx]
    return indeces, singleList

names = [ "answerWord", "allowedWord" ]
for i, words in enumerate([answerWords, sorted(list(set(allowedWords) - set(answerWords)))]):
    processed = Process(words)
    print('    const unsigned* {0}Indeces = {{{1}}};'.format(names[i], ", ".join(str(idx) for idx in processed[0])))
    print('    const char* {0}s = "{1}";'.format(names[i], processed[1]))
    print()

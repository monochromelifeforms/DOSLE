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
        singleList += word[1:-1]
        idx += 1
    indeces += [idx]

    print(len(singleList))
    return indeces, singleList

print(Process(answerWords))

#print(Process(list(set(allowedWords) - set(answerWords))))

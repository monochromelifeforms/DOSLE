#!/usr/bin/env python3
#
# I found the WORDLE lists in a reddit thread,
#   https://www.reddit.com/r/wordle/comments/s4tcw8/a_note_on_wordles_word_list/
# where two repos on github were referenced:
#   https://gist.github.com/cfreshman/a03ef2cba789d8cf00c08f767e0fad7b
#   https://gist.github.com/cfreshman/cdcdf777450c5b5301e439061d29694c
#
# After downloading the two lists, run this python script (on a Linux machine),
# unix2dos the resulting file, and use it in the DOSLE code.
#
# The resulting WORDLE.HPP file is already in this repository, so it doesn't
# have to be redone.
#

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

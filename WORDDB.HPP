#ifndef dosle_worddb_h
#define dosle_worddb_h

class CWordDb
{
  public:
    CWordDb(const unsigned* indeces, const char* wordList);
    void ChooseRandomWord();
    int IsValidWord(const char* word) const;
    const char* CurrentWord() const { return s_currentWord; }

  protected:
    const unsigned* p_indeces;
    const char* p_wordList;
    char s_currentWord[6];
};

#endif //dosle_worddb_h
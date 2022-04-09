#ifndef dosle_display_h
#define dosle_display_h

typedef enum
{
  StyleNeutral,
  StyleUnused,
  StyleUsed,
  StyleRightPlace
} Style_t;

class CDisplay
{
  public:
    virtual void ClearScreen() const=0;
    virtual void ShowGrid() const=0;
    virtual void ShowKeyboard() const=0;
    virtual void ShowCharacter(unsigned column, unsigned row, char character, Style_t style) const=0;
    virtual void ShowMessage(const char* message, Style_t style = StyleNeutral) const=0;
    virtual void ClearMessage() const {} // Do nothing by default.
    virtual void IndicateRow(unsigned /*indicatedRow*/) const {} // DO nothing by default.
    virtual void ShowStats() const=0;
    // Abstract classes need virtual destructors.
    virtual ~CDisplay() {}

    // Lock a word in place in the given row. Uses overloaded ShowCharacter() above.
    void LockWord(unsigned row, const char* answer, const char* guess);
    // Add the number of guesses required to find a word. "7" means the game was lost.
    void AddStat(unsigned guesses = 7) { ++a_stats[guesses-1]; }

  protected:
    char p_unused[27];
    char p_used[27];
    char p_rightPlace[27];

    unsigned a_stats[7]; // 1-6 guesses, and "lost"

    CDisplay(); // Initialize the character lists and stats.
};

#endif // disle_display_h
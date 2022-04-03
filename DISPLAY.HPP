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
    virtual void ShowStats(unsigned stats[7]) const=0;
    virtual void ShowMessage(const char* message, Style_t style = StyleNeutral) const=0;
    virtual void ClearMessage() const {} // Do nothing by default.
    virtual void IndicateRow(unsigned /*indicatedRow*/) const {} // DO nothing by default.
    // Abstract classes need virtual destructors.
    virtual ~CDisplay() {}

    // Lock a word in place in the given row. Uses overloaded ShowCharacter() above.
    void LockWord(unsigned row, const char* answer, const char* guess);

  protected:
    char p_unused[27];
    char p_used[27];
    char p_rightPlace[27];

    CDisplay(); // Initialize the character lists.
};

#endif // disle_display_h
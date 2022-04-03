#ifndef dosle_dmgasimp_h
#define dosle_dmgasimp_h

#include "display.hpp"

class CDisplayMgaSimple : public CDisplay
{
  public:
    CDisplayMgaSimple(unsigned colOffset = 0, unsigned rowOffset = 0)
    { u_offset = colOffset + rowOffset*80; }
    virtual void ClearScreen() const;
    virtual void ShowGrid() const;
    virtual void ShowKeyboard() const;
    virtual void ShowCharacter(unsigned column, unsigned row, char character, Style_t style) const;
    virtual void ShowStats(unsigned stats[7]) const;
    virtual void ShowMessage(const char* message, Style_t style = StyleNeutral) const;
    virtual void ClearMessage() const;
    virtual void IndicateRow(unsigned indicatedRow) const;
  protected:
    unsigned u_offset;

    static void putc(unsigned col, unsigned row, char c, unsigned offset = 0, Style_t style = StyleNeutral);

};

#endif // dosle_dmgasimp_h
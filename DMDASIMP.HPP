#ifndef dosle_dmdasimp_h
#define dosle_dmdasimp_h

#include "display.hpp"

class CDisplayMdaSimple : public CDisplay
{
  public:
    CDisplayMdaSimple(unsigned colOffset = 0, unsigned rowOffset = 0)
      : CDisplay(), u_offset(colOffset + rowOffset*80) {}
    virtual void ClearScreen() const;
    virtual void ShowGrid() const;
    virtual void ShowKeyboard() const;
    virtual void ShowCharacter(unsigned column, unsigned row, char character, Style_t style) const;
    virtual void ShowMessage(const char* message, Style_t style = StyleNeutral) const;
    virtual void ClearMessage() const;
    virtual void IndicateRow(unsigned indicatedRow) const;
    virtual void ShowStats() const;
    virtual ~CDisplayMdaSimple();
  protected:
    unsigned u_offset;

    static void PutChar(unsigned col, unsigned row, char c, unsigned offset = 0, Style_t style = StyleNeutral);

};

#endif // dosle_dmdasimp_h
#ifndef dosle_dmda_h
#define dosle_dmda_h

#include "dmdasimp.hpp"

class CDisplayMda : public CDisplayMdaSimple
{
  public:
    CDisplayMda()
      : CDisplayMdaSimple(28, 2) {}
      // Column and row offset only position the keyboard and stats.
    virtual void ShowGrid() const;
    virtual void ShowCharacter(unsigned column, unsigned row, char character, Style_t style) const;
    virtual void UnshowCharacter(unsigned column, unsigned row) const;
    virtual void ShowMessage(const char* message, Style_t style = StyleNeutral) const;
    virtual void ClearMessage() const;
    virtual void IndicateRow(unsigned indicatedRow) const;

    // Everything else can just be used from CDisplayMdaSimple.
};

#endif
#ifndef dosle_dmgasimp_h
#define dosle_dmgasimp_h

#include "display.hpp"

class CDisplayMgaSimple : public CDisplay
{
  public:
    virtual void ClearScreen() const;

    virtual void ShowGrid() const;

    virtual void ShowKeyboard(const char* neutral,
			      const char* unused,
			      const char* used,
			      const char* rightPlace) const;

    virtual void ShowCharacter(unsigned column, unsigned row, char character, Style_t style) const;

    virtual void ShowStats(unsigned stats[7]) const;
};

#endif // dosle_dmgasimp_h
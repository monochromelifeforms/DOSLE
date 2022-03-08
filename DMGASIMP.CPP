#include "dmgasimp.hpp"

#include <mem.h>

char* const vidmem = (char*)0xB0000000;

void CDisplayMgaSimple::ClearScreen() const
{
  for (unsigned i = 0; i < 80*25; ++i)
    vidmem[i*2] = 0x20;
}

void CDisplayMgaSimple::ShowGrid() const
{
  const static unsigned offset = 2*80 + 10;
  vidmem[0 + offset] = 0xDA;
  vidmem[1 + offset] = 0x07;
  for (unsigned col = 0; col < 5; ++col)
    for (unsigned row = 0; row <= 6; ++row)
    {
      vidmem[offset + 2 + 4*col + row*80*2] = 0xC4;
      vidmem[offset + 2 + 4*col + row*80*2 + 1] = 0x7;
    }
}

void CDisplayMgaSimple::ShowKeyboard(const char* neutral,
				     const char* unused,
				     const char* used,
				     const char* rightPlace) const
{
}

void CDisplayMgaSimple::ShowCharacter(unsigned column, unsigned row, char character, Style_t style) const
{
}

void CDisplayMgaSimple::ShowStats(unsigned stats[7]) const
{
}

#include "dmgasimp.hpp"

#include <assert.h>
#include <string.h>

char* const vidmem = (char*)0xB0000000;

void CDisplayMgaSimple::putc(unsigned col, unsigned row, char c, unsigned offset, Style_t style)
{
  const unsigned address = (offset + col + row*80)<<1;
  vidmem[address] = c;
  switch (style)
  {
    case StyleNeutral:
    case StyleUnused:
      vidmem[address + 1] = 0x07;
      break;
    case StyleUsed:
      vidmem[address + 1] = 0x0F;
      break;
    case StyleRightPlace:
      vidmem[address + 1] = 0x70;
      break;
    default:
      assert(0);
  }
}

void CDisplayMgaSimple::ClearScreen() const
{
  for (unsigned i = 0; i < 80*25; ++i)
  {
    vidmem[i*2] = 0x20;
    vidmem[i*2 + 1] = 0x07;
  }
}

void CDisplayMgaSimple::ShowGrid() const
{
  unsigned col, row;
  // corners
  putc( 0,  0, 0xDA, u_offset); // ul
  putc( 0, 12, 0xC0, u_offset); // ll
  putc(20,  0, 0xBF, u_offset); // ur
  putc(20, 12, 0xD9, u_offset); // lr
  for (col = 0; col <= 5; ++col)
    for (row = 0; row <= 6; ++row) {
      if (col != 5) { // horizontal lines
	putc(1 + 4*col, 2*row, 0xC4, u_offset);
	putc(2 + 4*col, 2*row, 0xC4, u_offset);
	putc(3 + 4*col, 2*row, 0xC4, u_offset);
      }
      if (row != 6) // vertical lines
	putc(4*col, 1 + 2*row, 0xB3, u_offset);
      if (row*col != 0 && row != 6 && col != 5) // inner crosses
	putc(4*col, 2*row, 0xC5, u_offset);
    }
  // Ts
  for (col = 1; col < 5; ++col) {
    putc(4*col,  0, 0xC2, u_offset); // top
    putc(4*col, 12, 0xC1, u_offset); // bottom
  }
  for (row = 1; row < 6; ++row) {
    putc( 0, 2*row, 0xC3, u_offset); // left
    putc(20, 2*row, 0xB4, u_offset); // right
  }
}

void CDisplayMgaSimple::ShowKeyboard() const
{
  static const char row1[] = "QWERTYUIOP";
  static const char row2[] = "ASDFGHJKL";
  static const char row3[] = "ZXCVBNM";
  static const char* rows[] = { row1, row2, row3 };
  for (unsigned row = 0; row < 3; ++row)
  {
    for (unsigned i = 0; i < strlen(rows[row]); ++i)
    {
      if (strchr(p_unused, rows[row][i]) != NULL)
	putc(25 + row + i*2, row, 'x', u_offset, StyleUnused);
      else if (strchr(p_used, rows[row][i]) != NULL)
	putc(25 + row + i*2, row, rows[row][i], u_offset, StyleUsed);
      else if (strchr(p_rightPlace, rows[row][i]) != NULL)
	putc(25 + row + i*2, row, rows[row][i], u_offset, StyleRightPlace);
      else
	putc(25 + row + i*2, row, rows[row][i], u_offset, StyleNeutral);
    }
  }
}

void CDisplayMgaSimple::ShowCharacter(unsigned column, unsigned row, char character, Style_t style) const
{
  const unsigned displayColumn = 2 + 4*column;
  const unsigned displayRow = 1 + 2*row;
  putc(displayColumn, displayRow, character, u_offset, style);
  // surrounding spaces
  putc(displayColumn - 1, displayRow, ' ', u_offset, style);
  putc(displayColumn + 1, displayRow, ' ', u_offset, style);
}

void CDisplayMgaSimple::ShowStats(unsigned /*stats*/[7]) const
{
}

void CDisplayMgaSimple::ShowMessage(const char* message, Style_t style) const
{
  unsigned pos = 0;
  while (message[pos] != 0)
    putc(pos, 14, message[pos++], u_offset, style);
}

void CDisplayMgaSimple::ClearMessage() const
{
  for (unsigned col = 0; col < (80 - (u_offset%80)); ++col)
    putc(col, 14, ' ', u_offset, StyleNeutral);
}

void CDisplayMgaSimple::IndicateRow(unsigned indicatedRow) const
{
  for (unsigned row = 0; row < 6; ++row)
    if (row == indicatedRow)
      putc(-2, 1 + 2*row, 0x1A, u_offset);
    else
      putc(-2, 1 + 2*row, ' ', u_offset);
}

#include "dmgasimp.hpp"

#include <assert.h>
#include <stdio.h>
#include <string.h>

char* const vidmem = (char*)0xB0000000;

void CDisplayMgaSimple::PutChar(unsigned col, unsigned row, char c, unsigned offset, Style_t style)
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
  PutChar( 0,  0, 0xDA, u_offset); // ul
  PutChar( 0, 12, 0xC0, u_offset); // ll
  PutChar(20,  0, 0xBF, u_offset); // ur
  PutChar(20, 12, 0xD9, u_offset); // lr
  for (col = 0; col <= 5; ++col)
    for (row = 0; row <= 6; ++row) {
      if (col != 5) { // horizontal lines
	PutChar(1 + 4*col, 2*row, 0xC4, u_offset);
	PutChar(2 + 4*col, 2*row, 0xC4, u_offset);
	PutChar(3 + 4*col, 2*row, 0xC4, u_offset);
      }
      if (row != 6) // vertical lines
	PutChar(4*col, 1 + 2*row, 0xB3, u_offset);
      if (row*col != 0 && row != 6 && col != 5) // inner crosses
	PutChar(4*col, 2*row, 0xC5, u_offset);
    }
  // Ts
  for (col = 1; col < 5; ++col) {
    PutChar(4*col,  0, 0xC2, u_offset); // top
    PutChar(4*col, 12, 0xC1, u_offset); // bottom
  }
  for (row = 1; row < 6; ++row) {
    PutChar( 0, 2*row, 0xC3, u_offset); // left
    PutChar(20, 2*row, 0xB4, u_offset); // right
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
	PutChar(25 + row + i*2, row, 'x', u_offset, StyleUnused);
      else if (strchr(p_rightPlace, rows[row][i]) != NULL)
	PutChar(25 + row + i*2, row, rows[row][i], u_offset, StyleRightPlace);
      else if (strchr(p_used, rows[row][i]) != NULL)
	PutChar(25 + row + i*2, row, rows[row][i], u_offset, StyleUsed);
      else
	PutChar(25 + row + i*2, row, rows[row][i], u_offset, StyleNeutral);
    }
  }
}

void CDisplayMgaSimple::ShowCharacter(unsigned column, unsigned row, char character, Style_t style) const
{
  const unsigned displayColumn = 2 + 4*column;
  const unsigned displayRow = 1 + 2*row;
  PutChar(displayColumn, displayRow, character, u_offset, style);
  // surrounding spaces
  PutChar(displayColumn - 1, displayRow, ' ', u_offset, style);
  PutChar(displayColumn + 1, displayRow, ' ', u_offset, style);
}

void CDisplayMgaSimple::ShowMessage(const char* message, Style_t style) const
{
  unsigned pos = 0;
  while (message[pos] != 0)
    PutChar(pos, 14, message[pos++], u_offset, style);
}

void CDisplayMgaSimple::ClearMessage() const
{
  for (unsigned col = 0; col < (80 - (u_offset%80)); ++col)
    PutChar(col, 14, ' ', u_offset, StyleNeutral);
}

void CDisplayMgaSimple::IndicateRow(unsigned indicatedRow) const
{
  for (unsigned row = 0; row < 6; ++row)
    if (row == indicatedRow)
      PutChar(-2, 1 + 2*row, 0x1A, u_offset);
    else
      PutChar(-2, 1 + 2*row, ' ', u_offset);
}

void CDisplayMgaSimple::ShowStats() const
{
  unsigned i, j; // loop variables
  char message[80];
  unsigned total = 0;
  unsigned max = 0;
  for (i = 0; i < 7; ++i) {
    total += a_stats[i];
    if (a_stats[i] > max) max = a_stats[i];
  }

  for (i = 0; i < 7; ++i) {
    PutChar(28, 4+i, i+'1', u_offset);
    PutChar(30, 4+i, 0xB3, u_offset);
    if (total == 0)
      PutChar(32, 4+i, '0', u_offset);
    else
    {
      const unsigned len = 15; // TODO: move to a global place?
      const unsigned barLen = len * double(a_stats[i])/double(max) + 0.5;
      for (j = 0; j < barLen; ++j)
	PutChar(31+j, 4+i, ' ', u_offset, StyleRightPlace);
      for (j = barLen; j < len; ++j)
	PutChar(31+j, 4+i, ' ', u_offset, StyleNeutral);
      sprintf(message, "%.1lf%%", 100.*double(a_stats[i])/double(total));
      const unsigned messageLen = strlen(message);
      const unsigned messageOffset = (messageLen+2 <= barLen) ? (barLen-messageLen-2) : barLen;
      const Style_t messageStyle = (messageLen+2 <= barLen) ? StyleRightPlace : StyleNeutral;
      for (j = 0; j < messageLen; ++j)
	PutChar(32 + messageOffset + j, 4+i, message[j], u_offset, messageStyle);
    }
  }
  const char lost[] = "lost";
  for (i = 0; i < 4; ++i)
    PutChar(25+i, 4+6, lost[i], u_offset);
  const char totStr[] = "total";
  for (i = 0; i < 5; ++i)
    PutChar(24+i, 4+7, totStr[i], u_offset, StyleUsed);
  PutChar(30, 4+7, 0xB3, u_offset);
  sprintf(message, "%u", total);
  for (i = 0; i < strlen(message); ++i)
    PutChar(32+i, 4+7, message[i], u_offset, StyleUsed);
}


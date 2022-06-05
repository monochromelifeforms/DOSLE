#include "dmda.hpp"

#include <string.h>

// Contains the first 127 characters as 8x8 bitpatterns.
char far* const fontLower = (char far*)0xffa6000e;

const unsigned gridOffset = 5u;

void CDisplayMda::ShowGrid() const
{
  for (unsigned col = 0; col < 5; ++col)
    for (unsigned row = 0; row < 6; ++row)
      UnshowCharacter(col, row);
}

void CDisplayMda::ShowCharacter(unsigned column, unsigned row, char character, Style_t style) const
{
  if (character >= 128) character = '?';
  const Style_t displayStyle = style==StyleRightPlace?StyleUsed:StyleNeutral;
  const unsigned flagInvert = style == StyleUsed || style == StyleRightPlace;
  const char far* address = &fontLower[character*8];
  for (unsigned j = 0; j < 8; j+=2) { // rows, two at a time, because we combine two pixels into one character
      for (unsigned k = 0; k < 8; ++k) { // columns
	const unsigned upper = (address[j]&(1<<(7-k))) != 0;
	const unsigned lower = (address[j+1]&(1<<(7-k))) != 0;
	switch ((upper<<1)|lower) {
	  case 0: PutChar(column*8 + k, row*4 + (j>>1), flagInvert?0xDB:0x20, gridOffset, displayStyle); break;
	  case 1: PutChar(column*8 + k, row*4 + (j>>1), flagInvert?0xDF:0xDC, gridOffset, displayStyle); break;
	  case 2: PutChar(column*8 + k, row*4 + (j>>1), flagInvert?0xDC:0xDF, gridOffset, displayStyle); break;
	  case 3: PutChar(column*8 + k, row*4 + (j>>1), flagInvert?0x20:0xDB, gridOffset, displayStyle); break;
	  default: PutChar(column*8 + k, row*4 + (j>>1), '?', gridOffset, displayStyle); break;
	}
      }
    }
}

void CDisplayMda::UnshowCharacter(unsigned col, unsigned row) const
{
  PutChar(col*8,   row*4,   0xDA, gridOffset); // upper left corner
  PutChar(col*8+7, row*4,   0xBF, gridOffset); // upper right corner
  PutChar(col*8,   row*4+3, 0xC0, gridOffset); // lower left corner
  PutChar(col*8+7, row*4+3, 0xD9, gridOffset); // lower right corner

  unsigned i;
  for (i = 1; i < 7; ++i) {
    PutChar(col*8+i, row*4,   0xC4, gridOffset);
    PutChar(col*8+i, row*4+1, 0x20, gridOffset);
    PutChar(col*8+i, row*4+2, 0x20, gridOffset);
    PutChar(col*8+i, row*4+3, 0xC4, gridOffset);
  }
  for (i = 1; i < 3; ++i) {
    PutChar(col*8,   row*4+i, 0xB3, gridOffset);
    PutChar(col*8+7, row*4+i, 0xB3, gridOffset);
  }
}

void CDisplayMda::ShowMessage(const char* message, Style_t style) const
{
  unsigned currentRow = 16; // We start in this row.
  unsigned startColumn = (u_offset % 80) + 23;

  unsigned startPrint = 0;
  unsigned lastSpace = 0;
  for (unsigned i = 0; i < strlen(message); ++i) {
    if (message[i] == 0x20) lastSpace = i;
    if (startColumn + i - startPrint == 79 || i == strlen(message)-1) {
      const unsigned endPrint = (i == strlen(message)-1)?strlen(message):lastSpace;
      for (unsigned j = startPrint; j < endPrint; ++j)
	PutChar(startColumn + j - startPrint, currentRow, message[j], 0, style);
      startPrint = lastSpace + 1;
      ++currentRow;
    }
  }
}

void CDisplayMda::ClearMessage() const
{
  for (unsigned row = 16; row < 18; ++row)
    for (unsigned col = (u_offset % 80) + 23 ; col < 80; ++col)
      PutChar(col, row, 0x20, 0);
}

void CDisplayMda::IndicateRow(unsigned indicatedRow) const
{
  if (indicatedRow > 0) {
    // Delete what we printed before.
    for (unsigned i = 0; i < 3; ++i)
      for (unsigned j = 1; j < 3; ++j) {
	PutChar(-2-i, (indicatedRow-1)*4 + j, 0x20, gridOffset);
	PutChar(5*8+1+i, (indicatedRow-1)*4 + j, 0x20, gridOffset);
      }
  }
  for (unsigned j = 1; j < 3; ++j) {
    PutChar(-4, indicatedRow*4 + j, 0xB0, gridOffset);
    PutChar(-3, indicatedRow*4 + j, 0xB1, gridOffset);
    PutChar(-2, indicatedRow*4 + j, 0xB2, gridOffset);
    PutChar(5*8+1, indicatedRow*4 + j, 0xB2, gridOffset);
    PutChar(5*8+2, indicatedRow*4 + j, 0xB1, gridOffset);
    PutChar(5*8+3, indicatedRow*4 + j, 0xB0, gridOffset);
  }
}

/*
 *  keyboard.h
 *  Typing
 *
 *  Created by Michael Dickens on 8/7/09.
 *
 * Includes the keyboard struct and the fitness function.
 */

#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__
 
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "tools.h"

/* Takes a Keyboard pointer k and an integer index.
 * 
 * WARNING: Both k and index are evaluated multiple times.
 */
#define charAt(k, index) ((k)->layout2[(char)((index)/ksize)][(index)%ksize])
#define setCharAt(k, index, c) charAt((k), (index)) = (c)
//#define charAt(k, index) ((index) < ksize ? (k)->layout[index] : (k)->layout[1][index - ksize])
//#define setCharAt(k, index, c) ((index) < ksize ? ((k)->layout[index] = (c)) : ((k)->layout[1][index - ksize] = (c)))

void buildShuffledIndices(int indices[], int length);

int initKeyboard(Keyboard *k);
int setLayout(Keyboard *k, char *layout);
int layoutFromFile(FILE *file, Keyboard *k);
void copyKeyboard(Keyboard *k, Keyboard *original);
int swap(Keyboard *k, int loc1, int loc2);
int swapPair(Keyboard *k, int loc1, int loc2);
int printLayoutOnly(Keyboard *k);
int printLayoutRaw(char layout[]);
int printPercentages(Keyboard *k);
int charToPrintable(char *buffer, char c, int changeSpace);

int qwertyPositions(Keyboard *k);
int readLayouts(Keyboard pool[], int length);

int isSwappable(char c);
int isLegalSwap(Keyboard *k, int i, int j);
void shuffleLayout(Keyboard *kbd);

/* Returns the index of c on either the shifted or unshifted layout. */
int locIgnoreShifted(Keyboard *k, char c);

/* Returns the index of c if c is on the unshifted layout, or index + ksize 
 * if c is on the shifted layout.
 */
int locWithShifted(Keyboard *k, char c);

/* To use, set USE_COST_ARRAY to TRUE. */
int allDigraphCosts[KSIZE_MAX][KSIZE_MAX];

int calcFitnessDirect(Keyboard *k);
int scoreDigraphDirect(Keyboard *k, char digraph[], int64_t multiplier);
int calcFitness(Keyboard *k);
int scoreDigraph(Keyboard *k, char digraph[], int64_t multiplier, int allLocs[]);


char shortcutKeys[4];
char seedLayout[KSIZE_MAX]; // Holds every letter and is randomly shuffled. Used to seed the keyboards.
unsigned int seedVal;

int64_t calcShortcuts(Keyboard *k);
int64_t calcQWERTY(Keyboard *k);
int64_t calcBrackets(Keyboard *k);
int64_t calcBracketsGeneric(Keyboard *k, char openChar, char closeChar);
int64_t calcNumbersShifted(Keyboard *k);

int calcFingerWork(Keyboard *k);
int calcInRoll(int loc0, int loc1);
int calcOutRoll(int loc0, int loc1);
int calcSameFinger(int loc0, int loc1);
int calcRowChange(int loc0, int loc1);
int calcHomeJump(int loc0, int loc1);
int calcRingJump(int loc0, int loc1);
int calcToCenter(int loc0, int loc1);
int calcToOutside(int loc0, int loc1);


#endif

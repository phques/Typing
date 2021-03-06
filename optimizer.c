/*
 *  optimizer.c
 *  Typing
 *
 *  Created by Michael Dickens on 8/11/09.
 *
 */

#include <stdio.h>
#include "accessories.h"

int main()
{
    int c, idx=0;

    /* Initialize the typing data and the keyboard layout settings. */
    strcpy(keysMask, ""); /* initialy empty*/

    /* Init to same values as : isalpha(c) || isspace(c) || c == '\b' */
    memset(keepShiftPairsChars, 0, sizeof(keepShiftPairsChars));
    for (c = 0; c < 256; c++)
    {
        if (isalpha(c) || isspace(c) || c == '\b')
            keepShiftPairsChars[idx++] = c;
    }

    setksize(K_NO);
    getCommands();
    
	return 0;
}


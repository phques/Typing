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
    /* Initialize the typing data and the keyboard layout settings. */
	initCosts(); //PQ moved from initValues
    setksize(K_NO);
    getCommands();
    
	return 0;
}


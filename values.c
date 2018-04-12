/*
 *  values.c
 *  Typing
 *
 *  Created by Michael Dickens on 8/23/09.
 *
 */

#include "values.h"

/* returns True if keysMask is valid / should be used.
 Also sets trueksize according to mask */
int checkKeysMask()
{
	int useMask = FALSE;

	if (strlen(keysMask) > 0) {
		if (strlen(keysMask) != ksize) {
			printf("Wrong nbr of keys in mask (%d), need %d\n", strlen(keysMask), ksize);
			useMask = FALSE;
		}
		else {
			int i, newsize =0;
			printf("Using keys mask: %s\n", keysMask);
			useMask = TRUE;

			/* calc trueksize */
			for (i = 0; i < ksize; i++)
				newsize += (keysMask[i] == '1');

			if (newsize != trueksize) {
				trueksize = newsize;
				printf("trueksize adjusted to %d from mask\n", newsize);
			}
		}
	}

	return useMask;
}

int initValues()
{
	int i;

	initCosts();
	
	if (fullKeyboard == K_NO) {
		// Set keyboard position costs. These costs were determined by looking 
		// at how the positions were valued on some of the best alternative 
		// layouts.
		static int64_t costsCopy[KSIZE_MAX] = {
			 40,  40,  30,  40,  70,  80,  40,  30,  40,  40, 
			  0,   0,   0,   0,  30,  30,   0,   0,   0,   0, 
			 70,  70,  70,  50,  95,  60,  40,  60,  70,  70, 
		};
	
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];
		
	} else if (fullKeyboard == K_STANDARD) {
		
		// These costs are optimized for a full standard layout. Any cost that 
		// is 999 is not supposed to contain any character.
#if 1
		static int64_t costsCopy[KSIZE_MAX] = {
			110, 100,  90,  75, 100, 120, 160, 100,  75,  90, 100, 110, 120, 999,
			999,  40,  40,  30,  40,  70,  80,  40,  30,  40,  40,  60,  90, 140, 
			999,   0,   0,   0,   0,  30,  30,   0,   0,   0,   0,  50, 999, 999, 
			999,  70,  70,  70,  50,  95,  60,  40,  60,  70,  70, 999, 999, 999, 
		};
#else
		// full version with costs from 30 mains chars in anglez / curl
		static int64_t costsCopy[KSIZE_MAX] = {
			110, 100,  90,  75, 100, 120, 160, 100,  75,  90, 100, 110, 120, 999,
			999,  70,  35,  33,  45,  80,  93,  40,  33,  35,  70,  80,  90, 140,
			999,  16,   6,   0,   0,  55,  50,   0,   0,   6,  16,  60, 999, 999,
			999,  50,  60,  30,  58,  93,  55,  30,  60,  50,  75, 999, 999, 999,
		};
#endif
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];
			
	} else if (fullKeyboard == K_KINESIS) {
		
		// These costs are optimized for Kinesis. Any cost that is 999 is not 
		// supposed to contain any character.
		static int64_t costsCopy[KSIZE_MAX] = {
			120, 110, 100,  75, 100, 130, 130, 100,  75, 100, 110, 120, 
			 90,  40,  40,  30,  40,  70,  70,  40,  30,  40,  40,  90, 
			 60,   0,   0,   0,   0,  40,  40,   0,   0,   0,   0,  60, 
			999,  70,  70,  70,  50,  80,  80,  50,  70,  70,  70, 999, 
			999, 140, 140, 999, 999, 999, 999, 999, 999, 140, 140, 999, 	
			  0,  50, 999, 999, 999, 999, 999, 999, 999, 999,  50,   0, 
		};
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];
		
	} else if (fullKeyboard == K_IPHONE) {
		
		// Thumbs are centered over the QWERTY D and K keys.
		static int64_t costsCopy[KSIZE_MAX] = {
			  45,  30,  20,  10,  20,  20,  10,  20,  30,  40, 
			  20,  10,   0,   0,  10,  10,   0,   0,  10, 999,
			 999,  60,  50,  30,  20,  20,  50,  60, 999, 999, 
		};
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];
		
	} else	if (fullKeyboard == K_CURLAZ30) {
		/* Left hand bottom row, using 'angleZ' ergo mod, where the lower keys are
		accessed to the left rather than to the right, following natural curving of fingers.
		Values converted from colemak mod-dh base efforts
		assumed range 1..4 => 0..100
		Also original values are for *ISO* kbd with shift
		so left bottom 3.5 2.8 2.5 1.7 2.6
		becomes        2.8 2.5 1.7 2.6 3.8 for *us* kbd
		3.5 2.4 2.0 2.2 3.4 3.8 2.2 2.0 2.4 3.5
		1.5 1.2 1.0 1.0 2.9 2.9 1.0 1.0 1.2 1.5
		2.8 2.5 1.7 2.6 3.8 2.6 1.7 2.5 2.8 3.5
		*/
		// PQ, adjusted based on personal taste (as in workman layout, avoid mid column on home row)
#if 0
		static int64_t costsCopy[KSIZE_MAX] = {
			//  83,  35,  33,  40,  80,  93,  40,  33,  35,  83,
			70,  35,  33,  40,  80,  93,  40,  33,  35,  70,
			16,   6,   0,   0,  63,  63,   0,   0,   6,  16,
			50,  60,  23,  50,  93,  50,  23,  60,  50,  75,
			//  60,  55,  23,  50,  93,  50,  23,  55,  60,  83,
		};
#else   // angleZ reduced curl
		static int64_t costsCopy[KSIZE_MAX] = {
			//  83,  35,  33,  40,  80,  93,  40,  33,  35,  83,
			70,  35,  33,  45,  80,  85,  40,  33,  35,  70,
			16,   6,   0,   0,  55,  50,   0,   0,   6,  16,
			50,  60,  30,  58,  95,  55,  30,  60,  50,  75,
			//  60,  55,  23,  50,  93,  50,  23,  55,  60,  83,
		};
#endif
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];


	} else	if (fullKeyboard == K_CURLAZ32) {
		// K_CURLAZ30 + 2 chars at right of right hand ('[)
#if 0
		// angleZ reduced curl
		static int64_t costsCopy[KSIZE_MAX] = {
			70,  35,  33,  45,  80,  93,  40,  33,  35,  70,  80,
			16,   6,   0,   0,  55,  50,   0,   0,   6,  16,  60,
			50,  60,  30,  58,  93,  55,  30,  60,  50,  75, 999,
		};
#elif 1
		// + reduced costs on right pinky outside home
		static int64_t costsCopy[KSIZE_MAX] = {
			70,  35,  33,  45,  80,  85,  40,  33,  35,  70,  80,
			16,   6,   0,   0,  55,  50,   0,   0,   6,  16,  45,
			50,  60,  30,  58,  95,  55,  30,  60,  50,  75, 999,
		}; 
#endif

		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];
		
	} else	if (fullKeyboard == K_CURLAZ33) {
		// K_CURLAZ30 + 3 chars at right of right hand ('[])
		// angleZ reduced curl
		static int64_t costsCopy[KSIZE_MAX] = {
			70,  35,  33,  45,  80,  85,  40,  33,  35,  70,  80,  90,
			16,   6,   0,   0,  55,  50,   0,   0,   6,  16,  45, 999,
			50,  60,  30,  58,  95,  55,  30,  60,  50,  75, 999, 999,
		};
		
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];

	} else if (fullKeyboard == K_MAIN33) {
		static int64_t costsCopy[KSIZE_MAX] = {
			40,  40,  30,  40,  70,  80,  40,  30,  40,  40,   80,  90,
			 0,   0,   0,   0,  30,  30,   0,   0,   0,   0,   45, 999,
			70,  70,  70,  50,  95,  60,  40,  60,  70,  70,  999, 999,
		};

		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];

	} else	if (fullKeyboard == K_BEAKLASALLE) {
		/* weights from BEAK, http://shenafu.com/smf/index.php?topic=89.msg785#msg785
			uses idea of 3x3 'home block' vs home row
		*/

		// BEAKL 8-9 according to http://shenafu.com/smf/index.php?topic=89.msg2180#msg2180
        // mod PQ 2018-04, trying to get LaSalle fingering, where home row uses awef jio;
        // hmm not really home block anymore !!
		static int64_t costsCopy[KSIZE_MAX] = {
		   // 150,  5,  5, 15, 50,   50, 15,  5,  5, 150,
			 // 8, 10, 10,  5, 18,   18,  5, 10, 10, 8, 
			// 70, 50, 50, 15, 70,   70, 15, 50, 50, 70
		   150,  5,  5, 15, 50,   50, 15,  5,  5, 150,
			30, 10, 10,  5, 20,   20,  5, 10, 10, 30, 
			70, 50, 50, 15, 70,   70, 15, 50, 50, 70
		};
		   // 150, 15, 10, 15, 50,   50, 15, 10, 15, 150,
			// 50,  5,  5,  5, 15,   15,  5,  5,  5, 50, 
			// 70, 20, 50, 10, 70,   70, 10, 50, 20, 70
        
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];

	} else	if (fullKeyboard == K_BEAK) {
		/* weights from BEAK, http://shenafu.com/smf/index.php?topic=89.msg785#msg785
			uses idea of 3x3 'home block' vs home row
		*/
#if 1
		// BEAKL 8-9 according to http://shenafu.com/smf/index.php?topic=89.msg2180#msg2180
        // slight mod PQ 2018-04
		static int64_t costsCopy[KSIZE_MAX] = {
		   150, 15, 10, 20, 50,   50, 20, 10, 15, 150,
			50,  5,  5,  5, 18,   18,  5,  5,  5, 50, 
			70, 15, 50, 10, 70,   70, 10, 50, 15, 70
		};
		   // 150, 15, 10, 15, 50,   50, 15, 10, 15, 150,
			// 50,  5,  5,  5, 15,   15,  5,  5,  5, 50, 
			// 70, 20, 50, 10, 70,   70, 10, 50, 20, 70
        
#else
        // older BEAKL weights  ver 3 ??
		static int64_t costsCopy[KSIZE_MAX] = {
			90, 10, 10, 10, 50, 50, 10, 10, 10, 90,
			50,  5,  5,  5, 20, 20,  5,  5,  5, 50,
			90, 20, 30, 10, 50, 50, 10, 30, 20, 90 
		};
#endif

		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];

	} else if (fullKeyboard == K_BEAKPQ) {
		/* weights from BEAK, http://shenafu.com/smf/index.php?topic=89.msg785#msg785
		uses idea of 3x3 'home block' vs home row
		*/
#if 1
		// try going back to closer to original beakl (beakl + angleZ)
		// tried top row index 15 vs 10 but worst numbers !?
		static int64_t costsCopy[KSIZE_MAX] = {
			90, 10, 10, 10, 50, 50, 10, 10, 10, 90,
			50,  5,  5,  5, 20, 20,  5,  5,  5, 50,
			20, 30, 10, 50, 90, 50, 10, 30, 20, 90
		};
#else
		// PQ modified for perso taste (higher cost top row index, left hand bottom anglez / curl)
		static int64_t costsCopy[KSIZE_MAX] = {
			//90, 10, 10, 15, 50, 50, 15, 10, 10, 90,
			//50,  5,  5,  5, 20, 20,  5,  5,  5, 50,
			//20, 30, 10, 50, 80, 50, 10, 30, 20, 90

			70,  20,  15,  35,  80,  93,  35,  15,  20,  70,
			50,   6,   0,   0,  45,  45,   0,   0,   6,  50,
			20,  30,  10,  50,  93,  50,  10,  30,  20,  75,
		};
#endif
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];

	} else if (fullKeyboard == K_BEAKPQ33) {
		/* weights from BEAK, http://shenafu.com/smf/index.php?topic=89.msg785#msg785
		uses idea of 3x3 'home block' vs home row
		*/

		// try going back to closer to original beakl (beakl + angleZ)
		// tried top row index 15 vs 10 but worst numbers !?
		static int64_t costsCopy[KSIZE_MAX] = {
			90, 10, 10, 10, 50, 50, 10, 10, 10, 90,	110, 120,
			50,  5,  5,  5, 20, 20,  5,  5,  5, 50,	100, 999,
			20, 30, 10, 50, 90, 50, 10, 30, 20, 90,	999, 999,
		};

		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];

	} else if (fullKeyboard == K_BEAKPQFULL) {
		/* weights from BEAK, http://shenafu.com/smf/index.php?topic=89.msg785#msg785
		uses idea of 3x3 'home block' vs home row
		*/
		// PQ modified for perso taste (higher cost top row index, left hand bottom anglez / curl)
#if 1
		static int64_t costsCopy[KSIZE_MAX] = {
			//110, 100,  90,  75, 100, 120, 160, 100,  75,  90, 100, 110, 120, 999,
			//999,  90,  10,  10,  15,  50,  50,  15,  10,  10,  90, 100, 120, 140,
			//999,  50,   5,   5,   5,  20,  20,   5,   5,   5,  50, 100, 999, 999,
			//999,  20,  30,  10,  50,  80,  50,  10,  30,  20,  90, 999, 999, 999,

			110, 100,  90,  75, 100, 120, 160, 100,  75,  90, 100, 110, 120, 999,
			999,  70,  20,  15,  35,  80,  93,  35,  15,  20,  70, 100, 120, 140,
			999,  50,   6,   0,   0,  45,  45,   0,   0,   6,  50, 100, 999, 999,
			999,  20,  30,  10,  50,  93,  50,  10,  30,  20,  75, 999, 999, 999,
		};
#else
		// 'wide' on sculpt ergo
		static int64_t costsCopy[KSIZE_MAX] = {
			110, 100,  90,  75, 100, 120,  160, 160, 100,  75,  90, 100, 110, 999,
			999,  90,  10,  10,  15,  50,  160,  50,  15,  10,  10,  90, 100, 120,
			999,  50,   5,   5,   5,  20,  140,  20,   5,   5,   5,  50, 999, 999,
			999,  20,  30,  10,  50,  80,  120,  50,  10,  30,  20, 999, 999, 999,
		};
#endif


		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];
	}

	// Mask out keys if we have a key mask 
	// (this might not be required? since printable[] is also set according to mask..)
	if (checkKeysMask()) {
		for (i = 0; i < ksize; ++i) {
			if (keysMask[i] == '0')
				distanceCosts[i] = 999;
		}
	}


	// Based on distance from the ctrl key and how much of a stretch it is.
	shortcutCosts[ 0] =  0; shortcutCosts[ 1] =  0; shortcutCosts[ 2] =  1; shortcutCosts[ 3] =  3; shortcutCosts[ 4] =  4; 
	shortcutCosts[ 5] =  8; shortcutCosts[ 6] = 10; shortcutCosts[ 7] = 10; shortcutCosts[ 8] = 10; shortcutCosts[ 9] = 10; 
	shortcutCosts[10] =  0; shortcutCosts[11] =  0; shortcutCosts[12] =  2; shortcutCosts[13] =  3; shortcutCosts[14] =  5; 
	shortcutCosts[15] =  8; shortcutCosts[16] = 10; shortcutCosts[17] = 10; shortcutCosts[18] = 10; shortcutCosts[19] = 10; 
	shortcutCosts[20] =  0; shortcutCosts[21] =  0; shortcutCosts[22] =  0; shortcutCosts[23] =  2; shortcutCosts[24] =  4; 
	shortcutCosts[25] =  8; shortcutCosts[26] = 10; shortcutCosts[27] = 10; shortcutCosts[28] = 10; shortcutCosts[29] = 10; 
	
	return 0;
}

void initCosts()
{
	detailedOutput = TRUE;
    
    /* If you do not wish to use multithreading, set numThreads to 1. */
	numThreads = 1;
	
	keepZXCV = FALSE;
	keepQWERTY = FALSE;
	keepNumbers = 1;
	keepBrackets = TRUE;
	//keepShiftPairs = 3; // whitespace, \b, islpha()
	keepShiftPairLetters = 2; // islpha
	keepShiftPairSpace = TRUE;
	keepShiftPairOther = FALSE;
	keepTab = TRUE;
	keepConsonantsRight = FALSE;
	keepNumbersShifted = FALSE;
	
	zCost = 10;
	xCost =  6;
	cCost = 12;
	vCost = 14;
	qwertyPosCost = 14;
	qwertyFingerCost = 4;
	qwertyHandCost = 20;
	bracketsCost = 5000000;
	numbersShiftedCost = -1000000;

	if (fullKeyboard == K_KINESIS) {
		fingerPercentMaxes[0] = fingerPercentMaxes[FINGER_COUNT - 1] =  7.5;
		fingerPercentMaxes[1] = fingerPercentMaxes[FINGER_COUNT - 2] = 10.0;
		fingerPercentMaxes[2] = fingerPercentMaxes[FINGER_COUNT - 3] = 20.0;
		fingerPercentMaxes[3] = fingerPercentMaxes[FINGER_COUNT - 4] = 20.0;
		fingerPercentMaxes[4] = fingerPercentMaxes[FINGER_COUNT - 5] = 18.0;
	} else {
		fingerPercentMaxes[0] = fingerPercentMaxes[FINGER_COUNT - 1] =  9.0;
		fingerPercentMaxes[1] = fingerPercentMaxes[FINGER_COUNT - 2] = 11.5;
		fingerPercentMaxes[2] = fingerPercentMaxes[FINGER_COUNT - 3] = 22.0;
		fingerPercentMaxes[3] = fingerPercentMaxes[FINGER_COUNT - 4] = 22.0;
		fingerPercentMaxes[4] = fingerPercentMaxes[FINGER_COUNT - 5] = 18.0;		
	}

	
	fingerWorkCosts[0] = fingerWorkCosts[FINGER_COUNT - 1] = 40;
	fingerWorkCosts[1] = fingerWorkCosts[FINGER_COUNT - 2] = 30;
	fingerWorkCosts[2] = fingerWorkCosts[FINGER_COUNT - 3] = 20;
	fingerWorkCosts[3] = fingerWorkCosts[FINGER_COUNT - 4] = 20;
	fingerWorkCosts[4] = fingerWorkCosts[FINGER_COUNT - 5] = 20;
	
	/* All values are compounding. For example, say we jump over the home row
	 * on the index finger. The cost is 
     *     sameHand + rowChange + homeJump + homeJumpIndex.
     */
	distance =		  1;
	inRoll =		-40;
	outRoll =		  5;
	sameHand =		  5;
	sameFingerP =	150;
	sameFingerR =	140;
	sameFingerM =	110;
	sameFingerI =	 90;
	sameFingerT =	100;
	rowChangeDown =  10;
	rowChangeUp =    15;
	handWarp =		 25;
	handSmooth =	- 5;
	homeJump =		100;
	homeJumpIndex = -90;
	doubleJump =	220; /* Does not compound with homeJump. */
	ringJump =       40;
	toCenter =		 30;
	toOutside =		 30;
	
	shiftCost =		100;
	doubleShiftCost=150;

	leftHandCost = 0;
	rightHandCost = 0;
	singleKeySameFinger = 0;
}

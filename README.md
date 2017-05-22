Changes to forked, PQ  
2017-04-29 Added sethandbias  
2017-04-30 Added "curlaz30" kbd  
2017-04-30 Added "beak" kbd using weights from http://shenafu.com/smf/index.php?topic=89.msg785#msg785  
2017-04-30 Added "beakpq" kbd, adjusted weights (higher cost top row index, left hand bottom anglez / curl)  
2017-05-20 
 + Added setmask "110011.." command, to select keys to use in kbd / layout,  
   This usually also requires "use aabcd..ABCD.." with correct nbr of / wanted chars  
 + keepShiftedPairs var is now 0-3, from none to all  
 + Fixed bug where using a kbd with trueksize < ksize : shifted pos less likely to be moved.  
   Actually in some cases, shifted pos where NEVER moved  
 + Changed logic about isLegalSwap for keepShiftPairs handling
2017-05-21 
 + Added variable singleKeySameFinger, which is a percentage of sameFinger cost for 
   same finger on a single key
 + Fixed printLayoutRaw for 30keys, was not behaving properly with sparse layouts

2017-05-22 replaced keepShiftPair with keepShiftPairLetters, keepShiftPairSpace, keepShiftPairOther. 
 
Note: using setmask calls setksize, which RESETS all variables, be carefull

 
ABOUT
-----

This is a program designed to efficiently optimize keyboard layouts, inspired by the work done by Peter Klausler. It uses a (relatively) friendly command-line interface to allow the user to customize a keyboard layout.

I began developing this program in 2008 and have been working on it since then. For updates, see http://mathematicalmulticore.wordpress.com/category/keyboards/ and https://github.com/michaeldickens/Typing.


INSTALLATION
------------

1. If you don't have gcc installed, install it. http://gcc.gnu.org/
2. Run "make" to produce an executable file.
3. You may now execute "optimizer" with `./optimizer`.

This program is designed for a 64-bit platform. If you are using a 32-bit or smaller platform, it will run significantly slower.


HOW TO RUN THE ALGORITHM
------------------------

The program itself provides documentation for the various options.


USING THE FULL KEYBOARD
-----------------------

The default setting is to evaluate the main 30 keys on the keyboard (this is how the program was originally written). You can also use it to evaluate the entire keyboard by changing it at runtime or by changing this line near the beginning of `initValues()` in values.c: 

    fullKeyboard = <K_SETTING>;

To use the main 30 keys write `K_NO`, for the full keyboard use `K_STANDARD`, and for a full Kinesis keyboard use `K_KINESIS`.

For the more casual keyboard optimizer I recommended just optimizing the main 30 keys, as the other keys don't have a very large effect and the rarer keys are much more difficult to re-learn. But if you want maximum optimization, this is the option for you. This option can use a standard keyboard or the Kinesis Advantage Pro keyboard (if you're willing to go to the trouble of re-learning your entire keyboard then you may as well buy a top-of-the-line ergonomic keyboard too).

The full standard keyboard supposedly has 56 characters: 4 rows of 14. In truth it only has 47: 

(m indicates a main-30 key, and k indicates an additional key.)

    k k k k k k k k k k k k k
      m m m m m m m m m m k k k
      m m m m m m m m m m k
      m m m m m m m m m m

The full Kinesis keyboard supposedly has 72 keys: 6 rows of 12. In truth it only has 50: 
 
    k k k k k k k k k k k
    m m m m m m m m m m k
    m m m m m m m m m m k
    m m m m m m m m m m
    k k             k k
    k k               k k // thumb keys

The costs for individual keys on the keyboard must be edited from inside the source code. Change `costsCopy` in `initValues()` in values.c to change the costs for the individual keys. Then run "make" again to re-compile the source code.


FILE SYSTEM
-----------

main.c: Runs the core functions.

cjalgorithm.c: Runs an algorithm based on one written by Chris Johnson (kinky_b@hotmail.com). It has the same purpose as algorithm.c but runs much faster.

accessories.h: Header file for accessories.
accessories.c: Contains various extras that are not directly related to the algorithm. Contains a keyboard improvement function, a function to collect timing data, a function that compares various layouts in a simple way, and a function to evaluate the cost of each individual digraph for a given keyboard.

keyboard.h: Header file for keyboard and fitness.
keyboard.c: Contains functions that center around the keyboard structure itself. Responsible for initializing and printing a keyboard. Also contains some miscellaneous functions that are directly related to the keyboard structure.

fitness.c: Contains the core `calcFitness()` function as well as several smaller functions for individual aspects of fitness such as same hand usage, same finger, finger travel distance, etc.

tools.h: Header file for tools and trikeys.
tools.c: Contains necessary tools for running the algorithm. Contains the lists of digraphs and monographs. Also contains some miscellaneous functions such as the `rand30()` function.

values.h: Contains various constants as well as the fitness costs.
values.c: Contains some fitness costs as arrays.


FITNESS
-------

See [Fitness.txt.](/doc/Fitness.md)
 

ADDING YOUR OWN PHYSICAL KEYBOARD
---------------------------------

By default there are three options for physical keyboards: a keyboard with just the main 30 keys (`K_NO`), a full standard keyboard (`K_STANDARD`), and a Kinesis keyboard (`K_KINESIS`). You can add your own physical keyboard by modifying the source code in a few places. Let's say you want to add a keyboard called Binary which only has two keys on it. You would have to follow these steps.

1. At the beginning of values.h, you will see this:

        #define K_NO 0
        #define K_STANDARD 1
        #define K_KINESIS 2
        // ...
    
Add this line to the end: 

        #define K_BINARY 10

It doesn't matter what number you give as long as no other keyboard uses the same number.

2. In tools.c near the bottom there's a function called setksize(). It sets the size of the keyboard. Add your keyboard to the switch statement, like so: 

        case K_BINARY:
            ksize = 2; /* The size of the keyboard in this case is 2 */
            break;

3. In values.c there's a function called `initValues()` containing code that looks like this:

        if (full_keyboard == K_NO) {
            // Set keyboard position costs manually. These costs were
            // determined by looking at how the positions were valued on
            // some of the best alternative layouts.
            long long costsCopy[KSIZE_MAX] = {
                70,  35,  30,  40,  60,  80,  40,  30,  35,  70, 
                10,   4,   0,   0,  35,  35,   0,   0,   4,  10, 
                90,  85,  60,  50,  95,  70,  40,  60,  80,  90, 
            };
            for (i = 0; i < ksize; ++i)
                distanceCosts[i] = costsCopy[i];
    
        // ...
            
        } else if (full_keyboard == K_STANDARD) {
            
        // ...

        } else if (full_keyboard == K_KINESIS) {
            
        // ...
            
        }

Add a new section that looks like this:

        if (full_keyboard == K_BINARY) {
            long long costsCopy[KSIZE_MAX] = {
                // Whatever you want the costs for each index to be. In
				// this case, the first index costs 10 and the second
				// costs 5.
                10, 5
            }
            for (i = 0; i < ksize; ++i)
                distanceCosts[i] = costsCopy[i];
        }

4. In tools.c there's a function called `initKeyboardData()`. It includes all the data for each keyboard, including `fingerCopy`, `rowCopy`, `homeRow`, `handCopy`, `isCenterCopy`, `isOutsideCopy`, `printItCopy`, `indicesCopy`. You'll have to create one of each of these. See tools.h for an explanation of what they each do. (In tools.h the names don't contain the word 'Copy'.) Also add this line in `initKeyboardData()`: 

        strcpy(keysToInclude, DEFAULT_KEYBOARD_BINARY);

5. Now you need to define the default keyboard. In tools.h, write

        #define DEFAULT_KEYBOARD_BINARY "<list of characters to include on the keyboard>"

6. If you want to be able to set your keyboard from the command prompt, go to accessories.c in `getCommands()`. Under the line

    } else if (streqn(cmd, "setksize ", strlen("setksize "))) {

There's a series of if/else statements that check if the user typed in the name of one of the available keyboards. Add your keyboard to the list.
   
And you're done.

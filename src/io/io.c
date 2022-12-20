//
// Created by Andrei Paul Ionescu on 30/05/2022.
//

///////////////////////////////
///// Version 0.0.2 //////////
/////////////////////////////

/// TODO: Find a good way in which to test these features and commence implementing the parser.

// Headers belonging to the standard C library.
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Headers defined within the scope of this project.
#include "io.h"

// Macro/symbolic constants of this compilation unit.
#define MAXIMUM_LENGTH_OF_LINE 1024
#define INITIAL_GROWTH_FACTOR 1

// Prototypes of the static functions contained within this compilation unit.
static int _get_line(char line[], int buffer,int starting_position, FILE *input);
static void _resize(char array[], int growth_factor);

// Global variables of the program.
int current_growth_factor = INITIAL_GROWTH_FACTOR;

// Implementations of the static functions contained within this compilation unit.
static void _resize(char array[], int growth_factor){
    /**
     * @param array[]; a character array which we wish to resize.
     * @param growth_factor; the growth_factor indicates how many times the size is going to be increased when compared
     *                       to the initial length of the array, which is defined in a symbolic constant in the unit.
     *
     * This here method resizes a given array by temporary allocating the necessary memory to a temporary location in
     * memory, in which it then copies all the values of the current array and then it alters the referenes so that
     * array now points to the newly allocated area and thus the program concludes by liberating/freeing the
     * previously occupied memory zones, thus mutating the array object.
     *
     * @since 0.0.1
     * @version 0.0.1
     * @author Andrei-Paul Ionescu
     */

    // Make sure that the addressed which is communicated to the function is properly reserved.
    assert(array);

    // Create a temporary zone in the memory whose size is the MAXIMUM_LENGTH_OF_LINE multiplied with the current
    // growth factor.
    char *temporary = malloc(growth_factor * MAXIMUM_LENGTH_OF_LINE);

    // Check to see whether or not the program was able to reserve the memory.
    if(temporary == NULL) abort(); // Since the function does not return anything simply abort;

    // Copy all the content of the current array to the memory zone indicated by the temporary pointer.
    strcpy(temporary, array);

    // Vacant the memory occupied by array.
    free(array);

    // Mutate the array pointer so that now it points to the newly created and instantiated memory zone.
    array = temporary;

}

static int _get_line(char line[], int buffer, int starting_position, FILE *input){
    /**
     * @param line[]; a character array for which, this function assumes, the memory was properly reserved.
     * @param buffer; the maximal number of characters which are to be read and rendered as a line.
     *
     * This here method reads a number of characters specified by the buffer parameter and copies them within the
     * line array; the method yields 0 if the line contained no characters or an positive integer which represents the
     * number of characters which were present within the line.
     *
     * In addition to all this, if the program runs of out of space and a new line had not been reached then the buffer
     * will be doubled in size and the reading will continue until either a '\n' or EOF is encountered.
     *
     * @since 0.0.1
     * @version 0.0.1
     * @author Andrei-Paul Ionescu
     */
    char c;
    int i;
    for(i = starting_position ; i < buffer - 1 && (c = fgetc(input)) != EOF && c!='\n'; ++i)
        line[i] = c;

    if(c == '\n'){
        // If the last character in the sequence of characters read is the new line character then add it to the line,
        // increment the counter and move to the end phase of the procedure which attaches the null character and
        // concludes the method.
        line[i] = c;
        ++i;
    } else if(c == EOF){
        // Nothing happens if EOF was encountered.
    }
    else{
        // If not, then it means that neither the EOF or the new line character were encountered and therefore the
        // line has not concluded, thus since the already reserved memory is occupied in entirety we have to
        // dynamically adjust our array and update our growth factor and then commence the _get_line process once more
        // this time with the updated buffer, line array and starting position.
        _resize(line, ++current_growth_factor);
        _get_line(line, buffer*current_growth_factor, i, input);
    }

    line[i] = '\0';
    return i;
}

// Implementation of the extern functions which are specified within the associated header of this compilation unit.
extern void read_file(const char *path){
    /**
     * @param path; a constant string literal which indicates the location where the file is stored.
     *
     * This here method initialises the reading process and it handles the interpretation of the lines read.
     *
     * @since 0.0.2
     * @version 0.0.1
     * @author Andrei-Paul Ionescu
     */

     // Determine whether the input given to this method is valid or not.
    assert(path);

    // Instantiate a new FILE object which will we will use so as to retrieve the information stored within the target
    // file.
    FILE *input = fopen(path, "r");

    // Check to see whether any errors had occurred whilst opening the file.
    if(input == NULL) abort();

    printf("%s", );
}
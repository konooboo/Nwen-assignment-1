#include <stdio.h>
#include "editor.h"
#include <string.h>



/**
 * Task 1.
 * Insert a charater in the editing buffer.
 * @param editing_buffer Editing buffer
 * @param editing_buflen Length of editing buffer in bytes
 * @param to_insert Character to insert
 * @param pos Index where insertion should occur
 * @return 1 if the insertion occurred, otherwise 0
 * // search the array
 */

int editor_insert_char(char editing_buffer[], int editing_buflen, char to_insert, int pos)
{ 
	if(pos<0 || pos >= editing_buflen || editing_buffer[editing_buflen- 1] != '\0'){ //check the second to last chart is not a null terminator
		return 0;
	}

	for (int i = editing_buflen - 1; i >= pos; i--){
		//work through the array from the last element, moving every elememt to the right until position
		editing_buffer[i+1] = editing_buffer[i];
	}

	editing_buffer[pos] = to_insert;

	return 1;

}

/**
 * Task 2.
 * Delete the first occurrence of the character in the editing buffer.
 * @param editing_buffer Editing buffer
 * @param editing_buflen Length of editing buffer in bytes
 * @param to_delete Character to delete
 * @param offset Index to start searching for the character to delete
 * @return 1 if the deletion occurred, otherwise 0
 */

int editor_delete_char(char editing_buffer[], int editing_buflen, char to_delete, int offset)
{
	if (offset >= editing_buflen|| offset < 0){
		return 0; 
	}

	int found = 0;
	for (int i = offset; i < editing_buflen; i++){ //search for the index of chararacter to delete
		if (editing_buffer[i] == to_delete){
			offset = i;
			found = 1; //value is in the array,break
			break;
		}
	}

	if (found){
		for (int i = offset; i < editing_buflen; i++){
			editing_buffer[i] = editing_buffer[i+1];
			//moves every element after offset, which is now the index of what we want to delete, left 

		}

	}


	editing_buffer[editing_buflen -2] = '\0'; // -2 to account for the one less character in array

	return found;

}


//replaces first occurence of str wih replacement
// search for the string in the list
// if the string is in the list, check the size of the string compared to the one that needs to be inserted
// if the inserted string is bigger, move every element after str to the right, throw oout any characters that dont fit in the buffer
// if it is smaller, mover every elemnt after to the left, inserting null character in the position
// if replacement is empty, this is equvalent to deleting the string
// if replacement has occured, return the index of the last letter of replacemet


int  editor_replace_str(char editing_buffer[], int editing_buflen, const char *str, const char *replacement, int offset)
{
	char *first_pos = strstr(editing_buffer + offset, str); 
	//returns pointer to first occurence of str in the array, after offset

	if (offset >= editing_buflen || offset < 0 || strlen(str) == 0 || first_pos == NULL){
		return -1;
	}

	int old_length = strlen(str);
	int new_length = strlen(replacement);
    int index = first_pos - editing_buffer;
    //gives position of str, relative to start of editing buffer array

    // Adjust the length of the replacement if it exceeds limits
    if (index + new_length >= editing_buflen) {
        new_length = editing_buflen - index - 1;  // Leave space for null terminator
    }

    // Delete the old string
    for (int i = 0; i < old_length; i++) {
        editor_delete_char(editing_buffer, editing_buflen, editing_buffer[index], index);
        //only excecuted on length of string with [index]
    }

    // Insert the new string
    for (int i = 0; i < new_length; i++) {
        if (!editor_insert_char(editing_buffer, editing_buflen, replacement[i], index + i)) {
            return -1;  // Failed to insert
        }
    }

    return index + new_length - 1;  // Return the index of the last letter of the replacement
}






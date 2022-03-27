#ifndef _STSPLIT_H_
#define _STSPLIT_H_
/*
 * returns an array of character pointers, one to each word in 'line'
 * a sentinel pointer of NULL terminates the list
 *
 * the array of pointers has been allocated from the heap, and must be
 * returned to the heap by calling stfree() when done with it
 * */
char **stsplit(char *line);

/*
 * free the heap-allocated memory returned by stpslit()
 * */
void stfree(char **words);

#endif /* _STPLIT_H_ */

#ifndef BWT_H
#define BWT_H

char *bwt_encode(char *src);
// create a table, where the rows are all possible roataions of s
// sort rows alphabetically
// return (last column of the table)
char *bwt_decode(char *src);
// create empty table
// repeat strlen(src) times
// first insert creates first column
// insert s as a column of table before first column of the table
// sort rows of the table alphabetically
// return (row that ends with the 'EOF' character)

#endif

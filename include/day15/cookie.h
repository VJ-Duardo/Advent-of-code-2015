#ifndef COOKIE_H
#define COOKIE_H


#define PROPERTIES 5
int** getIngredients(char** lines, int size);
void getTotalHighestCookie(int** ingredients, int size, int curr, int* fractions, int* biggest);


#endif
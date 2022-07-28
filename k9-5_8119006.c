#include <stdio.h>


void init(char data[15][15]) {	
	int i, j;
	for ( i = 0 ; i < 15 ; i ++ ) {
		for ( j = 0 ; j < 15 ; j++ ) {
			data[i][j] = '+';	
		}
	}
	return;
}

void dump(char data[15][15]) {
	int i, j;
	char data2[16][16];
	for ( i = 1 ; i < 16 ; i++ ) {
		for ( j = 1 ; j < 16 ; j++ ) {
			data2[i][j] = data[i - 1][j - 1];
		}
	}
	for ( i = 1 ; i < 16 ; i++ ) {
		data2[0][i] = 96 + i;
	}
	for ( i = 1 ; i < 16 ; i++ ) {
		data2[i][0] = 64 + i;
	}
	data2[0][0] = ' ';
	for ( i = 0 ; i < 16 ; i++ ) {
		for ( j = 0 ; j < 16 ; j ++ ) {
			if ( j != 15 ) {
				printf("%c ", data2[i][j]);
			} else {
				printf("%c\n", data2[i][j]);
			}
		}
	}
	return;
}

int input_stone(int Turn, int *pRow, int *pColumn) {
	char input[4];
	int i, j, k;
	if ( Turn == 0 ) {
		printf("sente(@)>");
	}
	if ( Turn == 1 ) {
		printf("gote(O)>");
	}
	fgets( input, 4, stdin );
	i = input[0];
	j = input[1];
	k = input[2];
	if ( input[2] != '\n') {
		return 1;
	}
	if ( i == 90 && j == 122 ) {
		return 2;
	}
	if ( i == 82 && j == 114 ) {
		return 3;
	}
	if ( i < 65 && 79 < i ) {
		return 1;
	}
	if ( j < 97 && 111 < j ) {
		return 1;
	}
	*pRow = i - 65;		
	*pColumn = j - 97;	
	return 0;
}

int place_stone( char data[15][15], int Turn, int Row, int Column ) {
	if ( data[Row][Column] == '+' ) {
		if ( Turn == 1 ) {
			data[Row][Column] = '@';
		} else {
			data[Row][Column] = 'O';
		}	
	} else {
		return 1;
	}
	return 0;
}

int judge( int Row, int Column, char data[15][15] ) {
	int i;
	for ( i = 0 ; i < 4 ; i++ ) {
		if ( data[Row][Column] == data[Row - 4 + i][Column] && data[Row][Column] == data[Row - 3 + i][Column] && data[Row][Column] == data[Row - 2 + i][Column] && data[Row][Column] == data[Row - 1 + i][Column] && data[Row][Column] == data[Row + i][Column] ) {
			return 1;
		} 
		if ( data[Row][Column] == data[Row][Column - 4 + i] && data[Row][Column] == data[Row][Column - 3 + i] && data[Row][Column] == data[Row][Column - 2 + i] && data[Row][Column] == data[Row][Column - 1 + i] && data[Row][Column] == data[Row][Column + i] ) {
			return 1;
		}
		if ( data[Row][Column] == data[Row - 4 + i][Column - 4 + i] && data[Row][Column] == data[Row - 3 + i][Column - 3 + i] && data[Row][Column] == data[Row - 2 + i][Column - 2 + i] && data[Row][Column] == data[Row - 1 + i][Column - 1 + i] && data[Row][Column] == data[Row + i][Column + i] ) {
			return 1;
		}
		if ( data[Row][Column] == data[Row - 4 + i][Column + 4 - i] && data[Row][Column] == data[Row - 3 + i][Column + 3 - i] && data[Row][Column] == data[Row - 2 + i][Column + 2 - i] && data[Row][Column] == data[Row - 1 + i][Column + 1 - i] && data[Row][Column] == data[Row + i][Column - i] ) {
			return 1;
		}
	}
	for ( i = 0 ; i < 4 ; i++ ) {
		if ( data[Row][Column] == data[Row + 4 - i][Column] && data[Row][Column] == data[Row + 3 - i][Column] && data[Row][Column] == data[Row + 2 - i][Column] && data[Row][Column] == data[Row + 1 - i][Column] && data[Row][Column] == data[Row - i][Column] ) {
			return 1;
		} 
		if ( data[Row][Column] == data[Row][Column + 4 - i] && data[Row][Column] == data[Row][Column + 3 - i] && data[Row][Column] == data[Row][Column + 2 - i] && data[Row][Column] == data[Row][Column + 1 - i] && data[Row][Column] == data[Row][Column - i] ) {
			return 1;
		}
		if ( data[Row][Column] == data[Row + 4 - i][Column + 4 - i] && data[Row][Column] == data[Row + 3 - i][Column + 3 - i] && data[Row][Column] == data[Row + 2 - i][Column + 2 - i] && data[Row][Column] == data[Row + 1 - i][Column + 1 - i] && data[Row][Column] == data[Row - i][Column + i] ) {
			return 1;
		}
		if ( data[Row][Column] == data[Row + 4 - i][Column - 4 + i] && data[Row][Column] == data[Row + 3 - i][Column - 3 + i] && data[Row][Column] == data[Row + 2 - i][Column - 2 + i] && data[Row][Column] == data[Row + 1 - i][Column - 1 + i] && data[Row][Column] == data[Row - i][Column + i] ) {
			return 1;
		}
	}

	return 0;
}

int main(void) {
	int Input, Place, Turn = 0, Row, Column;
	int Judgement;
	char Board[15][15];
	init( Board );
	dump( Board );
	while ( 1 ) {
		Input = input_stone( Turn, &Row, &Column );
		if ( Input == 0 ) {
			Place = place_stone( Board, Turn, Row, Column );
			if ( Place == 0 ) {
				dump(Board);
				Judgement = judge( Row, Column, Board ); 	
				if ( Judgement == 1 && Turn == 1 ) {
					printf("Winner: sente(@)\n");
					return 0;
				}
				if ( Judgement == 1 && Turn == 0 ) {
					printf("Winner: gote(O)\n");
					return 0;
				}
				if ( Turn == 1 ) {
					Turn = 0;
				} else {
					Turn = 1;
				}

			}
		} else if ( Input == 2 ) {
			return 0;
		} else if ( Input == 3 ) {
			dump( Board );
		}
	}
	return 0;
}


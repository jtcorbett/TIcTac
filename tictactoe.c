// made by John Corbett 2011

#define USE_TI89

#include <tigcclib.h>

#define px 1
#define po 2

#define EMPTY(x) ((x) == 0)
#define WIN0 ((board[0] == board[1] & board[1] == board[2]) & (board[0] != 0))
#define WIN1 ((board[3] == board[4] & board[4] == board[5]) & (board[3] != 0))
#define WIN2 ((board[6] == board[7] & board[7] == board[8]) & (board[6] != 0))
#define WIN3 ((board[0] == board[3] & board[3] == board[6]) & (board[0] != 0))
#define WIN4 ((board[1] == board[4] & board[4] == board[7]) & (board[1] != 0))
#define WIN5 ((board[2] == board[5] & board[5] == board[8]) & (board[2] != 0))
#define WIN6 ((board[0] == board[4] & board[4] == board[8]) & (board[0] != 0))
#define WIN7 ((board[2] == board[4] & board[4] == board[6]) & (board[2] != 0))
#define WIN (WIN0 | WIN1 | WIN2 | WIN3 | WIN4 | WIN5 | WIN6 | WIN7)

typedef enum {
	upperLeft = '7',
	upperMiddle,
	upperRight,
	middleLeft = '4',
	middleMiddle,
	middleRight,
	lowerLeft = '1',
	lowerMiddle,
	lowerRight
} Position;

int ptoi(Position pos) {
	switch (pos) {
		case upperLeft:
			return 0;
		case upperMiddle:
			return 1;
		case upperRight:
			return 2;
		case middleLeft:
			return 3;
		case middleMiddle:
			return 4;
		case middleRight:
			return 5;
		case lowerLeft:
			return 6;
		case lowerMiddle:
			return 7;
		case lowerRight:
			return 8;
			break;
		default:
			break;
	}
	return 0;
}

const unsigned long X[] = {
	0xA0000003,
	0x3000000A,
	0x0A000030,
	0x030000A0,
	0x00A00300,
	0x00300A00,
	0x000A3000,
	0x0003A000,
	0x0003A000,
	0x000A3000,
	0x00300A00,
	0x00A00300,
	0x030000A0,
	0x0A000030,
	0x3000000A,
	0xA0000003
};

const unsigned long O[] = {
	0x00008000,
	0x00036000,
	0x00063000,
	0x000C1800,
	0x00180C00,
	0x00300600,
	0x00600300,
	0x00C00180,
	0x00C00180,
	0x00600300,
	0x00300600,
	0x00180C00,
	0x000C1800,
	0x00063000,
	0x00036000,
	0x00008000
};

void drawBoard() {
	DrawLine(53, 0, 53, 100, A_NORMAL);
	DrawLine(54, 0, 54, 100, A_NORMAL);
	DrawLine(52, 0, 52, 100, A_NORMAL);
	
	DrawLine(106, 0, 106, 100, A_NORMAL);
	DrawLine(107, 0, 107, 100, A_NORMAL);
	DrawLine(105, 0, 105, 100, A_NORMAL);
	
	DrawLine(0, 33, 160, 33, A_NORMAL);
	DrawLine(0, 32, 160, 32, A_NORMAL);
	DrawLine(0, 31, 160, 31, A_NORMAL);
	
	DrawLine(0, 66, 160, 66, A_NORMAL);
	DrawLine(0, 65, 160, 65, A_NORMAL);
	DrawLine(0, 64, 160, 64, A_NORMAL);
}

void draw(Position	pos, char sprite) {
	int x, y;
	
	if ((pos >= upperLeft) & (pos <= upperRight))
		y = 8;
	else if ((pos >= middleLeft) & (pos <= middleRight))
		y = 41;
	else if ((pos >= lowerLeft) & (pos <= lowerRight))
		y = 74;
	
	switch (pos) {
		case upperLeft:
		case middleLeft:
		case lowerLeft:
			x = 10;
			break;
		case upperMiddle:
		case middleMiddle:
		case lowerMiddle:
			x = 63;
			break;
		case upperRight:
		case middleRight:
		case lowerRight:
			x = 116;
			break;			
		default:
			break;
	}
	if (sprite == 'x')
		Sprite32(x, y, 16, X, LCD_MEM, SPRT_XOR);
	else
		Sprite32(x, y, 16, O, LCD_MEM, SPRT_XOR);

}

void welcomeScreen() {
	puts("Tic-Tac-Toe v1.0
by John Corbett\n
(press any key)");
	
	ngetchx();
	clrscr();
}

void _main(void) {
	clrscr();
	
	welcomeScreen();
	
	unsigned short retry;
	
	do {	
		clrscr();
		unsigned short board[9];
		short player = px;
		
		int i = 0;
		
		for (i = 0; i < 9; i++)
			board[i] = 0;
		
		drawBoard();
		
		i = 0;

			
		while (i < 9) {
			char playerz;
			if (player == px)
				playerz = 'x';
			else
				playerz = 'o';
			
			Position pos;
			
			pos = (Position) ngetchx();
			
			if (EMPTY(board[ptoi(pos)]) & pos >= '1' & pos <= '9') {
				draw(pos, playerz);
				board[ptoi(pos)] = player;
				if (player == px)
					player = po;
				else
					player = px;
				i++;
			}
			unsigned short x1, y1, x2, y2;
			
			if (WIN0) {
				x1 = 26;
				x2 = 134;
				y1 = y2 = 16;
			}
			else if (WIN1) {
				x1 = 26;
				x2 = 134;
				y1 = y2 = 50;
			}
			else if (WIN2) {
				x1 = 26;
				x2 = 134;
				y1 = y2 = 84;
			}
			else if (WIN3) {
				x1 = x2 = 26;
				y1 = 16;
				y2 = 84;
			}
			else if (WIN4) {
				x1 = x2 = 80;
				y1 = 16;
				y2 = 84;
			}
			else if (WIN5) {
				x1 = x2 = 114;
				y1 = 16;
				y2 = 84;
			}
			else if (WIN6) {
				x1 = 26;
				x2 = 134;
				y1 = 16;
				y2 = 84;
			}
			else if (WIN7) {
				x1 = 134;
				x2 = 26;
				y1 = 16;
				y2 = 84;
			}
			if (WIN) {
				DrawLine(x1, y1, x2, y2, A_NORMAL);
				DrawLine(x1+1, y1+1, x2+1, y2+1, A_NORMAL);
				DrawLine(x1-1, y1-1, x2-1, y2-1, A_NORMAL);
				break;
			}
		}
		
		ngetchx();
		clrscr();
			
		puts("Play Again?\n(1 = YES / 2 = NO): ");
		retry = ngetchx();
	
	} while (retry == '1');
	
	
	clrscr();
}

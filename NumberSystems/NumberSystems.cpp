// NumberSystems - програма переводу чисел в різні системи числення
//

#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

char* DecToBin(int); // 10 -> 2
int BinToDec(char*); // 2 -> 10

char* DecToHex(int); // 10 -> 16
int HexToDec(char*); // 16 -> 10

char* BinToHex(char*); // 2 -> 16
char* HexToBin(char*); // 16 -> 2
void RulesOfHex(int, char*, char*);

void gotoxy(int, int);
//char buf[15];
int main(){
	char num[15], result[15] = "";
	double num1 = 0, choice;
	setlocale(LC_ALL, "Rus");
	cout << "Выберите режим(1. 10->2; 2. 10->16; 3. 2->10; 4. 16 -> 10): ";
	cin >> choice;
	if (choice == 1) {
		do {
			cin >> num1;
		} while (num1>16383);

		for (int i = 0; i < strlen(DecToBin(num1)); i++)
		{
			result[i] = DecToBin(num1)[i];
		}
		cout << result << endl;
	}
	else
	if (choice == 2)
	{
		cin >> num1;
		for (int i = 0; i < strlen(DecToHex(num1)); i++)
		{
			result[i] = DecToHex(num1)[i];
		}
		cout << result << endl;
	}
	else
	if (choice == 3) {
		cin >> num;
		cout << BinToDec(num);
	}
	else
	if (choice == 4)
	{
		cin >> num;
		cout << HexToDec(num);
	}
	else
	if (choice == 5)
	{
		cin >> num;
		BinToHex(num);
	}
	else
	if (choice == 6)
	{
		cin >> num;
		HexToBin(num);
	}
	system("pause");
	return 0;
}

int BinToDec(char* value)  // вводимо строку - число в двійковій системі, на виході отримуємо ціле число в 10-вій системі
{
	int f = 0;
	int d = 0;
	int len = strlen(value);

	for (int i = len - 1, j = 0; i >= 0; i--)
	{
		char c = value[i];
		if (int(c) == 48) d = 0; else d = 1;
		f += d*pow(2, j);
		j++;
	}
	return f;
}

char* DecToBin(int num) // вводимо число в десятковій системі, на виході отримуємо рядок - число у двійковій системі
{                       // max = 16383
	int ost;
	char bin[15] = "", bin2[15] = "";
	do
	{
		ost = num % 2; // остача від ділення
		itoa(ost, bin2, 10); strcat(bin, bin2);
		num = num / 2;
	} while (num >= 2);
	itoa(num, bin2, 10); strcat(bin, bin2);
	strrev(bin); // виводимо у зворотному порядку
	// cout << bin;
	return bin;
}

char* DecToHex(int num) // вводимо число в 10-вый системі числення, на виході - число в 16-вій системі, число у вигляді рядка
{                       // max = 2000000000
	int ost;
	char hex[15] = "", hex2[15] = "";
	do
	{
		ost = num % 16; // остача від ділення
		RulesOfHex(ost, hex, hex2);
		num = num / 16;
	} while (num > 16);
	RulesOfHex(num, hex, hex2);
	strrev(hex); // виводимо у зворотному порядку
	if (hex[0] == '0'){
		for (int i = 0; i < strlen(hex); i++)
			hex[i] = hex[i + 1];
	}
	return hex;
}

int HexToDec(char* value)  // вводимо строку - число в 16-ій системі, на виході отримуємо ціле число в 10-вій системі
{
	int f = 0;
	int d = 0;
	int len = strlen(value);
	char k[10] = "";
	for (int i = len - 1, j = 0; i >= 0; i--)
	{
		char c = value[i];
		switch (c)
		{
		case 'A': {d = 10; break; }
		case 'B': {d = 11; break; }
		case 'C': {d = 12; break; }
		case 'D': {d = 13; break; }
		case 'E': {d = 14; break; }
		case 'F': {d = 15; break; }
		default:{ k[0] = c;  d = atoi(k); break; }
		}
		f += d*pow(16, j);
		j++;
	}
	return f;
}

char* BinToHex(char* value) // вводимо число в 10-вый системі числення, на виході - число в 16-вій системі, число у вигляді рядка
{
	char result[15] = "";
	int k = BinToDec(value);
	for (int i = 0; i < strlen(DecToHex(k)); i++)
	{
		result[i] = DecToHex(k)[i];
	}
	cout << result;
	return result;
}

char* HexToBin(char* value) // вводимо число в 10-вый системі числення, на виході - число в 16-вій системі, число у вигляді рядка
{                           // max = 3FFF
	char result[15] = "";
	int k = HexToDec(value);
	for (int i = 0; i < strlen(DecToBin(k)); i++)
	{
		result[i] = DecToBin(k)[i];
	}
	cout << result;
	return result;
}

void RulesOfHex(int value, char *st1, char *st2)
{
	switch (value)
	{
	case 10: {strcat(st1, "A"); break; }
	case 11: {strcat(st1, "B"); break; }
	case 12: {strcat(st1, "C"); break; }
	case 13: {strcat(st1, "D"); break; }
	case 14: {strcat(st1, "E"); break; }
	case 15: {strcat(st1, "F"); break; }
	default: {itoa(value, st2, 10); strcat(st1, st2); }
	}
}



void gotoxy(int xpos, int ypos)
{
	COORD scrn; // Объявление необходимой структуры

	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE); // Получение дескриптора устройства стандартного вывода

	scrn.X = xpos; scrn.Y = ypos; // Установка координат

	SetConsoleCursorPosition(hOuput, scrn); // Перемещение каретки по заданным координатам
}

/*int DecToBin(int x1)
{
int  b;
long c = 0;
for (int i = 0; x1 > 0; i++)
{
b = x1 % 2;
x1 = (x1 - b) / 2;
c += b * pow(10, i);

}

return c;
}
*/
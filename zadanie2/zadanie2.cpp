// dzad2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
// вариант 17 ПУШКИН 
//Циклический сдвиг
//вправо 2
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;
//0000 0000  0000 0000 --2 байта 
int main(int argc, const char* argv[]) {
	if (argc != 3) {
		cerr << "Error: Use three parameters\n";
		return 5;
	}

	const string mode(argv[1]); // Режим работы
	const string file_name(argv[2]); // Имя файла
	ofstream file; // ofstream предназначен для вывода или записи файлов.
	ifstream file1; //ifstream предназначен для ввода или чтения файлов.
	if (mode == "encryption") {
		// Режим шифрование

		string text;
		int password;
		cout << "write text which we will encrypt BUT 2 char:";
		getline(cin, text);
		if (text.length() != 2) { cout << "incorect vvod"; }
		cout << endl << "write password key :";
		cin >> password;
		srand(password);
		int chislo = 0; // для перевода текста в число 
		for (unsigned int i = 0; i < text.length(); i++)
		{
			int   number = static_cast<int>(text[i]);// char  >> int 

			//char 1 байт а текст из 2 символов поэтому 1 символ умножим на 2
			if (i == 0)
			{
				number *= (int)pow(2, 8);
			}
			chislo += number;
		}

		chislo = chislo ^ rand();
		int kray = chislo % 2; // иначе при сдвиге потеряется последний
		int predkray = (chislo % 4 - kray) / 2; //  остатком от 4 получим последнии два вычтем последний и 
		// и теперь либо 00  либо 10 и возьмем целую часть от 2 >> либо 0 либо 1 соответственно 
		chislo = chislo >> 2;
		chislo = (predkray * pow(2, 15)) + (kray * pow(2, 14)) + chislo; // крайний станет вторым предкрай ( второй с конца ) первым 




		file.open(file_name, ios::binary); //ios::binary	Открытие файла для двоичных операций ввода-вывода 
		file << chislo;
		file.close();

	}


	else if (mode == "decryption") {
		// Режим расшифрования

		int password2;
		cout << endl << "write password key :";
		cin >> password2;
		srand(password2);

		//пока в файле число только в файле 
		//расшифрованные данные из файла выводятся на консоль
		file1.open(file_name, ios::binary);
		int chislo;
		file1 >> chislo;
		//2 сдвига влево 
		// надо сохранить первые 2 цифры в двоичном виде 

		int first = chislo / (int)pow(2, 15);
		int second = (int)(chislo / pow(2, 14)); // 2 первые получили при делении на 2^14  поэтому возьмем остаток 
		second = second % 2;
		chislo = chislo << 2; // справа 00 
		chislo = chislo + (first * 2) + second; // first станет вторым с конца поэтому на 2 умножение 

		// теперь число правильное после цикл сдвига 
		chislo = chislo ^ rand(); // xor и есть обратная функция к xor из encrypt 
		// осталось число перевести в стринг 
		//0000 0000 0000 0000 

		char number1 = chislo / (int)pow(2, 8);
		char  number2 = chislo % (int)pow(2, 8);
		cout << number1 << number2;

	}
	return 0;

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"
// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

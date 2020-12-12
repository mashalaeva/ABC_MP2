/* Вариант 5: 
* (27 % 22 = 5)
* Задача о каннибалах.
* Племя из n дикарей ест вместе из большого горшка,
* который вмещает m кусков тушеного миссионера. Когда
* дикарь хочет обедать, он ест из горшка один кусок,
* если только горшок не пуст, иначе дикарь будит повара
* и ждет, пока тот не наполнит горшок. Повар, сварив
* обед, засыпает. Создать многопоточное приложение,
* моделирующее обед дикарей. При решении задачи
* пользоваться семафорами.
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <thread>
#include <mutex>
#include <exception>
#include <ctime>   

// Имя входного файла.
std::string input;
// Максимальное количество кусков тушеного
// миссионера.
int m;
// Количество кусков миссионера в горшке
// на данный момент.
int currentNumOfPeices;
// Количество каннибалов в племени.
int n;
// Вектор для хранения порядка номеров каннибалов,
// которые едят из горшка.
std::vector<int> currentCannibalNumber;
// Количество исполняемых потоков, эквивалентное
// числу строчек с командами в исходном файле.
int numberOfThreads;
// Двоичный семафор mutex для обработки критических
// секций.
std::mutex mut;

/// <summary>
/// Функция для проверки входных параментов 
/// main'а.
/// </summary>
/// <param name="argc"> - количество аргументов</param>
/// <param name="argv"> - массив аргументов</param>
/// <returns>возвращает true, если входные
/// данные корректны</returns>
bool checkArguments(const int& argc, char* argv[])
{
	// Если количество введенных параметров меньше
	// нужного количества, сообщаем об этом пользователю
	// и возвращаем false.
	if (argc != 2) {
		std::cout << "An invalid format of input params!\n"
			"Use the name of an input file as the first value.\n\n"
			"P.S.\n"
			"- The first string in the file consists of two numbers:\n"
			"     m - maximum number of missionary's pieces;\n"
			"     n - number of cannibals in one tribe\n"
			"  *n should be integer value > 0, because there should\n"
			"  be at least one cannibal*;\n\n"
			"- All other strings in the file are commands, which\n"
			"  have type of \"cannibal N is hungry\", where N is\n"
			"  number of cannibal in tribe; N is integer value in\n"
			"  range of [1, n].\n"
			"\n--------------------------------------------------------\n\n";
		return false;
	}
	input = argv[1];
	return true;
}

/// <summary>
/// Функция, демострирующая обед
/// одного каннибала.
/// </summary>
/// <param name="currentCommandDigit"> - 
/// индекс строки из файла, с помощью
/// которого можно узнать, номер какого
/// каннибала передавался в этой строчке.</param>
void feedHungryCannibal(const int& currentCommandDigit)
{
	// Начало критической секции.
	mut.lock();

	// Если номер каннибала под переданным индексом
	// не подходит, выводим соответствующее сообщение.
	if (currentCannibalNumber[currentCommandDigit] > n
		|| currentCannibalNumber[currentCommandDigit] < 1)
	{
		std::cout << "EVENT " << currentCommandDigit + 1
			<< "! (which ID is " << std::this_thread::get_id() << 
			")\n\nGreat pitty! Cannibal " << 
			currentCannibalNumber[currentCommandDigit] <<
			" does not leave\nin this tribe, he cannot eat "
			"missionary's\nmeat with other savages...\n"
			"\n----------------------------------------------\n\n";
		// Преждевременный конец критической секции.
		mut.unlock();
		return;
	}

	std::cout << "EVENT " << currentCommandDigit + 1
		<< "! (which ID is " << std::this_thread::get_id() << 
		")\n\nCannibal " << currentCannibalNumber[currentCommandDigit] <<
		" had a meal.\nNow there are "
		<< --currentNumOfPeices <<
		" pieces of stewed missionary.\n"
		"\n----------------------------------------------\n\n";

	// Конец критической секции.
	mut.unlock();
}

/// <summary>
/// Функция для заполнения горшочка
/// в случае, если тот пуст.
/// </summary>
void cookDinner()
{
	// Начало критической секции.
	mut.lock();

	// Возобновляем количество кусков
	// миссионера в горшочке.
	currentNumOfPeices = m;
	std::cout << "UNEXPECTED EVENT! (which ID is " 
		<< std::this_thread::get_id() <<
		")\n\nThere aren't any food in the pot.\n"
		"We woke up a cook. He made new portion\n"
		"of stewed missionary and went to sleep again...\n"
		"\n----------------------------------------------\n\n";
	
	// Конец критической секции.
	mut.unlock();
}

/// <summary>
/// Функция для работы с потоками.
/// </summary>
void workWithThreads()
{
	// Инициализируем вектор потоков.
	std::vector<std::thread> threads(numberOfThreads);

	// Цикл, вызывающий соответствующую 
	// функцию для работы каждого потока.
	for (int i = 0; i < numberOfThreads; ++i) {

		// Если горшочек пуст, то заполняем 
		// его с помощью нового потока,
		// олицетворяющего повора.
		if (currentNumOfPeices <= 0)
		{
			// Динамически выделяем память
			// для нового потока-повора.
			std::thread* cook = new std::thread(cookDinner);
			cook->join();
			// Очищаем память.
			delete cook;
		}
		// Вызываем для потока функцию feedHungryCannibal.

		threads[i] = std::thread(feedHungryCannibal, i);
		threads[i].join();
	}
}

/// <summary>
/// Функция для считывания информации
/// из входного файла.
/// </summary>
void workWithFiles()
{
	// Поток для считывания информации из файла.
	std::ifstream in;
	in.open(input, std::ios::in);

	if (!in.is_open())
	{
		// Если не удалось открыть файл.
		std::cout << "Opening of the file failed!\n";
	}
	else
	{
		int piecesOfMissionary, numOfCannibals;
		// Считываем максимальное количество кусков
		// миссионера и количество голодных каннибалов
		// из файла.
		in >> piecesOfMissionary >> numOfCannibals;
		m = piecesOfMissionary;
		n = numOfCannibals;

		std::string word;
		while (in >> word)
		{
			// Нас интересует только номер каннибала,
			// поэтому считывание других слов можно
			// сделать с использованием уже созданной
			// переменной std::string word.
			int number;
			in >> number >> word >> word;
			// Добавляем номер каннибала в список
			// (вектор currentCannibalNumber),
			// размер которого равен количеству
			// строчек с командами в исходном файле.
			currentCannibalNumber.push_back(number);
		}
		// Количество потоков приравниваем
		// к количеству считанных из файла
		// команд.
		numberOfThreads = currentCannibalNumber.size();
	}
	in.close();
}

int main(int argc, char* argv[])
{
	srand(time(0));
	std::cout << "\n\n---------------------"
		"-------------------------\n\n";
	if (!checkArguments(argc, argv))
		exit(0);
	workWithFiles();
	workWithThreads();

	// Выведем время работы программы.
	std::cout << "Time of program working = "
		<< clock() / 1000.0 << " sec\n\n"
		"----------------------------------------------\n\n";

	return 0;
}

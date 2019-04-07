#include <iostream>
#include <time.h>
#include <algorithm>

using namespace std;

struct LinearList { //структура данных, элемент списка
	int data; //данные элемента списка
	int index; //его индекс в списке
	LinearList *prev; //указатель на предыдущий элемент списка
	LinearList *next; //указатель на следующий элемент списка
}* HEAD = NULL; //указатель на голову списка, сразу обнуляем, так как пока список пуст

int sizeList() { //функция возвращающая размер списка
	if (HEAD == NULL) return 0; //если список пуст, то его размер 0
	int size = 0;
	LinearList *item = HEAD; //указатель на начало списка
	while (item->next != HEAD) { //обходим список от начала до конца
		size++; //увеличиваем размер
		item = item->next; //перехожим к след. элементу
	}
	return size++; //возвращаем размер списка
}

void addNode(int data, int pos) { //добавление элемента в список
	LinearList *item = new LinearList; //выделили память под новый элемент списка
	item->data = data; //присвоили элементу данные
	if (HEAD == NULL) { //если список пустой
		item->next = item; //то наш элемент становится началом списка
	    item->prev = item;
		HEAD = item;
	}
	else {
		LinearList *tmp = HEAD;
		//иначе пробегаем по списку до последнего эемента
		for (int i = pos; i > 1; i--)
			tmp = tmp->next;
		//добавляем элемент в список между предыдущим и следующим
		tmp->prev->next = item; 
		item->prev = tmp->prev;
		item->next = tmp; 
		tmp->prev = item; 
	}
	item->index = sizeList(); //присваиваиваем индексу последнего элемента размер списка
}

void deleteNode(int pos) { //удаление элемента из списка
	if (HEAD == NULL) { //если начала списка указывает на ноль, то список пуст
		cout << "List is empty\n"; //и удалять нечего
		return; 
	}
	if (HEAD == HEAD->next) { //если в списке всего 1 элемент, то удаляем его
		delete HEAD; 
		HEAD = NULL;
	}
	else {
		LinearList *tmp = HEAD;
		for (int i = pos; i > 1; i--)  //пробегаем список до элемента с нужным индексом
			tmp = tmp->next;
		if (tmp == HEAD) //если это первый элемент 
			HEAD = tmp->next; //то указатель на следующий элемент списка это начало списка
		tmp->prev->next = tmp->next; //удаляем указатель на следующий элемент от текущего
		tmp->next->prev = tmp->prev; //удаляем указатель на предыдущий элемент от текущего
		delete tmp; //удаляем сам элемент
	}
}


void output() { //функция вывода списка на экран
	if (sizeList() == 0) { //если размер списка 0
		cout << "List is empty" << endl; //то выводим сообщение что он пустой
	}
	else {
		LinearList *item = HEAD; 
		for (int i = sizeList(); i > 0; i--) { //пробегаем список от начала до конца
			cout << item->data << ' '; //выводим данные каждого элемента
			item = item->next;
		}
		cout << endl;
	}
}

void rand_fil(int amount) { //заполняем список случайными данными
	for (int i=0; i < amount; i++)
		addNode(rand() % 100 - (double)(rand() % 100000) / 100000,i);
}

void rand_fil_small_val(int amount) { //заполняем список случайными данными с малым разбросом, то есть почти отсортированными
	double a = rand() % 10000;
	for (int i=0; i < amount; i++) {
		if (rand() % 3 == 1)
			addNode(rand() % 10000, i);
		else
			addNode(a += rand() % 20, i);
	}
}

void rand_fil_reverse(int amount) { //заполняем список случайными данными в обратном порядке
	double a = 50000;
	for (int i =0; i<amount; i++)
		addNode(a -= rand() % 75, i);
}

LinearList* getNode(int idx) { //функция, возвращающая элемент списка по указанному индексу 
	LinearList *item = HEAD;
	for (int i = idx; i > 0; i--) //обходим список до нужной нам позиции
		item = item->next;
	return item; //возвращаем найденный элемент
}

void clearList() { //функция очистки списка
	for (int i =sizeList(); i > 0; i--) //пробегаем весь список и удаляем все узлы
		deleteNode(i);
}




void ShellsSort() { //сортировка Шелла
	unsigned i,j,step; //переменные циклов и шаг
	int tmp; //переменная для обмена данными
	for (step = sizeList() / 2; step > 0; step /= 2) //сортируем уменьшая шаг пополам
		for (i = step; i < sizeList(); i++) { //сортируем элементы
			tmp = getNode(i)->data; //записали в tmp данные i-го узла
			for (j = i; j >= step; j -= step) { //сравниваем его с данными элемента, находящегося на расстоянии шага от него
				if (tmp < getNode(j - step)->data) //если этот данные этого элемента меньше j-го
					getNode(j)->data = getNode(j - step)->data; //то меняем их местами
				else
					break;
			}
			getNode(j)->data = tmp; //меняем местами
		}
}


int main() {
	srand(time(NULL));
	//предлагается выбрать вариант заполнения списка
	cout << "Please choose method to fill list:" << endl;
	cout << "Filling with random sizeListbers: (1)" << endl;
	cout << "Filling with almost sorted sizeListbers: (2)" << endl;
	cout << "Filling with reverse sorted sizeListbers: (3)" << endl;
	int n, k;
	//защита ввода
	while (!(cin >> n) || n < 1 || n > 3 || (cin.peek() != '\n')) {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Incorrect method! Try again!" << endl;
	}
	//предлагается выбрать размер списка
	cout << "And now, please input amount of sizeListbers: " << endl;
	//защита ввода
	while (!(cin >> k) || k < 0 || (cin.peek() != '\n')) {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Incorrect value of amount! Try again!" << endl;
	}
	//в зависимости от выбора список заполняется
	if (n == 1)
		rand_fil(k);
	if (n == 2)
		rand_fil_small_val(k);
	if (n == 3)
		rand_fil_reverse(k);

	cout << "List: " << endl;
	output(); //выводится на экран сам список
	double time = clock(); //счетчик времени
	cout << "Sorted list:" << endl;
	ShellsSort(); //сортируем список
	output(); //выводим его на экран
	cout << " Time: " << (clock() - time) / CLOCKS_PER_SEC << endl; //выводим время его сортировки
	system("pause");
}
#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> 
#include <cstdlib>
#include <ctime>
using namespace std;
enum Spec { KN, ME, IT };
string specStr[] = { "КН", "МЕ", "ІТ" };
struct Students
{
	string prizv;
	int kurs;
	Spec spec;
	int phyg;
	int mag;
	int ing;
	union
	{
		int prog;
		int chmg;
		int pedg;
	};
};
void Create(Students* s, const int N);
void Print(Students* s, const int N);
void Sort(Students* s, const int N);
int* IndexSort(Students* s, const int N);
void PrintIndexSorted(Students* s, int* I, const int N);
int BinSearch(Students* s, const int N, const string prizv, const Spec spec, const int ing);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand((unsigned)time(NULL));
	int N;
	cout << "Введіть N: "; cin >> N;
	Students* s = new Students[N];
	string prizv;
	int kurs;
	int ispec;
	Spec spec;
	int phyg;
	int mag;
	int ing = 0;
	int found;
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - фізичне впорядкування даних" << endl;
		cout << " [4] - індексне впорядкування та вивід даних"
			<< endl;
		cout << " [5] - бінарний пошук працівника за посадою та прізвищем" << endl << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(s, N);
			break;
		case 2:
			Print(s, N);
			break;
		case 3:
			Sort(s, N);
			break;
		case 4:
			PrintIndexSorted(s, IndexSort(s, N), N);
			break;
		case 5:
			cout << "Введіть ключі пошуку:" << endl;
			cout << " спеціальність(0-KH, 1-ME, 2-IT): ";
			cin >> ispec;
			spec = (Spec)ispec;
			cin.get();
			cin.sync();
			cout << " прізвище: "; getline(cin, prizv);
			cout << " оцінка 3-го предмету: "; cin >> ing;
			if ((found = BinSearch(s, N, prizv, spec, ing)) != -1)
				cout << "Знайдено студента в позиції " << found + 1 << endl;
			else
				cout << "Шуканого студента не знайдено" << endl;
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	return 0;
}
void Create(Students* s, const int N)
{
	int spec;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;
		cin.get();
		cin.sync();

		cout << " прізвище: "; getline(cin, s[i].prizv);
		cout << " курс: "; cin >> s[i].kurs;
		cout << " спеціальність(0-KH, 1-ME, 2-IT): ";
		cin >> spec;
		s[i].spec = (Spec)spec;
		s[i].phyg = rand() % 4 + 2;
		s[i].mag = rand() % 4 + 2;
		s[i].ing = rand() % 4 + 2;
		switch (s[i].spec)
		{
		case KN:
			s[i].prog = rand() % 4 + 2;
			break;
		case IT:
			s[i].chmg = rand() % 4 + 2;
		case ME:
			s[i].pedg = rand() % 4 + 2;
			break;
		}
		cout << endl;
	}
}
void Print(Students* s, const int N)
{
	cout << "==================================================================================================="
		<< endl;
	cout << "| № |  Прізвище  | Курс | Спец. | Фізика | Матем. | Інформ. | Програм. | Чисельні м. | Педагогіка |"
		<< endl;
	cout << "---------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(11) << left << s[i].prizv
			<< "| " << setw(4) << right << s[i].kurs << " "
			<< "| " << setw(6) << left << specStr[s[i].spec] << "| " << setw(6) << setprecision(2) << fixed << right
			<< s[i].phyg << " |" << " " << setw(6) << right
			<< s[i].mag << " |" << setw(8) << right << s[i].ing << " ";
		switch (s[i].spec)
		{
		case KN:
			cout << "| " << setw(8) << right
				<< s[i].prog << " |" << setw(14) << right << " |" << setw(13) << right << "|" << endl;
			break;
		case IT:
			cout << "| " << setw(10) << right << " |" << setw(13) << right << s[i].chmg << "| " << setw(12) << fixed << right << " |" << endl;
			break;
		case ME:
			cout << "| " << setw(10) << right << " |" << setw(14) << right << " |" << setw(11) << right
				<< s[i].pedg << " |" << endl;
			break;
		}
	}
	cout << "===================================================================================================" << endl;
	cout << endl;
}
void Sort(Students* s, const int N)
{
	Students tmp;
	for (int i0 = 0; i0 < N - 1; i0++)
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((s[i1].ing < s[i1 + 1].ing)
				||
				(s[i1].ing == s[i1 + 1].ing &&
					s[i1].spec > s[i1 + 1].spec)
				||
				(s[i1].ing == s[i1 + 1].ing &&
					s[i1].spec == s[i1 + 1].spec &&
					s[i1].prizv > s[i1 + 1].prizv))
			{
				tmp = s[i1];
				s[i1] = s[i1 + 1];
				s[i1 + 1] = tmp;
			}
}
int* IndexSort(Students* s, const int N)
{ 
	int* I = new int[N]; 
	for (int i = 0; i < N; i++)
		I[i] = i; 
	int i, j, value; 
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((s[I[j]].ing < s[value].ing)
				||
				(s[I[j]].ing == s[value].ing &&
					s[I[j]].spec > s[value].spec)
				||
				(s[I[j]].ing == s[value].ing &&
					s[I[j]].spec == s[value].spec &&
					s[I[j]].prizv > s[value].prizv));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}
void PrintIndexSorted(Students* s, int* I, const int N)
{
	cout << "==================================================================================================="
		<< endl;
	cout << "| № |  Прізвище  | Курс | Спец. | Фізика | Матем. | Інформ. | Програм. | Чисельні м. | Педагогіка |"
		<< endl;
	cout << "---------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(11) << left << s[I[i]].prizv
			<< "| " << setw(4) << right << s[I[i]].kurs << " "
			<< "| " << setw(6) << left << specStr[s[I[i]].spec] << "| " << setw(6) << right
			<< s[I[i]].phyg << " |" << " " << setw(6) << right
			<< s[I[i]].mag << " |" << setw(8) << right << s[I[i]].ing << " ";
		switch (s[I[i]].spec)
		{
		case KN:
			cout << "| " << setw(8) << right
				<< s[I[i]].prog << " |" << setw(14) << right << " |" << setw(13) << right << "|" << endl;
			break;
		case IT:
			cout << "| " << setw(10) << right << " |" << setw(13) << right << s[I[i]].chmg << "| " << setw(12) << fixed << right << " |" << endl;
			break;
		case ME:
			cout << "| " << setw(10) << right << " |" << setw(14) << right << " |" << setw(11) << right
				<< s[I[i]].pedg << " |" << endl;
			break;
		}
	}
	cout << "===================================================================================================" << endl;
	cout << endl;
}

int BinSearch(Students* s, const int N, const string prizv, const Spec spec, const int ing)
{ 
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (s[m].prizv == prizv && s[m].spec == spec && s[m].ing == ing)
			return m;
		if ((s[m].ing > ing) ||
			(s[m].ing == ing &&
				s[m].spec < spec) || (s[m].ing == ing && s[m].spec == spec && s[m].prizv < prizv))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;


struct scan_info {
    char model[25]; // наименование модели
    int price;  // цена
    double x_size;  // горизонтальный размер области сканирования
    double y_size; // вертикальный размер области сканирования
    int optr; // оптическое разрешение
    int grey; // число градаций серого
};

int ShowMenu();
void CreateFile(int* n);
void ViewFile();
void AddFile();

int ShowMenu() {
    setlocale(LC_ALL, "Russian");
    char ch = '\0';
    cout << "1 : Создайте файл\n";
    cout << "2 : Просмотр файлов\n";
    cout << "3 : Добавить записи\n";
    cout << "4 : Вывод записи номер:\n";
    cout << "5 : Выхол\n";
    ch = getchar();
    return atoi(&ch);
}

void CreateFile(int* n)
{
    FILE* data;
    fopen_s(&data, "file.bin", "w+b");
    do {
        cout << endl << "Введите количество записей 1-8: ";
        cin >> *n;
    } while ((*n < 1) || (*n > 8));
    scan_info scan;
    fwrite(n, 4, 1, data); //n-позиция в потоке
    for (int i = 1; i <= *n; i++) {
        cout << "Сканер N: " << i << endl;
        cout << "Модель: ";
        cin >> scan.model;
        cout << "Цена: ";
        cin >> scan.price;
        cout << "Горизонтальная размер области сканирования: ";
        cin >> scan.x_size;
        cout << "Вертикальный размер области сканирования: ";
        cin >> scan.y_size;
        cout << "Оптическое разрешение: ";
        cin >> scan.optr;
        cout << "Число градаций серого: ";
        cin >> scan.grey;
        cout << endl;
        fwrite(&scan, sizeof(scan), 1, data);
    };
    fclose(data);
    cout << "" << endl << endl;
    getchar();
    return;
}

void ViewFile()
{
    FILE* data1;
    fopen_s(&data1, "file.bin", "rb");
    if (data1 == NULL) {
        cout << "Нельзя открыть файл для чтения." << endl << endl;
        getchar();
        return;
    };
    int n;
    // прочитали количество записей в файле
    fread(&n, 4, 1, data1);
    cout << "+++++" << n << endl;
    //  выводим на экран через массив
    cout << endl << "Количество сканеров: " << n << endl << endl;
    scan_info* s = new scan_info[n];
    for (int g = 0; g < n; g++)
        fread(&s[g], sizeof(scan_info), 1, data1);
    scan_info** q = new scan_info * [n]; //указатель на каждый элемент массива
    for (int i = 0; i < n; i++) {
        q[i] = &s[i];
    }
    //Sort(q, &n);

    for (int g = 0; g < n; g++) {
        cout << "Сканер N: " << g + 1 << endl;
        cout << "Модель: " << q[g]->model << endl;
        cout << "Цена: " << q[g]->price << endl;
        cout << "Горизонтальный размер области сканирования: " << q[g]->x_size << endl;
        cout << "Вертикальный размер области сканирования: " << q[g]->y_size << endl;
        cout << "Оптическое разрешение: " << q[g]->optr << endl;
        cout << "Число градаций серого: " << q[g]->grey << endl;
        cout << endl;
    };
    fclose(data1);
    cout << endl << endl;
    cout << n;
    getchar();
    return;
}

int save(scan_info* s, int n)
{
    if (s != NULL || n == 0) {
        FILE* fp;
        fopen_s(&fp, "file.bin", "rb");
        int nn;                            // кол-во старых записей
        fread((int*)&nn, 4, 1, fp);
        scan_info* ss = new scan_info[nn];
        if (nn != 0)
            for (int i = 0; i < nn; i++)
                fread(&ss[i], sizeof(scan_info), 1, fp);
        fclose(fp);
        /**/
        int k = n + nn;
        cout << endl << "*********" << k << "********" << endl;
        fopen_s(&fp, "file.bin", "wb");
        fseek(fp, 0, SEEK_SET);
        fwrite(&k, 4, 1, fp);
        fseek(fp, 0, SEEK_END);
        for (int i = 0; i < n; i++)
            fwrite(&s[i], sizeof(scan_info), 1, fp);
        fclose(fp);
    }
    return 0;
}


void AddFile() {
    int n;
    cout << endl << "Введите количество записей: ";
    cin >> n;
    scan_info* scan = new scan_info[n];
    for (int i = 1; i <= n; i++) {
        cout << "Сканер N: " << i << endl;
        cout << "Модель: ";
        cin >> scan[i - 1].model;
        cout << "Цена: ";
        cin >> scan[i - 1].price;
        cout << "Горизонтальная размер области сканирования: ";
        cin >> scan[i - 1].x_size;
        cout << "Вертикальный размер области сканирования: ";
        cin >> scan[i - 1].y_size;
        cout << "Оптическое разрешение: ";
        cin >> scan[i - 1].optr;
        cout << "Число градаций серого: ";
        cin >> scan[i - 1].grey;
        cout << endl;
    };
    save(scan, n);
    cout << "Файл  file.bin  обновлён." << endl << endl;
    getchar();
    return;
}

void getScan(int n) {
    cout << " Скан: " << n << endl;
    ifstream in("file.bin", ios::in | ios::binary);
    int x;
    in.read((char*)&x, sizeof(x));

    scan_info scan;
    for (int i = 0; i < n; i++) in.read((char*)&scan, sizeof(scan));
    cout << endl << scan.model << endl << scan.price << endl << scan.x_size << endl
        << scan.y_size << endl << scan.optr << endl << scan.grey << endl;
}


int main() {
    int n; 
    while (1) {
        switch (ShowMenu()) {
        case 1:
            CreateFile(&n);
            break;

        case 2:
            ViewFile();
            break;

        case 3:
            AddFile();
            break;

        case 4:
            cout << "номер товара: " << endl;
            cin >> n;
            getScan(n);
            break;

        case 5:
            return 0;

        default: break;
        }
    }
}
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;


struct scan_info {
    char model[25]; // ������������ ������
    int price;  // ����
    double x_size;  // �������������� ������ ������� ������������
    double y_size; // ������������ ������ ������� ������������
    int optr; // ���������� ����������
    int grey; // ����� �������� ������
};

int ShowMenu();
void CreateFile(int* n);
void ViewFile();
void AddFile();

int ShowMenu() {
    setlocale(LC_ALL, "Russian");
    char ch = '\0';
    cout << "1 : �������� ����\n";
    cout << "2 : �������� ������\n";
    cout << "3 : �������� ������\n";
    cout << "4 : ����� ������ �����:\n";
    cout << "5 : �����\n";
    ch = getchar();
    return atoi(&ch);
}

void CreateFile(int* n)
{
    FILE* data;
    fopen_s(&data, "file.bin", "w+b");
    do {
        cout << endl << "������� ���������� ������� 1-8: ";
        cin >> *n;
    } while ((*n < 1) || (*n > 8));
    scan_info scan;
    fwrite(n, 4, 1, data); //n-������� � ������
    for (int i = 1; i <= *n; i++) {
        cout << "������ N: " << i << endl;
        cout << "������: ";
        cin >> scan.model;
        cout << "����: ";
        cin >> scan.price;
        cout << "�������������� ������ ������� ������������: ";
        cin >> scan.x_size;
        cout << "������������ ������ ������� ������������: ";
        cin >> scan.y_size;
        cout << "���������� ����������: ";
        cin >> scan.optr;
        cout << "����� �������� ������: ";
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
        cout << "������ ������� ���� ��� ������." << endl << endl;
        getchar();
        return;
    };
    int n;
    // ��������� ���������� ������� � �����
    fread(&n, 4, 1, data1);
    cout << "+++++" << n << endl;
    //  ������� �� ����� ����� ������
    cout << endl << "���������� ��������: " << n << endl << endl;
    scan_info* s = new scan_info[n];
    for (int g = 0; g < n; g++)
        fread(&s[g], sizeof(scan_info), 1, data1);
    scan_info** q = new scan_info * [n]; //��������� �� ������ ������� �������
    for (int i = 0; i < n; i++) {
        q[i] = &s[i];
    }
    //Sort(q, &n);

    for (int g = 0; g < n; g++) {
        cout << "������ N: " << g + 1 << endl;
        cout << "������: " << q[g]->model << endl;
        cout << "����: " << q[g]->price << endl;
        cout << "�������������� ������ ������� ������������: " << q[g]->x_size << endl;
        cout << "������������ ������ ������� ������������: " << q[g]->y_size << endl;
        cout << "���������� ����������: " << q[g]->optr << endl;
        cout << "����� �������� ������: " << q[g]->grey << endl;
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
        int nn;                            // ���-�� ������ �������
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
    cout << endl << "������� ���������� �������: ";
    cin >> n;
    scan_info* scan = new scan_info[n];
    for (int i = 1; i <= n; i++) {
        cout << "������ N: " << i << endl;
        cout << "������: ";
        cin >> scan[i - 1].model;
        cout << "����: ";
        cin >> scan[i - 1].price;
        cout << "�������������� ������ ������� ������������: ";
        cin >> scan[i - 1].x_size;
        cout << "������������ ������ ������� ������������: ";
        cin >> scan[i - 1].y_size;
        cout << "���������� ����������: ";
        cin >> scan[i - 1].optr;
        cout << "����� �������� ������: ";
        cin >> scan[i - 1].grey;
        cout << endl;
    };
    save(scan, n);
    cout << "����  file.bin  �������." << endl << endl;
    getchar();
    return;
}

void getScan(int n) {
    cout << " ����: " << n << endl;
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
            cout << "����� ������: " << endl;
            cin >> n;
            getScan(n);
            break;

        case 5:
            return 0;

        default: break;
        }
    }
}
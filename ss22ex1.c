#include <stdio.h>
#include <string.h>

struct SinhVien {
    char id[50];
    char name[50];
    int age;
};

struct SinhVien sv[100];
int numberStudent = 0;

void getStudentByFile();
void printStudent();
void addStudent();
void saveStudent();
void editStudent();
void deleteStudent();
void searchStudent();
void sortStudents();

int main() {
    getStudentByFile();
    int choose;
    do {
        printf("1. In danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim thong tin sinh vien\n");
        printf("6. Sap xep sinh vien\n");
        printf("7. Thoat\n");
        printf("Moi ban nhap lua chon: ");
        scanf("%d", &choose);
        getchar(); // Clear buffer
        switch (choose) {
            case 1:
                printStudent();
                break;
            case 2:
                addStudent();
                break;
            case 3:
                editStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                searchStudent();
                break;
            case 6:
                sortStudents();
                break;
            case 7:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
        }
    } while (choose != 7);
    return 0;
}

void getStudentByFile() {
    FILE *file = fopen("sinhvien.bin", "rb");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        return;
    }
    numberStudent = fread(sv, sizeof(struct SinhVien), 100, file);
    fclose(file);
}

void printStudent() {
    if (numberStudent == 0) {
        printf("Khong co sinh vien nao.\n");
        return;
    }
    for (int i = 0; i < numberStudent; i++) {
        printf("Thong tin sinh vien thu %d:\n", i + 1);
        printf("Ma SV: %s\n", sv[i].id);
        printf("Ten SV: %s\n", sv[i].name);
        printf("Tuoi SV: %d\n", sv[i].age);
    }
}

void addStudent() {
    if (numberStudent >= 100) {
        printf("Danh sach sinh vien da day.\n");
        return;
    }
    struct SinhVien sv1;
    printf("Nhap ID: ");
    fgets(sv1.id, sizeof(sv1.id), stdin);
    sv1.id[strcspn(sv1.id, "\n")] = '\0';
    printf("Nhap ten: ");
    fgets(sv1.name, sizeof(sv1.name), stdin);
    sv1.name[strcspn(sv1.name, "\n")] = '\0';
    printf("Nhap tuoi: ");
    scanf("%d", &sv1.age);
    getchar(); // Clear buffer
    sv[numberStudent++] = sv1;
    saveStudent();
}

void saveStudent() {
    FILE *file = fopen("sinhvien.bin", "wb");
    if (file == NULL) {
        printf("Khong the mo file de ghi.\n");
        return;
    }
    fwrite(sv, sizeof(struct SinhVien), numberStudent, file);
    fclose(file);
}

void editStudent() {
    char updateId[50];
    printf("Moi nhap ma SV can sua: ");
    fgets(updateId, sizeof(updateId), stdin);
    updateId[strcspn(updateId, "\n")] = '\0';
    int flag = -1;
    for (int i = 0; i < numberStudent; i++) {
        if (strcmp(sv[i].id, updateId) == 0) {
            flag = i;
            break;
        }
    }
    if (flag == -1) {
        printf("Khong tim thay sinh vien co ma nay.\n");
        return;
    }
    printf("Nhap ten moi: ");
    fgets(sv[flag].name, sizeof(sv[flag].name), stdin);
    sv[flag].name[strcspn(sv[flag].name, "\n")] = '\0';
    printf("Nhap tuoi moi: ");
    scanf("%d", &sv[flag].age);
    getchar(); // Clear buffer
    saveStudent();
}

void deleteStudent() {
    char deleteId[50];
    printf("Moi nhap ma SV can xoa: ");
    fgets(deleteId, sizeof(deleteId), stdin);
    deleteId[strcspn(deleteId, "\n")] = '\0';
    int flag = -1;
    for (int i = 0; i < numberStudent; i++) {
        if (strcmp(sv[i].id, deleteId) == 0) {
            flag = i;
            break;
        }
    }
    if (flag == -1) {
        printf("Khong tim thay sinh vien co ma nay.\n");
        return;
    }
    for (int i = flag; i < numberStudent - 1; i++) {
        sv[i] = sv[i + 1];
    }
    numberStudent--;
    saveStudent();
}

void searchStudent() {
    char searchId[50];
    printf("Moi nhap ma SV can tim: ");
    fgets(searchId, sizeof(searchId), stdin);
    searchId[strcspn(searchId, "\n")] = '\0';
    for (int i = 0; i < numberStudent; i++) {
        if (strcmp(sv[i].id, searchId) == 0) {
            printf("Thong tin sinh vien:\n");
            printf("Ma SV: %s\n", sv[i].id);
            printf("Ten SV: %s\n", sv[i].name);
            printf("Tuoi SV: %d\n", sv[i].age);
            return;
        }
    }
    printf("Khong tim thay sinh vien co ma nay.\n");
}

void sortStudents() {
    for (int i = 0; i < numberStudent - 1; i++) {
        for (int j = i + 1; j < numberStudent; j++) {
            if (strcmp(sv[i].id, sv[j].id) > 0) {
                struct SinhVien temp = sv[i];
                sv[i] = sv[j];
                sv[j] = temp;
            }
        }
    }
    printf("Danh sach sinh vien da duoc sap xep.\n");
    saveStudent();
}

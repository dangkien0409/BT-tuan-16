#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char ten[100]; // Tên chương, phần, mục...
    int soTrang;   // Số trang của mục
    struct Node *conDau;   // Con đầu
    struct Node *anhEmKe; // Anh chị em tiếp theo
} Node;

//tạo node mới
Node* taoNode(const char* ten, int soTrang) {
    Node* nutMoi = (Node*)malloc(sizeof(Node));
    int i = 0;
    while (ten[i] != '\0' && i < 99) {
        nutMoi->ten[i] = ten[i];
        i++;
    }
    nutMoi->ten[i] = '\0';
    nutMoi->soTrang = soTrang;
    nutMoi->conDau = NULL;
    nutMoi->anhEmKe = NULL;
    return nutMoi;
}

//thêm con vào một node
void themCon(Node* cha, Node* con) {
    if (cha->conDau == NULL) {
        cha->conDau = con;
    } else {
        Node* tam = cha->conDau;
        while (tam->anhEmKe != NULL) {
            tam = tam->anhEmKe;
        }
        tam->anhEmKe = con;
    }
}

//tính tổng số trang của một node
int tinhTongSoTrang(Node* goc) {
    if (goc == NULL) return 0;
    int tong = goc->soTrang;
    Node* tam = goc->conDau;
    while (tam != NULL) {
        tong += tinhTongSoTrang(tam);
        tam = tam->anhEmKe;
    }
    goc->soTrang = tong; // Cập nhật số trang node hiện tại
    return tong;
}

//đếm số chương
int demSoChuong(Node* goc) {
    if (goc == NULL) return 0;
    int dem = 0;
    Node* tam = goc->conDau;
    while (tam != NULL) {
        dem++;
        tam = tam->anhEmKe;
    }
    return dem;
}

//tìm chương dài nhất
Node* timChuongDaiNhat(Node* goc) {
    if (goc == NULL) return NULL;
    Node* tam = goc->conDau;
    Node* chuongDaiNhat = NULL;
    int soTrangLonNhat = 0;
    while (tam != NULL) {
        if (tam->soTrang > soTrangLonNhat) {
            soTrangLonNhat = tam->soTrang;
            chuongDaiNhat = tam;
        }
        tam = tam->anhEmKe;
    }
    return chuongDaiNhat;
}

//tìm và xóa một mục (tên)
int xoaMuc(Node* goc, const char* ten) {
    if (goc == NULL) return 0;
    Node* tam = goc->conDau;
    Node* truoc = NULL;

    // Tìm node cần xóa
    while (tam != NULL) {
        int i = 0;
        int khop = 1;
        while (ten[i] != '\0' && tam->ten[i] != '\0') {
            if (ten[i] != tam->ten[i]) {
                khop = 0;
                break;
            }
            i++;
        }
        if (khop && ten[i] == '\0' && tam->ten[i] == '\0') break;

        truoc = tam;
        tam = tam->anhEmKe;
    }

    // không tìm thấy
    if (tam == NULL) return 0;

    //con đầu tiên
    if (truoc == NULL) {
        goc->conDau = tam->anhEmKe;
    } else {
        truoc->anhEmKe = tam->anhEmKe;
    }

    // Giải phóng bộ nhớ 
    free(tam);
    return 1;
}

//duyệt cây để hiển thị
void inCay(Node* goc, int cap) {
    if (goc == NULL) return;
    for (int i = 0; i < cap; i++) printf("  ");
    printf("- %s (%d trang)\n", goc->ten, goc->soTrang);
    Node* tam = goc->conDau;
    while (tam != NULL) {
        inCay(tam, cap + 1);
        tam = tam->anhEmKe;
    }
}

int main() {
    Node* goc = taoNode("Sach", 0);

    // Thêm các chương
    Node* chuong1 = taoNode("Chuong 1", 30);
    Node* chuong2 = taoNode("Chuong 2", 50);
    Node* chuong3 = taoNode("Chuong 3", 40);
    themCon(goc, chuong1);
    themCon(goc, chuong2);
    themCon(goc, chuong3);

    // Thêm mục con cho Chương
    themCon(chuong1, taoNode("Muc 1.1", 10));
    themCon(chuong1, taoNode("Muc 1.2", 20));

    // Cập nhật tổng số trang
    tinhTongSoTrang(goc);

    // Hiển thị cây
    printf("\nCau truc cay:\n");
    inCay(goc, 0);

    // Đếm số chương
    printf("\nSo chuong: %d\n", demSoChuong(goc));

    // Tìm chương dài nhất
    Node* daiNhat = timChuongDaiNhat(goc);
    if (daiNhat != NULL) {
        printf("Chuong dai nhat: %s (%d trang)\n", daiNhat->ten, daiNhat->soTrang);
    }

    // Xóa một mục
    if (xoaMuc(goc, "Chuong 2")) {
        printf("\nSau khi xoa 'Chuong 2':\n");
        tinhTongSoTrang(goc); // Cập nhật tổng số trang sau khi xóa
        inCay(goc, 0);
    } else {
        printf("\nKhong tim thay 'Chuong 2'.\n");
    }

    return 0;
}
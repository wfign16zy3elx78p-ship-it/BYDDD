#include <iostream>
#include <string>
using namespace std;

// ================= LOP CHA =================
class Order {
protected:
    string id;
    string name;
    int price;

public:
    virtual void Input() {
        cout << "Nhap ma don: ";
        cin >> id;
        cin.ignore();

        cout << "Nhap ten KH: ";
        getline(cin, name);

        cout << "Nhap gia: ";
        cin >> price;
    }

    virtual void Output() {
        cout << "Ma: " << id
             << " | Ten: " << name
             << " | Gia: " << price;
    }

    virtual double getTotal() = 0;
};

// ================= ONLINE =================
class OnlineOrder : public Order {
private:
    int km;

public:
    void Input() {
        Order::Input();
        cout << "Nhap so km: ";
        cin >> km;
    }

    double getTotal() {
        double total = price;

        if (price > 300000)
            total = total * 0.9;

        if (price < 500000)
            total = total + km * 3000;

        return total;
    }

    void Output() {
        Order::Output();
        cout << " | Online | Tong: " << getTotal() << endl;
    }
};

// ================= STORE =================
class StoreOrder : public Order {
private:
    int discount;

public:
    void Input() {
        Order::Input();
        cout << "Nhap giam gia: ";
        cin >> discount;
    }

    double getTotal() {
        double c1 = price - discount;

        if (price >= 300000) {
            double c2 = price * 0.85;

            if (c1 < c2)
                return c1;
            else
                return c2;
        }

        return c1;
    }

    void Output() {
        Order::Output();
        cout << " | Store | Tong: " << getTotal() << endl;
    }
};

// ================= QUAN LY =================
class OrderList {
private:
    Order* arr[100];
    int n;

public:
    void Input() {
        cout << "Nhap so don hang: ";
        cin >> n;

        for (int i = 0; i < n; i++) {
            int chon;

            cout << "\n1. Online\n2. Store\nChon: ";
            cin >> chon;

            if (chon == 1)
                arr[i] = new OnlineOrder();
            else
                arr[i] = new StoreOrder();

            arr[i]->Input();
        }
    }

    void Output() {
        cout << "\n===== DANH SACH =====\n";

        for (int i = 0; i < n; i++) {
            arr[i]->Output();
        }
    }

    double TongTien() {
        double s = 0;

        for (int i = 0; i < n; i++) {
            s = s + arr[i]->getTotal();
        }

        return s;
    }
};

// ================= MAIN =================
int main() {
    OrderList ds;

    ds.Input();
    ds.Output();

    cout << "\nTong tien tat ca: " << ds.TongTien();

    return 0;
}

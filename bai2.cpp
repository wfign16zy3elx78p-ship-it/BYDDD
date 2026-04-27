#include <iostream>
using namespace std;

// ===== Lớp cơ sở =====
class Invoice {
private:
    string id;
    string customerName;
    string customerType;

public:
    virtual void input() {
        cout << "Nhap ID: ";
        cin >> id;
        cin.ignore();

        cout << "Nhap ten: ";
        getline(cin, customerName);

        cout << "Loai (sinhhoat/khac): ";
        getline(cin, customerType);
    }

    string getCustomerType() {
        return customerType;
    }

    virtual double getTotal() = 0;

    virtual void output() {
        cout << "ID: " << id << endl;
        cout << "Ten: " << customerName << endl;
        cout << "Loai: " << customerType << endl;
    }
};

// ===== Hóa đơn điện =====
class ElectricInvoice : public Invoice {
private:
    int kWh;

public:
    void input() {
        Invoice::input();
        cout << "Nhap kWh: ";
        cin >> kWh;
    }

    double getTotal() {
        double total = 0;
        string type = getCustomerType(); // phải dùng getter

        if (type == "sinhhoat") {
            if (kWh <= 50)
                total = kWh * 1984;
            else if (kWh <= 100)
                total = 50 * 1984 + (kWh - 50) * 2050;
            else
                total = 50 * 1984 + 50 * 2050 + (kWh - 100) * 2380;
        } else {
            total = kWh * 3500;
            if (kWh > 500) total *= 1.1;
        }

        return total;
    }

    void output() {
        cout << "\n--- Hoa don dien ---\n";
        Invoice::output();
        cout << "kWh: " << kWh << endl;
        cout << "Tong tien: " << getTotal() << endl;
    }
};

// ===== Hóa đơn nước =====
class WaterInvoice : public Invoice {
private:
    int m3;

public:
    void input() {
        Invoice::input();
        cout << "Nhap m3: ";
        cin >> m3;
    }

    double getTotal() {
        double total = 0;
        string type = getCustomerType(); // dùng getter

        if (type == "sinhhoat") {
            if (m3 <= 10)
                total = m3 * 4580;
            else if (m3 <= 30)
                total = 10 * 4580 + (m3 - 10) * 5488;
            else
                total = 10 * 4580 + 20 * 5488 + (m3 - 30) * 6849;
        } else {
            total = m3 * 10000;
        }

        return total;
    }

    void output() {
        cout << "\n--- Hoa don nuoc ---\n";
        Invoice::output();
        cout << "m3: " << m3 << endl;
        cout << "Tong tien: " << getTotal() << endl;
    }
};

// ===== Danh sách =====
class InvoiceList {
private:
    Invoice* ds[100];
    int n;

public:
    void input() {
        cout << "Nhap so hoa don: ";
        cin >> n;

        for (int i = 0; i < n; i++) {
            int type;
            cout << "\n1. Dien - 2. Nuoc: ";
            cin >> type;

            if (type == 1)
                ds[i] = new ElectricInvoice();
            else
                ds[i] = new WaterInvoice();

            ds[i]->input();
        }
    }

    void output() {
        for (int i = 0; i < n; i++) {
            ds[i]->output();
        }
    }

    ~InvoiceList() {
        for (int i = 0; i < n; i++)
            delete ds[i];
    }
};

// ===== Main =====
int main() {
    InvoiceList list;
    list.input();
    list.output();
    return 0;
}

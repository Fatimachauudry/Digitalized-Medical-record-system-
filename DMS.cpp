#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

struct Patient {
    int id;
    std::string name;
    int severity; // 1 (Critical) to 5 (Non-urgent)
    std::string condition;

    Patient(int id, std::string name, int severity, std::string condition)
        : id(id), name(name), severity(severity), condition(condition) {}
};

class EmergencyRoomQueue {
private:
    std::vector<Patient> heap;

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index].severity < heap[parent].severity) {
                std::swap(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int size = heap.size();
        while (index < size) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;

            if (left < size && heap[left].severity < heap[smallest].severity) {
                smallest = left;
            }
            if (right < size && heap[right].severity < heap[smallest].severity) {
                smallest = right;
            }

            if (smallest != index) {
                std::swap(heap[index], heap[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
    }

public:
    void addPatient(int id, const std::string& name, int severity, const std::string& condition) {
        Patient newPatient(id, name, severity, condition);
        heap.push_back(newPatient);
        heapifyUp(heap.size() - 1);
        std::cout << "[+] Registered: " << name << " (Severity: " << severity << ")\n";
    }

    void treatNextPatient() {
        if (heap.empty()) {
            std::cout << "[!] No patients currently waiting in the ER queue.\n";
            return;
        }

        Patient next = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);

        std::cout << "\n----------------------------------------\n";
        std::cout << ">>> TREATING PATIENT <<<\n";
        std::cout << "ID: " << next.id << "\n";
        std::cout << "Name: " << next.name << "\n";
        std::cout << "Severity Level: " << next.severity << "\n";
        std::cout << "Condition: " << next.condition << "\n";
        std::cout << "----------------------------------------\n\n";
    }

    void displayQueue() const {
        if (heap.empty()) {
            std::cout << "\nQueue is currently empty.\n";
            return;
        }

        std::cout << "\n================ Current ER Queue ================\n";
        std::cout << "ID\tName\t\tSeverity\tCondition\n";
        std::cout << "--------------------------------------------------\n";
        for (const auto& patient : heap) {
            std::cout << patient.id << "\t" 
                      << patient.name << "\t\t" 
                      << patient.severity << "\t\t" 
                      << patient.condition << "\n";
        }
        std::cout << "==================================================\n\n";
    }

    bool isEmpty() const {
        return heap.empty();
    }
};

int main() {
    EmergencyRoomQueue er;

    // Registering initial patients
    er.addPatient(101, "Ali", 4, "Mild Fever");
    er.addPatient(102, "Sara", 1, "Cardiac Arrest");
    er.addPatient(103, "Usman", 3, "Fractured Arm");
    er.addPatient(104, "Zainab", 2, "Severe Burn");

    // Display state before treatment
    er.displayQueue();

    // Treat highest priority patient (Sara - Severity 1)
    er.treatNextPatient();

    // Add a new critical emergency mid-operation
    std::cout << "[!] Emergency arrival!\n";
    er.addPatient(105, "Hamza", 1, "Severe Trauma");

    er.displayQueue();

    // Process remaining treatments
    while (!er.isEmpty()) {
        er.treatNextPatient();
    }

    return 0;
}

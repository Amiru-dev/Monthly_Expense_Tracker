/*
 Group Number: 03

Members:
 1. A.U.Vidanapathirana – ITBSC/2025/EA/WD/003
 2. Amaya Y.G.N. – ITBSC/2025/EA/WD/005
 3. H.P.K.Jayathilaka – ITBSC/2025/EA/WD/004
*/

/*
 * Monthly Expense Tracker with Budget Alerts
 * Scenario 4 - C++ Program
 * Features: Modular design, Input validation, Budget alerts, Expense analysis
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

// ============================================
// CONSTANT DEFINITIONS
// ============================================
const int NUM_CATEGORIES = 5;
const string CATEGORIES[] = {"Food", "Travel", "Utilities", "Entertainment", "Other"};
const double BUDGET_LIMITS[] = {10000.0, 5000.0, 8000.0, 3000.0, 2000.0};

// ============================================
// FUNCTION DEFINITIONS
// ============================================

/**
 * Function: displayWelcomeMessage
 * Purpose: Displays program title and budget limits
 * Parameters: None
 * Returns: void
 */
void displayWelcomeMessage() {
    cout << "=================================================\n";
    cout << "   MONTHLY EXPENSE TRACKER WITH BUDGET ALERTS\n";
    cout << "=================================================\n\n";
    cout << "Budget Limits:\n";

    for (int i = 0; i < NUM_CATEGORIES; i++) {
        cout << "  - " << CATEGORIES[i] << ": LKR " << fixed << setprecision(2) << BUDGET_LIMITS[i] << endl;
    }
    cout << "\n";
}


/**
 * Function: inputExpenses
 * Purpose: Gets expense input from user with validation
 * Parameters: expenses[] -> array to store expense values
 * Returns: void
 */
void inputExpenses(double expenses[]) {
    cout << "=== ENTER EXPENSES ===\n\n";
    cout << "Enter your monthly expenses for 5 categories.\n\n";
    cout << fixed << setprecision(2); // Set output to 2 decimal places

    for (int i = 0; i < NUM_CATEGORIES; i++) {
        while (true) {
            cout << "Enter expense for " << CATEGORIES[i] << ": LKR ";

            if (cin >> expenses[i] && expenses[i] >= 0) {
                break;
            }

            cout << "Invalid input. Please enter a non-negative number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    cout << endl;
}


/**
 * Function: calculateTotal
 * Purpose: Calculates total of all expenses
 * Parameters: expenses[] -> array containing expense values
 * Returns: double -> total expenses
 */
double calculateTotal(const double expenses[]) {
    double total = 0.0;

    for (int i = 0; i < NUM_CATEGORIES; i++) {
        total += expenses[i];
    }

    return total;
}


/**
 * Function: calculateAverage
 * Purpose: Calculates average expense per category
 * Parameters: total -> total expenses
 * Returns: double -> average expense
 */
double calculateAverage(double total) {
    return total / NUM_CATEGORIES;
}


/**
 * Function: findMinMaxExpenses
 * Purpose: Finds indices of highest and lowest expense categories
 * Parameters: expenses[] -> array containing expense values
 *             maxIndex -> reference to store index of maximum expense
 *             minIndex -> reference to store index of minimum expense
 * Returns: void
 */
void findMinMaxExpenses(const double expenses[], int &maxIndex, int &minIndex) {
    // Initialize with first element
    maxIndex = 0;
    minIndex = 0;

    // Compare with remaining elements
    for (int i = 1; i < NUM_CATEGORIES; i++) {
        if (expenses[i] > expenses[maxIndex]) {
            maxIndex = i;
        }
        if (expenses[i] < expenses[minIndex]) {
            minIndex = i;
        }
    }
}


/**
 * Function: checkBudgetLimits
 * Purpose: Checks if any category exceeds budget and displays alerts
 * Parameters: expenses[] -> array containing expense values
 * Returns: void
 */
void checkBudgetLimits(const double expenses[]) {
    cout << "\n=== BUDGET ALERTS ===\n";

    bool alertShown = false;
    int overBudgetCount = 0;

    for (int i = 0; i < NUM_CATEGORIES; i++) {
        if (expenses[i] > BUDGET_LIMITS[i]) {
            alertShown = true;
            overBudgetCount++;

            cout << "ALERT: " << CATEGORIES[i] << " exceeded the budget limit (" << BUDGET_LIMITS[i] << ")!\n";
        }
    }

    if (!alertShown) {
        cout << "- All expenses are within budget limits. Excellent financial management!\n";
    } else {
        cout << "\n Summary: " << overBudgetCount << " category(ies) exceeded budget.\n";
    }
    cout << "================================================================\n";
}


/**
 * Function: displayExpenseSummary
 * Purpose: Displays detailed summary of all expenses
 * Parameters: expenses[] -> array containing expense values
 *             total -> total expenses
 *             average -> average expense per category
 *             maxIndex -> index of highest expense
 *             minIndex -> index of lowest expense
 * Returns: void
 */
void displayExpenseSummary(const double expenses[], double total, double average, int maxIndex, int minIndex) {
    cout << "\n======================================" << endl;
    cout << "         EXPENSE SUMMARY" << endl;
    cout << "======================================" << endl;

    // Use iomanip functions for clean output formatting
    cout << fixed << setprecision(2);

    // Display individual expenses
    for (int i = 0; i < NUM_CATEGORIES; i++) {
        cout << "* " << setw(15) << left << CATEGORIES[i] << ": " << expenses[i] << endl;
    }
    cout << "--------------------------------------" << endl;

    // Display calculated statistics (Task 6)
    cout << "TOTAL EXPENSES         : " << total << endl;
    cout << "AVERAGE EXPENSE        : " << average << endl;
    cout << "HIGHEST CATEGORY       : " << CATEGORIES[maxIndex] << " (" << expenses[maxIndex] << ")" << endl;
    cout << "LOWEST CATEGORY        : " << CATEGORIES[minIndex] << " (" << expenses[minIndex] << ")" << endl;
    cout << "======================================" << endl;
}

// ============================================
// MAIN FUNCTION
// ============================================
int main() {
    double expenses[NUM_CATEGORIES];      // Array to store expenses for each category
    double total, average;                // Total and average expenses
    int maxIndex, minIndex;               // Indices for highest and lowest expenses

    // Display program welcome message
    displayWelcomeMessage();

    // Step 1: Input expenses with validation
    inputExpenses(expenses);

    // Step 2: Calculate total and average expenses
    total = calculateTotal(expenses);
    average = calculateAverage(total);

    // Step 3: Find highest and lowest expense categories
    findMinMaxExpenses(expenses, maxIndex, minIndex);

    // Step 4: Display comprehensive expense summary
    displayExpenseSummary(expenses, total, average, maxIndex, minIndex);

    // Step 5: Check budget limits and display alerts
    checkBudgetLimits(expenses);

    return 0;
}

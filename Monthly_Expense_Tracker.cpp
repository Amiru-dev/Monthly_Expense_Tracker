/*
Members:
 1. A.U.Vidanapathirana
 2. Amaya Y.G.N.
 3. H.P.K.Jayathilaka
*/

/*
 * Monthly Expense Tracker with Budget Alerts
 * C++ Program
 * Features: Modular design, Input validation, Budget alerts, Expense analysis
 * IMPROVED: User-defined categories and budget limits
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

// ============================================
// GLOBAL VARIABLES
// ============================================
const int MAX_CATEGORIES = 10;          // Maximum allowed categories
int numCategories;                       // Actual number of categories (user-defined)
string categories[MAX_CATEGORIES];       // Category names
double budgetLimits[MAX_CATEGORIES];     // Budget limits for each category
double expenses[MAX_CATEGORIES];         // Expenses for each category

// ============================================
// FUNCTION DECLARATIONS (Prototypes)
// ============================================
void getNumberOfCategories();
void setupCategories();
void displayWelcomeInfo();
void inputExpenses();
double calculateTotal();
double calculateAverage(double total);
void findMinMaxExpenses(int &maxIndex, int &minIndex);
void displayBudgetAlerts();
void displayExpenseSummary(double total, double average, int maxIndex, int minIndex);

// ============================================
// FUNCTION DEFINITIONS
// ============================================

/**
 * Function: getNumberOfCategories
 * Purpose: Gets the number of expense categories from user
 * Parameters: None
 * Returns: void (stores result in global numCategories)
 */
void getNumberOfCategories() {
    cout << "=================================================\n";
    cout << "        EXPENSE TRACKER SETUP\n";
    cout << "=================================================\n\n";

    while (true) {
        cout << "How many expense categories do you want to track? (1-" << MAX_CATEGORIES << "): ";

        if (cin >> numCategories && numCategories >= 1 && numCategories <= MAX_CATEGORIES) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer for getline
            break;
        }

        cout << "Invalid input. Please enter a number between 1 and " << MAX_CATEGORIES << ".\n\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


/**
 * Function: setupCategories
 * Purpose: Allows user to define category names and budget limits
 * Parameters: None
 * Returns: void (stores results in global arrays)
 */
void setupCategories() {
    cout << "\n=== DEFINE YOUR CATEGORIES ===\n\n";

    for (int i = 0; i < numCategories; i++) {
        // Get category name
        cout << "Enter name for Category " << setw(10) << left << (i + 1) << ": ";
        getline(cin, categories[i]);

        // Validate non-empty category name
        while (categories[i].empty()) {
            cout << "Category name cannot be empty. Please enter a valid name: ";
            getline(cin, categories[i]);
        }

        // Get budget limit for this category
        while (true) {
            cout << "Enter budget limit for " << setw(10) << left << categories[i] << " : LKR ";

            if (cin >> budgetLimits[i] && budgetLimits[i] > 0) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
                break;
            }

            cout << "Invalid input. Please enter a positive number.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << endl;
    }
}


/**
 * Function: displayWelcomeInfo
 * Purpose: Displays program title and budget limits
 * Parameters: None
 * Returns: void
 */
void displayWelcomeInfo() {
    cout << "\n=================================================\n";
    cout << "   MONTHLY EXPENSE TRACKER WITH BUDGET ALERTS\n";
    cout << "=================================================\n\n";
    cout << "Your Budget Limits:\n";

    // Display budget limits
    for (int i = 0; i < numCategories; i++) {
        cout << "  - " << setw(10) << left << categories[i] << ": LKR " << budgetLimits[i] << endl;
    }
    cout << "\n";
}


/**
 * Function: inputExpenses
 * Purpose: Gets expense input from user with validation
 * Parameters: None
 * Returns: void (stores results in global expenses array)
 */
void inputExpenses() {
    cout << "=== ENTER EXPENSES ===\n\n";
    cout << "Enter your monthly expenses for " << numCategories << " categories.\n\n";

    // Input expenses for all categories
    for (int i = 0; i < numCategories; i++) {
        while (true) {
            cout << "Enter expense for " << setw(10) << left << categories[i] << ": LKR ";

            if (cin >> expenses[i] && expenses[i] >= 0) {
                break;
            }

            cout << "Invalid input. Please enter a non-negative number.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    cout << endl;
}


/**
 * Function: calculateTotal
 * Purpose: Calculates total of all expenses
 * Parameters: None
 * Returns: double -> total expenses
 */
double calculateTotal() {
    double total = 0.0;

    for (int i = 0; i < numCategories; i++) {
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
    return total / numCategories;
}


/**
 * Function: findMinMaxExpenses
 * Purpose: Finds indices of highest and lowest expense categories
 * Parameters: maxIndex -> reference to store index of maximum expense
 *             minIndex -> reference to store index of minimum expense
 * Returns: void
 */
void findMinMaxExpenses(int &maxIndex, int &minIndex) {
    // Initialize with first element
    maxIndex = 0;
    minIndex = 0;

    // Compare with remaining elements
    for (int i = 1; i < numCategories; i++) {
        if (expenses[i] > expenses[maxIndex]) {
            maxIndex = i;
        }
        if (expenses[i] < expenses[minIndex]) {
            minIndex = i;
        }
    }
}


/**
 * Function: displayBudgetAlerts
 * Purpose: Checks if any category exceeds budget and displays alerts
 * Parameters: None
 * Returns: void
 */
void displayBudgetAlerts() {
    cout << "\n=== BUDGET ALERTS ===\n";
    // Initialize the over-budget count
    int overBudgetCount = 0;

    // Display alerts if budget is exceeded
    for (int i = 0; i < numCategories; i++) {
        if (expenses[i] > budgetLimits[i]) {
            overBudgetCount++;
            cout << "ALERT: " << categories[i] << " exceeded the budget limit (LKR " << budgetLimits[i] << ")!\n";
        }
    }

    // Display over-budget count or message
    if (overBudgetCount == 0) {
        cout << "- All expenses are within budget limits. Excellent financial management!\n";
    } else {
        cout << "\nSummary: " << overBudgetCount << " category(ies) exceeded budget.\n";
    }
    cout << "================================================================\n";
}


/**
 * Function: displayExpenseSummary
 * Purpose: Displays detailed summary of all expenses
 * Parameters: total -> total expenses
 *             average -> average expense per category
 *             maxIndex -> index of highest expense
 *             minIndex -> index of lowest expense
 * Returns: void
 */
void displayExpenseSummary(double total, double average, int maxIndex, int minIndex) {
    cout << "\n==============================================" << endl;
    cout << "               EXPENSE SUMMARY" << endl;
    cout << "==============================================" << endl;

    // Display individual expenses
    for (int i = 0; i < numCategories; i++) {
        cout << "* " << setw(15) << left << categories[i] << ": LKR " << expenses[i] << endl;
    }
    cout << "----------------------------------------------" << endl;

    // Display calculated statistics
    cout << "TOTAL EXPENSES      : LKR " << total << endl;
    cout << "AVERAGE EXPENSE     : LKR " << average << endl;
    cout << "HIGHEST CATEGORY    : " << categories[maxIndex] << " (LKR " << expenses[maxIndex] << ")" << endl;
    cout << "LOWEST CATEGORY     : " << categories[minIndex] << " (LKR " << expenses[minIndex] << ")" << endl;
    cout << "==============================================" << endl;
}


// ============================================
// MAIN FUNCTION
// ============================================
int main() {
    // Set currency format: 2 decimal places for all monetary outputs
    cout << fixed << setprecision(2);

    // Variables for calculations
    double total, average;
    int maxIndex, minIndex;

    // Step 1: Get number of categories from user
    getNumberOfCategories();

    // Step 2: Setup categories and budget limits
    setupCategories();

    // Step 3: Display program welcome information with user-defined budgets
    displayWelcomeInfo();

    // Step 4: Input expenses with validation
    inputExpenses();

    // Step 5: Calculate total and average expenses
    total = calculateTotal();
    average = calculateAverage(total);

    // Step 6: Find highest and lowest expense categories
    findMinMaxExpenses(maxIndex, minIndex);

    // Step 7: Display comprehensive expense summary
    displayExpenseSummary(total, average, maxIndex, minIndex);

    // Step 8: Check budget limits and display alerts
    displayBudgetAlerts();

    return 0;
}

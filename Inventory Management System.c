#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // For detecting lower-case letters

struct Product {
    int id;                  // Product ID
    char name[50];           // Product name
    char type[50];           // Product type
    int quantity;            // Product quantity
    int minStockThreshold;   // Minimum stock threshold
    float price;             // Product price
    struct Product* next;    // Pointer to next product
};

struct Product* head = NULL; // Head of the linked list of products
static int idCounter = 1;    // Static to keep track of the ID across multiple function calls

void addProduct() { // Add a product
    struct Product* newProduct = (struct Product*)malloc(sizeof(struct Product));

    // Assigning an ID to each new product
    newProduct->id = idCounter++;  // Always increment from the last assigned ID

    printf("Enter product name: ");
    getchar(); // To clear any leftover newline character
    fgets(newProduct->name, 50, stdin);
    newProduct->name[strcspn(newProduct->name, "\n")] = 0; // Remove trailing newline

    printf("Enter product type: ");
    fgets(newProduct->type, 50, stdin);
    newProduct->type[strcspn(newProduct->type, "\n")] = 0; // Remove trailing newline

    printf("Enter product quantity: ");
    scanf("%d", &newProduct->quantity);

    printf("Enter minimum stock threshold: ");
    scanf("%d", &newProduct->minStockThreshold);

    printf("Enter product price: ");
    char priceInput[20];
    scanf("%s", priceInput);
    sscanf(priceInput + 1, "%f", &newProduct->price); // Parse price after "P for Philippine Peso

    // If the list is empty, make the new product the head
    if (head == NULL) {
        newProduct->next = NULL;
        head = newProduct;
    } else {
        // Otherwise, find the last product in the list
        struct Product* current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newProduct;
        newProduct->next = NULL;  // New product should point to NULL
    }

    printf("Product added successfully! ID: %d\n", newProduct->id);
}

// Helper function to convert a string to lowercase (used for searching)
void toLowerCase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void updateProduct() { // Update the product you want to modify
    char name[50];
    printf("Enter product name to update: ");
    getchar(); // To clear any leftover newline character
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = 0; // Remove trailing newline
    toLowerCase(name); // Convert user input name to lowercase

    struct Product* current = head;

    while (current != NULL) {
        char productName[50];
        strcpy(productName, current->name); // Copy product name to a temporary buffer
        toLowerCase(productName); // Convert product name to lowercase

        if (strcmp(productName, name) == 0) {
            // Found the product, update it
            printf("Enter new product name: ");
            fgets(current->name, 50, stdin);
            current->name[strcspn(current->name, "\n")] = 0; // Remove trailing newline

            printf("Enter new product type: ");
            fgets(current->type, 50, stdin);
            current->type[strcspn(current->type, "\n")] = 0; // Remove trailing newline

            printf("Enter new quantity: ");
            scanf("%d", &current->quantity);

            printf("Enter new minimum stock threshold: ");
            scanf("%d", &current->minStockThreshold);

            printf("Enter new price: ");
            char priceInput[20];
            scanf("%s", priceInput);
            sscanf(priceInput + 1, "%f", &current->price); // Parse price after "P"

            printf("Product updated successfully!\n");
            return;
        }
        current = current->next;
    }
    printf("Product not found!\n");
}

void deleteProduct() { // Delete the product you want to exclude
    char name[50];
    printf("Enter product name to delete: ");
    getchar(); // To clear any leftover newline character
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = 0; // Remove trailing newline
    toLowerCase(name); // Convert user input name to lowercase

    struct Product* current = head;
    struct Product* previous = NULL;

    while (current != NULL) {
        char productName[50];
        strcpy(productName, current->name); // Copy product name to a temporary buffer
        toLowerCase(productName); // Convert product name to lowercase

        if (strcmp(productName, name) == 0) {
            // Found the product, delete it
            if (previous == NULL) {
                head = current->next; // Delete the head
            } else {
                previous->next = current->next;
            }
            free(current);
            printf("Product deleted successfully!\n");
            return;
        }
        previous = current;
        current = current->next;
    }
    printf("Product not found!\n");
}

void processSale() { // Entering the quantity to sell that is less than the original stock
    char name[50];
    int quantity;

    printf("Enter product name to sell: ");
    getchar(); // To clear any leftover newline character
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = 0; // Remove trailing newline
    toLowerCase(name); // Convert user input name to lowercase

    printf("Enter quantity to sell: ");
    scanf("%d", &quantity);

    struct Product* current = head;

    while (current != NULL) {
        char productName[50];
        strcpy(productName, current->name); // Copy product name to a temporary buffer
        toLowerCase(productName); // Convert product name to lowercase

        if (strcmp(productName, name) == 0) {
            // Check for sufficient stock
            if (current->quantity >= quantity) {
                current->quantity -= quantity;
                printf("Sale processed successfully! Remaining stock for '%s': %d\n", current->name, current->quantity);
                return;
            } else {
                printf("Insufficient stock for '%s'. Available quantity: %d\n", current->name, current->quantity);
                return;
            }
        }
        current = current->next;
    }
    printf("Product not found!\n");
}

void generateReport() { // Output for Inventory Report
    struct Product* current = head;

    printf("\n\t\t\t\t                                AV Paper n' Pixels\t\t\t\t\n");
    printf("|=================================================================================================================================================|\n");
    printf(" %-5s %-40s %-32s %-10s %-22s %-16s %-20s\n", "ID", "Name", "Type", "Quantity", "Min. Stock Threshold", "Price", "Stock Status");
    printf("|-------------------------------------------------------------------------------------------------------------------------------------------------|\n");

    while (current != NULL) {
        // Determine the stock status based on the comparison between quantity and minimum stock threshold
        char stockStatus[20];
        if (current->quantity == 0) {
            strcpy(stockStatus, "Out of Stock");
        } else if (current->quantity < current->minStockThreshold) {
            strcpy(stockStatus, "Low Stock");
        } else {
            strcpy(stockStatus, "Enough Stock");
        }

        // Adjusted width for Quantity, Min. Stock Threshold, Price, and Stock Status to align properly
        printf(" %-5d %-40s %-32s %-10d %-22d P%-15.2f %-19s\n",
               current->id, current->name, current->type, current->quantity, current->minStockThreshold, current->price, stockStatus);
        current = current->next;
    }

    printf("|=================================================================================================================================================|\n");
}

int main() { // Main menu and loop
    int choice;
    do {
        printf("\n AV Paper n' Pixels\n");
        printf("--------------------\n");
        printf("1. Add Product\n");
        printf("2. Update Product\n");
        printf("3. Delete Product\n");
        printf("4. Process Sale\n");
        printf("5. Generate Report\n");
        printf("6. Check Low Stock\n");
        printf("7. Clear Screen\n"); // Adding Clear Screen option
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                updateProduct();
                break;
            case 3:
                deleteProduct();
                break;
            case 4:
                processSale();
                break;
            case 5:
                generateReport();
                break;
            case 6:
                // Checking low stock
                break;
            case 7:
                // Clearing the screen
                break;
            case 8:
                printf("Program Exit.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 8);

    // Free the allocated memory for the products before exiting
    struct Product* current = head;
    struct Product* nextProduct;
    while (current != NULL) {
        nextProduct = current->next;
        free(current);
        current = nextProduct;
    }

    return 0;
}

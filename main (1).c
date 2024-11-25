#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LOW_STOCK_THRESHOLD 5

struct Product {
    char name[50];  // Allow longer names
    char type[50];  // Allow longer types
    int quantity;
    float price;
    struct Product* next;
};

struct Product* head = NULL;

void addProduct() {
    struct Product* newProduct = (struct Product*)malloc(sizeof(struct Product));

    printf("Enter product name: ");
    getchar(); // To clear any leftover newline character
    fgets(newProduct->name, 50, stdin);
    newProduct->name[strcspn(newProduct->name, "\n")] = 0; // Remove trailing newline

    printf("Enter product type: ");
    fgets(newProduct->type, 50, stdin);
    newProduct->type[strcspn(newProduct->type, "\n")] = 0; // Remove trailing newline

    printf("Enter product quantity: ");
    scanf("%d", &newProduct->quantity);

    printf("Enter product price: ");
    char priceInput[20];
    scanf("%s", priceInput);
    sscanf(priceInput + 1, "%f", &newProduct->price); // Parse price after the "P"

    newProduct->next = head;
    head = newProduct;

    printf("Product added successfully!\n");
}

void updateProduct() {
    char name[50];
    printf("Enter product name to update: ");
    getchar(); // To clear any leftover newline character
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = 0; // Remove trailing newline

    struct Product* current = head;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("Enter new product type: ");
            fgets(current->type, 50, stdin);
            current->type[strcspn(current->type, "\n")] = 0; // Remove trailing newline

            printf("Enter new quantity: ");
            scanf("%d", &current->quantity);

            printf("Enter new price: ");
            char priceInput[20];
            scanf("%s", priceInput);
            sscanf(priceInput + 1, "%f", &current->price); // Parse price after the "P"

            printf("Product updated successfully!\n");
            return;
        }
        current = current->next;
    }
    printf("Product not found!\n");
}

void deleteProduct() {
    char name[50];
    printf("Enter product name to delete: ");
    getchar(); // To clear any leftover newline character
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = 0; // Remove trailing newline

    struct Product* current = head;
    struct Product* previous = NULL;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
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

void processSale() {
    char name[50];
    int quantity;
    printf("Enter product name to sell: ");
    getchar(); // To clear any leftover newline character
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = 0; // Remove trailing newline

    printf("Enter quantity to sell: ");
    scanf("%d", &quantity);

    struct Product* current = head;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (current->quantity >= quantity) {
                current->quantity -= quantity;
                printf("Sale processed successfully!\n");
                return;
            } else {
                printf("Insufficient stock!\n");
                return;
            }
        }
        current = current->next;
    }
    printf("Product not found!\n");
}

void generateReport() {
    struct Product* current = head;

    printf("\n\t\t\t\t        Inventory Report\t\t\t\t\n");
    printf("|===============================================================================================|\n");
    printf(" %-25s %-25s %-18s %-20s\n", "Name", "Type", "Quantity", "Price");
    printf("|-----------------------------------------------------------------------------------------------|\n");

    while (current != NULL) {
        printf(" %-25s %-25s %-18d P%-9.2f\n",
               current->name, current->type, current->quantity, current->price);
        current = current->next;
    }

    printf("|===============================================================================================|\n");
}

void checkLowStock() {
    struct Product* current = head;
    printf("\nLow Stock Alert:\n");
    int lowStockFound = 0; // Flag to check if any low stock is found
    while (current != NULL) {
        if (current->quantity < LOW_STOCK_THRESHOLD) {
            printf("Product %s (Type: %s) is low on stock (Quantity: %d)\n", current->name, current->type, current->quantity);
            lowStockFound = 1; // Set flag if low stock is found
        }
        current = current->next;
    }
    if (!lowStockFound) {
        printf("No products are low on stock.\n");
    }
}

int main() {
    int choice;
    do {
        printf("\nInventory Management System\n");
        printf("1. Add Product\n");
        printf("2. Update Product\n");
        printf("3. Delete Product\n");
        printf("4. Process Sale\n");
        printf("5. Generate Report\n");
        printf("6. Check Low Stock\n");
        printf("7. Exit\n");
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
                checkLowStock();
                break;
            case 7:
                printf("Program Exit.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 7);

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

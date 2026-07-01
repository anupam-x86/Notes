/*
Q6 — Simple Billing System (8 marks)

UserInputs:

```
item price
quantity
tax %
```

Output:

```
subtotal
tax amount
grand total
```

Formulas:

subtotal     = price × quantity
taxAmount    = subtotal × (taxPercent / 100)
grandTotal   = subtotal + taxAmount

Constraints: Show numbers neatly.

*/
#include <iostream>

double calculateSubTotal(const double itemPrice, const int itemQuantity);
double calculateTaxAmount(const double subTotal, const double taxPercent);
double calculateGrandTotal(const double subTotal, const double taxAmount);

int main()
{

    double itemPrice{};
    std::cout << "Enter Item Price: ";
    std::cin >> itemPrice;

    int itemQuantity{};
    std::cout << "Enter Item Quantity: ";
    std::cin >> itemQuantity;

    double taxPercent{};
    std::cout << "Enter Tax (in %): ";
    std::cin >> taxPercent;

    const double subTotalAmount{calculateSubTotal(itemPrice, itemQuantity)};
    const double taxedAmount{calculateTaxAmount(subTotalAmount, taxPercent)};
    const double grandTotalAmount{calculateGrandTotal(subTotalAmount, taxedAmount)};

    std::cout << "----------------------------" << '\n';
    std::cout << "Item Price: " << itemPrice << '\n';
    std::cout << "Item Quantity: " << itemQuantity << '\n';
    std::cout << "Tax Percentage: " << taxPercent << '\n';
    std::cout << "----------------------------" << '\n';
    std::cout << "SubTotal: " << subTotalAmount << '\n';
    std::cout << "Tax Amount: " << taxedAmount << '\n';
    std::cout << "GrandTotal: " << grandTotalAmount << '\n';
    std::cout << "----------------------------" << '\n';

    return 0;
}

double calculateSubTotal(const double itemPrice, const int itemQuantity)
{
    return itemPrice * itemQuantity; // Formula: subtotal = price × quantity
}

double calculateTaxAmount(const double subTotalAmount, const double taxPercent)
{
    return subTotalAmount * (taxPercent / 100); // Formula: taxAmount = subTotal × ( taxPercent / 100 )
}

double calculateGrandTotal(const double subTotalAmount, const double taxedAmount)
{
    return subTotalAmount + taxedAmount; // Formula: grandTotal = subTotal + taxAmount
}
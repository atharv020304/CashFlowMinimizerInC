

# 💸 Cash Flow Minimizer

A C-based system that optimizes and **minimizes cash transactions** between multiple banks by finding the minimal set of transactions needed to settle all debts. It also handles compatibility between different payment types via a special **"World Bank"** intermediary.


## 📌 Problem Statement

When multiple banks owe each other money, the naive way is to execute each transaction individually. This system **reduces the total number of transactions** by analyzing net balances and common payment modes between banks. If two banks can't transact directly due to incompatible payment modes, the system uses a **World Bank** that supports all modes.

---

## ✅ Features

* 🔄 **Net balance computation** for each bank
* 🔁 **Minimization of transactions** to settle debts
* 🌐 **Support for multiple payment modes**
* 🏦 **World Bank** acts as an intermediary when direct payments aren't possible
* 📊 Custom **hashmap** and **set** implementations
* 📈 Memory-safe and fully modular design

---

## 🛠️ Input Format

1. **Number of banks** involved (first one is the World Bank)
2. For each bank:

   * Bank name (no spaces)
   * Number of supported payment types
   * Names of payment types
3. **Number of transactions**
4. For each transaction:

   * Debtor Bank name
   * Creditor Bank name
   * Amount

---

## 🧪 Sample Input

```
4
worldbank 2 UPI NEFT.
BankA 1 UPI
BankB 1 NEFT
BankC 1 RTGS
3
BankA BankB 100
BankB BankC 200
BankC BankA 50
```

---

## 📤 Sample Output

```
The transactions for minimum cash flow are as follows:

BankA pays Rs 50 to BankB via UPI
BankC pays Rs 150 to BankB via NEFT
```

---

## 💡 How It Works

1. Calculates **net amount** for each bank.
2. Repeatedly picks the bank with the **minimum** and **maximum** net amounts.
3. Finds a **common payment type** for direct transaction.
4. If no common type exists, uses **World Bank** as a bridge.
5. Updates net balances and continues until all are settled.

---


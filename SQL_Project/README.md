# SQLite Phone Rental Management System

## 📖 Project Description
This project implements a relational database using **SQLite** to manage the core operations of a phone rental business. The system is designed to store and organize information related to customers, various phone models (including their specifications), individual phone units in inventory, and rental contracts. It facilitates efficient data retrieval and management for tracking rentals, customer history, and inventory status.

---

## 🗂️ Database Structure
The database schema consists of four primary tables, interconnected via foreign keys to maintain data integrity and enable complex queries:

### 1. **Customer**
-   Stores essential information about the individuals or entities renting phones.
-   **Fields**:
    -   `ID` (INTEGER, Primary Key, Auto-increment): Unique identifier for each customer.
    -   `Name` (TEXT, Not Null): Full name of the customer.
    -   `Email` (TEXT, Unique, Not Null): Email address of the customer, used for communication and unique identification.

### 2. **PhoneModel**
-   Contains details of the various phone models available for rental.
-   **Fields**:
    -   `ModelNumber` (TEXT, Primary Key): Unique model number acting as an identifier (e.g., "A2643" for iPhone 13 Pro).
    -   `Name` (TEXT, Not Null): Common name of the phone model (e.g., "iPhone 13 Pro", "Samsung Galaxy S22 Ultra").
    -   `Storage` (TEXT): Storage capacity (e.g., "128GB", "256GB", "512GB").
    -   `Color` (TEXT): Color of the phone model (e.g., "Graphite", "Sierra Blue").

### 3. **Phone**
-   Tracks each individual physical phone unit in the inventory. Each phone is an instance of a `PhoneModel`.
-   **Fields**:
    -   `SerialNumber` (TEXT, Primary Key): Unique serial number for each physical phone unit.
    -   `ModelNumber` (TEXT, Foreign Key referencing `PhoneModel(ModelNumber)`): Links to the specific model of this phone.
    -   `Status` (TEXT, Default "Available"): Current status of the phone (e.g., "Available", "Rented", "Under Maintenance", "Damaged").

### 4. **RentalContract**
-   Records the details of each rental agreement, linking a customer to a specific rented phone unit.
-   **Fields**:
    -   `ContractID` (INTEGER, Primary Key, Auto-increment): Unique identifier for each rental contract.
    -   `CustomerID` (INTEGER, Foreign Key referencing `Customer(ID)`): Links to the customer who rented the phone.
    -   `SerialNumber` (TEXT, Foreign Key referencing `Phone(SerialNumber)`): Links to the specific phone unit rented.
    -   `StartDate` (DATE, Not Null): The date when the rental period begins.
    -   `EndDate` (DATE): The date when the rental period is scheduled to end. Can be NULL for ongoing rentals.
    -   `ActualReturnDate` (DATE): The date when the phone was actually returned. (Optional enhancement)
    -   `Cost` (REAL, Not Null): Total calculated cost for the rental period.

---

## ✨ Key Features
-   **Comprehensive Customer Management**: Store, retrieve, and manage detailed customer information.
-   **Detailed Inventory Tracking**: Maintain an organized inventory of all phone models and individual phone units, including their current status.
-   **Efficient Rental Management**: Record, track, and manage all aspects of phone rentals, including rental periods, costs, and customer-phone associations.
-   **Data Integrity and Consistency**: Enforce data accuracy and consistency through the use of primary keys, foreign keys, unique constraints, and appropriate data types.
-   **Robust Querying Capabilities**: Allows for complex SQL queries to derive business insights, such as rental history, popular phone models, customer rental patterns, and revenue analysis.

---

## ⚙️ Technologies Used
-   **Database System**: SQLite 3
-   **Data Modeling**: Relational database design principles.
-   **Interaction**: SQL (Structured Query Language).
-   **Management Tools**: Any SQLite-compatible database browser or tool (e.g., [DB Browser for SQLite](https://sqlitebrowser.org/), SQLiteStudio, DBeaver, Visual Studio Code with an SQLite extension).

---

## 🚀 How to Access and Use

1.  **Prerequisites**:
    -   Install an SQLite database management tool if you don't have one.

2.  **Access the Database**:
    -   Ensure the database file (e.g., `phone_rental.db` or `projects.db`) is available.
    -   Open this database file using your chosen SQLite tool. You might need to navigate to the `Phone_Rental_DB_SQL` directory (or the current project directory) if you cloned the repository.

3.  **Interact with the Database**:
    -   **View Schema**: Use your tool to explore the table structures, columns, data types, primary keys, foreign keys, and other constraints.
    -   **Browse Data**: View the existing data within each table.
    -   **Execute SQL Queries**: Utilize the SQL editor in your tool to run queries. Examples:
        ```sql
        -- Find all phones currently available for rent
        SELECT P.SerialNumber, PM.Name, PM.Storage, PM.Color
        FROM Phone P
        JOIN PhoneModel PM ON P.ModelNumber = PM.ModelNumber
        WHERE P.Status = 'Available';

        -- Get rental history for a specific customer (e.g., CustomerID = 1)
        SELECT RC.ContractID, C.Name AS CustomerName, P.SerialNumber, PM.Name AS PhoneModel, RC.StartDate, RC.EndDate, RC.Cost
        FROM RentalContract RC
        JOIN Customer C ON RC.CustomerID = C.ID
        JOIN Phone P ON RC.SerialNumber = P.SerialNumber
        JOIN PhoneModel PM ON P.ModelNumber = PM.ModelNumber
        WHERE RC.CustomerID = 1
        ORDER BY RC.StartDate DESC;
        ```
    -   **Modify Data**: Use SQL `INSERT`, `UPDATE`, `DELETE` statements or the tool's GUI features to add new records, update existing ones, or remove data (with caution).

---

## 📄 License
This project is licensed under the MIT License. See the main [LICENSE](../../LICENSE) file for details.

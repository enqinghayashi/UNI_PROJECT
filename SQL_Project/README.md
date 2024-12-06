# SQL Database Project: Customer and Phone Rental Management

## 📖 Project Description  
This project is a **SQLite database** designed to manage operations related to a phone rental business. It includes functionality for storing and managing information about customers, phone models, individual phones, and rental contracts.

---

## 🗂️ Database Structure  
The database consists of four main tables:

### 1. **Customer**  
- Stores information about customers.  
- **Fields**:  
  - `ID` (Primary Key)  
  - `Name`  
  - `Email`  

### 2. **PhoneModel**  
- Details of available phone models.  
- **Fields**:  
  - `ModelNumber` (Primary Key)  
  - `Name`  
  - `Storage` (e.g., 64GB, 128GB)  
  - `Color`  

### 3. **Phone**  
- Stores information about individual phones in the inventory.  
- **Fields**:  
  - `SerialNumber` (Primary Key)  
  - `ModelNumber` (Foreign Key referencing PhoneModel)  

### 4. **RentalContract**  
- Links customers to rented phones and records rental details.  
- **Fields**:  
  - `ContractID` (Primary Key)  
  - `CustomerID` (Foreign Key referencing Customer)  
  - `SerialNumber` (Foreign Key referencing Phone)  
  - `StartDate`  
  - `EndDate`  
  - `Cost`  

---

## ⚙️ Technologies Used  
- **SQLite**: For database creation and management.  
- **SQLite-compatible database management tools**: For viewing, querying, and modifying the database.

---

## 🚀 How to Access  
1. Clone this repository to your local machine.  
2. Open the `projects.db` file using any SQLite-compatible database management tool (e.g., [DB Browser for SQLite](https://sqlitebrowser.org/), SQLiteStudio, or Visual Studio Code with an SQLite extension).  
3. Explore the tables and modify or query the data as needed.  

---

## ✨ Features  
- Manage customer details efficiently.  
- Keep an organized inventory of phone models and individual phones.  
- Record and track phone rentals, including rental periods and costs.  
- Ensure data consistency with well-defined table relationships.

---

## 📫 Contact  
For any queries or suggestions, feel free to contact:  
**[Your Name]**  
**[Your Email]**

---

### 📝 License  
This project is licensed under the [MIT License](LICENSE).  

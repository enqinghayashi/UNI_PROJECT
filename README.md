# UNI_PROJECTS

This repository contains my small university projects across different programming languages. Each project is organized into its own folder, with a focus on distinct programming languages and topics. Below is an overview of the projects included.

## Overview
---

### C_Project


[**ML Transpiler**](./C_Project)
- **runml**: A transpiler written in C11 that translates a mini-language (ml) into C, compiles it, and executes the generated program. 
  - [The Project README](./C_Project/README.md) - Contains more detailed instructions for the `runml` project.

---

### Java_Project


[**Message Delivery Status Tracker**](./Java_Project)
- A Java application that determines whether messages should be delivered or dropped based on their timestamps and a configurable delay threshold \(k\).  
- **Key Features**:  
  - Uses a HashMap to track the last delivery time for each message.  
  - Compares the current timestamp with the last delivery time to decide delivery status.  
  - Returns a list of `"true"` or `"false"` indicating delivery (`"true"`) or drop (`"false"`) for each message.  

This project highlights the use of collections, control structures, and efficient algorithms for solving real-world challenges.  







---

### Python_Project


[**Worldwide Population Analaysis Tool**](./Python_Project)
 - **Population Analysis**  : Analyzes population and area data to identify the most and least populated countries within a specified region, calculate statistical measures, and provide insights.  

 - **Regional Population Analysis**  : Processes population data from a CSV file to compute regional statistics, such as standard error and cosine similarity, using nested dictionaries for data organization.  






---

### SQL_Project


[**Phone Rental Database Management**](./SQL_Project)
 - **Customer and Phone Rental Management**  : A SQLite database project for managing customer and phone rental operations. The database includes information about customers, phone models, individual phones, and rental contracts, enabling various operations like tracking rentals, costs, and customer details.

#### Key Features  
- **Customer Management**: Stores customer details like ID, name, and email.  
- **Phone Models**: Maintains data on phone models, including specifications such as storage and color.  
- **Rental Contracts**: Links customers with phones, tracks rental periods, and calculates costs.  
---

## How to Use

1. **Clone the repository:**
   ```bash
   git clone https://github.com/your-username/UNI_PROJECTS.git
   cd UNI_PROJECTS
2. **Navigate to the specific project folder:**
   ```bash
   cd C_Project
4. **Follow the instructions in each project's README file for details on how to run the projects.**

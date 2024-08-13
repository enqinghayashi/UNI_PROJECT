# UNI_PROJECT
This repository contains two primary projects that demonstrate data analysis and database management skills using Python and SQL. Each project is focused on handling and analyzing data related to population statistics and managing customer and phone rental information.

# Python Overview
## Project 1: Population Analysis

Description
This Python script performs various data analysis tasks on a dataset containing population information. The main focus is on analyzing population and area data to derive insights such as:
- Identifying the most and least populated countries within a specified region.
- Calculating the standard deviation of populations within a region.
- Performing operations on population and area lists to compute various statistical measures.

Features
- Population Analysis: Determines key statistics, including most and least populated countries.
- **Area-Based Calculations: Processes data to calculate the average and standard deviation of populations and areas.
- Data Filtering: Focuses analysis on specific regions as defined by the user.

Technologies Used
- Python
- File Handling

How to Run
1. Ensure you have Python installed on your system.
2. Place the input data file in the same directory as the script.
3. Run the script with the command:
   ```bash
   python Python_Project1.py
   ```
4. Follow the prompts to input the desired region for analysis.

## Project 2: Regional Population Analysis

Description
This Python project is designed to analyze population data from a CSV file and compute various statistical measures. The primary outputs are:
- The standard error of the population for each region.
- Cosine similarity between population and land area for each region.

The script organizes the data into a dictionary where each region contains sub-dictionaries for each country, storing relevant statistics such as population, net change, and density.

Features
- Statistical Analysis: Computes standard error and cosine similarity for population and land area.
- Dictionary-Based Data Organization: Efficiently stores and accesses data through nested dictionaries.
- CSV File Handling: Reads data from a CSV file for processing.

Technologies Used
- Python
- CSV File Handling

How to Run
1. Ensure you have Python installed on your system.
2. Place the CSV file in the same directory as the script.
3. Run the script with the command:
   python Python_Project2.py

## SQL Overview
## Database Project: Customer and Phone Rental Management

Description
This project involves managing a SQLite database containing information about customers, phone models, individual phones, and rental contracts. The database is structured to handle various operations related to phone rentals.

Database Structure
- Customer: Stores customer information (ID, Name, Email).
- PhoneModel: Details of phone models including model number, name, storage, and color.
- Phone: Lists individual phones with serial numbers.
- rentalContract: Records details of rental contracts, linking customers to phones, along with rental periods and costs.

Technologies Used
- SQLite
- Python (for database interaction)

How to Access
1. Open the `projects.db` file using any SQLite-compatible database management tool.
2. Explore the tables to view or modify the data.



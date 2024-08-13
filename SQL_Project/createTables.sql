CREATE TABLE Phone (
modelNumber TEXT,
modelName TEXT,
IMEI TEXT PRIMARY KEY CHECK(length(IMEI) == 15 AND ((CAST(substr(IMEI, 1, 1) AS INTEGER)
        + CAST(substr(IMEI, 3, 1) AS INTEGER)
        + CAST(substr(IMEI, 5, 1) AS INTEGER)
        + CAST(substr(IMEI, 7, 1) AS INTEGER)
        + CAST(substr(IMEI, 9, 1) AS INTEGER)
        + CAST(substr(IMEI, 11, 1) AS INTEGER) 
        + CAST(substr(IMEI, 13, 1) AS INTEGER)
        + CAST(substr(IMEI, 15, 1) AS INTEGER)
        + (CAST(substr(IMEI, 2, 1) AS INTEGER)*2 % 10)
        + (CAST(substr(IMEI, 2, 1) AS INTEGER)*2 / 10)
        + (CAST(substr(IMEI, 4, 1) AS INTEGER)*2 % 10)
        + (CAST(substr(IMEI, 4, 1) AS INTEGER)*2 / 10)
        + (CAST(substr(IMEI, 6, 1) AS INTEGER)*2 % 10)
        + (CAST(substr(IMEI, 6, 1) AS INTEGER)*2 / 10)
        + (CAST(substr(IMEI, 8, 1) AS INTEGER)*2 % 10)
        + (CAST(substr(IMEI, 8, 1) AS INTEGER)*2 / 10)
        + (CAST(substr(IMEI, 10, 1) AS INTEGER)*2 % 10)
        + (CAST(substr(IMEI, 10, 1) AS INTEGER)*2 / 10)
        + (CAST(substr(IMEI, 12, 1) AS INTEGER)*2 % 10)
        + (CAST(substr(IMEI, 12, 1) AS INTEGER)*2 / 10)
        + (CAST(substr(IMEI, 14, 1) AS INTEGER)*2 % 10)
        + (CAST(substr(IMEI, 14, 1) AS INTEGER)*2 / 10))
        % 10) = 0),
FOREIGN KEY (modelNumber) REFERENCES PhoneModel(modelNumber));

CREATE TABLE PhoneModel (
    modelNumber TEXT PRIMARY KEY,
    modelName TEXT,
    storage INTEGER,
    colour TEXT,
    baseCost REAL,
    dailyCost REAL);

CREATE TABLE rentalContract (
    customerId INTEGER,
    IMEI TEXT,
    dateOut TEXT,
    dateBack TEXT,
    rentalCost REAL,
    PRIMARY KEY (IMEI, dateOUT),
    FOREIGN KEY (IMEI) REFERENCES Phone(IMEI),
    FOREIGN KEY (customerID) REFERENCES Customer(customerId));

CREATE TABLE Customer (
    customerId INTEGER PRIMARY KEY,
    customerName TEXT,
    customerEmail TEXT);
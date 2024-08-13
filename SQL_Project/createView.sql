CREATE VIEW CustomerSummary
AS
SELECT customerId,
CASE
    WHEN IMEI IS NULL THEN NULL 
    ELSE modelName
END AS modelName,
SUM(julianday(dateBack) - julianday(dateOut) + 1) AS daysRented,
CASE
    WHEN strftime('%m-%d', dateBack) >= '07-01'
    THEN strftime('%Y', dateBack) || '/' || ((CAST(substr(dateBack, 3,2) AS INTEGER))+1)
    ELSE strftime('%Y', dateBack,'-1 year') || '/' || substr(dateBack,3,2) 
        END AS taxYear,
SUM(rentalCost) AS TotalRentalCost
FROM rentalContract NATURAL JOIN Phone
WHERE dateBack IS NOT NULL
GROUP BY rentalContract.customerId, modelName, taxYear;
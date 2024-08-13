CREATE TRIGGER CalculateRentalCost
     AFTER UPDATE OF dateBack
     ON rentalContract
     FOR EACH ROW
     WHEN NEW.dateBack IS NOT NULL AND OLD.dateBack IS NULL
BEGIN
    UPDATE rentalContract
    SET rentalCost = ROUND( (SELECT (baseCost + dailyCost * (julianday(NEW.dateBack) - julianday(OLD.dateOut) + 1) ) 
                             FROM PhoneModel
                             WHERE PhoneModel.modelNumber = (SELECT Phone.modelNumber
                                                             FROM Phone
                                                             WHERE Phone.IMEI = NEW.IMEI)),2)
    WHERE rentalContract.dateBack = NEW.dateBack AND IMEI = NEW.IMEI;
END;
-- To get an idea of the tables in the database
.schema

-- To see the crime scene report
SELECT * FROM crime_scene_reports;

-- To see the crime scene report from 'Humphrey Street'
SELECT * FROM crime_scene_reports WHERE street = 'Humphrey Street';

-- To get the idea of what the interviews table looks like
SELECT * FROM interviews LIMIT 10;

-- TO get the interviews related to the burglary
SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28
AND transcript LIKE '%bakery%';

-- The interviews gave me 3 leads -
-- Check the security footage from the bakery parking lot at that time
-- Check morning ATM log form Leggett Street for money withdrawl
-- See phone log less then a min and see the 1st flight out of Fiftyville

-- To see what the security logs looks like
SELECT * FROM bakery_security_logs;

-- To see the log at the time of burglary (10:15 AM)
SELECT * FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15;

-- Refile my search , to the plate numbers that exit between 15 - 20 , gives a list of suspected_license_plate
SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND activity = 'exit' AND minute < 21;

-- To get the atm transactions of that day
SELECT * FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28;

-- Refile my serch with the given information from the inverviews, gives a list of suspected account number
SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';

-- Search for the 1st flight the follwing day
SELECT * FROM flights WHERE year = 2021 AND month = 7 AND day = 29 ORDER BY hour ASC;

-- Search for the city they ecapped to 4
SELECT * FROM airports WHERE id = 4;

--He ecaped to New York City

-- Search for the passport id
SELECT passport_number FROM passengers WHERE flight_id = 36;


-- Find the person with the by matching phone_number, license_plate_passport_number and bank acc number
-- Join people with licencepalte log, flight info and bank_accounts
SELECT * FROM people, bakery_security_logs, passengers, bank_accounts
WHERE people.license_plate = bakery_security_logs.license_plate
AND people.passport_number = passengers.passport_number
AND people.id = bank_accounts.person_id
AND year = 2021 AND month = 7 AND day = 28 AND flight_id = 36 AND hour = 10 AND
account_number IN
(SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw');

-- This narrows my search to 3 people

-- Lets see if thease people made any call at that time lasting less then 1 min
SELECT * FROM people, bakery_security_logs, passengers, bank_accounts, phone_calls
WHERE people.license_plate = bakery_security_logs.license_plate
AND people.passport_number = passengers.passport_number
AND people.id = bank_accounts.person_id
AND people.phone_number = phone_calls.caller
AND bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.minute < 25 AND flight_id = 36 AND hour = 10 AND duration < 60 AND phone_calls.day = 28 AND
account_number IN
(SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw');

-- This narrows down my list to only Bruce
-- Lets see who Bruce called

SELECT * FROM people WHERE phone_number = '(375) 555-8161';
-- So Robin helped Bruce to buy a plane ticket

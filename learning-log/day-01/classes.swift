import Foundation

//A class to simulate a bank profile of a user
class BankProfile {
    //Some basic variables of statistics for a bank profile
    var Name = ""
    var _balance = 0.00
    
    //a function to increase the balance for some deeper experimentation on classes
    func addBalance(_ amount:Double) -> Double {
        _balance += amount
        //return the balance
        return _balance
    }
}

//A simple var to test the function
var weeklyIncome = 120.00

//Creating the first profile
let firstBankProf = BankProfile()
firstBankProf.Name = "Jason"
firstBankProf._balance = 60.80
firstBankProf._balance = firstBankProf.addBalance(weeklyIncome)

//print the name and the incremented balance of the first profile
print(firstBankProf.Name, firstBankProf._balance)

//creating the second profile
let secondBankProf = BankProfile()
secondBankProf.Name = "User2"
secondBankProf._balance = 100.00
secondBankProf._balance = secondBankProf.addBalance(weeklyIncome)

//print the name and the incremented balance of the second profile
print(secondBankProf.Name, secondBankProf._balance)
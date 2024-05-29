# Post-Office-System

Description: The program operates as a “mail system” where one can send private letters between individuals, letters with tracking that allow one to see at which station the letter is located, and pay fines. In the MenuManager department, there are two containers: 1. Customers, 2. Employees. There is an initial login menu where one can identify as a customer or an employee, and accordingly, a customized menu with different accesses is opened. Initially, details about customers and employees are “pulled” from a text file, each having containers of documents (Document*). In the system, an employee can 1. Print a list of customers. 2. Print a list of employees. 3. Add a fine to a customer. 4. Delete a customer. 5. Add a customer. 6. Add employees. A customer can 1. Send a letter (regular/tracked) 2. Pay a fine. At the end, all data are recorded to a text file so that in the next run of the program, it will be possible to continue from the same point.

Work Constraints:

1.A field of pointer type: char* name in the PoliceStation class, in addition to a container of Document* in the Person class.
2.Addition of a method to the Document class we received: The PrintField method assists the Show function so that it is possible to print on cmd.
3.Implement inheritance and containment relationships: The Worker class inherits from Person. The TrackedLetter class inherits from Letter which inherits from Document. The Fine class inherits from Document and PoliceStation (multiple inheritance).
4.Contained Date object: Found in both Fine and Person.
5.Abstract class: The Document class is abstract and has a pure virtual Show method.
6.Static field: Exists in the Document class and in the TrackedLetter class.
7.Friend method: Exists in both the Date class and the PoliceStation class, a friend class in order to implement the << operator to input an object.
8.STL container fields: There is a list in the TrackedLetter class, in addition, there is a Vector in the Person class and two Vectors in the MenuManager class, using Iterator and Template in a large number of functions.
9.Method for searching for an element in MenuManager: The isExist method searches by ID whether the person exists in the container, if so, returns its location and True, otherwise -1 and False.
10.Exceptions: There are 3 exceptions: a. In creating a date, checking for a valid date month 1-12, day 1-30 except for February which allows 1-29 and a positive year. b. In changing the status at the letter station, can only contain English letters and space. c. A boolean variable that the postal worker enters whether the package has arrived or not, can only be 0/1. In all exceptions, we decided to handle with a while loop until a valid value is entered so that it is possible to continue running the program without problems.

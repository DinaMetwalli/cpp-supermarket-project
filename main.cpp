#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <string.h>
#include <limits>

struct products
{
  std::string name, DOE, type;
  int quantity;
  float price;
};
void readFile(std::vector<products> &vitems);

void searchDatabase(std::vector<products> &vitems, std::vector<std::string> eraseditems, int num);

void remove(std::vector<products> vitems, std::string removeditem);

void add(std::vector<products> &vitems, int &display);

void edit(std::vector<products> &vitems, int &display);

void updateDatabase(std::vector<products> vitems, int display);

void displayDatabase(std::vector<products> vitems);

void options(std::vector<products> vitems, std::string removeditem, std::vector<std::string> eraseditems, int display);

void specificDisplay(std::vector<products> vitems);

void lowStock(std::vector<products> vitems);

void expire(std::vector<products> vitems);

void certainType(std::vector<products> vitems);

void searchForItems(std::vector<products> vitems);

void saveResults(std::string itemName, std::vector<products> vitems, int file);

void displayResults(void);

int main()
{

  int display = 0;
  std::string removeditem;
  std::vector<products> vitems;
  std::vector<std::string> eraseditems;
  readFile(vitems);
  options(vitems, removeditem, eraseditems, display);
}

/**
 * void readFile (std::vector<products>& vitems)
 *
 * Parameters   : structure vector 'vitems' which contains all the items in the database
 *
 * Return Value : Nothing -- Note: Modifies the vector 'vitems'
 *                                 by pushing back the items from the file into it.
 *
 * Description:
 *
 *    This function reads the content of the 'products.txt' text file.
 *    Then, the retrieved content is split up and stored inside the 'vitems' vector.
 */
void readFile(std::vector<products> &vitems)
{
  std::string data;
  std::ifstream myfile("data/products.txt");
  // using ifstream function to open the products.txt file and giving it the name "myfile".

  std::string name, DOE, type;
  int quantity;
  float price;

  int id = 0;
  while (getline(myfile, data))
  // getline() is used inside this while loop to retreive the information or data from the text file, line by line.
  {
    std::istringstream iss(data);
    if (!(iss >> name >> DOE >> quantity >> price >> type))
      throw std::runtime_error("Invalid data.");
    iss >> name >> DOE >> quantity >> price >> type;

    vitems.push_back(products());
    // pushing back the structure members into the vector.
    vitems[id].name = name;
    vitems[id].DOE = DOE;
    vitems[id].quantity = quantity;
    vitems[id].price = price;
    vitems[id].type = type;

    id++;
    // accessing the id of each line.
  }
  myfile.close();
  return;
}

/**
 * void options(std::vector<products> vitems, std::string removeditem, std::vector<std::string> eraseditems, int display)
 *
 * Parameters   : structure vector: 'vitems' Which contains all the items in the database.
 *                string vector: 'eraseditems' A vector containing the items that the user wants to remove.
 *                string: 'removeditem' The name of the removed item.
 *
 * Return Value : Nothing.
 *
 * Description:
 *
 *    This function allows the user to choose an option for what they want to do.
 *    It contains multiple function calls depending on the user choice.
 */
void options(std::vector<products> vitems, std::string removeditem, std::vector<std::string> eraseditems, int display)
{
  int option = 0;
  while (option != 8)
  {
    std::cout << std::endl
              << "What would you like to do?" << std::endl
              << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "1 -> Display all items in the supermarket." << std::endl;
    std::cout << "2 -> Remove an item." << std::endl;
    std::cout << "3 -> Add an item." << std::endl;
    std::cout << "4 -> Edit an item." << std::endl;
    std::cout << "5 -> Find certain items." << std::endl;
    std::cout << "6 -> Search for a specific item." << std::endl;
    std::cout << "7 -> Display specific search results." << std::endl;
    std::cout << "8 -> Exit the program." << std::endl;
    std::cout << "option : ";
    std::cin >> option;
    switch (option)
    {
    case 1:
      displayDatabase(vitems);
      break;
    case 2:
      remove(vitems, removeditem);
      break;
    case 3:
      add(vitems, display);
      break;
    case 4:
      edit(vitems, display);
      break;
    case 5:
      specificDisplay(vitems);
      break;
    case 6:
      searchForItems(vitems);
      break;
    case 7:
      displayResults();
      break;
    case 8:
      return;
    default:
      if (std::cin.fail())
      {
        std::cout << "The input must be only numbers! Please try again." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      else
        std::cout << "That is not one of the options!" << std::endl;
    }
  }
}

/**
 * void searchForItems(std::vector<products> vitems)
 *
 * Parameters   : structure vector: 'vitems' Which contains all the items in the database.
 *
 * Return Value : Nothing.
 *
 * Description:
 *
 *    This function allows the user to search for specific items
 *    which exist inside the 'vitems' vector.
 *    Once the desired items are found, the 'saveResults()'
 *    function is called to save the search findings into a text file.
 *    If the item is not found inside the vector
 *    an error message is printed out.
 */
void searchForItems(std::vector<products> vitems)
{
  bool flag = 0;
  int file = 1;
  std::string name, itemName, option;
  std::cout << "Please enter the name of the item you're searching for: ";
  std::cin >> name;
  // Converting first letter of input into uppercase letter:
  // https://stackoverflow.com/questions/8530529/convert-first-letter-in-string-to-uppercase
  name[0] = toupper(name[0]);
  int j = 0;
  auto it = std::find_if(vitems.begin(), vitems.end(), [&](const products &p) -> int
                         // https://cplusplus.com/reference/algorithm/find_if/
                         // https://www.geeksforgeeks.org/lambda-expression-in-c/
                         { return (p.name).substr(0, name.size()) == name.substr(0, name.size()); });
  // substr() function:
  // https://www.simplilearn.com/tutorials/cpp-tutorial/cpp-substring#:~:text=In%20C%2B%2B%2C%20a%20substring,characters%20from%20the%20starting%20position.
  if (it != vitems.end()) // If the item was found..
  {
    std::cout << "Would you like to add the filtered items to the file or do you want to display them?" << std::endl;
    std::cout << "1. Add to file" << std::endl;
    std::cout << "2. Display items" << std::endl;
    std::cin >> option;
    for (auto elem : vitems)
    {
      if ((elem.name).substr(0, name.size()) == name.substr(0, name.size()))
      {
        itemName = elem.name;
        if (option == "1")
          saveResults(itemName, vitems, file); // saveResults() function is called everytime an item match is found to save it into the file.
        else if (option == "2")
        {
          std::cout << std::setw(13) << std::left << elem.name;
          std::cout << std::setw(15) << std::left << elem.DOE;
          std::cout << std::setw(9) << std::left << elem.quantity;
          std::cout << std::setw(9) << std::left << elem.price;
          std::cout << elem.type << std::endl;
          // https://www.youtube.com/watch?v=ytFT-1s7EWo&ab_channel=PortfolioCourses
        }
      }
    }
  }
  else // If no matching items were found in the vector, give error message
    std::cout << "There is no such item in the database." << std::endl;
  return;
}

/**
 * void saveResults(std::string itemName, std::vector<products> vitems, int file)
 *
 * Parameters   : structure vector: 'vitems' Which contains all the items in the database.
 *                string: 'itemName' A string of the item found by one of the
 *                                   search functions
 *
 * Return Value : Nothing.
 *
 * Description:
 *
 *    This function writes the results collected by the search functions
 *    searchForItems(), lowStock(), expire(), or certainType()
 *    functions into the proper textfile for each of the search types.
 */
void saveResults(std::string itemName, std::vector<products> vitems, int file)
{
  // https://www.geeksforgeeks.org/lambda-expression-in-c/
  auto it = std::find_if(vitems.begin(), vitems.end(), [&](const products &p) -> int
                         { return (p.name).substr(0, itemName.size()) == itemName.substr(0, itemName.size()); });
  if (it != vitems.end())
  {
    // Finding the index of a certain item in a vector:
    // https://www.geeksforgeeks.org/how-to-find-index-of-a-given-element-in-a-vector-in-cpp/
    int index = (it - vitems.begin());
    std::fstream myfile;
    // To write into a text file without overwriting:
    // https://stackoverflow.com/questions/4155537/writing-into-a-text-file-without-overwriting-it
    // Depending on the value of 'file', the file saves the results of the called search function.
    if (file == 1)
      myfile.open("data/results.txt", std::fstream::app);
    else if (file == 2)
      myfile.open("data/lowInStock.txt", std::fstream::app);
    else if (file == 3)
      myfile.open("data/expire.txt", std::fstream::app);
    else if (file == 4)
      myfile.open("data/certainTypes.txt", std::fstream::app);
    if (myfile.is_open())
    {
      myfile << vitems[index].name << "\t" << vitems[index].DOE << "\t" << vitems[index].quantity << "\t" << vitems[index].price << "\t" << vitems[index].type << std::endl;
    }
    myfile.close();
  }
  return;
}

/**
 * void displayResults(void)
 *
 * Parameters   : Nothing.
 *
 * Return Value : Nothing.
 *
 * Description:
 *
 *    This function displays the information in the text file
 *    'results.txt' to the screen.
 */
void displayResults(void)
{
  int quantity;
  float price;
  std::string myText, name, DOE, type;
  std::ifstream myReadFile("data/results.txt");

  while (getline(myReadFile, myText))
  {
    std::istringstream iss(myText);
    if (!(iss >> name >> DOE >> quantity >> price >> type))
      throw std::runtime_error("Invalid data.");
    iss >> name >> DOE >> quantity >> price >> type;
    std::cout << std::setw(13) << std::left << name;
    std::cout << std::setw(15) << std::left << DOE;
    std::cout << std::setw(9) << std::left << quantity;
    std::cout << std::setw(9) << std::left << price;
    std::cout << type << std::endl;
    // setw:
    // https://www.youtube.com/watch?v=ytFT-1s7EWo&ab_channel=PortfolioCourses
  }
}

/**
 * void updateDatabase(std::vector<products> vitems, int display)
 *
 * Parameters   : structure vector: 'vitems' Which contains all the items in the database.
 *                integer: 'display' A variable passed from the other functions
 *                                   add(), remove(), and edit() which decides whether
 *                                   to display updated database or not.
 *
 * Return Value : Nothing.
 *
 * Description:
 *
 *    This function writes into the text file 'products.txt'
 *    the updated version of the 'vitems' vector.
 *    It also provides the user with the option to display
 *    the database after every update.
 */
void updateDatabase(std::vector<products> vitems, int display)
{
  std::ofstream myfile("data/products.txt");
  if (myfile.is_open())
  {
    for (int i = 0; i < vitems.size(); i++)
    {
      myfile << vitems[i].name << "\t" << vitems[i].DOE << "\t" << vitems[i].quantity << "\t" << vitems[i].price << "\t" << vitems[i].type << std::endl;
    }
  }
  myfile.close();

  if (display == 1)
  {
    std::string answer;
    std::cout << "Would you like to see the updated database?" << std::endl;
    std::cin >> answer;
    if (answer == "yes" || answer == "Yes")
      displayDatabase(vitems);
  }
  return;
}

/**
 * void remove(std::vector<products> vitems, std::string removeditem)
 *
 * Parameters   : structure vector: 'vitems' Which contains all the items in the database.
 *                string: 'removeditem' The name of the item the user wants to remove.
 *
 * Return Value : Nothing.
 *
 * Description:
 *
 *    This function takes in user input of how many and which
 *    items they would like to remove from the database.
 *    The desired items are stored in the 'eraseditems' vector.
 *    Then the searchDatabase() function is called to
 *    find those items and erase them.
 */
void remove(std::vector<products> vitems, std::string removeditem)
{
  int num;
  std::vector<std::string> eraseditems;
  bool flag = 0;
  std::cout << "Please type how many items you would like to remove: ";
  while (!flag)
  {
    std::cin >> num;
    if (num > vitems.size())
      std::cout << "That is more than the amount of items in the database, please try again." << std::endl;
    else if (std::cin.fail())
      std::cout << "Sorry, but you must only enter numbers. Could you try again?" << std::endl;
    else
      flag = 1;
    if (!flag)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

      /*
      References for error handling using clear() and ignore():

      https://stackoverflow.com/questions/13440831/how-do-i-check-if-input-is-an-integer-string
      https://stackoverflow.com/questions/41475922/prompt-user-input-until-correct-c
      https://stackoverflow.com/questions/69212175/c-program-does-not-allow-me-to-give-a-second-input
      */
    }
  }
  if (num == 0)
  {
    return;
  }
  else
  {
    std::cout << "Enter that(those) items:" << std::endl;
    for (int i = 0; i < num; i++)
    {
      std::cin >> removeditem;
      removeditem[0] = toupper(removeditem[0]);
      // https://stackoverflow.com/questions/8530529/convert-first-letter-in-string-to-uppercase
      eraseditems.push_back(removeditem);
    }
    searchDatabase(vitems, eraseditems, num);
  }
  return;
}

/**
 * void searchDatabase(std::vector<products>& vitems, std::vector<std::string> eraseditems, int num)
 *
 * Parameters   : structure vector: 'vitems' Which contains all the items in the database.
 *                string vector: 'eraseditems' A vector containing the items that the user wants to remove.
 *                integer: 'num' The number of the items the user wants to remove.
 *
 * Return Value : Nothing. -- Note: Modifies the vector 'vitems' because it is passed by reference.
 *
 * Description:
 *
 *    This function searches the 'vitems' vector to check
 *    if any of the items in the 'eraseditems' vector are in it.
 *    Once a matching item is found,
 *    it is erased from the vector 'vitems'.
 */
void searchDatabase(std::vector<products> &vitems, std::vector<std::string> eraseditems, int num)
{
  int display = 1;
  for (int i = 0; i < num; i++)
  {
    auto it = std::find_if(vitems.begin(), vitems.end(), [&](const products &p) -> int
                           { return p.name == eraseditems[i]; });
    // Return true if the name is equal to any of the items in eraseditems vector
    // https://www.geeksforgeeks.org/lambda-expression-in-c/

    if (it != vitems.end())
    {

      int index = (it - vitems.begin());
      // https://www.geeksforgeeks.org/how-to-find-index-of-a-given-element-in-a-vector-in-cpp/
      vitems.erase(vitems.begin() + index);
      // Erased the items from the vector 'vitems' meaning that they're still in the text file but no longer in the vector.
    }
    else
    {
      std::cout << std::endl
                << "Item not in database." << std::endl;
      display = 0;
    }
  }
  updateDatabase(vitems, display);
  // Calling updateDatabase() function removes items from text file as well.
  return;
}

/**
 * void add(std::vector<products>& vitems, int &display)
 *
 * Parameters   : structure vector: 'vitems' Which contains all the items in the database.
 *                integer: 'display' A variable to choose whether or not to display the database.
 *
 * Return Value : Nothing. -- Note: Modifies the vector 'vitems', and int 'display' because they are passed by reference.
 *
 * Description:
 *
 *    This function adds new items to the 'vitems' vector
 *    and calls the 'updateDatabase()' function to
 *    update the 'products.txt' text file.
 */
void add(std::vector<products> &vitems, int &display)
{
  bool check = 0;
  products tmp;
  std::string answer;

  do
  {
    std::cout << "Enter the name of the item you would like to add: ";
    std::cin >> tmp.name;
    tmp.name[0] = toupper(tmp.name[0]);
    // https://stackoverflow.com/questions/8530529/convert-first-letter-in-string-to-uppercase
    std::cout << "Enter the date of experation for the " << tmp.name << ": ";
    while (!check)
    {
      std::cin >> tmp.DOE;
      for (int i = 0, j = 0; i < 2 && j < 4; i++, j++)
      {
        if (!isdigit((tmp.DOE).substr(0, 2)[i]) || !isdigit((tmp.DOE).substr(3, 2)[i]) || !isdigit((tmp.DOE).substr(6, 4)[j]))
        {
          std::cout << "The date format must be DD/MM/YYYY" << std::endl;
          break;
        }
        else if ((tmp.DOE).substr(2, 1) != "/" || (tmp.DOE).substr(5, 1) != "/")
        {
          std::cout << "The date format must be DD/MM/YYYY" << std::endl;
          break;
        }
        else
          check = 1;
      }
      // https://www.simplilearn.com/tutorials/cpp-tutorial/cpp-substring#:~:text=In%20C%2B%2B%2C%20a%20substring,characters%20from%20the%20starting%20position.
      if (!check)
      {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // https://stackoverflow.com/questions/13440831/how-do-i-check-if-input-is-an-integer-string
        // https://stackoverflow.com/questions/41475922/prompt-user-input-until-correct-c
        // https://stackoverflow.com/questions/69212175/c-program-does-not-allow-me-to-give-a-second-input
      }
    }
    std::cout << "Enter the quantity of the " << tmp.name << ": ";
    std::cin >> tmp.quantity;
    while (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "The quantity must be a number." << std::endl;
      std::cin >> tmp.quantity;
    }
    std::cout << "Enter the price for the " << tmp.name << ": ";
    std::cin >> tmp.price;
    while (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "The price must be a number." << std::endl;
      std::cin >> tmp.price;
    }
    std::cout << "What is the type of the " << tmp.name << "? ";
    std::cin >> tmp.type;
    tmp.type[0] = toupper(tmp.type[0]);
    // https://stackoverflow.com/questions/8530529/convert-first-letter-in-string-to-uppercase
    vitems.push_back(tmp);
    std::cout << "Would you like to add another item?" << std::endl;
    std::cin >> answer;
    answer[0] = toupper(answer[0]);
    while (((answer != "Yes") && (answer != "No")) || (!std::cin))
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Sorry, I didn't understand that.. Would you like to add another item?" << std::endl;
      std::cin >> answer;
      answer[0] = toupper(answer[0]);
    }
  } while (answer == "Yes");

  display = 1;
  updateDatabase(vitems, display);
  if (answer == "No")
  {
    return;
  }
}

/**
 * void edit(std::vector<products>& vitems, int &display)
 *
 * Parameters   : structure vector: 'vitems' Which contains all the items in the database.
 *                integer: 'display' A variable to choose whether or not to display the database.
 *
 * Return Value : Nothing. -- Note: Modifies the vector 'vitems', and int 'display' because they are passed by reference.
 *
 * Description:
 *
 *    This function finds the index of the item to be edited
 *    in the 'vitems' vector and resets its properties
 *    by overwriting them.
 *    Calls the 'updateDatabase()' function to
 *    update the 'products.txt' text file.
 */
void edit(std::vector<products> &vitems, int &display)
{
  int index, newQuantity, flag = 1;
  bool check = 0;
  float newPrice;
  std::string itemToEdit, toEdit, newName, newDOE, newType, answer;

  do
  {
    std::cout << "Which item would you like to modify?" << std::endl;
    std::cin >> itemToEdit;
    itemToEdit[0] = toupper(itemToEdit[0]);
    // https://stackoverflow.com/questions/8530529/convert-first-letter-in-string-to-uppercase
    auto it = std::find_if(vitems.begin(), vitems.end(), [&](const products &p)
                           // https://cplusplus.com/reference/algorithm/find_if/
                           // https://www.geeksforgeeks.org/lambda-expression-in-c/
                           { return p.name == itemToEdit; });
    if (it != vitems.end())
    {
      while ((flag = 1))
      {
        std::cout << "Which part of the data about the " << itemToEdit << " would you like to edit?" << std::endl;
        std::cout << "1- Name" << std::endl;
        std::cout << "2- Date of Expiration" << std::endl;
        std::cout << "3- Quantity" << std::endl;
        std::cout << "4- Price" << std::endl;
        std::cout << "5- Type" << std::endl;
        std::cin >> toEdit;

        int index = (it - vitems.begin());

        if (vitems[index].name == itemToEdit)
        // https://www.geeksforgeeks.org/how-to-find-index-of-a-given-element-in-a-vector-in-cpp/
        {
          if (toEdit == "1")
          {
            std::cout << "Please Enter the new name: ";
            std::cin >> newName;
            vitems[index].name = newName;
          }
          else if (toEdit == "2")
          {
            std::cout << "Please enter the new DOE: ";
            while (!check)
            {
              std::cin >> newDOE;
              for (int i = 0, j = 0; i < 2 && j < 4; i++, j++)
              {
                if (!isdigit((newDOE).substr(0, 2)[i]) || !isdigit((newDOE).substr(3, 2)[i]) || !isdigit((newDOE).substr(6, 4)[j]))
                // https://www.simplilearn.com/tutorials/cpp-tutorial/cpp-substring#:~:text=In%20C%2B%2B%2C%20a%20substring,characters%20from%20the%20starting%20position.
                {
                  std::cout << "The date format must be DD/MM/YYYY" << std::endl;
                  break;
                }
                else if ((newDOE).substr(2, 1) != "/" || (newDOE).substr(5, 1) != "/")
                {
                  std::cout << "The date format must be DD/MM/YYYY" << std::endl;
                  break;
                }
                else
                  check = 1;
              }
              if (!check)
              {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                // https://stackoverflow.com/questions/13440831/how-do-i-check-if-input-is-an-integer-string
                // https://stackoverflow.com/questions/41475922/prompt-user-input-until-correct-c
                // https://stackoverflow.com/questions/69212175/c-program-does-not-allow-me-to-give-a-second-input
              }
            }
            vitems[index].DOE = newDOE;
          }
          else if (toEdit == "3")
          {
            std::cout << "Please enter the new quantity: ";
            std::cin >> newQuantity;
            while (!std::cin)
            {
              std::cin.clear();
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
              std::cout << "The quantity must be a number." << std::endl;
              std::cin >> newQuantity;
            }
            vitems[index].quantity = newQuantity;
          }
          else if (toEdit == "4")
          {
            std::cout << "Please enter the new price: ";
            std::cin >> newPrice;
            while (!std::cin)
            {
              std::cin.clear();
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
              std::cout << "The price must be a number." << std::endl;
              std::cin >> newPrice;
            }
            vitems[index].price = newPrice;
          }
          else if (toEdit == "5")
          {
            std::cout << "Please enter the new type: ";
            std::cin >> newType;
            newType[0] = toupper(newType[0]);
            vitems[index].type = newType;
          }
          else
          {
            std::cout << "That is not one of the options, please enter a number." << std::endl;
            std::cin >> toEdit;
          }
        }
        std::cout << "Would you like to edit another property of the " << itemToEdit << "?" << std::endl;
        std::cin >> answer;
        answer[0] = toupper(answer[0]);
        while (((answer != "Yes") && (answer != "No")) || (!std::cin))
        {
          std::cout << "Sorry, I didn't understand that.. Could you type your answer again?" << std::endl;
          std::cin >> answer;
          answer[0] = toupper(answer[0]);
        }
        if (answer == "No")
          break;
      }
    }
    else
    {
      std::cout << "This item does not exist in the database." << std::endl;
      flag = 0;
    }
    std::cout << "Would you like to modify another item?" << std::endl;
    std::cin >> answer;
    answer[0] = toupper(answer[0]);
    while (((answer != "Yes") && (answer != "No")) || (!std::cin))
    {
      std::cout << "Sorry, I didn't understand that.. Could you type your answer again?" << std::endl;
      std::cin >> answer;
      answer[0] = toupper(answer[0]);
    }
  } while (answer == "Yes"); // do/while loop keeps iterating if user wants to modify more items.
  if (flag == 1)
  {
    display = 1;
    updateDatabase(vitems, display);
  }
  if (answer == "No")
    return;
}

/**
 * void specificDisplay(std::vector<products> vitems)
 *
 * Parameters   : structure vector: 'vitems' Which contains all the items in the database.
 *
 * Return Value : Nothing.
 *
 * Description:
 *
 *    This function gets the user input of the type of
 *    display they would like.
 *    Afterwards, the approriate function is called
 *    depending on the user input
 */
void specificDisplay(std::vector<products> vitems)
{
  std::string itemType;
  int display;

  std::cout << "What type of items would you like to display?" << std::endl;
  std::cout << "1. Items low in stock" << std::endl;
  std::cout << "2. Items about to expire" << std::endl;
  std::cout << "3. Items of a certain type" << std::endl;

  bool flag = 0;
  while (!flag)
  {
    std::cin >> display;
    if (display > 3)
      std::cout << "That is not one of the options. Please try again." << std::endl;
    else if (std::cin.fail())
      std::cout << "Sorry, but you must only enter numbers. Could you try again?" << std::endl;
    else
      flag = 1;
    if (!flag)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    // https://stackoverflow.com/questions/13440831/how-do-i-check-if-input-is-an-integer-string
    // https://stackoverflow.com/questions/41475922/prompt-user-input-until-correct-c
    // https://stackoverflow.com/questions/69212175/c-program-does-not-allow-me-to-give-a-second-input
  }

  if (display == 1)
  {
    lowStock(vitems);
  }
  else if (display == 2)
  {
    expire(vitems);
  }
  else if (display == 3)
  {
    certainType(vitems);
  }
  return;
}

/**
 * void lowStock (std::vector<products> vitems)
 *
 * Parameters   : structure vector: 'vitems' Which contains all the items in the database.
 *
 * Return Value : Nothing.
 *
 * Description:
 *
 *    This function displays the items low in stock
 *    based on the user input and if desired, saves them by
 *    calling saveResults().
 */
void lowStock(std::vector<products> vitems)
{
  int number, file = 2;
  std::string itemName, option;
  std::cout << "How many items do you consider low in stock?" << std::endl;
  std::cin >> number;
  while (!std::cin)
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // https://stackoverflow.com/questions/13440831/how-do-i-check-if-input-is-an-integer-string
    // https://stackoverflow.com/questions/41475922/prompt-user-input-until-correct-c
    // https://stackoverflow.com/questions/69212175/c-program-does-not-allow-me-to-give-a-second-input
    std::cout << "Sorry, you must only enter numbers." << std::endl;
    std::cin >> number;
  }
  auto it = std::find_if(vitems.begin(), vitems.end(), [&](const products &p) -> int
                         // https://cplusplus.com/reference/algorithm/find_if/
                         // https://www.geeksforgeeks.org/lambda-expression-in-c/
                         { return p.quantity <= number; });
  // substr() function:
  // https://www.simplilearn.com/tutorials/cpp-tutorial/cpp-substring#:~:text=In%20C%2B%2B%2C%20a%20substring,characters%20from%20the%20starting%20position.
  if (it != vitems.end())
  {
    std::cout << "Would you like to add the filtered items to the file or do you want to display them?" << std::endl;
    std::cout << "1. Add to file" << std::endl;
    std::cout << "2. Display items" << std::endl;
    std::cin >> option;
    for (auto elem : vitems)
    {
      if (elem.quantity <= number)
      {
        if (option == "1")
        {
          itemName = elem.name;
          saveResults(itemName, vitems, file);
        }
        else if (option == "2")
        {
          std::cout << std::setw(13) << std::left << elem.name;
          std::cout << std::setw(15) << std::left << elem.DOE;
          std::cout << std::setw(9) << std::left << elem.quantity;
          std::cout << std::setw(9) << std::left << elem.price;
          std::cout << elem.type << std::endl;

          // https://www.youtube.com/watch?v=ytFT-1s7EWo&ab_channel=PortfolioCourses
        }
      }
    }
  }
  else
    std::cout << "There were no items with this quantity or lower in the database." << std::endl;
  return;
}

/**
 * void expire(std::vector<products> vitems)
 *
 * Parameters   : structure vector: 'vitems' Which contains all the items in the database.
 *
 * Return Value : Nothing.
 *
 * Description:
 *
 *    This function displays the items about to expire
 *    based on the user input and saves them to file by calling saveResults().
 */
void expire(std::vector<products> vitems)
{
  int days, counter = 0, flag = 0, file = 3;
  std::string option, itemName, answer;
  std::cout << "How many days into the future do you want to display?" << std::endl;
  std::cin >> days;
  while (!std::cin)
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Sorry, you must only enter numbers." << std::endl;
    std::cin >> days;
    // https://stackoverflow.com/questions/41475922/prompt-user-input-until-correct-c
    // https://stackoverflow.com/questions/69212175/c-program-does-not-allow-me-to-give-a-second-input
    // https://stackoverflow.com/questions/13440831/how-do-i-check-if-input-is-an-integer-string
  }
  /*
  References for getting current time and time conversion:

  https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
  https://cplusplus.com/reference/ctime/localtime/
  https://www.scaler.com/topics/char-array-to-string-cpp/
  https://stackoverflow.com/questions/3053999/c-convert-time-t-to-string-with-format-yyyy-mm-dd-hhmmss
  */
  char format[15];             // A characater array which will store the formatted string of the date.
  time_t current = time(NULL); // Getting the current time.
  while (counter < days)
  {
    strftime(format, 15, "%d/%m/%Y", localtime(&current));
    // strftime() formats the date from seconds into a string of format DD/MM/YYYY
    std::string date = "";
    for (int i = 0; i < 10; i++)
    {
      date = date + format[i];
      // Saving the array items into the empty string 'date'.
    }
    for (auto elem : vitems)
    {
      if (elem.DOE == date)
      {
        std::cout << std::setw(13) << std::left << elem.name;
        std::cout << std::setw(15) << std::left << elem.DOE;
        std::cout << std::setw(9) << std::left << elem.quantity;
        std::cout << std::setw(9) << std::left << elem.price;
        std::cout << elem.type << std::endl;
        itemName = elem.name;
        saveResults(itemName, vitems, file);

        // https://www.youtube.com/watch?v=ytFT-1s7EWo&ab_channel=PortfolioCourses
        flag = 1;
        // Setting flag to 1 to act as a check for whether there are items that will expire during the period of time until that day or not.
      }
    }
    current = current + 86400; // Increasing the current variable by a day in each iteration.
    counter = counter + 1;
  }
  if (flag == 0)
    std::cout << "There are no items that are going to expire in that number of days" << std::endl;
  return;
}

/**
 * void certainType(std::vector<products> vitems)
 *
 * Parameters   : structure vector: 'vitems' Which contains all the items in the database.
 *
 * Return Value : Nothing.
 *
 * Description:
 *
 *    This function displays items of a certain type
 *    based on the user input and if desired, saves them by
 *    calling saveResults().
 */
void certainType(std::vector<products> vitems)
{
  int file = 4;
  std::string itemType, option, itemName;
  std::cout << "Which type of items would you like to display?" << std::endl;
  std::cin >> itemType;
  itemType[0] = toupper(itemType[0]);
  auto it = std::find_if(vitems.begin(), vitems.end(), [&](const products &p) -> int
                         { return p.type == itemType; });
  if (it != vitems.end())
  {
    std::cout << "Would you like to add the filtered items to the file or do you want to display them?" << std::endl;
    std::cout << "1. Add to file" << std::endl;
    std::cout << "2. Display items" << std::endl;
    std::cin >> option;
    for (auto elem : vitems)
    {
      if (elem.type == itemType)
      {
        if (option == "1")
        {
          itemName = elem.name;
          saveResults(itemName, vitems, file);
        }
        else if (option == "2")
        {
          std::cout << std::setw(13) << std::left << elem.name;
          std::cout << std::setw(15) << std::left << elem.DOE;
          std::cout << std::setw(9) << std::left << elem.quantity;
          std::cout << std::setw(9) << std::left << elem.price;
          std::cout << elem.type << std::endl;
          // https://www.youtube.com/watch?v=ytFT-1s7EWo&ab_channel=PortfolioCourses
        }
      }
    }
  }
  else
    std::cout << "There is no item of this type in the database." << std::endl;
  return;
}

/**
 * void displayDatabase(std::vector<products> vitems)
 *
 * Parameters   : structure vector: 'vitems' Which contains all the items in the database.
 *
 * Return Value : Nothing.
 *
 * Description:
 *
 *    This function displays all of the items inside the
 *    'vitems' vector to the screen.
 */
void displayDatabase(std::vector<products> vitems)
{
  for (auto elem : vitems)
  {
    std::cout << std::setw(13) << std::left << elem.name;
    std::cout << std::setw(15) << std::left << elem.DOE;
    std::cout << std::setw(9) << std::left << elem.quantity;
    std::cout << std::setw(9) << std::left << elem.price;
    std::cout << elem.type << std::endl;
    // https://www.youtube.com/watch?v=ytFT-1s7EWo&ab_channel=PortfolioCourses
  }
  return;
  // return statements:
  // https://learn.microsoft.com/en-us/cpp/cpp/return-statement-cpp?view=msvc-170
}
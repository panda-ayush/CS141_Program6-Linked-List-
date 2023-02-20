/* main.cpp
  Program 6 March Madness Frenzy 2.0

   Author: Ayush Panda
   Date: 04/25/2022
   Class: CS 141, Spring 2022, UIC
   System: Mac OS using CLion

  Description: A C++ program that builds off of Program 5, by implementing the hierarchy of the NCAA Basketball Tournament brackets via linked lists.
*/

#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <cassert>    // For the assert statement
#include <vector>     // For vectors
#include <sstream>    // For reading in CSV file and splitting by commas

using namespace std;

class Node; // this is the declaration, so that it can be used inside class Game below
            // the definition of the Node class comes after the Game class

class Game {
    public:
        // Default up to Fully-Qualified Constructor
        Game(string region="N/A", int rankOne=-1, string teamOne="N/A", int scoreOne=-1,
             int rankTwo=-1, string teamTwo="N/A", int scoreTwo=-1, 
             string winningTeam="N/A", int roundNumber=-1, int gameNumber=-1)
        {
            this->region = region;
            this->team1Rank = rankOne;
            this->team1Name = teamOne;
            this->team1Score = scoreOne;
            this->team2Rank = rankTwo;
            this->team2Name = teamTwo;
            this->team2Score = scoreTwo;
            this->winningTeam = winningTeam;
            this->roundNum = roundNumber;
            this->gameNum = gameNumber;
            this->subBrackets = NULL;
        }

        // Copy Constructor
        Game(const Game & otherGame) {
            this->region = otherGame.region;
            this->team1Rank = otherGame.team1Rank;
            this->team1Name = otherGame.team1Name;
            this->team1Score = otherGame.team1Score;
            this->team2Rank = otherGame.team2Rank;
            this->team2Name = otherGame.team2Name;
            this->team2Score = otherGame.team2Score;
            this->winningTeam = otherGame.winningTeam;
            this->roundNum = otherGame.roundNum;
            this->gameNum = otherGame.gameNum;
            this->subBrackets = otherGame.subBrackets;
        }

        // Getters / Accessor methods
        string getRegion(){ return region; }
        int getRoundNum(){ return roundNum; }
        string getTeamOneName() { return team1Name; }
        int getTeamOneRank() { return team1Rank; }
        int getTeamOneScore() { return team1Score; }
        string getTeamTwoName() { return team2Name; }
        int getTeamTwoRank() { return team2Rank; }
        int getTeamTwoScore() { return team2Score; }
        string getWinner(){ return winningTeam; }
        Node* getSubBrackets() { return subBrackets; }

        // Setters / Mutator methods
        void setTeamOneName(string newTeamOneName) { this->team1Name = newTeamOneName; }
        void setTeamTwoName(string newTeamTwoName) { this->team2Name = newTeamTwoName; }
        void setWinner(string newWinner) { this->winningTeam = newWinner; }
        void setSubBrackets(Node* newSubBrackets) { this->subBrackets = newSubBrackets; }

        // Utility function to display the game
        void displayGame() {
            cout << "Round " << roundNum << ", Game " << gameNum << ": "
                 << team1Name << " vs " << team2Name << ". "
                 << "Winner: " << winningTeam << "\n";
        }
    
    private:
        string region;
        int roundNum;
        int gameNum;
        string team1Name;
        string team2Name; 
        string winningTeam;
        int team1Rank;
        int team2Rank;
        int team1Score;
        int team2Score;
        Node* subBrackets;  // This is a pointer to a Node, in order to represent the subbracts as a linked list
};

// Node class in order to implement linked lists
class Node {

    public:
        Node() {
            pNext = NULL;
        }

        Node(Game theSubBracket, Node* thePNext) {
            subBracket = theSubBracket;
            pNext = thePNext;
        }

        // ideally these should be private, but we are making them public to make the code a bit simpler
        Game subBracket;
        Node* pNext;
};

//--------------------------------------------------------------------------------
// Display welcome message, introducing the user to the program
void displayWelcomeMessage()
{
    cout << "Program 6: March Madness Frenzy 2.0\n"
        << "CS 141, Spring 2022, UIC\n"
        << "\n"
        << "This program reads in data from NCAA Basketball Tournaments (aka March Madness). "
        << "It uses the hierarchy of the brackets (implemented via linked lists) to allow you "
        << "to see the path taken to the championship, and evaluate the resulting brackets if "
        << "some games had a different outcome.\n"
        << endl;
}//end displayWelcomeMessage()

//--------------------------------------------------------------------------------
// Read in the game data and store in a vector
void readInGameData(string filename, vector<Game>& games) {

    string region, teamOne, teamTwo, winningTeam;
    int rankOne, rankTwo, roundNumber, gameNumber, scoreOne, scoreTwo;

    ifstream inStream;
    inStream.open(filename);
    assert(inStream.fail() == false);

    string row;
    getline(inStream, row); // read in header from file, and ignore

    // read in each line of the file
    while (getline(inStream, row)) {
        stringstream s_stream(row); //create stringstream from the row

        // separate the line by commas into each column
        int colNum = 0;
        while (s_stream.good()) {
            string columnVal;
            getline(s_stream, columnVal, ','); //get first string delimited by comma

            // use the substring to fill in the appropriate part of the BillboardRecord
            switch (colNum) {
                case 0:
                    region = columnVal;
                    break;
                case 1:
                    rankOne = stoi(columnVal);
                    break;
                case 2:
                    teamOne = columnVal; 
                    break;
                case 3:
                    if(columnVal != "") { scoreOne = stoi(columnVal); }
                    else { scoreOne = -1; }
                    break;
                case 4:
                    rankTwo = stoi(columnVal);
                    break;
                case 5:
                    teamTwo = columnVal;
                    break;
                case 6:
                    if(columnVal != "") { scoreTwo = stoi(columnVal); }
                    else { scoreTwo = -1; }
                    break;
                case 7:
                    winningTeam = columnVal;
                    break;
                case 8:
                    roundNumber = stoi(columnVal);
                    break;
                case 9:
                    gameNumber = stoi(columnVal);
                    break;
                default: // should not get here, because there are only 10 columns
                    cout << "More columns in the file than expected... Exiting program" << endl;
                    exit(0);
                    break;
            }
            colNum++;
        }
        // Create instance of the class using the column values
        Game oneGame;
        oneGame = Game(region, rankOne, teamOne, scoreOne, rankTwo, teamTwo, scoreTwo, winningTeam, roundNumber, gameNumber);
        // and add it to the vector
        games.push_back(oneGame);

    } // end while(getline(instream, row))

} // end readInGameData() function

//--------------------------------------------------------------------------------
// Identify the sub-brackets for each game and modify the class instances in the vector accordingly
void determineSubBrackets(vector<Game>& games) {

    // Nested loop to find the sub-brackets for each game
    // We go in reverse, starting at round 1 and going up to round 6
    //      Note - this is so that when we add subbrackets for round 6, the subbrackets for the games
    //             in round 5 have been determined, and so on and so forth
    for(int i=games.size()-1; i>=0; i--) {
        for(int j=games.size()-1; j>=0; j--) {
            // Check that we are not looking at the same game
            if(i==j) {
                continue;
            }
            // games[j] is a sub-bracket of games[i] if it is from the previous round,
            // and if the winning team from games[j] is one of the teams in games[i]
            if( (games.at(j).getRoundNum() == (games.at(i).getRoundNum() - 1)) &&
                (games.at(j).getWinner() == games.at(i).getTeamOneName() || games.at(j).getWinner() == games.at(i).getTeamTwoName()) ) {
              Node* head = new Node (games[j], games[i].getSubBrackets());
              games[i].setSubBrackets(head);
                    //Adds games[j] to the linked list of sub-brackets for games[i]
                }
        }
    }

} // end of determineSubBrackets() function

void recursiveOption2(string finalWinner, Game &option2) {
   Node* active = option2.getSubBrackets();
      
  do {
    if (active != NULL){
      if (active -> subBracket.getWinner() == finalWinner) {
         recursiveOption2(finalWinner, active->subBracket);
         active -> subBracket.displayGame();
      }
         active = active -> pNext;
  }
    }
    while (active != NULL);
}

void recursiveOption3(int round, Game &option3) {
   Node* active = option3.getSubBrackets();
   
   if (round == 1) {
      if (option3.getWinner() == option3.getTeamOneName()) {
         option3.setWinner(option3.getTeamTwoName());
      }
      else if (option3.getWinner() == option3.getTeamTwoName()) {
         option3.setWinner(option3.getTeamOneName());
      }
      return;
   }
  do {
    if (active != NULL){
     if (active -> subBracket.getWinner() == option3.getWinner()) {
         recursiveOption3(round - 1, active -> subBracket);
         
         if (option3.getWinner() == option3.getTeamOneName()) {
            option3.setWinner(active -> subBracket.getWinner());
            option3.setTeamOneName(active -> subBracket.getWinner());
         }
         if (option3.getWinner() == option3.getTeamTwoName()) {
            option3.setWinner(active -> subBracket.getWinner());
            option3.setTeamTwoName(active -> subBracket.getWinner());
         }
      }
      active = active -> pNext;
    }
  }
    while (active != NULL);
}
// ----------------------------------------------------------------------
// Main() function of the program
int main()
{
    //Vector to hold tournament games
    vector<Game> games;

    displayWelcomeMessage();
    bool condition = false;
    int menuOption;

    // Prompt user for the name of the file with the data
    string fileName;
    cout << "Enter the name of the file with the data for the NCAA tournament: ";
    cin >> fileName;

    // Read in the data from the file into a vector
    readInGameData(fileName, games);
    // Also identify sub-brackets for each game
    determineSubBrackets(games);
    condition = true;

    // TO DO: Handle the different menu options
  while(condition){
    cout << "Select a menu option: " << endl;
    cout << "\t1. See the sub-brackets of one game " << endl;
    cout << "\t2. Display the path of the winning team to the championship " << endl;
   cout << "\t3. Undo the championship game for a given number of rounds " << endl;
    cout << "\t4. Exit " << endl;
    cout << "Your choice --> ";
    cin >> menuOption;
    if (menuOption == 1) {
      int userRound;
      string userWinner;
      bool bracketBool = true;
      
      cout << "Enter the round number of the game: ";
      cin >> userRound;
      cout << "Enter the winning team of the game: ";
      getline(cin, userWinner);
      getline(cin, userWinner);

      Node* current;
      for (int i = 0; i < games.size(); i++){
        if (games[i].getRoundNum() == userRound && games[i].getWinner() == userWinner) {
          bracketBool = false;
          cout << "The game is:" << endl;

          games[i].displayGame();
          current = games[i].getSubBrackets();

          cout << "Sub-brackets of this game are:" << endl;

          while(current != NULL) {
            current->subBracket.displayGame();
            current = current->pNext;
          }
        }
      }
      if (bracketBool == true){
        cout << "Sorry, no games matching that round number and winning team were found." << endl;
      }
      continue;
    }
      
    else if (menuOption == 2){
      Node* active;
      string finalWinner = games[0].getWinner();

      cout << "Path to the championship: " << endl;

      recursiveOption2( finalWinner, games[0]);
      games[0].displayGame();
         
      continue;
      
    }
    else if (menuOption == 3){
      do {
        if (true){
            int userInput; 
            cout << "Enter the number of rounds that you would like to undo (max of 6 allowed):" << endl;
            cin >> userInput; 
            Game option3 = games[0];
            
            if (userInput >= 1 && userInput <= 6) {
               recursiveOption3 (userInput, option3);
               recursiveOption2(option3.getWinner(), games[0]);
               option3.displayGame();
            }
            else {
               cout << "Invalid entry. Try again." << endl;
               
               continue;
            }
            break;
        }
      }
        while (true);
         
         continue;
    }
    else if (menuOption == 4) {
      break;
    }
    else {
      cout << "Invalid value. Please re-enter a value from the menu options below." << endl;
    }
  }

    cout << "Exiting program...";

    return 0;
} // end main()
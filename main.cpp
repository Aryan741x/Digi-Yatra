#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <random>
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
using namespace std;

class Dijkstras
{
private:
    vector<vector<int>> graph;
    int number_of_vertices;

public:
    void accept(int n)
    {
        number_of_vertices = n;
        graph.resize(number_of_vertices, vector<int>(number_of_vertices, 0));

        for (int i = 0; i < number_of_vertices; i++)
        {
            for (int j = 0; j < number_of_vertices; j++)
            {
                if (i != j)
                {
                    cout << "\t\t\tEnter distance between city " << i + 1 << " and city " << j + 1 << ": ";
                    cin >> graph[i][j];
                }
            }
        }
    }

    void display()
    {
        cout << "\t\t\tGraph:" << endl;
        for (int i = 0; i < number_of_vertices; i++)
        {
            for (int j = 0; j < number_of_vertices; j++)
            {
                cout <<"\t\t\t"<<graph[i][j] << " ";
            }
            cout << endl;
        }
        cout<<endl;
    }

    int calculate_distance(int source, int destination)
    {
        vector<int> distance(number_of_vertices, numeric_limits<int>::max());
        vector<bool> visited(number_of_vertices, false);

        distance[source - 1] = 0;

        for (int i = 0; i < number_of_vertices - 1; i++)
        {
            int min_distance = numeric_limits<int>::max();
            int min_index = -1;

            for (int j = 0; j < number_of_vertices; j++)
            {
                if (!visited[j] && distance[j] < min_distance)
                {
                    min_distance = distance[j];
                    min_index = j;
                }
            }

            visited[min_index] = true;

            for (int j = 0; j < number_of_vertices; j++)
            {
                if (!visited[j] && graph[min_index][j] != 0 && distance[min_index] != numeric_limits<int>::max() &&
                        distance[min_index] + graph[min_index][j] < distance[j])
                {
                    distance[j] = distance[min_index] + graph[min_index][j];
                }
            }
        }

        return distance[destination - 1];
    }
};
bool isValid(vector<vector<int>>& board, int row, int col, int num)
{
    for (int x = 0; x < 9; ++x)
    {
        if (board[row][x] == num || board[x][col] == num || board[3 * (row / 3) + x / 3][3 * (col / 3) + x % 3] == num)
        {
            return false;
        }
    }
    return true;
}
bool solveSudoku(vector<vector<int>>& board)
{
    for (int row = 0; row < 9; ++row)
    {
        for (int col = 0; col < 9; ++col)
        {
            if (board[row][col] == 0)
            {
                for (int num = 1; num <= 9; ++num)
                {
                    if (isValid(board, row, col, num))
                    {
                        board[row][col] = num;
                        if (solveSudoku(board))
                        {
                            return true;
                        }
                        else
                        {
                            board[row][col] = 0;
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}
int main()
{
    cout<<CYAN<<"\t\t\t\t\t\tWELCOME"<<endl;
    cout<<GREEN<<"\t\t\t\tJAYPEE INSTITUTE OF INFORMATION TECHNOLOGY-128"<<endl;
    cout<<"\n";
    cout<<YELLOW<<"\t\t\t\t\t\tProject"<<endl;
    cout<<"\t\t\t\t\t"<<"      DIJI-YATRA\n";
    string password;
    string role;

    double busFare = 1.5; // per km
    double trainFare = 2.0; // per km
    double metroFare = 2.5; // per km

    int number_of_vertices = 0;
    cout <<CYAN<< "\n\t\t\tEnter number of cities: ";
    cin >> number_of_vertices;
    cout<<endl;
    Dijkstras busObj, trainObj, metroObj;

    while (true)
    {
        cout << "\t\t\tEnter your role (admin/customer/exit): ";
        cin >> role;
        cout<<endl;
        if (role == "exit")
        {
            break;
        }

        cout << "\t\t\tEnter your password: ";
        cin >> password;
        cout<<endl;
        if (role == "admin")
        {
            if (password == "admin123")
            {
                cout << "\t\t\t\t\tAccess granted to admin." << endl;
                cout << "\t\t\tEnter new fare for bus travel: ";
                cin >> busFare;
                cout << "\t\t\tEnter new fare for train travel: ";
                cin >> trainFare;
                cout << "\t\t\tEnter new fare for metro travel: ";
                cin >> metroFare;
                cout<<endl;
                cout << "\t\t\tEnter distances for bus travel:" << endl;
                busObj.accept(number_of_vertices);
                busObj.display();

                cout << "\t\t\tEnter distances for train travel:" << endl;
                trainObj.accept(number_of_vertices);
                trainObj.display();

                cout << "\t\t\tEnter distances for metro travel:" << endl;
                metroObj.accept(number_of_vertices);
                metroObj.display();
            }
            else
            {
                cout << "\t\t\tIncorrect password for admin." << endl;
                continue;
            }
        }
        else if (role == "customer")
        {
            if (password == "cust123")
            {
                cout << "\t\t\t\t\tAccess granted to customer." << endl;
                cout<<endl;
                int source = 0;
                int destination = 0;
                cout << "\t\t\tEnter source city number: ";
                cin >> source;
                cout << "\t\t\tEnter destination city number: ";
                cin >> destination;

                string useBus, useTrain, useMetro;
                cout << "\t\t\tDo you want to use bus? (yes/no): ";
                cin >> useBus;
                cout << "\t\t\tDo you want to use train? (yes/no): ";
                cin >> useTrain;
                cout << "\t\t\tDo you want to use metro? (yes/no): ";
                cin >> useMetro;
                cout<<endl;
                double minPrice = numeric_limits<double>::max();
                string minTransport = "";

                random_device rd;
                mt19937 gen(rd());
                uniform_int_distribution<> dis(100000, 999999);

                if (useBus == "yes")
                {
                    int busDistance = busObj.calculate_distance(source, destination);
                    cout << "\t\t\tThe shortest bus distance between city " << source << " and city " << destination << " is: " << busDistance << endl;
                    double busPrice = busDistance * busFare;
                    cout << "\t\t\tYour bus ticket number is: " << dis(gen) << endl;
                    cout<<endl;
                    if (busPrice < minPrice)
                    {
                        minPrice = busPrice;
                        minTransport = "bus";
                    }
                }

                if (useTrain == "yes")
                {
                    int trainDistance = trainObj.calculate_distance(source, destination);
                    cout << "\t\t\tThe shortest train distance between city " << source << " and city " << destination << " is: " << trainDistance << endl;
                    double trainPrice = trainDistance * trainFare;
                    cout << "\t\t\tYour train ticket number is: " << dis(gen) << endl;
                    cout<<endl;
                    if (trainPrice < minPrice)
                    {
                        minPrice = trainPrice;
                        minTransport = "train";
                    }
                }

                if (useMetro == "yes")
                {
                    int metroDistance = metroObj.calculate_distance(source, destination);
                    cout << "\t\t\tThe shortest metro distance between city " << source << " and city " << destination << " is: " << metroDistance << endl;
                    double metroPrice = metroDistance * metroFare;
                    cout << "\t\t\tYour metro ticket number is: " << dis(gen) << endl;
                    cout<<endl;
                    if (metroPrice < minPrice)
                    {
                        minPrice = metroPrice;
                        minTransport = "metro";
                    }
                }

                cout << "\t\t\tThe optimum price for travelling from city " << source << " to city " << destination << " is by " << minTransport << " and it is: " << minPrice << endl;
            }
            else
            {
                cout << "\t\t\tIncorrect password for customer." << endl;
                continue;
            }
            string solveSudokuOpt;
            cout << "\t\t\tDo you want to solve a Sudoku puzzle? (yes/no): ";
            cin >> solveSudokuOpt;
            if (solveSudokuOpt == "yes")
            {

                vector<vector<int>> sudokuBoard =
                {
                    {5, 3, 0, 0, 7, 0, 0, 0, 0},
                    {6, 0, 0, 1, 9, 5, 0, 0, 0},
                    {0, 9, 8, 0, 0, 0, 0, 6, 0},
                    {8, 0, 0, 0, 6, 0, 0, 0, 3},
                    {4, 0, 0, 8, 0, 3, 0, 0, 1},
                    {7, 0, 0, 0, 2, 0, 0, 0, 6},
                    {0, 6, 0, 0, 0, 0, 2, 8, 0},
                    {0, 0, 0, 4, 1, 9, 0, 0, 5},
                    {0, 0, 0, 0, 8, 0, 0, 7, 9}
                };
                cout << "\t\t\tSudoku puzzle to solve:" << endl;
                cout<<endl;

                for (const auto& row : sudokuBoard)
                {
                    cout<<"\t\t\t\t\t";
                    for (int val : row)
                    {
                        cout <<YELLOW<< val << " ";
                    }
                    cout << endl;
                }
                string ghf;
                cout<<"\t\t\tDo you want its solution now(yes/no):";
                cin>>ghf;
                if(ghf=="yes")
                {
                    if (solveSudoku(sudokuBoard))
                    {
                        cout << "\t\t\tSolved Sudoku puzzle:" << endl;
                        cout<<endl;
                        for (const auto& row : sudokuBoard)
                        {
                            cout<<"\t\t\t\t\t";
                            for (int val : row)
                            {
                                cout << val << " ";
                            }
                            cout << endl;
                        }
                    }
                    else
                    {
                        cout << "\t\t\tNo solution exists for the provided Sudoku puzzle." << endl;
                    }
                }
                cout<<CYAN;
            }
        }
        else
        {
            cout << "Invalid role entered." << endl;
            continue;
        }
    }

    return 0;
}

#include <iostream>
#include <thread>
#include <vector>

void bubbleDisplay(const std::vector<int>& vec, int comp) 
{
    std::cout << "\nTotal Comparisons #" << comp << "\n\n";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::string spacers{};
        int val_len = 0, cpy = vec[i];
        while(cpy!=0){
            val_len++;
            cpy /= 10;
        }

        if (val_len == 0 || val_len == 1)
            spacers = "  : ";
        else if (val_len == 2)
            spacers = " : ";
        else
            spacers = ": ";

        std::cout << "  "<< vec[i] <<spacers;
        for(int j = 0; j < vec[i]; j++)
            std::cout << "#";

        std::cout << '\n';
    }
}

void bubbleSort() 
{
    int size{};
    std::cout << "\n\n  Enter number of elements: ";
    std::cin >> size;
    std::vector<int> vec;
    std::cout<<"\n  Enter the elements: ";

    while (size--) {
        int i;
        std::cin >> i;
        vec.push_back(i);
    }

    int comparison = 0;
    for (size_t i = 0; i < vec.size() - 1; i++) {
        int swp = 0;
        for (size_t j = 0; j < vec.size() - i - 1; j++) {
            if (vec[j] > vec[j+1]) {
                swp = 1;
                std::swap(vec[j], vec[j+1]);
                comparison++;
            }

#if __linux__
            system("clear");
#elif _WIN32
            system("cls");
#endif

            bubbleDisplay(vec, comparison);
            if (swp == 0)
                std::cout << "\n\n " << vec[j] <<" is less than "<<vec[j+1]<<" no swaps!\n\n";
            else
                std::cout << "\n\n " << vec[j] << " and " << vec[j+1] << " are swapped!\n\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }

#if __linux__
    system("clear");
#elif _WIN32
    system("cls");
#endif

    std::cout << "\nSorted Array: \n";
    bubbleDisplay(vec, comparison);
}


int counter = 0;
std::vector<int> from, aux, to;

void printTower(int comp) 
{
#if __linux__
    system("clear");
#elif _WIN32
    system("cls");
#endif

    std::cout<<"\n\n1st Tower: ";
    for (auto i : from) std::cout<<i<<" ";
    std::cout<<"\n\n2nd Tower: ";
    for (auto i : aux) std::cout<<i<<" ";
    std::cout<<"\n\n3rd Tower: ";
    for (auto i : to) std::cout<<i<<" ";
    std::cout<<"\n\nMove #"<<comp<<"\n\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

void towerOfHonai(int n, std::vector<int>& from, std::vector<int>& to, std::vector<int>& aux) 
{
    if (n == 1) 
    {
        counter++;
        to.push_back(from.back());
        from.pop_back();
        printTower(counter);
        return;
    }

    towerOfHonai(n - 1, from, aux, to);
    to.push_back(from.back());
    from.pop_back();
    counter++;
    printTower(counter);
    towerOfHonai(n - 1, aux, to, from);
}

void hanoiStarter() 
{
    int n{};
    std::cout << "\n  Enter number of discs: ";
    std::cin >> n;
    for (int i = n; i >= 1; i--)
        from.push_back(i);
    towerOfHonai(n, from, to, aux);
}

struct Node 
{
    int data;
    Node* next;
};

void push(Node** head, int value) 
{
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = *head;
    *head = newNode;
}

void pop(Node** head) 
{
    if (*head == nullptr) {
        return;
    } else {
        Node* temp = *head;
        *head = (*head)->next;
        delete temp;
    }
}

void displayPostfix(Node* head) 
{
    Node* ptr = head;
    std::cout<<"\nStack (Linked List): \n\n";
    std::cout<<"[ " << ptr->data << " | next -> " << &(ptr->next) <<" ] <--- Top\n";

    if (ptr != NULL) ptr = ptr->next;

    while(ptr!=nullptr) 
    {
        std::cout<<"[ " << ptr->data << " | next -> " << &(ptr->next) <<" ]";
        ptr = ptr->next;
        std::cout << "\n";
    }
    std::cout << "[   NULL   ]\n\n";
}

void postfix()
{
    std::string expr{};
    Node* head= nullptr;
    std::cout << "\n\nEnter Postfix Expression: ";
    std::cin >> expr;

    for (int i = 0; expr[i] != 0; ++i) {

#if __linux__
        system("clear");
#elif _WIN32
        system("cls");
#endif

        std::cout << "\nExpression: " << expr <<"\n";
        std::cout << "\nCurrent Token: "<< expr[i] <<'\n';

        if (isspace(expr[i])) continue;
        
        if (isdigit(expr[i])) {
            std::cout<<"Action: Push "<<expr[i]<<" to the stack\n";
            push(&head, expr[i] - '0');
        } else {
            int op2 = head->data;
            pop(&head);
            int op1 = head->data;
            pop(&head);

            int result;
            switch(expr[i]){
                case '+': 
                    result = op1 + op2; 
                    std::cout<<"Action: Add "<< op1 << " and " << op2 << ", then push result: "<< result <<"\n";
                    break;
                case '-': 
                    result = op1 - op2; 
                    std::cout<<"Action: Subtract "<< op2 <<" from "<< op1 <<", then push result: "<< result <<"\n";
                    break;
                case '*': 
                    result = op1 * op2; 
                    std::cout<<"Action: Multiply "<< op2 <<" and " << op1 << ", then push result: "<< result <<"\n";
                    break;
                case '/':
                    if (op2 == 0) return;
                    result = op1 / op2;
                    std::cout<<"Action: Divide "<<op2<<" and " << op1 << ", then push result: "<< result <<"\n";
                    return;
                default:
                    return;
            }

            push(&head, result);
        }
        displayPostfix(head); 
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    std::cout << "\nFinal evaluated Result: "<< head->data <<"\n\n";
}

int main() 
{
    std::cout << "\n\n\t\tAlgorithm Visualizer";
    std::cout << "\n\n\t[1] BubbleSort Visualizer\n\t[2] Tower Of Hanoi Visualizer";
    std::cout << "\n\t[3] Postfix Evaluation with Linked Stack Visual\n\n\tchoose: ";

    int n{};
    std::cin >> n;
    switch(n) {
        case 1:
            bubbleSort();
            break;
        case 2:
            hanoiStarter();
            break;
        case 3:
            postfix();
            break;
        default:
            break;
    } 
}

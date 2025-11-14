/*
Write a function called deleteRepeats that has a partially filled array of characters
as a formal parameter and that deletes all repeated letters from the array. Since a
partially filled array requires two arguments, the function will actually have two
formal parameters: an array parameter and a formal parameter of type int that
gives the number of array positions used. When a letter is deleted, the remaining
letters are moved forward to fill in the gap. This will create empty positions at
the end of the array so that less of the array is used. Since the formal parameter is
a partially filled array, a second formal parameter of type int will tell how many
array positions are filled. This second formal parameter will be a call-by-reference
parameter and will be changed to show how much of the array is used after the
repeated letters are deleted. For example, consider the following code:
char a[10];
a[0] = 'a';
a[1] = 'b';
a[2] = 'a';
a[3] = 'c';
int size = 4;
deleteRepeats(a, size);
After this code is executed, the value of a[0] is 'a', the value of a[1] is 'b', the
value of a[2] is 'c', and the value of size is 3. (The value of a[3] is no longer
of any concern, since the partially filled array no longer uses this indexed variable.)
You may assume that the partially filled array contains only lowercase letters. Embed
your function in a suitable test program.
*/

#include <iostream>
#include <limits>
#include <span>

constexpr int SIZE = 10;

void fillArray(char letters[], std::size_t size, int& numberUsed);

void removeDuplicates(char letters[], std::size_t size, int& numberUsed);

int main( ) {
    int numberUsed = 0;
    char letters[SIZE];
    fillArray(letters, std::size(letters), numberUsed);
    for (const char element : std::span(letters, numberUsed))
        std::cout << element << " ";

    std::cout << "\n";
    return 0;
}

void fillArray(char letters[], std::size_t size, int& numberUsed) {
    std::size_t idx = 0;
    std::string next;
    std::cout << "Enter up to " << size << " letters (-1 to end).\n";

    while (idx < size) {
        if (!(std::cin >> next)) {
            std::cout << "Not a letter\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (next == "-1")
            break;
        if (next.size() != 1 || !std::isalpha(static_cast<unsigned char>(next[0])) ) {
            std::cout << "Please insert a letter or -1 to exit\n";
            continue;
        }

        letters[idx++] = next[0];
        ++numberUsed;
    }
}

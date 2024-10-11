#include "clases/LinkedList.h"
    
using namespace std;

int main()
{
    LinkedList list1 = LinkedList();
    list1.addFile("bitacora-1");

    cout << list1.getHead()->ipComparableValue;
    
    list1.exportToTxt("bitacoraOrdenadaIP-Eq2");
    return 0;
}



// liste_doublement_chainee_v1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "ldc.h"
#include "client.h"

int main()
{

    struct Ldc* list;
    struct Client* client1, * client2, * client3, * client4, * client5, * client6;

    list = ldc_new();

    client1 = client_new("Einstein", "Albert", 1);
    client2 = client_new("Newton", "Isaac", 2);
    client3 = client_new("Turing", "Alan", 3);
    client4 = client_new("Hubblie", "Edwin", 4);
    client5 = client_new("Musk", "Elon", 5);
    client6 = client_new("Tesla", "Nicolas", 6);

    ldc_insert(list, client5, client_compare);
    ldc_insert(list, client1, client_compare);
    ldc_insert(list, client6, client_compare);
    ldc_insert(list, client3, client_compare);
    ldc_insert(list, client2, client_compare);
    ldc_insert(list, client4, client_compare);

    ldc_display_asc(list, client_display);
    //ldc_display_desc(list, client_display);

    ldc_remove(list, client1, client_compare, client_del);
    ldc_remove(list, client4, client_compare, client_del);
    ldc_remove(list, client2, client_compare, client_del);

    ldc_display_asc(list, client_display);

    ldc_del(list, client_del);

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

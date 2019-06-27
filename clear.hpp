#include <iostream>
//my try on making system-wide screen clears
#if defined (_WIN32) || defined(_WIN64)
void clear(void){
    system("cls");
}
#endif //windows check
#if defined(__unix)
void clear(void){
    system("clear");
}
#endif //linux check
#if ((!defined(__unix)) && (!defined(_WIN32)) && (!defined(_WIN64)))
void clear(void){
    for(int i=0; i < 100; ++i)
        std::cout << "\n";
}
#endif //not windows or unix
#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#include <type_traits>
#include <stack>
#include <queue>


template <typename T>
void print(const T& cont) {
    if constexpr (std::is_pointer<
                                  std::decay_t<
                                               decltype(*std::begin(cont))
                                                                          >
                                                                           >() ) {
        for(auto &el : cont) {
            std::cout << *el << ' ';
        }
    }
    else {
        for(auto &el : cont) {
            std::cout << el << ' ';
        }
    }
    std::cout << '\n';
}

template<typename F, typename S>
auto sum(const F& f, const S& s) {
    if constexpr (std::is_same< std::vector<S>, F>()) {
        std::vector<S> vs = f;
        for (auto &el : vs) {
            el += s;
        }
        return vs;
    }
    else {
        return f + s;
    }
}

template<typename F>
void adapter_print(F &f) {
    if constexpr (std::is_same <std::stack<typename F::value_type>, F> () ||
                  std::is_same <std::priority_queue<typename F::value_type>, F> () ) {
        if constexpr ( std::is_pointer <typename F::value_type> ()) {
            while(!f.empty()) {
                std::cout << *f.top() << ' ';
                f.pop();
            }
        }
        else {
            while (!f.empty()) {
                std::cout << f.top() << ' ';
                f.pop();
            }
        }
    }
    else if constexpr (( std::is_same <std::queue<typename F::value_type>, F> ())) {
        if constexpr ( std::is_pointer <typename F::value_type> ()) {
            while (!f.empty()) {
                std::cout << *f.front() << ' ';
                f.pop();
            }
        }
        else {
            while (!f.empty()) {
                std::cout << f.front() << ' ';
                f.pop();
            }
        }
    }
    else {
        std::cerr << "ERROR TYPE";
    }
    std::cout<< '\n';
}


class myFunc{
public:
    bool operator() (const std::shared_ptr<std::string>& l, const std::shared_ptr<std::string>& r) const {
        return *l < *r;
    }
};

bool alphaCheck(const std::string str) {
    for (const auto& ch : str) {
        if (!isalpha(ch)) return false;
    }
    return true;
}

bool digitCheck(const std::string str) {
    for (const auto& ch : str) {
        if (!isdigit(ch)) return false;
    }
    return true;
}


size_t findSum(const std::vector<std::shared_ptr<std::string>>& v){
    size_t res = 0;
    for (auto &ptr : v) {
        for (auto& ch : *ptr) {
            int i = ch - '0';
            res += i;
        }
    }
    return res;
}

int main()
{

/***************************************************************/
//Задание 1.

    /*
    Реализуйте шаблон функции для печати любых последовательностей (vector, list, deque, set и встроенного массива), которые могут содержать:
    •	как объекты любого типа,
    •	так и указатели на объекты любого типа (указатели распечатывать неинтересно => в этом случае следует получать значение по адресу)
    Подсказки: if constexpr
    */
    {
        std::vector <std::string*> vs = {new std::string("aaa"), new std::string("bb"), new std::string("ccc")};
        print(vs);

        for(auto &el : vs)
        {
            delete el;
        }

        int* ar[4] = {new int(1), new int(2), new int(3), new int(4)};
        print(ar);

        for(auto &el : ar)
        {
            delete el;
        }

        std::vector <int> vi = {5,6,7,8};
        print(vi);
    }

/***************************************************************/
//Задание 2.
    /* Реализуйте шаблон функции сложения двух значений.
    Если первое слагаемое является вектором, то все элементы вектора нужно увеличить на значение второго параметра.
    При этом элементы вектора и второй параметр должны быть одного и того же типа.
    Подсказки: if constexpr, is_same
    */
    {
        std::cout << sum(3.5, 5) << '\n';
        std::vector<int> vi = {1,2,3,4,5};
        vi = sum(vi, 45);
        print(vi);


    }


    /***************************************************************/
//Задание 3.
    /* 	Реализуйте шаблон функции вывода на печать значений элементов любого адаптера (stack, queue, priority_queue)
    Подсказки: if constexpr, is_same
    Предусмотрите вывод значений, если в адаптере хранятся указатели.
    */
    {
        std::stack <int> si;
        std::queue <int> qi;
        std::priority_queue <int> pqi;
        for( size_t i = 0; i < 5; i++) {
            si.push(i);
            qi.push(i);
            pqi.push(i);
        }


       adapter_print(si);
       adapter_print(qi);
       adapter_print(pqi);

       int* ar[4] = {new int(1), new int(2), new int(3), new int(4)};

       std::queue <int*> qip;

       for( int i = 0; i < 4; i++) {
           qip.push(ar[i]);
       }

       adapter_print(qip);
    }

/***************************************************************/
//Задание 4.
    {
        //Дан массив элементов типа string
        std::string strings[] = {"zzz", "abc", "123", "qwerty", "#$%"};
        //До завершения фрагмента строки должны существовать в единственном экземпляре.
        //Требуется обеспечить манипулирование строками а) без копирования и б) без изменения порядка
        //элементов в массиве!

        //В std::set "складываем" по алфавиту обертки для строк, которые содержат только буквы

        auto lamb = [](std::string* sp){sp = nullptr; };


        std::set <std::shared_ptr<std::string>, myFunc> alphaStr;

        for(size_t i = 0; i < std::size(strings); i++)
        {
            if ( alphaCheck(strings[i])) {
                alphaStr.insert(std::shared_ptr<std::string>(&strings[i], lamb));
            }
        }

        for( auto & el : alphaStr) {
            std::cout<< *el << ' ';
        }
        std::cout << '\n';

        /******************************************************************************************/

        //В std::vector "складываем" обертки для строк, которые содержат только цифры
        //Выводим на экран
        //Находим сумму

        std::vector<std::shared_ptr< std::string>> vecStr;

        for(size_t i = 0; i < std::size(strings); i++)
        {
            if ( digitCheck(strings[i])) {
                vecStr.push_back(std::shared_ptr<std::string>(&strings[i], lamb));
            }
        }

        for( auto & el : vecStr) {
            std::cout<< *el << ' ';
        }

        std::cout<< "Sum = "<<findSum(vecStr) << '\n';

        /******************************************************************************************/
        //сюда "складываем" обертки для строк, которые не содержат ни символов букв, ни символов цифр
        //и просто выводим


    }


/******************************************************************************************/
//Задание 5.
    {
        //Дано:
        std::string ar[] = {"my","Hello", "World"};
        std::vector < std::shared_ptr<std::string>> v = {std::make_shared<std::string>("good"), std::make_shared<std::string>("bye")};



        //а) Требуется добавить в вектор обертки для элементов массива, НЕ копируя элементы массива!
        //б) Отсортировать вектор по алфавиту и вывести на экран
        //в) Обеспечить корректное освобождение памяти



    }
    /***************************************************************/
        //Задание 6. shared_ptr и weak_ptr
        //Создаем генеалогическое дерево посредством класса human. В классе хранятся:
        //имя - string
        //возможно признак: жив или уже нет...
        //родители - shared_ptr (родители не всегда известны...)
        //дети - контейнер из weak_ptr (чтобы избежать циклических зависимостей)

        //Методы класса human:
        //конструктор - для инициализации имени и признака
        //конструктор копирования, оператор присваивания, move ???
        //статический метод child() -
        //				должен создать создать и вернуть обертку для родившегося человека
        //				+ сформировать все связи ребенка с родителями и наоборот

        //Ввести возможность распечатать генеалогическое дерево для указанного индивидума

    {
        //История должна с кого-то начинаться => "Жили-были дед да баба, например, Адам и Ева"
        //(то есть на самом деле два деда и две бабы):


        //std::shared_ptr<human> grandM1(new human("Eva"));
        //...

        //у них появились дети - child():


        //а у детей в свою очередь свои дети:


        //...

    }



//***************************************************************/
//Задание 7.

    /*Пользовательский deduction guide – для вывода типов параметров шаблона
    Задан шаблон класса, который инкапсулирует внедренный ограниченный массив известной
    размерности с элементами любого типа. */
/*
template<typename T, size_t size> class MyArray
    {
        T ar[size]; //как обеспечить инициализацию элементов базового типа по умолчанию нулем?
        …
    };

*/
/*
//Требуется обеспечить работоспособность приведенных примеров использования.
    {
        MyArray<int, 5> ar1;//MyArray<int,5>
        MyArray ar2{"ABC"}; //MyArray<char,4>
        int ar[] = { 1,2,3 };
        MyArray ar3{ ar };

    }
*/



}

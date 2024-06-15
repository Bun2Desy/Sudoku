# Игра Sudoku
## Краткое описание
Игра Sudoku с возможностью одиночной игры и игры вдвоём. Поле 9х9 разделено на 9 квадратов 3х3. Некоторые ячейки заполнены цифрами. Для победы необходимо заполнить весь квадрат 9х9 цифрами от 1 до 9 так, чтобы выполнялись следующие условия:
* В любой строчке каждая цифра повторяется ровно один раз
* В любом столбце каждая цифра повторяется ровно один раз
* В любом квадрате 3х3 каждая цифра повторяется ровно один раз

## Функционал игры
### Генерация
Алгоритм генерации полей прописан так, что они всегда имеют уникальное решение.

### Мультиплеер
В данной игре предусмотрена возможность игры как одному, так и вдвоём (в мультиплеере ходы идут асинхронно). В режиме мультиплеера подключение к серверу происходит по ip. Пользователь вводит ip и по нему происходит подключение клиентов к общему серверу.

### Сложность
В игре доступно 3 уровня сложности: 
* Easy - 40 пустых ячеек
* Normal - 50 пустых ячеек
* Hard - 55 пустых ячеек

### Время и ошибки
Во время игры идёт время, которое в случае победы сравнивается с лучшим временем и записывается как результат игры. Также во время игры идёт подсчёт ошибок. Если игрок ошибся 3 раза, то игра заканчивается.

## Установка
Данная игра основана на двух внешних библиотеках: ***Qt*** и ***Boost***. Ниже будет описан принцип установки этих библиотек.

### Qt
Qt - библиотека для создания приложений с графичеким интерфейсом. Для установки понадобится скачать с официального сайта [Qt Online Installer](https://www.qt.io/download-dev). На территории РФ скачать установщик не получится, поэтому используем ВПН(например ***PlanetVPN***). Для успешной работы программы необходимо:
1. Во время установки указать путь C:/Qt
2. Установить Qt версии 6.6.3
3. В системную переменную среды Path добавить путь С:/Qt/6.6.3/mingw_64/bin

### Boost
Достаточно обширная библиотека, но нам достаточно будет Boost.Asio. Данная библиотека необходима для работы сетевой части игры. Устанавливаем с официального сайта Boost версию [1.84.0](https://www.boost.org/users/history/version_1_84_0.html). Извлекаем так, чтобы все файлы(один из них bootstrap.bat) лежали по пути: С:/boost_1_84_0. После этого в терминале из папки boost_1_84_0 вводим следующие команды:
1. *bootstrap.bat*
2. *.\b2 --toolset=msvc-14.3 --build-type=complete --with-system*
3. *.\b2 --toolset=gcc-13 --build-type=complete --with-thread --with-chrono --with-date_time*

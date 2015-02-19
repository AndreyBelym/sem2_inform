#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED
/*
Функция Compare сравнивает 2 числа a и b.
Если a<b, возвращается -1; если равны - возвращается 0;
    если больше - 1.
Параметры:
a,b - числа для сравнения.
Локальные переменные:
отсутствуют.
*/
int Compare(double a,double b);


/*
Функция clearline очищает строку в файле f. Возвращает количество
непробельных символов в считанной строке.
Параметры:
f - Файл для очистки строки.
Локальные переменные:
count - количество непробельных символов;
ch - текущий считанный символ.
*/
int clearline(FILE *f);


/*
Функция GetReqResult позволяет получить ответ "да" или "нет" от пользователя.
Возвращает 1 в случае согласия пользователя, 0 - в случае несогласия.
Параметры:
отсутствуют.
Локальные переменные:
answer - текущий ответ пользователя.
*/
int GetReqResult();


/*
Функция GetOption позволяет выбрать пользователю один из нескольких(до 10) вариантов,
представленных цифрами от a до b. Возвращает символ, соответствующий выбранной цифре.
Параметры:
a,b - границы предлагаемых вариантов.
Локальные переменные:
ch - текущий ответ пользователя;
ok - флаг отсутствия ошибки (1 - нет ошибки).
*/
char GetOption(char a,char b);


/*
Функция fexists() проверяет существование файла с именем fname.
Возвращает 1, если такой файл существует, или 0, если нет.
Параметры:
fname - имя файла для проверки.
Локальные переменные:
f - временный файл для проверки.
*/
int fexists(char  *fname);


/*
Функция GetInFile() получает файл f для чтения.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
f - запрашиваемый файл.
Локальные переменные:
error - флаг ошибки (1 - ошибка);
req_rslt - флаг ответа пользователя (1 - согласие пользователя).
*/
int GetInFile(FILE **f);


/*
Функция GetOutFile() получает файл f для записи.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
f - запрашиваемый файл.
Локальные переменные:
error - флаг ошибки (1 - ошибка);
req_rslt - флаг ответа пользователя (1 - согласие пользователя).
*/
int GetOutFile(FILE **f);


/*
Процедура PrintVector() печатает массив array размером size файл f.
Параметры:
f - файл для вывода;
array - массив для вывода;
size - размер массива.
Локальные переменные:
i - переменная-счетчик.
*/
void PrintVector(FILE *f,double array[],long size);


/*
Основная часть программы поиска количества элементов массива,
различных относительно заданного числа (больше,меньше или равно).
Переменные:
size - размер массива;
array - обрабатываемый массив;
K - число для сравнения элементов массива;
und,eq,ov - кол-во элементов меньших, равных и больших K;
i - переменная-счетчик.
*/
int main();


/*
Функция Input() получает от пользователя некоторое вещественное число param.
При этом она в процессе запроса выводит поясняющее сообщение message,
и приглашение ко вводу в виде имени параметра - name.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
message - сообщение о параметре;
name - имя параметра;
param - запрашиваемый параметр.
Локальные переменные:
ok - флаг отсутствия ошибки (1 - нет ошибки);
req_rslt - флаг ответа пользователя (1 - согласие пользователя).
*/
int Input(const char message[],
              const char name[],
              double *param
                    );


/*
Функция InputIndex() получает от пользователя индекс массива -
некоторое длинное целое число index из промежутка от 0 до верхней границы h_bound.
При этом она в процессе запроса выводит поясняющее сообщение message,
и приглашение ко вводу в виде имени параметра - name.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
message - сообщение о параметре;
name - имя параметра;
index - запрашиваемый индекс;
h_bound - верхняя граница индекса.
Локальные переменные:
ok - флаг отсутствия ошибки (1 - нет ошибки);
req_rslt - флаг ответа пользователя (1 - согласие пользователя).
*/
int InputIndex(const char message[],const char name[],long *index,long h_bound);


/*
Функция InputConsole() позволет пользователю считать массив array размером size с клавиатуры.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
array - массив для ввода;
size -  размер массива.
Локальные переменные:
log - флаг отсутствия ошибки (1 - нет ошибки);
elem_name - имя элемента;
msg - сообщение об элементе;
i - переменная-счетчик.
*/
int InputConsole(double array[],long size);


/*
Функция InputFile() позволет пользователю считать массив array размером size из файла.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
array - массив для ввода;
size -  размер массива.
Локальные переменные:
log - флаг отсутствия ошибки (1 - нет ошибки);
f - файл для ввода;
ch - текущий считанный символ;
i - переменная-счетчик.
*/
int InputFile(double array[],long size);


/*
Функция InputRandom() позволет пользователю заполнить массив array случайными числами.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
array - массив для ввода;
size -  размер массива.
Локальные переменные:
log - флаг отсутствия ошибки (1 - нет ошибки);
req_rslt - флаг ответа пользователя (1 - согласие пользователя);
min, max - границы генерации случайных чисел;
i - переменная-счетчик.
*/
int InputRandom(double array[],long size);


/*
Функция InputData позволяет запросить у пользователя размер size массива array,
а также число K, отсносительного которого будут сравниваться элементы array,
и заполнить array различными способами.
Возвращает 1, если операция прошла успешно, иначе возвращается 0.
Параметры:
array - массив для ввода;
size -  размер массива;
K - число для сравнения элементов массива.
Локальные переменные:
log - флаг отсутствия ошибки (1 - нет ошибки);
msg - сообщение об параметре.
*/
int InputData(double array[],long *size,double *K);


#endif // DEFINES_H_INCLUDED

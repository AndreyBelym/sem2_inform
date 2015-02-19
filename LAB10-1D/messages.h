#ifndef MESSAGES_H_INCLUDED
#define MESSAGES_H_INCLUDED
#define MSG_INPUT_SYM "Введите цифру от %c до %c.\n"
#define MSG_SCREEN_TOOSMALL "Массив %ldx%ld слишком большой для вывода на экран!\n"
#define MSG_FILE_NAME_NEEDED "Необходимо имя файла!\n"
#define MSG_WELCOME "Программа сортирует по возрастанию элементы главной диагонали\n"\
                     "матрицы размера mxm.\n"
#define MSG_RESULT "Главная диагональ матрицы размера %ldx%ld отсортирована!...\n"
#define MSG_ABORTED "Работа программы прервана!\n"
#define MSG_OPERATION_SUCCEEDED "Работа успешно выполнена!\n"
#define MSG_PRESS_ANYKEY "Нажмите <Enter>...\n"
#define MSG_REQUEST_VERIFY "Продолжить?(Y/N)\n"
#define MSG_REQUEST_TRUST "Вы уверены в правильности введенных данных?(Y/N)\n"
#define MSG_CHECK_INFO "Будет выполна сортировка главной диагонали матрицы %ldx%ld :\n"
#define MSG_SIZE_ERROR "Размер массива меньше/равен 0!\n"
#define MSG_REQUEST_ERROR "Неправильный ответ! Допустимо:\n"\
					  "Y - да; N - нет.\n"
#define MSG_REQUEST_FILEOUTPUT "Хотите вывести матрицу в файл? Y/N\n"
#define MSG_REQUEST_OUTPUT "1 - вывод матрицы на экран (затем возможен вывод в файл);\n"\
							"2 - вывод матрицы в файл без вывода на экран.\n"
#define MSG_SYM_INPUT_ERROR "Неправильный ответ!\n"
#define MSG_VERIFY_ERROR "Введенные данные некорректны или ввод отменён!\n"
#define MSG_ARRAY_TOOLONG "Массив слишком большой!\n"
#define MSG_REQUEST_SIZE "Введите  m - размер матрицы.\n"
#define MSG_REQUEST_ELEMENT "Введите элемент А[%ld,%ld].\n"
#define MSG_REQUEST_MIN_RANDOM "Введите min - минимальное из случайных чисел.\n"
#define MSG_REQUEST_MAX_RANDOM "Введите max - минимальное из случайных чисел.\n"
#define MSG_REQUEST_INFILE "Введите имя файла-источника.\n"
#define MSG_REQUEST_OUTFILE "Введите имя файла-результата.\n"
#define MSG_FILE_EXISTS "ВНИМАНИЕ! Указанное имя файла занято!\n"
#define MSG_REWRITE_FILE "ПЕРЕЗАПИСАТЬ ФАЙЛ? (Y/N)\n"
#define NFO_FILE "Файл"
#define MSG_FILE_NOT_FOUND "Неправильное имя файла! \n"
#define MSG_INPUT_ERROR   "Введено неправильное значение!\n"
#define MSG_REPEAT_INPUT "Хотите повторить ввод? (Y/N)\n"
#define MSG_MEMALLOC_ERROR "Ошибка выделения памяти!\n"
#define MSG_BOUND_ERROR "Верхняя граница (max) меньше нижней (min)!\n"
#define MSG_SIZE_FREAD_ERROR "Размер массива не указан в файле!\n"
#define MSG_ARR_FREAD_ERROR "Ошибка при чтении из файла элемента [%ld].\n"
#define MSG_REQUEST_INPUT "Заполните матрицу:\n"\
							"1 - заполнить случайными числами;\n"\
							"2 - ввести из файла;\n"\
							"3 - ввести с клавиатуры;\n"\
							"0 - завершить программу.\n"
#define MSG_INPUT_CANCELED "Ввод отменён!\n"
#endif // MESSAGES_H_INCLUDED

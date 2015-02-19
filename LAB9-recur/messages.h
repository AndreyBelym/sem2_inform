#ifndef MESSAGES_H_INCLUDED
#define MESSAGES_H_INCLUDED
#define MSG_WELCOME "Программа находит корень функции %s на отрезке [a,b] с точностью eps.\n"
#define MSG_RESULT "Корень на промежутке [%1.4lf,%1.4lf] равен %1.8lf.\n"
#define MSG_ABORTED "Работа программы прервана!\n"
#define MSG_PRESS_ANYKEY "Нажмите <Enter>...\n"
#define MSG_REQUEST_VERIFY "Будет выполнен поиск корня\n"\
                        "на интервале от %1.4lf до %1.4lf с точностью %1.8lf\n"\
                        "Продолжить?(Y/N)\n"
#define MSG_REQUEST_ERROR "Неправильный ответ! Допустимо:\n"\
					  "Y - да; N - нет.\n"
#define MSG_REQUEST_PARAM "Введите %s - вещественное число. %s\n"
#define MSG_INPUT_ERROR   "Введено неправильное значение!\n"
#define MSG_REPEAT_INPUT "Хотите повторить ввод? Y/N\n"                      
#define MSG_BOUND_ERROR "Верхняя граница интервала поиска корня (b) меньше нижней (a)!\n"
#define MSG_PRECISION_ERROR "Точность вычислений (eps) меньше/равна 0!\n"
#define MSG_NOT_FOUND "Корня на промежутке [%1.4lf,%1.4lf] не найдено.\n"
#endif // MESSAGES_H_INCLUDED

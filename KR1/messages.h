#ifndef MESSAGES_H_INCLUDED
#define MESSAGES_H_INCLUDED
#define MSG_WELCOME "Программа выполняет расчет определенного интеграла\n"\
                    "на интервале от a до b с точностью eps для f(x)...\n"\
                    "        / sqrt(3)*(x+d)/3+d , x<=d;\n"\
                    "f(x) = |  -x, d<x<=e;\n"\
                    "        \\ sqrt(3)*(x-e)-e , e<x.\n"
#define MSG_RESULT "Интеграл на промежутке [%1.4lf,%1.4lf] равен %1.8lf+-%1.8lf.\n"
#define MSG_ABORTED "Работа программы прервана!\n"
#define MSG_PRESS_ANYKEY "Нажмите <Enter>...\n"
#define MSG_REQUEST_VERIFY "Будет выполнен расчет определенного интеграла\n"\
                        "на интервале от %1.4lf до %1.4lf с точностью %1.8lf.\n"\
                        "Параметры функции: d=%1.4lf; e=%1.4lf.\n"\
                        "Продолжить?(Y/N)\n"
#define MSG_REQUEST_ERROR "Неправильный ответ! Допустимо:\n"\
					  "Y - да; N - нет.\n"
#define MSG_VERIFY_ERROR "Введенные данные некорректны!\n"
#define MSG_D_ERROR "Ошибка! d должно быть меньше/равно 0!\n"
#define MSG_E_ERROR "Ошибка! c должно быть больше/равно 0!n"
#define MSG_FPARAM_ERROR "Ошибка в параметре функции!\n %s должно быть больше %s!\n"
#define MSG_REQUEST_C "Введите c - вещественное число.\n"
#define MSG_REQUEST_D "Введите d - вещественное число.\n"
#define MSG_REQUEST_E "Введите е - вещественное число.\n"
#define MSG_REQUEST_A "Введите а - вещественное число.\n"
#define MSG_REQUEST_B "Введите b - вещественное число.\n"
#define MSG_REQUEST_EPS "Введите eps - вещественное число.\n"
#define MSG_INPUT_ERROR   "Введено неправильное значение!\n"
#define MSG_REPEAT_INPUT "Хотите повторить ввод? Y/N\n"
#define MSG_BOUND_ERROR "Верхняя граница интервала (b) меньше нижней (a)!\n"
#define MSG_PRECISION_ERROR "Точность вычислений (eps) меньше/равна 0!\n"
#endif // MESSAGES_H_INCLUDED

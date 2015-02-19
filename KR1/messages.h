#ifndef MESSAGES_H_INCLUDED
#define MESSAGES_H_INCLUDED
#define MSG_WELCOME "�ணࠬ�� �믮���� ���� ��।�������� ��⥣ࠫ�\n"\
                    "�� ���ࢠ�� �� a �� b � �筮���� eps ��� f(x)...\n"\
                    "        / sqrt(3)*(x+d)/3+d , x<=d;\n"\
                    "f(x) = |  -x, d<x<=e;\n"\
                    "        \\ sqrt(3)*(x-e)-e , e<x.\n"
#define MSG_RESULT "��⥣ࠫ �� �஬���⪥ [%1.4lf,%1.4lf] ࠢ�� %1.8lf+-%1.8lf.\n"
#define MSG_ABORTED "����� �ணࠬ�� ��ࢠ��!\n"
#define MSG_PRESS_ANYKEY "������ <Enter>...\n"
#define MSG_REQUEST_VERIFY "�㤥� �믮���� ���� ��।�������� ��⥣ࠫ�\n"\
                        "�� ���ࢠ�� �� %1.4lf �� %1.4lf � �筮���� %1.8lf.\n"\
                        "��ࠬ���� �㭪樨: d=%1.4lf; e=%1.4lf.\n"\
                        "�த������?(Y/N)\n"
#define MSG_REQUEST_ERROR "���ࠢ���� �⢥�! �����⨬�:\n"\
					  "Y - ��; N - ���.\n"
#define MSG_VERIFY_ERROR "�������� ����� �����४��!\n"
#define MSG_D_ERROR "�訡��! d ������ ���� �����/ࠢ�� 0!\n"
#define MSG_E_ERROR "�訡��! c ������ ���� �����/ࠢ�� 0!n"
#define MSG_FPARAM_ERROR "�訡�� � ��ࠬ��� �㭪樨!\n %s ������ ���� ����� %s!\n"
#define MSG_REQUEST_C "������ c - ����⢥���� �᫮.\n"
#define MSG_REQUEST_D "������ d - ����⢥���� �᫮.\n"
#define MSG_REQUEST_E "������ � - ����⢥���� �᫮.\n"
#define MSG_REQUEST_A "������ � - ����⢥���� �᫮.\n"
#define MSG_REQUEST_B "������ b - ����⢥���� �᫮.\n"
#define MSG_REQUEST_EPS "������ eps - ����⢥���� �᫮.\n"
#define MSG_INPUT_ERROR   "������� ���ࠢ��쭮� ���祭��!\n"
#define MSG_REPEAT_INPUT "���� ������� ����? Y/N\n"
#define MSG_BOUND_ERROR "������ �࠭�� ���ࢠ�� (b) ����� ������ (a)!\n"
#define MSG_PRECISION_ERROR "��筮��� ���᫥��� (eps) �����/ࠢ�� 0!\n"
#endif // MESSAGES_H_INCLUDED

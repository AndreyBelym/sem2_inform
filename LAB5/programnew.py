#!/usr/bin/env python2
# -*- coding: UTF-8 -*-
def GetCount():
    while True:
        Count=raw_input( 'Введите количество студентов:')
        try:
            Count=int(Count)
        except:
            print 'Введено не число! Повторите ввод'
        else:
            break

    else:
        raise Exception,'Ошибка ввода'
    return Count
def GetStudent(studNumber):
    student={}
    print '***************'
    print 'Введите данные студента %d'%(studNumber)
    student['Имя']=raw_input('Введите имя студента %d:'%(studNumber))
    student['Фамилия']=raw_input('Введите фамилию студента %d:'%(studNumber))
    student['Отчество']=raw_input('Введите отчество студента %d:'%(studNumber))
    student['Университет']=raw_input('Введите университет студента %d:'%(studNumber))
    student['Номер группы']=raw_input('Введите группу студента %d:'%(studNumber))
    return student
def GetStudents():
    StudCount=GetCount();
    Students=[]
    for i in range(1,StudCount+1):
        Students.append(GetStudent(i))
    return Students
def GetUniList(students):
    unis=[]
    for stud in students:
        if stud['Университет'] not in unis:
            unis.append(stud['Университет'])
    return unis
def GetGroupList(students):
    groups=[]
    for stud in students:
        if stud['Номер группы'] not in groups:
            groups.append(stud['Номер группы'])
    return groups
def GetByUni(uni,students):
    studlist=[]
    for stud in students:
        if stud['Университет']==uni:
            studlist.append(stud)
    return studlist
def GetByGroup(group,students):
    studlist=[]
    for stud in students:
        if stud['Номер группы']==group:
            studlist.append(stud)
    return studlist
def GetClassmates(students):
    Classmates=[]
    for uni in GetUniList(students):
        studinuni=GetByUni(uni,students)
        for group in GetGroupList(studinuni):
            studingroup=GetByGroup(group,studinuni)
            
            if len(studingroup)>1:
                Classmates.append(studingroup)
    return Classmates
def main():
    print "Программа находит одногруппников среди заданного списка студентов"
    try:
        AllStudents=GetStudents();
    except Exception as excpt:
        print ("Программа завершена...",excpt)
    else:
        Classmates=GetClassmates(AllStudents)
        
        if Classmates!=[]:
            for group in Classmates:
                print '***************'
                print 'Университет: %s Группа:%s'%(group[1]['Университет'],group[1]['Номер группы'])
                for stud in group:
                    print '%s %s %s'%(stud['Фамилия'],stud['Имя'],stud['Отчество'])
                
        return 0
if __name__=="__main__":
    main()

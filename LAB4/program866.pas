const nn=10;
type 
    student=record
        FstName,LstName,Surname:string[20];
        University:string[50];
        GroupNum:longint;
    end;
 
    
function GetString(var paramVar :string; const paramDescr,paramTip:string):boolean;
var ch:char; temp:string;
begin
    ch:='y';
    repeat
        WriteLn(paramDescr);
        Write(paramTip,':');
        ReadLn(temp);
        if temp='' then begin
            WriteLn('�訡��! ������� ����?(Y/N)');
            ReadLn(ch);
        end
    until (UpCase(ch)='N') or (temp<>'');
    if temp<>'' then begin
        GetString:=true;
        paramVar:=temp;
    end else begin
        GetString:=false;
        paramVar:='';
    end;
end;

function GetGroup(var paramVar :longint):boolean;
var ch:char; buf:string; code:integer; temp:longint;
begin
    ch:='y';
    repeat
        WriteLn('������ ����� ��㯯�.');
        Write('����� ��㯯�:');
        ReadLn(buf); val(buf,temp,code);
        if code<>0 then begin
            WriteLn('�訡��! ������� ����?(Y/N)');
            ReadLn(ch);
        end else 
            if temp<=0 then begin
                code:=-1;
                WriteLn('����� ��㯯�<=0! ������� ����?(Y/N)');
                ReadLn(ch);
            end;
    until (UpCase(ch)='N') or (code=0);
    if code=0 then begin
        GetGroup:=true;
        paramVar:=temp;
    end else begin
        GetGroup:=false;
        paramVar:=0;
    end;
end;

function GetCount(var paramVar :word):boolean;
var ch:char; buf:string; code:integer; temp:word;
begin
    ch:='y';
    repeat
        WriteLn('������ ��饥 ������⢮ ��㤥�⮢.(>=1 � <=',nn,')');
        Write('��㤥�⮢:');
        ReadLn(buf); val(buf,temp,code);
        if code<>0 then begin
            WriteLn('�訡��! ������� ����?(<Y>es/<N>o)');
            ReadLn(ch);
        end else 
            if (temp<1) or (temp>nn) then begin
                code:=-1;
                WriteLn('������⢮ ��㤥�⮢ ���ࠢ��쭮! ������� ����?(<Y>es/<N>o)');
                ReadLn(ch);
            end;
    until (UpCase(ch)='N') or (code=0);
    if code=0 then begin
        GetCount:=true;
        paramVar:=temp;
    end else begin
        GetCount:=false;
        paramVar:=0;
    end;
end;

function GetStudent(var stud:student):boolean;
var log:boolean;
begin
    log:=GetString(stud.LstName,'������ 䠬���� ��㤥��.','�������');
    if log then 
        log:=GetString(stud.FstName,'������ ��� ��㤥��.','���');
    if log then
        log:=GetString(stud.Surname,'������ ����⢮ ��㤥��.','����⢮');
    if log then 
        log:=GetString(stud.University,'������ �������� 㭨������.','���������');
    if log then
        log:=GetGroup(stud.GroupNum);
    GetStudent:=log;
end;

function InputData(var studCount:word; var students:array of student):boolean;
var i:word; log:boolean;
begin
    log:=GetCount(studCount);
    i:=1;
    while (i<=studCount) and log do begin
        WriteLn('****************************');
        WriteLn('���� ������ � ��㤥�� �',i);
        WriteLn('****************************');
        log:=GetStudent(students[i]);
        inc(i);
    end;   
    InputData:=log;
       
end; 

function CheckData(const studCount:word;var stud:array of student):boolean;
var i:word; ch:char;
begin
    WriteLn('���� �஢���� ����� � ������ ��㤥�� �� ���浪�?(�⢥��� <V>erify);');
    WriteLn('�������� ࠡ���?<A>bort;');
    WriteLn('�த������ ࠡ���?<C>ontinue ��� �� ��㣮�.');
    ReadLn(ch);
    if UpCase(ch)='V' then begin
        i:=1;
        repeat 
            WriteLn('****************************');
            WriteLn('����窠 ��㤥�� �',i);
            WriteLn('****************************');
            WriteLn('***���������: ',stud[i].University,' ��㯯�:',stud[i].GroupNum);
            WriteLn(stud[i].LstName,' ', stud[i].FstName,' ', stud[i].SurName);
            WriteLn('�ࠢ��쭮? �� - <Y>es (�� 㬮�砭��);');
            WriteLn('���, �������� ����� - <R>');
            WriteLn('���, �������� �ணࠬ�� - <A>');
            ReadLn(ch);
            if UpCase(ch)='R' then begin
                WriteLn('****************************');
                WriteLn('���� ������ � ��㤥�� �',i);
                WriteLn('****************************');
                GetStudent(stud[i]);
                {if not GetStudent(students[i]) then UpCase(ch)='A';}
            end else inc(i);
        until (UpCase(ch)='A') or (i>studCount);
    end;
    CheckData:=UpCase(ch)<>'A';
end;

procedure FindStudents(const inStudCount:word;const inStud:array of student;var outStudCount:word;var outStud:array of student);
var k,i,j:word; founded:boolean; outed:array [1..nn] of boolean;
begin
    
    k:=0;
    for i:=1 to nn do
        outed[i]:=false;
    founded:=false;
     
        for i:=1 to inStudCount-1 do begin
            if not outed[i] then begin
                for j:=i+1 to inStudCount do
                    if not outed[j] 
                       and (inStud[i].GroupNum=inStud[j].GroupNum) 
                       and (inStud[i].University=inStud[j].University) then begin
                          founded:=true;inc(k);
                          outStud[k]:=inStud[j];
                          outed[j]:=true;
                    end;
                if founded then begin
                    inc(k);
                    outStud[k]:=inStud[i];
                    founded:=false;
                end;
            end;
        end;
    
    outStudCount:=k;
    
end;

procedure PrintData(const studCount:word;const stud:array of student);
var i:word;
begin
    WriteLn('�������� ������㯭���:');
    i:=1;
    
        WriteLn('***���������: ',stud[i].University,' ��㯯�:',stud[i].GroupNum);
        WriteLn(stud[i].LstName,' ', stud[i].FstName,' ', stud[i].SurName);
        for i:=2 to studCount do begin
            if (stud[i].GroupNum<>stud[i-1].GroupNum) 
               or (stud[i].University<>stud[i-1].University) then
                  WriteLn(#10#13,'***���������: ',stud[i].University,' ��㯯�:',stud[i].GroupNum);
            WriteLn(stud[i].LstName,' ', stud[i].FstName,' ', stud[i].SurName);
        end;
    
     
end;

type students=record
        Count:word;
        Stud:array[1..nn] of student;
    end;
    
var AllStudents, FoundedStudents:students;
    log:boolean;
BEGIN
    WriteLn('�ணࠬ�� ��室�� ������㯭���� �न ������ ��㤥�⮢');
    log:=InputData(AllStudents.Count,AllStudents.stud);
    if log then 
        log:=CheckData(AllStudents.Count,AllStudents.stud);
    if log then begin
        FindStudents(AllStudents.Count,AllStudents.Stud,FoundedStudents.Count,FoundedStudents.Stud);
        if FoundedStudents.Count<>0 then
            PrintData(FoundedStudents.Count,FoundedStudents.Stud)
        else
            WriteLn('������㯭���� �� �������');
    end else
        Writeln('�ணࠬ�� �����襭� ���짮��⥫��');
    Readln;
END.        
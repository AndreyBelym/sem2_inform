{-----ПРОГРАММА РЕШЕНИЯ СИСТЕМЫ 2-Х УРАВНЕНИЙ С 2-МЯ НЕИЗВЕСТНЫМИ-----}
Program SysSolver;
const maxvars=2;{кол-во переменных системы}
type MatColumn=array[1..maxvars] of real; {тип "матрица-столбец"}

{------ФУНКЦИЯ ВВОДА ВЕЩЕСТВЕННОГО ПАРАМЕТРА-----}
{Параметры: имя запрашиваемого параметра; номер параметра; переменная состояния}
function GetParam(const paramName:char;const paramNum:integer; var log:boolean):real;
var temp:real; buf:string; code:integer; ch:char;
begin
    ch:='Y'; temp:=0; {инициализация переменных}
    repeat
        WriteLn('Введите ',paramName,paramNum,' - вещественное число.');
        Write(paramName,paramNum,':');ReadLn(buf); Val(buf,temp,code);
        if code<>0 then begin {введено не вещественное число?}
            WriteLn('Недопустимое значение ',paramName,paramNum,'.');
            WriteLn('Повторить ввод?(y/n)');
            ReadLn(ch);
        end;
    until (Upcase(ch)='N') or (code=0);
    {пока пользователь не отказался или число некорректное}
    log:=code=0;{число введено корректно?}
    if log then    
        GetParam:=temp;{вернём значение}
end;

{------ФУНКЦИЯ ВВОДА ДАННЫХ-----}
{Параметры:коэффициенты при х; коэффициенты при у; свободные коэффициенты}
function InputData(var A,B,C:MatColumn):boolean;
var i:byte; log:boolean;
begin
    
    log:=true;i:=1; {инициализация переменной}
    while (i<=maxvars) and log do begin
        A[i]:=GetParam('a',i,log);
        if log then
            B[i]:=GetParam('b',i,log);
        if log then
            C[i]:=GetParam('c',i,log);
        inc(i);
    end;
    InputData:=log;
end;

{------ФУНКЦИЯ ПРОВЕРКИ ЗНАЧЕНИЙ-----}
{Параметры:коэффициенты при х; коэффициенты при у; свободные коэффициенты}
function CheckData(const A,B,C:MatColumn):boolean;
var ch:char; 
begin
    WriteLn('Вы ввели:');
    WriteLn(A[1]:1:4,'x + ',B[1]:1:4,'y = ',C[1]:1:4);
	WriteLn(A[2]:1:4,'x + ',B[2]:1:4,'y = ',C[2]:1:4);
	WriteLn('a1=',A[1]:1:4,'; b1=',B[1]:1:4,'; c1=',C[1]:1:4);
	WriteLn('a2=',A[2]:1:4,'; b2=',B[2]:1:4,'; c2=',C[2]:1:4);
	WriteLn('OK?(y/n)');
	Readln(ch);
	CheckData:=UpCase(ch)='Y';
end;

{------ФУНКЦИЯ ПОДСЧЕТА ОПРЕДЕЛИТЕЛЯ-----}
{Параметры: первый столбец определителя; второй столбец определителя}
function GetDet(const A,B:MatColumn):real;
begin
    GetDet:=A[1]*B[2]-B[1]*A[2];
end;

{------ФУНКЦИЯ РЕШЕНИЯ СИСТЕМЫ-----}
{Параметры:коэффициенты при х; коэффициенты при у; свободные коэффициенты
                        найденное значение х; значение у}
function SolveSys(const A,B,C:MatColumn; var x,y:real):boolean;
var d,dx,dy:real;
begin
    d:=GetDet(A,B);
    if d<>0 then begin
        dx:=GetDet(C,B);
	    dy:=GetDet(A,C);
	    x:=dx/d;
	    y:=dy/d;
	    SolveSys:=true;
	end else SolveSys:=false;
end;

{------ПРОЦЕДУРА ВЫВОДА КОРНЕЙ СИСТЕМЫ-----}
{Параметры: значение х; значение у}
procedure PrintData(const x,y:real);
begin
    WriteLn('Ответ:');
	WriteLn('x =',x);
	WriteLn('y =',y);
end;

{------ОСНОВНАЯ ПРОГРАММА-----}
var A,B,C:MatColumn;
{коэффециенты при x; при y; свободные коэффециенты}	
	x,y:real;
{значение x; значение у}
    log:boolean;
{переменная состояния}
BEGIN

	WriteLn('Данная программа находит корни системы уравнений');
	WriteLn('(a1)x+(b1)y=(c1);');
	WriteLn('(a2)x+(b2)y=(c2);');
	log:=InputData(A,B,C);
	if log then
	    log:=CheckData(A,B,C);
	if log then begin
	    log:=SolveSys(A,B,C,x,y);
	    if log then 
	        PrintData(x,y)
	    else 
	        WriteLn('Система не совместна!');
	end else 
	    WriteLn('Программа завершена.');
	WriteLn('Нажмите <Enter>...');
    ReadLn;
END.

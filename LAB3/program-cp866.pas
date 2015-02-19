{-------ПРОГРАММА ПОИСКА КОРНЯ ФУНКЦИИ------}
program FunctionRoot;
type TestFunc=function(const x:real):real;

{$F+}
function f(const x:real):real; 
begin
    f:=sin(x);
end;
{$F-}
{------ФУНКЦИЯ ВВОДА ВЕЩЕСТВЕННОГО ПАРАМЕТРА-----}
{Параметры: 
paramName - имя запрашиваемого параметра; 
paramCond - дополнительная информация о параметре;
log - переменная состояния}
function GetParam(const paramName,paramCond:string;var log:boolean):real;
var temp:real; buf:string; code:integer; ch:char;
begin
    ch:='Y'; temp:=0; {инициализация переменных}
    repeat
        WriteLn('Введите ',paramName,' - вещественное число. ',paramCond);
        Write(paramName,':');ReadLn(buf); Val(buf,temp,code);
        if code<>0 then begin {введено не вещественное число?}
            WriteLn('Недопустимое значение ',paramName,'.');
            WriteLn('Повторить ввод?(y/n)');
            ReadLn(ch);
        end;
    until (Upcase(ch)='N') or (code=0);
    {пока пользователь не отказался или число некорректное}
    log:=code=0;{число введено корректно?}    
    GetParam:=temp;{вернём значение}
end;

{--------ФУНКЦИЯ ВВОДА ДАННЫХ-------}
{Параметры:
a,b - границы отрезка поиска корня;
eps - точность вычислений;
log - переменная состояния}
function InputData(var a,b,eps:real):boolean;
var log:boolean; ch:char;
begin
    ch:='Y'; {инициализация так и только так! см. ниже, почему}
    repeat
        case UpCase(ch) of
            'A':a:=GetParam('a','',log);
            'B':b:=GetParam('b','b>a.',log);
            else begin
                a:=GetParam('a','',log);
                if log then
                    b:=GetParam('b','b>a.',log);
            end;
        end;  
        if log and not (b>a) then begin
            WriteLn('Ошибка! b<=a!');
            WriteLn('Повторить ввод?');
            WriteLn('Y - ввести а и b;');
            WriteLn('A - ввести только а;');
            WriteLn('B - ввести только b;');
            WriteLn('N - отмена.');
            ReadLn(ch);  
        end;
    until not(log) or (b>a) or (UpCase(ch)='N');
    log:=log and (b>a);
    if log then 
        repeat
            eps:=GetParam('eps','eps>0.',log); 
            if log and not (eps>0) then begin
                WriteLn('Ошибка! eps<=0!');
                WriteLn('Повторить ввод?(Y/N)');
                ReadLn(ch);
            end;
        until not(log) or (eps>0) or (UpCase(ch)='N');
    log:=log and (eps>0);
    InputData:=log and (ch<>'N');
end;

{-------ФУНКЦИЯ ПРОВЕРКИ ДАННЫХ------}
{Параметры:
a,b - границы отрезка поиска корня;
eps - точность вычислений}
function CheckData(const a,b,eps:real):boolean;
var ch:char;
begin
    WriteLn('Будет выполнен поиск корня');
    WriteLn(' на интервале от ',a:1:4,' до ',b:1:4,' с точностью ',eps:1:8);
    WriteLn('Продолжить?(Y/N)');
    ReadLn(ch);
    CheckData:=UpCase(ch)='Y';
end;

{------ФУНКЦИЯ ПОЛУЧЕНИЯ КОРНЯ------}
{Параметры:
f - анализируемая функция;
a,b - границы отрезка поиска корня;
eps - точность вычислений;
f_root - найденный корень}
function GetRoot(const f:TestFunc; const a,b,eps:real;var f_root:real):byte;

{------ФУНКЦИЯ РАСЧЕТА КОРНЯ------}
{Параметры:
f - анализируемая функция;
a,b - границы отрезка поиска корня;
eps - точность вычислений;}
function Root(const f:TestFunc; const a,b,eps:real):real;
var c:real;
begin
    c:=(a+b)/2;
    if b-a>eps then
        if f(c)*f(a)<=0 then
            Root:=Root(f,a,c,eps) 
        else 
            Root:=Root(f,c,b,eps)      
    else
        Root:=c;
end;
begin
    if not(b>a) then 
        GetRoot:=1
    else
        if not(eps>0) then
            GetRoot:=2
        else
            if f(a)*f(b)>0 then
                GetRoot:=3 
            else begin
                GetRoot:=0;
                f_root:=Root(f,a,b,eps);
            end;
end;

{------ОСНОВНАЯ ПРОГРАММА-------}
{a,b - границы отрезка поиска корня;
eps - точность вычислений;
log - переменная состояния;
code - код ошибки поиска корня}
const func_name='sin(x)';
var a,b,eps,f_root:real;log:boolean; code:byte;
Begin
WriteLn('Программа находит корень функции ',func_name,' на отрезке [a,b] с точностью eps.');
log:=InputData(a,b,eps);
if log then
    log:=CheckData(a,b,eps);
if log then begin
    code:=GetRoot(f,a,b,eps,f_root);
    case code of
        0:WriteLn('Корень на промежутке [',a:1:4,',',b:1:4,'] равен ',f_root:1:8);
        1:WriteLn('Верхняя граница интервала поиска корня меньше нижней...');
        2:WriteLn('Точность вычислений меньше/равна 0!');
        3:WriteLn('Корня на промежутке [',a:1:4,',',b:1:4,'] не найдено.');
    end
end
else
    WriteLn('Программа завершена пользователем...');
end.

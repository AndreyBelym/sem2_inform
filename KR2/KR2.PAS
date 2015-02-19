program Func;

function GetAnswer:boolean;
var answer:char;
begin
    ReadLn(answer);
    while (UpCase(answer)<>'Y')
           and(UpCase(answer)<>'N') do begin
        WriteLn('Неправильный ответ! Допустимо:',#13#10,'Y - да; N - нет.');
        ReadLn(answer);
    end;
    GetAnswer:=UpCase(answer)='Y';
end;

function FileExists(var f:text):boolean;
var exist:boolean;
begin
    {$I-}
        ReSet(f);
    {$I+}
    exist:=ioresult=0;
    if exist then close(f);
    FileExists:=exist;
end;
function GetInputFile(var f:text):boolean;
var ok,rept:boolean;
    fileName:string;
begin
    ok:=true; rept:=false;
    repeat
        WriteLn('Введите имя файла-источника.');
        Write('Файл:');ReadLn(fileName);
        Assign(f,fileName);
        {$I-}
            Reset(f);
        {$I+}
        ok:=(ioresult=0)and(fileName<>'');
        if not ok then begin
            WriteLn('Неправильное имя файла! Повторить ввод? <Y>/<N>');
            rept:=GetAnswer;
		end;
    until ok or not rept;
	GetInputFile:=ok;
end;

function GetOutputFile(var f:text):boolean;
var ok,rept:boolean;
    fileName:string;
begin
    ok:=true; rept:=false;
    repeat
        WriteLn('Введите имя файла-результата.');
        Write('Файл:');ReadLn(fileName);
        Assign(f,fileName);
        if FileExists(f) then begin
            ok:=false;
            WriteLn('Указанный файл сушествует! Перезаписать? (Y/N)');
            ok:=GetAnswer;
        end;
        if ok then begin
            {$I-}
            ReWrite(f);
            {$I+}
            ok:=(ioresult=0)and(fileName<>'');
        end;
        if not ok then begin
            WriteLn('Ошибка при создании файла! Повторить ввод? <Y>/<N>');
            rept:=GetAnswer;
        end;
    until ok or not rept;
    GetOutputFile:=ok;
end;

procedure GetSeries(const x,eps:real;var y:real;var last:longint);
var sqrx,ylast:real;
begin
    sqrx:=sqr(x);{запомним x^2}
    y:=1;ylast:=1;last:=0;{инициализация}
    repeat
        inc(last);
        ylast:=ylast*sqrx/(2*last)/(2*last-1);{очередной элемент последовательности}
        y:=y+ylast;
    until abs(ylast)<eps;
end;

function CheckData(const a,b,h,eps:real):boolean;
begin
    WriteLn('Вычисление значений функции');
    WriteLn('на интервале от ',a:1:4,' до ',b:1:4,' с шагом ',h:1:4,'. Точность - ',eps:1:4);
    WriteLn('Данные корректны? (Y/N)');
    CheckData:=GetAnswer;
end;

function GetParam(const message:string;const name:string; var param:real):boolean;
var buf :string; ok,rept:boolean; code:integer;
begin
    ok:=true; rept:=false;
    repeat
        ok:=True;{пока всё xорошо}
        WriteLn(message);
        Write(name,': ');
        readln(buf);
        val(buf,param,code);
        if code<>0 then begin
            ok:=false;{Ошибка}
            WriteLn('Некорректное значение! Повторить ввод?(Y/N)!');
            rept:=GetAnswer;
        end;
    until ok or not rept;
    GetParam:=ok;
end;

function GetQuiet(var f:text; var param:real):boolean;
begin
    {$I-}
    read(f,param);
    {$I+}

    GetQuiet:=(ioresult=0);
end;

function InputConsole(var a,b,h,eps:real):boolean;
var  ok,rept:boolean;
begin
    ok:=true; rept:=false;
    ok:=GetParam('Введите минимальное x (a) - вещественное число','a',a);
    if ok then 
        repeat
            ok:=GetParam('Введите максимальное x (b) - вещественное число. b>=a.','b',b);
            if ok and (b<a) then begin
                ok:=false; 
                WriteLn('b<a! Повторить ввод?(Y/N)'); 
                rept:=GetAnswer;
            end;
        until ok or not rept;
    if ok then 
        repeat
            ok:=GetParam('Введите шаг изменения x (h) - вещественное число. h>=0.','h',h);
            if ok and (h<0) then begin
                ok:=false; 
                WriteLn('h<0! Повторить ввод?(Y/N)'); 
                rept:=GetAnswer;
            end;
        until ok or not rept;
    if ok then 
        repeat
            ok:=GetParam('Введите точность вычислений (eps) - вещественное число. eps>0.','eps',eps);
            if ok and (eps<=0 ) then begin
                ok:=false; 
                WriteLn('eps<=0 ! Повторить ввод?(Y/N)'); 
                rept:=GetAnswer;
            end;
        until ok or not rept;
    InputConsole:=ok;
end;
function InputFile(var a,b,h,eps:real):boolean;
var ok,rept:boolean; fin:text; curr_param:string;
begin
    ok:=true; rept:=false;
    ok:=GetInputFile(fin);
    if ok then begin
        ok:=GetQuiet(fin,a); curr_param:='a';
        if ok then 
            ok:=GetQuiet(fin,b); curr_param:='b';
        if ok then 
            ok:=b>=a;
        if ok then
            ok:=GetQuiet(fin,h); curr_param:='h';
        if ok then
            ok:=h>=0;
        if ok then 
            ok:=GetQuiet(fin,eps); curr_param:='eps';
        if ok then 
            ok:=eps>0;
        if not ok then
            WriteLn('Ошибка при чтении параметра ',curr_param,'!');
        Close(fin);
        end else
            WriteLn('Ошибка при открытии файла!');
    InputFile:=ok;
end;

function InputData(var a,b,h,eps:real):boolean;
var file_in:boolean;
begin
    WriteLn('Желаете считать параметры из файла?');
    WriteLn('Y - из файла, N - с клавиатуры');
    file_in:=GetAnswer;
    if file_in then
        InputData:=InputFile(a,b,h,eps)
    else
        InputData:=InputConsole(a,b,h,eps);
end;
procedure PrintResult(a,b,h,eps:real);
var file_out:boolean; n,last:longint; x,y:real; fout:text;
begin
    if h=0 then begin
       b:=a; h:=1;
    end;
    WriteLn('Все готово к расчету... ');
    WriteLn('Желаете выводить результаты в файл?');
    WriteLn('Y - в файл, N - на экран');
    file_out:=GetAnswer;
    if file_out then
        if not GetOutputFile(fout) then begin
            WriteLn('Ошибка открытия файла, текст будет выведен на экран...');
            file_out:=false;
        end;
    if not file_out then begin
        Assign(fout,'');Rewrite(fout);
        WriteLn(fout,'Справка:');
        WriteLn(fout,'n - порядковый номер вычисления');
        WriteLn(fout,'x - текущий аргумент функции f(x)');
        WriteLn(fout,'f(x) - значение функции');
        WriteLn(fout,'Nx - номер последнего вычисленного элемента ряда');
    end;
    writeln(fout,'n':4,'x':16,'f(x)':16,'Nx':4);

    x:=a; n:=1;
    while x<=b do begin
        GetSeries(x,eps,y,last);
        writeln(fout,n:4,x:16:4,y:16:4,last:4);
        inc(n);x:=x+h;{следующий шаг}
    end;
        close(fout);
    if file_out then WriteLn('Расчет выполнен! Смотрите указанный файл...');
end;

var a,b,h,eps:real; 
    ok,rept:boolean; 
BEGIN 
WriteLn('Программа вычисляет значения функции f(x) с точностью eps'); 
WriteLn('где x изменяется от a до b с шагом h'); 
WriteLn('Функция f(x):'); 
WriteLn('         x^2   x^4          x^2k'); 
writeln('f(x)=1 + --- + --- + ... + ------'); 
writeln('          2!    4!          (2k)!'); 
{начало ввода}
repeat
    ok:=InputData(a,b,h,eps);
    if ok then 
        ok:=CheckData(a,b,h,eps);  
    if not ok then begin
        WriteLn('Введённые данные некорректны! Повторить ввод?(Y/N)');
        rept:=GetAnswer;
    end;
until ok or not rept;

{конец ввода} 
{начало обработки} 
if ok then    
    PrintResult(a,b,h,eps)
else 
    WriteLn('Программа завершена...'); 
{конец обработки} 
WriteLn('Нажмите <Enter>...'); 
ReadLn; 
END.
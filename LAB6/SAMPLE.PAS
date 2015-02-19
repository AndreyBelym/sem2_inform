program sample10;
  { pointer arithmetic & arbitrary storage }
  var
    mem_ptr: pointer;
    mem_ptr_proc: pointer;
    array_size: longint;
    mem_ptr_arith: ^longint;
    begin_of_mem, end_of_mem, index_counter: longint;
    proc_counter: integer;

  begin
    { Establish addressability for pointer arithmetic with our proc index }
    mem_ptr_arith := @mem_ptr_proc;
    { now ask for memory size and get it. }
    {write('Enter size of integer array to be allocated: ');
    readln(array_size);}
    array_size:=maxlongint;
    getmem(mem_ptr, array_size*sizeof(integer));
    { set our pointers to access memory based on getmem }
    mem_ptr_proc := mem_ptr;
    begin_of_mem := mem_ptr_arith^;
    end_of_mem := mem_ptr_arith^ + array_size * sizeof(integer);
    writeln('Memory address for arithmetic is: ', begin_of_mem);
    writeln('End of memory is: ', end_of_mem);
    { process against this memory - from 1 to array_size }
    index_counter := begin_of_mem;
    proc_counter := 1;
    while (index_counter <= end_of_mem) do
      begin
        mem_ptr_arith^ := index_counter;
        move(proc_counter, mem_ptr_proc^, sizeof(proc_counter));
        inc(index_counter, sizeof(integer));
        inc(proc_counter, 1);
      end;
    { now write the memory back }
    index_counter := begin_of_mem;
    while (index_counter < end_of_mem) do
      begin
        mem_ptr_arith^ := index_counter;
        writeln(integer(mem_ptr_proc^));
        inc(index_counter, sizeof(integer));
      end;
    { midpoint of memory -100 is entered, 50 is returned }
    index_counter := end_of_mem - begin_of_mem;
    index_counter := (index_counter div 2) - sizeof(integer);
    index_counter := begin_of_mem + index_counter;
    mem_ptr_arith^ := index_counter;
    writeln('Midpoint is: ', integer(mem_ptr_proc^));
    { release the memory }
    freemem(mem_ptr, array_size * sizeof(integer));
  end.
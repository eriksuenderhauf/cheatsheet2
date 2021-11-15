g++ -std=gnu++17 -g program.cpp
gdb a.out
  break function # set a breakpoint at the beginning of the specified function
  break line-number # set a breakpoint at the specified line
  info break # show all breakpoints
  clear # remove all breakpoints
  clear function # remove the breakpoint at the specified function
  clear line-number # remove the breakpoint at the specified line
  run < input.in > output.out # run the program with input and output
  step # execute next line of code, enter into functions
  next # execute next line of code, do not enter into functions
  backtrace # show backtrace of the current position
  backtrace full # show backtrace and values of local variables
  print variable-name # show value of the specified variable
  ptype variable-name # show type of the specified variable
  continue # continue execution
  finish # continue after the current function returns
  kill # end the execution
  quit # quit gdb

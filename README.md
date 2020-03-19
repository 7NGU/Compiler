# Compiler
Convert high-level language to machine language.
The program contains the following sections：

 	·Lexical Analyzer

	·Grammar Analyzer

	·Semantic analyzer  

	·Intermediate code generator    
        
&emsp;&emsp;These parts belong to the relationship of gradually improving functions (except for the intermediate code generator, which has been implemented in each code).    
***

### Lexical Analyzer
`Function:`Lexical analysis is a process in computer science that converts character sequences into word sequences. Programs or functions that perform lexical analysis are called lexical analyzers and scanners. Lexical analyzers generally exist in the form of functions for the parser to call.

`Implement:`Because the state of all the word characters is already known, the deterministic finite automaton DFA can be used to achieve the determination of the division of the input string. A self-defined structure is used to represent a word symbol. The structure contains the type code and attribute value of the word symbol. The program reads data by typing one line at a time for the keyboard, and builds a global character array to store each recognized word symbol. If it meets the conditions of the word symbol, it is read into the character array until it reads a character that does not meet the requirements (such as reading a space or reading punctuation after English and numbers), and then the global character array The matched string is searched for each part, and finally the returned value is returned to the main function to implement the functional call of the lexical analyzer. The main function of the lexical analyzer is analyze (), which mainly includes reading and judging characters one by one. The pop function analyzes the current string after reading the characters, and pushes the unqualified characters with the push function.
***

### Grammar Analyzer
`Function:`A parser usually appears as a component of a compiler or an interpreter, and its role is to check the syntax and build a data structure composed of the input words (usually a hierarchical analysis tree, abstract syntax tree, etc.) Data structure). A parser usually uses a separate lexical analyzer to separate "words" from the input character stream, and uses the word stream as its input. In actual development, the parser can be written manually, or it can be generated automatically using tools (semi-).

`Implement:`After the grammar is modified to meet the LL (1) condition, a top-down analysis program without backtracking can be constructed for it. This analysis program consists of a set of recursive processes, each corresponding to a grammar Non-terminal. The benefit of using this definition system to describe the grammar is intuitive and easy to understand, and it is convenient to represent left recursive elimination and factor extraction. In the course of the experiment, the experimental questions have been given grammars that satisfy the LL (1) condition, so you only need to create corresponding functions according to the specific grammar and call them according to the corresponding grammar.

`Corresponding code grammar and description:`<br/>
e.g.
stmt ⟶ loc = expr;<br/>
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&ensp;| if(bool) stmt else stmt<br/>
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&ensp;| while(bool) stmt<br/>
&emsp;&emsp;After entering the stmt function, you first need to determine the currently read word symbol. By calling the lexical analyzer, the type encoding of the read word characters is returned, and an array is set to store the type encoding. Operation can realize the judgment of characters. If 111 is stored in the current array, indicating that the currently read character is an identifier, the loc function is called, and the character is judged after the call. If it is '=', the character is read, and then the expr function is called. After the call, it is judged whether it is ';'; if the current array is stored 17, it indicates that the currently read character is "if", and then it is judged whether it is followed by '(', and if so, then the bool_x function is called ( Because bool is a reserved word on my computer, it cannot be used for naming), and then judge the ')'. Then call the stmt function. After the call, the following characters are judged. If it is "else", the program advances and the stmt function is called. If the current array stores 20, indicating that the current character is "while", the left and right parentheses are also performed. Judge and call the bool_x function in it, and finally call the stmt function directly. This is the overall process of the stmt function call. If any of these conditions are not met, the corresponding error will be displayed in the corresponding place in the production output mode.

`Processing of output:`Because the parser has two output forms, which are output by production and output by derivation. According to the degree of difficulty, the former is obviously less difficult, and an output statement can be directly placed in the corresponding function. So the first choice in writing is to output by production. After confirming that there is no problem in calling each function and that the error can also work normally, add the output according to the derivation process to it. The implementation is to use a string array res as the final input array, and then define a global temporary array output to store the output information generated by each step of derivation (using the repalce function in string to replace the corresponding string), each Once a change occurs, it is recorded once in res. Finally, extra spaces are eliminated, and the string in res is output circularly. That is to say, the form of output by deduction can be achieved.
*** 
### Semantic analyzer and Intermediate code generator  
`Function:`Semantic analysis is a logical stage of the compilation process. The task of semantic analysis is to examine the structurally correct source program for the context-related nature and type review. Semantic analysis is to review the source program for semantic errors and collect type information for the code generation phase. For example, a job of semantic analysis is to perform a type review to check whether each operator has operands allowed by the language specification. When the language specification is not met, the compiler should report an error. If there is a compiler, it will report an error when the real number is used as the array index. Another example is that some programs stipulate that operands can be forced. When the binocular operation is applied to an integer and a real object, the compiler should convert the integer to a real type and should not consider it to be a source program error. Intermediate code is a code between the source language and the target code. The introduction of intermediate code can facilitate the generation of target code, and also facilitate subsequent optimization. It is also more convenient when porting.

`Implement:`The implementation is divided into two parts.
<br/>
&emsp;&emsp;(1)The first part is the calculation of arithmetic expressions, that is, input an arithmetic expression, perform the operation according to the correct operation rules, and output the correct result. This part can be expanded on the basis of a parser, a recursive descent parser. All functions in the parser are of type void and have no return value. To implement the calculation of arithmetic expressions, you need to change the type to a function that returns an int type. According to the table in the calculation process in the implementation problem, Parameter definition and function return value determination can be performed in the corresponding function part of the parser.

`Corresponding code grammar and description:`<br/>
e.g.<br/>
*Grammar Analyzer:* expr ⟶ term rest5 
<br/>
&emsp;&emsp;The expr function first calls the term function and then the rest5 function;

*Arithmetic expression:*{rest5.in = term.val}
<br/>
 &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;{expr.val = rest5.val; 
 <br/>
 &emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;print(expr.val)}
<br/>
 &emsp;&emsp;The specific calculation flow in the arithmetic expression is as follows: first you need to assign a value to rest5.in, call the term function to get its return value term.val, assign its value to rest5.in, and then call the rest5 function to get its return value. Assign it to rest5.val, where rest5.in is passed as a parameter in the rest5 function, and finally rest5.val is assigned to expr.val to complete the output of the expression value. There are operations for addition, subtraction, and multiplication.

 &emsp;&emsp;(2)The second part of the experiment is to output the three-address code of the assignment statement. Because it is an assignment statement, the function initially entered cannot be the same as the expr function in the arithmetic expression, but should be the same as the parser and entered by the stmts function, but The specific writing process is similar to the arithmetic expression, except that the type of the called function is string.





 ***Implementation ideas and algorithms and related grammars refer to the book 《Compilers》 2nd Edition***

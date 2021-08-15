# Clockwise-Cipher
A cipher that inputs a given string into a matrix corner-clockwise.

--HOW IT WORKS
The program will take in input a string and insert it corner-clockwise into a matrix. The matrix will then be read row-wise; this final result will the encrypted phrase.

--WHAT IS 'Corner-Clockwise'
Corner-Clockwise means that the characters are put clockwise ONLY in the corners of the matrix. When a corner is full, the character will be added to the next nearer clockwise location. The matrix has to be quadratic, here is an example: (Without spaces, although they can be used in the program)

String: Hello-Mark_!!;)

| H | o | r | e |   
| ! | ! | ; | - |  
| a |   | ) | k |  
| l | _ | M | l |  

Result: Hore!!;-a )kl_Ml

As you see there are 15 characters in the string, the matrix needs ceil(sqrt(size)) rows and colums, therefore 4 rows and colums. The characters are inserted corner-clockwise.

--HOW DO I INSERT THE CHARACTERS IN THE MATRIX
There are various ways in which you can make this work, I decided to find an iterative method so that it can be a bit more clear. The idea is to only take in consideration the 'outsides' of the matrix and 'level down' everytime we fill the part taken in consideration.
Every matrix (but the 1x1 and 2x2) has 1 or more submatrixes. (For example a 6x6 matrix has: 6x6, 4x4, 2x2  ;  a 3x3 matrix has: 3x3, 1x1). What I do is fill the corners of these submatrixes starting from the bigger one with a basic mathematical iteration. You can look at the function fill_matrix() and iterate_func() to see how it is done.

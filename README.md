This project about understanding multiprocessing.     
Program executed as follows:

**./pipex file1 cmd1 cmd2 ... cmdN file2**

where **cmd** are **shell command** with their parameters.

It behave the same as the shell command:

**$> < file1   cmd1  |   cmd2  |   ...   |   cmdN   > file2**

Program supports **<<** and **>>** when the first parameter is "hede_doc".

This:

**$> ./pipex here_doc LIMITER cmd cmd1 file**

behaves like this:

**$> cmd << LIMITER | cmd1 >> file**

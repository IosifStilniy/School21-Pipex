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

---

<img width="1188" alt="Screen Shot 2022-09-04 at 19 19 43" src="https://user-images.githubusercontent.com/89987795/188323239-51f6752c-867b-4037-9192-2b4c81e40bf7.png">

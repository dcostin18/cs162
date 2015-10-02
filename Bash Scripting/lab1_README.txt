Language: Bash

Objective: This lab was a series of bash scripting exercises. The goals for each exercise are briefly as follows:

fsmap.sh: Take two arguments: a command and a file. If the file is a regular file then it should run the command and pass the file as an argument. If the file is a directory then the command should be applied to all regular files in the subtree rooted at the directory.

list_contents.sh: Use fsmap.sh to report the number of lines and words for each file separately within the subtree of the file system rooted at a file list_contents.sh takes as an argument.

fs_additive_fold.sh: Take a command and a file as input. Recurse over the subtree that has the file as root.

disk_usage.sh: Write a script disk_usage.sh which takes a file as input and outputs the total number of kilobytes used by that file or directory using fs_additive_fold.sh. 

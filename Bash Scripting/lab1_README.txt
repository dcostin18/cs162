This lab was a series of bash scripting exercises. The goals for each exercise were stated as follows:

fsmap.sh: Write a bash script that takes two arguments: a command and a file. If the file is a regular file then it should run the command and pass the file as an argument. If the file is a directory then the command should be applied to all regular files in the subtree rooted at the directory.

list_contents.sh: Write a script list_contents.sh that uses fsmap.sh to report the number of lines and words for each file separately within the subtree of the file system rooted at a file list_contents.sh takes as an argument. The output should have one line per file with the file name, the word count, and the line count for that file.

fs_additive_fold.sh: Write a script fs_additive_fold.sh that takes a command and a file as input. It shall recurse over the subtree that has the file as root (which will be a single file if the file is not a directory or link). The command is assumed to take a single file as input and output a number. For every regular file in the subtree rooted at the input file, get the numbers they output and add them.

disk_usage.sh: Write a script disk_usage.sh which takes a file as input and outputs the total number of kilobytes used by that file or directory using fs_additive_fold.sh. Compare its output to what you get with du (and the correct flags: read the man page). Use time to profile their execution speeds on a system of directories (say your home directory on the lab machine) and put the outputs of time into your lab writeup README file included in your submission.


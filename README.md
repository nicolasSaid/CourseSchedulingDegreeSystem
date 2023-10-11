<h3>Note: group work was done via liveshare</h3>

<h1>Notice before running: When running a downloaded test file, the input was full of errors. By copying and pasting a text file into one present within the directory, it began working again - not sure why this occurs, I think it has to do with txt files</h1>

<h2>How to run</h2>
<ol>
    <li> run <i>make</i> to generate three executables:
    <ul>
        <li><b>pr_check</b>, which runs the prerequisite checker with one parameter (prereq.txt)
        <li><b>sch_check</b>, which runs the schedule checker with two parameters (prereq.txt, sched.txt)
        <li><b>waitlist</b>, which runs the waitlist command checker with four parameters (semester, prereq.txt, sched.txt, enroll.txt)
    </ul>
    <li> run <i>clean</i> to remove object and executable files
</ol>

<h2>File List</h2>
<ul>
    <li> <b>pr_check.cpp</b> - implementation of prerequisite checker
    <li> <b>pr_main.cpp</b> - file containing main function that calls prerequisite checker
    <li> <b>sch_check.cpp</b> - implementation of schedule checker
    <li> <b>sch_main.cpp</b> - file containing main function that calls schedule checker
    <li> <b>waitlist.cpp</b> - file containing main function and implementation that calls the waitlist function
    <li> <b>priorityQueue.h</b> - file containing outline for our maxheap implementation
    <li> <b>priorityQueue.cpp</b> - file containing the implemetation of an array-based maxheap for student objects
    <li> <b>student.h</b> - class to contain a student's bnumber and priority in the waitlist
    <li> <b>Node.h</b> - file a node used to represent the possible options to fulfill a prerequisite requirement
    <li> <b>Text Files</b> - files used to test the programs provided on brightspace
</ul>

<h1>Partners</h1>
<ul>
    <li> Yin Hei (Jason) Chan
    <li> Nicolas Said
    <li> Oluwatomisin Adetunji
</ul>

#Chat++

###Introduction
Chat++ is a simple C++ program we wrote for our Class 12th (High School) Computer Science Project.

It has a simple and easy to understand code and as its open source, you can customize it as per your requirement. Its components can be dismantled with ease.

For example,
- To Hide Timestamps : Simply remove the insertTimestamp() function.
- To Disable Chat History : Remove the chathistory() function.

We made Chat++ so that we could chat during our class to pass notes, discuss answers and obviously for fun.
Sadly we couldn't get it to work on our lab's homegroup sharing until the last month of school.
(Took time to figure out how to bypass the firewall rules.)

###Local Area Concept
####(Small Scale)
The exe is placed on a server accessible by other computers over the network. On running the exe file, the sender’s computer creates a [chat] file which is read by the receiver’s computer. The messages are simultaneously also placed in a [chat history] file. Timestamps can also be recorded.

###Internet Concept
####(Large Scale)
In theory, every computer runs a chat client locally in a shared folder. The files are transmitted using a file sharing service, like DropBox or BitTorrent Sync.
We used BTS for our testing.

###Media
[Watch the demonstration on YouTube!](https://www.youtube.com/watch?v=kZRTRSy9o4k)

![Concept Image](http://31.media.tumblr.com/c050871653c48f1ba57416c69c513094/tumblr_inline_nkw5kxydld1sgdhf8.png)


###Collaborators
- Abhishek Sarin
- Priyanshu Mukhopadhyay
- Puranjay Rajvanshi 
- Raghav Bhasin

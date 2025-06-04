This project focuses on detecting mail in a mailbox via IR-technology and through various methods allowing a user to know if there is mail or not at any time. 

It is a work in progress and the branches that are being worked on are vastly different in their application.
The "Boxxy branch" is based on a system of 24+ mailboxes using multiplexers to deliver the mail information to another ESP32 via serial.

The "Esp-now" branch is focused on a single mail box aimed at home owners in rural areas where access to the mailbox is not possible without leaving the house. 
This branch uses the same IR-technology but uses the "esp-now" protocol to deliver mailbox status inside the house. 
